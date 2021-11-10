// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

#include "Json.hpp"
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

std::uint64_t depthStencilStateBits[11] =
{
	9938018369538,
	246300270658114,
	246300270690882,
	4418985394178,
	2211374301763,
	9938018369539,
	246300270658115,
	246300270690883,
	281474443903811,
	281474443903811,
	281474440757250
}; // idk

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

#define MATERIAL_DUMP_STATE_MAP(entry,size) \
	ordered_json carr##entry; \
	for (int i = 0; i < size; i++) \
	{ \
		ordered_json cent##entry; \
		cent##entry["loadBits"][0] = asset->entry[i].loadBits[0]; \
		cent##entry["loadBits"][1] = asset->entry[i].loadBits[1]; \
		cent##entry["loadBits"][2] = 0; \
		for (int j = 0; j < 11; j++) \
		{ \
			cent##entry["depthStencilStateBits"][j] = depthStencilStateBits[j]; \
		} \
		cent##entry["blendState"][0] = 0; \
		cent##entry["blendState"][1] = 0; \
		cent##entry["rasterizerState"] = 0; \
		carr##entry[i] = cent##entry; \
	} \
	matdata[#entry] = carr##entry;

namespace ZoneTool
{
	namespace IW3
	{
		void IMaterial::dump_statebits(Material* mat)
		{
			if (mat && mat->techniqueSet)
			{
				//ITechset::dump_statebits(va("iw3/%s", mat->techniqueSet->name), mat->stateBitsEntry);
			}
		}

		void IMaterial::dump(Material* asset, ZoneMemory* mem)
		{
			if (asset)
			{
				dump_statebits(asset);

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
					matdata["techniqueSet->name"] = va("iw3/%s", asset->techniqueSet->name);
				}

				MATERIAL_DUMP_INT(gameFlags);
				MATERIAL_DUMP_INT(sortKey); // needs to be recalculated
				matdata["renderFlags"] = 0;

				MATERIAL_DUMP_INT(surfaceTypeBits);
				matdata["hashIndex"] = 0;

				MATERIAL_DUMP_INT(stateFlags);
				MATERIAL_DUMP_INT(cameraRegion);
				matdata["materialType"] = 0;
				matdata["assetFlags"] = 0;

				if (asset->constantTable->name == "envMapParms"s)
				{
					IW3::vec4_t copy;
					memcpy(copy, asset->constantTable->literal, sizeof(float) * 4);
					asset->constantTable->literal[0] *= 0.0875f;
					asset->constantTable->literal[1] *= 0.165f;
					asset->constantTable->literal[2] *= 1.4f;
					asset->constantTable->literal[3] *= 3.2f;
					MATERIAL_DUMP_CONST_ARRAY(constantTable, asset->constantCount);
					memmove(asset->constantTable->literal, copy, sizeof(float) * 4);
				}
				else
				{
					MATERIAL_DUMP_CONST_ARRAY(constantTable, asset->constantCount);
				}

				MATERIAL_DUMP_STATE_MAP(stateMap, asset->stateBitsCount);

				nlohmann::json material_images;
				for (int i = 0; i < asset->numMaps; i++)
				{
					nlohmann::json image;

					// watermap
					if (asset->maps[i].semantic == 11)
					{
						water_t* waterData = reinterpret_cast<water_t*>(asset->maps[i].image);

						image["image"] = waterData->image->name;

						nlohmann::json waterdata;
						waterdata["floatTime"] = waterData->writable.floatTime;
						//waterdata["codeConstant"][0] = waterData->codeConstant[0];
						//waterdata["codeConstant"][1] = waterData->codeConstant[1];
						//waterdata["codeConstant"][2] = waterData->codeConstant[2];
						//waterdata["codeConstant"][3] = waterData->codeConstant[3];
						waterdata["M"] = waterData->M;
						waterdata["N"] = waterData->N;
						waterdata["Lx"] = waterData->Lx;
						waterdata["Lz"] = waterData->Lz;
						waterdata["gravity"] = waterData->gravity;
						waterdata["windvel"] = waterData->windvel;
						waterdata["winddir"][0] = waterData->winddir[0];
						waterdata["winddir"][1] = waterData->winddir[1];
						waterdata["amplitude"] = waterData->amplitude;

						nlohmann::json waterComplexData;
						nlohmann::json wTerm;

						for (int i = 0; i < waterData->M * waterData->N; i++)
						{
							nlohmann::json complexdata;
							nlohmann::json curWTerm;

							complexdata["real"] = waterData->H0[i].real;
							complexdata["imag"] = waterData->H0[i].imag;

							curWTerm[i] = waterData->wTerm[i];

							waterComplexData[i] = complexdata;
						}

						waterdata["complex"] = waterComplexData;
						waterdata["wTerm"] = wTerm;

						image["waterinfo"] = waterdata;
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
					image["samplerState"] = asset->maps[i].sampleState;
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
}