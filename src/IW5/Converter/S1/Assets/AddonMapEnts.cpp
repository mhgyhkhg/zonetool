#include "stdafx.hpp"
#include "../Include.hpp"

#include "AddonMapEnts.hpp"

namespace ZoneTool::IW5
{
	namespace S1Converter
	{
		S1::AddonMapEnts* GenerateS1MapEnts(AddonMapEnts* asset, allocator& mem)
		{
			// allocate S1 MapEnts structure
			const auto s1_asset = mem.allocate<S1::AddonMapEnts>();

			s1_asset->name = asset->name;

			if (ZoneTool::currentlinkermode == ZoneTool::linker_mode::iw5)
			{
				const auto str = mapents::converter::iw5::convert_mapents_ids(
					std::string{ asset->entityString, static_cast<size_t>(asset->numEntityChars) });
				s1_asset->entityString = const_cast<char*>(mem.duplicate_string(str));
				s1_asset->numEntityChars = static_cast<int>(str.size());
			}
			else
			{
				s1_asset->entityString = asset->entityString;
				s1_asset->numEntityChars = asset->numEntityChars;
			}

			s1_asset->trigger.count = asset->trigger.count;
			s1_asset->trigger.models = reinterpret_cast<S1::TriggerModel*>(asset->trigger.models);
			s1_asset->trigger.hullCount = asset->trigger.hullCount;
			s1_asset->trigger.hulls = reinterpret_cast<S1::TriggerHull*>(asset->trigger.hulls);
			s1_asset->trigger.slabCount = asset->trigger.slabCount;
			s1_asset->trigger.slabs = reinterpret_cast<S1::TriggerSlab*>(asset->trigger.slabs);

			return s1_asset;
		}

		S1::AddonMapEnts* convert(AddonMapEnts* asset, allocator& allocator)
		{
			// generate s1 mapents
			return GenerateS1MapEnts(asset, allocator);
		}
	}
}
