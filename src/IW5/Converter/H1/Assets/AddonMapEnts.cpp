#include "stdafx.hpp"
#include "../Include.hpp"

#include "AddonMapEnts.hpp"

namespace ZoneTool::IW5
{
	namespace H1Converter
	{
		H1::AddonMapEnts* GenerateH1MapEnts(AddonMapEnts* asset, allocator& mem)
		{
			// allocate H1 MapEnts structure
			const auto h1_asset = mem.allocate<H1::AddonMapEnts>();

			h1_asset->name = asset->name;

			if (ZoneTool::currentlinkermode == ZoneTool::linker_mode::iw5)
			{
				const auto str = mapents::converter::iw5::convert_mapents_ids(
					std::string{ asset->entityString, static_cast<size_t>(asset->numEntityChars) });
				h1_asset->entityString = const_cast<char*>(mem.duplicate_string(str));
				h1_asset->numEntityChars = static_cast<int>(str.size());
			}
			else
			{
				h1_asset->entityString = asset->entityString;
				h1_asset->numEntityChars = asset->numEntityChars;
			}

			h1_asset->trigger.count = asset->trigger.count;
			h1_asset->trigger.models = reinterpret_cast<H1::TriggerModel*>(asset->trigger.models);
			h1_asset->trigger.hullCount = asset->trigger.hullCount;
			h1_asset->trigger.hulls = reinterpret_cast<H1::TriggerHull*>(asset->trigger.hulls);
			h1_asset->trigger.slabCount = asset->trigger.slabCount;
			h1_asset->trigger.slabs = reinterpret_cast<H1::TriggerSlab*>(asset->trigger.slabs);

			return h1_asset;
		}

		H1::AddonMapEnts* convert(AddonMapEnts* asset, allocator& allocator)
		{
			// generate h1 mapents
			return GenerateH1MapEnts(asset, allocator);
		}
	}
}