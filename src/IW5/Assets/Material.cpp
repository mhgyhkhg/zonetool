#include "stdafx.hpp"
//#include "IW6/Assets/Material.hpp"

#include "Json.hpp"
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace
{
	// need to figure out what cltrans and nfwpf mean. // could cltrans be _sat?
	// need to switch mc -> m?
	std::unordered_map<std::string, std::string> mapped_techsets =
	{
//	    IW5,										IW6
		{"wc_l_sm_a0c0",							"wc_l_sm_a0c0l0_nfwpf"},
		{"wc_l_sm_r0c0",							"wc_l_sm_r0c0l0_nfwpf"},
		{"wc_l_sm_r0c0n0",							"wc_l_sm_r0c0n0l0_nfwpf"},
		{"wc_l_sm_r0c0n0s0",						"wc_l_sm_r0c0n0s0l0_nfwpf"},
		{"wc_l_sm_r0c0n0s0p0",						"wc_l_sm_r0c0n0s0l0p0_nfwpf"},
		{"wc_l_sm_r0c0q0n0s0",						"wc_l_sm_r0c0q0n0s0l0_nfwpf"},
		{"wc_l_sm_r0c0q0n0s0p0",					"wc_l_sm_r0c0q0n0s0l0p0_nfwpf"},
		{"mc_l_sm_r0c0d0n0s0",						"mc_l_sm_r0c0d0n0s0l0_nfwpf"},
		{"wc_l_sm_r0c0d0n0s0p0",					"wc_l_sm_r0c0d0n0s0l0p0_nfwpf"},
		{"wc_l_sm_r0c0s0",							"wc_l_sm_r0c0s0l0_nfwpf"},
		{"mc_l_sm_r0c0s0_custom_grenade",			"wc_l_sm_r0c0s0"}, // couldn't find
		{"wc_l_sm_t0c0",							"wc_l_sm_t0c0l0_nfwpf"},
		{"wc_l_sm_t0c0n0",							"wc_l_sm_t0c0n0l0_nfwpf"},
		{"wc_l_sm_t0c0n0s0",						"wc_l_sm_t0c0n0s0l0_nfwpf"},
		{"wc_l_sm_t0c0p0",							"wc_l_sm_t0c0l0_nfwpf"},
		{"wc_l_sm_b0c0",							"wc_l_sm_ndw_b0c0l0_nfwpf"},
		{"wc_l_sm_b0c0n0",							"wc_l_sm_ndw_b0c0n0l0_nfwpf"},
		{"wc_l_sm_b0c0n0s0",						"wc_l_sm_ndw_b0c0n0s0l0_nfwpf"},
		{"wc_l_sm_b0c0s0p0",						"wc_l_sm_ndw_b0c0s0l0p0_nfwpf"},
		{"wc_l_sm_b0c0n0s0p0",						"wc_l_sm_ndw_b0c0n0s0l0p0_nfwpf"},
		{"wc_l_sm_b0c0n0p0",						"wc_l_sm_ndw_b0c0n0l0p0_nfwpf"},
		{"wc_l_sm_b0c0s0",							"wc_l_sm_ndw_b0c0s0l0_nfwpf"},
		{"wc_l_sm_b0c0q0n0s0",						"wc_l_sm_ndw_b0c0q0n0s0l0_nfwpf"},
		{"wc_l_sm_ua_b0c0n0s0p0_nocast",			"wc_l_sm_ndw_ua_b0c0s0l0p0_cltrans"}, // coudln't find nocast
		{"wc_l_sm_b0c0n0s0_custom_growing_ice_cracks", "wc_l_sm_ndw_b0c0n0s0l0_custom_growing_ice_cracks_nfwpf"},
		{"wc_l_sm_b0c0n0s0_custom_growing_ice_cracks_sat", "wc_l_sm_ndw_b0c0n0s0l0_custom_growing_ice_cracks_cltrans"},
		{"wc_unlit_multiply_lin",					"wc_unlit_multiply_lin_ndw_bl_nfwpf"},
		{"wc_unlit_replace_lin",					"wc_unlit_replace_lin_bl_nfwpf"},
		{"wc_sky",									"wc_sky_bl"},
		{"wc_shadowcaster",							"wc_shadowcaster"},
		{"wc_water",								"2d"}, // no techset found
		{"wc_tools",								"2d"}, // no techset found

		{"mc_l_sm_r0c0",							"mc_l_sm_r0c0l0_nfwpf"},
		{"mc_l_sm_r0c0_sat",						"mc_l_sm_r0c0l0_nfwpf"}, // couldn't find cltrans
		{"mc_l_sm_r0c0s0",							"mc_l_sm_r0c0s0l0_nfwpf"},
		{"mc_l_sm_r0c0n0",							"mc_l_sm_r0c0n0l0_nfwpf"},
		{"mc_l_sm_r0c0n0s0",						"mc_l_sm_r0c0n0s0l0_nfwpf"},
		{"mc_l_sm_r0c0n0s0p0",						"mc_l_sm_r0c0n0s0l0p0_nfwpf"},
		{"mc_l_sm_r0c0n0s0p0_sat",					"mc_l_sm_r0c0n0s0l0p0_nfwpf"}, // couldn't find cltrans
		{"mc_l_sm_r0c0q0n0s0",						"mc_l_sm_r0c0q0n0s0l0_nfwpf"},
		{"mc_l_sm_r0c0q0n0s0p0",					"mc_l_sm_r0c0q0n0s0l0p0_nfwpf"},
		{"mc_l_sm_t0c0",							"mc_l_sm_t0c0l0_nfwpf"},
		{"mc_l_sm_t0c0_nocast",						"mc_l_sm_t0c0l0_nocast_nfwpf"},
		{"mc_l_sm_t0c0n0",							"mc_l_sm_t0c0n0l0_nfwpf"},
		{"mc_l_sm_t0c0n0s0",						"mc_l_sm_t0c0n0s0l0_nfwpf"},
		{"mc_l_sm_t0c0q0n0s0p0",					"mc_l_sm_t0c0q0n0s0l0_nfwpf"}, // couldn't find p0
		{"mc_l_sm_b0c0",							"mc_l_sm_ndw_b0c0l0_nfwpf"},
		{"mc_l_sm_b0c0_sat",						"mc_l_sm_ndw_b0c0l0_cltrans"},
		{"mc_l_sm_b0c0_nocast",						"mc_l_sm_ndw_b0c0l0_nfwpf"}, // couldn't find nocast
		{"mc_l_sm_b0c0s0",							"mc_l_sm_ndw_b0c0s0l0_nfwpf"},
		{"mc_l_sm_b0c0n0",							"mc_l_sm_ndw_b0c0n0l0_nfwpf"},
		{"mc_l_sm_b0c0n0_sat",						"mc_l_sm_ndw_b0c0n0l0_cltrans"},
		{"mc_l_sm_b0c0n0s0",						"mc_l_sm_ndw_b0c0n0s0l0_nfwpf"},
		{"mc_l_sm_b0c0n0s0_sat",					"mc_l_sm_ndw_b0c0n0s0l0_cltrans"},
		{"mc_l_sm_b0c0n0p0_sat",					"mc_l_sm_ndw_b0c0n0s0l0_cltrans"}, // couldn't find p0
		{"mc_l_sm_b0c0n0s0p0",						"mc_l_sm_ndw_b0c0n0s0l0p0_nfwpf"},
		{"mc_l_sm_b0c0n0s0p0_sat",					"mc_l_sm_ndw_b0c0n0s0l0p0_cltrans"},
		{"mc_l_sm_b0c0p0",							"mc_l_sm_ndw_b0c0l0_nfwpf"}, // couldn't find p0
		{"mc_l_sm_b0c0q0n0s0_sat",					"mc_l_sm_ndw_b0c0q0n0s0l0_nfwpf"},
		{"mc_l_sm_b0c0n0s0_custom_growing_ice_cracks", "mc_l_sm_ndw_b0c0n0s0l0_custom_growing_ice_cracks_nfwpf"},
		{"mc_l_sm_b0c0n0s0_custom_growing_ice_cracks_sat", "mc_l_sm_ndw_b0c0n0s0l0_custom_growing_ice_cracks_cltrans"},
		{"mc_l_sm_flag_t0c0n0s0",					"mc_l_sm_flag_t0c0n0s0l0_nfwpf"},
		{"mc_l_r0c0n0s0",							"mc_l_r0c0n0s0l0_nfwpf"},
		{"mc_l_r0c0n0s0_nocast",					"mc_l_r0c0n0s0l0_nocast_nfwpf"},
		{"mc_l_t0c0n0s0",							"mc_l_t0c0n0s0l0_nfwpf"},
		{"mc_unlit_add_lin",						"mc_unlit_add_lin_ndw_bl_nfwpf"},
		{"mc_unlit_blend_lin",						"mc_unlit_blend_lin_ndw_bl_abl_cltrans"}, // could be wrong
		{"mc_unlit_replace_lin",					"mc_unlit_replace_lin_bl_nfwpf"},
		{"mc_unlit_replace_lin_nocast",				"mc_unlit_replace_lin_nocast_bl_nfwpf"},
		{"mc_ambient_t0c0",							"mc_ambient_t0c0l0_nfwpf"},
		{"mc_ambient_t0c0_nocast",					"mc_ambient_t0c0l0_nocast_nfwpf"},
		{"mc_shadowcaster_atest",					"mc_shadowcaster_atest"},

		{"mc_effect_falloff_add_nofog",				"mc_effect_falloff_add_nofog_ndw_flow_nohdrcolor_blm_blmod"}, // could be wrong
		{"mc_effect_falloff_add_lin_nofog",			"mc_effect_falloff_add_lin_nofog_ndw_bl_blmod"},
		{"mc_effect_zfeather_falloff_add_lin_nofog", "mc_effect_zfeather_falloff_add_lin_nofog_ndw_bl_blmod"},
		{"mc_effect_zfeather_falloff_add_lin_nofog_eyeoffset", "mc_effect_zfeather_falloff_add_lin_nofog_eyeoffset_ndw_bl_blmod"},

		{"2d",										"2d"},

		{"distortion_scale",						"distortion_scale"},

		{"effect_add_nofog",						"effect_add_nofog_ndw_bl_blmod"},
		{"effect_blend",							"effect_blend_lin_ndw_bl_abl"}, // could be wrong (lin)
		{"effect_blend_nofog",						"effect_blend_lin_nofog_ndw_bl_abl"}, // could be wrong (lin)
		{"effect_replace_lin",						"effect_replace_lin_ndw_bl_abl"}, // could be wrong
		{"effect_zfeather_add",						"effect_zfeather_add_lin_ndw_bl_blmod"}, // could be wrong (lin)
		{"effect_zfeather_add_nofog",				"effect_zfeather_add_lin_nofog_ndw_bl_blmod"}, // could be wrong (lin)
		{"effect_zfeather_blend",					"effect_zfeather_blend_ndw_bl_abl"}, // could be wrong
		{"effect_zfeather_blend_nofog",				"effect_zfeather_blend_ndw_bl_abl"}, // could be wrong + couldn't find nofog
		{"effect_zfeather_falloff_add_nofog_eyeoffset", "effect_zfeather_falloff_add_lin_nofog_eyeoffset_ndw_bl_blmod"},
		{"effect_zfeather_falloff_blend",			"effect_zfeather_falloff_blend_lin_ndw_bl_abl"}, // could be wrong (lin)
		{"effect_zfeather_add_nofog_eyeoffset",		"effect_zfeather_add_lin_nofog_eyeoffset_ndw_bl_blmod"},

		{"particle_cloud",							"particle_cloud_replace_bl_abl_lin"}, // could be wrong
		{"particle_cloud_add",						"particle_cloud_add_bl_blmod_lin"},
		{"particle_cloud_outdoor_add",				"particle_cloud_outdoor_add_bl_blmod_lin"},
		{"particle_cloud_sparkf_add",				"particle_cloud_sparkf_add_bl_blmod_lin"},
		{"particle_cloud_spark_add",				"particle_cloud_spark_add_bl_blmod_lin"},

		{"tools_b0c0",								"tools_b0c0"},
	};

	std::string get_iw6_techset(std::string name, std::string matname)
	{
		if (mapped_techsets.find(name) == mapped_techsets.end())
		{
			ZONETOOL_ERROR("Could not find mapped IW6 techset for IW5 techset \"%s\" (material: %s)", name.data(), matname.data());
			return "2d";
		}
		return mapped_techsets[name];
	}

#define MATERIAL_DUMP_STRING(entry) \
	matdata[#entry] = std::string(asset->entry);

#define MATERIAL_DUMP_INT(entry) \
	matdata[#entry] = asset->entry;

#define MATERIAL_DUMP_CONST_ARRAY(entry,size) \
	ordered_json carr##entry; \
	for (int i = 0; i < size; i++) \
	{ \
		ordered_json cent##entry; \
		std::string name = asset->constantTable[i].name; \
		name.resize(12); \
		cent##entry["name"] = name.data(); \
		cent##entry["nameHash"] = asset->entry[i].nameHash; \
		nlohmann::json centliteral##entry; \
		centliteral##entry[0] = asset->entry[i].literal[0]; \
		centliteral##entry[1] = asset->entry[i].literal[1]; \
		centliteral##entry[2] = asset->entry[i].literal[2]; \
		centliteral##entry[3] = asset->entry[i].literal[3]; \
		cent##entry["literal"] = centliteral##entry; \
		carr##entry[i] = cent##entry; \
	} \
	matdata[#entry] = carr##entry;
}

namespace ZoneTool
{
	namespace IW5
	{
		void IMaterial::dump(Material* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::Material) == 936);

			std::string asset_name = asset->name;

			// clean name
			if (asset_name.starts_with('*'))
			{
				asset_name.erase(0, 1);
				asset_name.insert(0, "_");
			}

			auto path = "materials\\"s + asset_name;

			auto file = FileSystem::FileOpen(path, "wb");
			if (!file)
			{
				return;
			}

			nlohmann::ordered_json matdata;

			MATERIAL_DUMP_STRING(name);

			if (asset->techniqueSet)
			{
				matdata["techniqueSet->name"] = get_iw6_techset(asset->techniqueSet->name, asset->name);
			}

			MATERIAL_DUMP_INT(gameFlags);
			MATERIAL_DUMP_INT(sortKey); // needs to be recalculated
			matdata["renderFlags"] = 0; /// idk

			MATERIAL_DUMP_INT(surfaceTypeBits);
			matdata["hashIndex"] = 0; // idk

			MATERIAL_DUMP_INT(stateFlags);
			MATERIAL_DUMP_INT(cameraRegion);
			matdata["materialType"] = 0; // idk
			matdata["assetFlags"] = 0; // idk

			MATERIAL_DUMP_CONST_ARRAY(constantTable, asset->constantCount);

			nlohmann::ordered_json material_images;
			for (int i = 0; i < asset->numMaps; i++)
			{
				nlohmann::ordered_json image;

				// watermap
				if (asset->maps[i].semantic == 11)
				{
					image["waterinfo"] = nullptr;
				}
				else
				{
					if (asset->maps[i].image->name)
					{
						image["image"] = asset->maps[i].image->name;
					}
					else
					{
						image["image"] = "";
					}
				}

				image["semantic"] = asset->maps[i].semantic;
				image["samplerState"] = asset->maps[i].sampleState; // may be wrong from iw5->iw6
				image["lastCharacter"] = asset->maps[i].secondLastCharacter;
				image["firstCharacter"] = asset->maps[i].firstCharacter;
				image["typeHash"] = asset->maps[i].typeHash;

				// add image data to material
				material_images[i] = image;
			}
			matdata["textureTable"] = material_images;

			auto assetData = matdata.dump(4);

			// write data to disk
			fwrite(&assetData[0], assetData.size(), 1, file);
			FileSystem::FileClose(file);
		}
	}
}