#include "stdafx.hpp"
#include "../Include.hpp"

#include "AddonMapEnts.hpp"

namespace ZoneTool::IW5
{
	namespace IW6Converter
	{
		IW6::AddonMapEnts* GenerateIW6MapEnts(AddonMapEnts* asset, allocator& mem)
		{
			// allocate IW6 MapEnts structure
			const auto iw6_asset = mem.allocate<IW6::AddonMapEnts>();

			iw6_asset->name = asset->name;

			if (ZoneTool::currentlinkermode == ZoneTool::linker_mode::iw5)
			{
				const auto str = mapents::converter::iw5::convert_mapents_ids(
					std::string{ asset->entityString, static_cast<size_t>(asset->numEntityChars) });
				iw6_asset->entityString = const_cast<char*>(mem.duplicate_string(str));
				iw6_asset->numEntityChars = static_cast<int>(str.size());
			}
			else
			{
				iw6_asset->entityString = asset->entityString;
				iw6_asset->numEntityChars = asset->numEntityChars;
			}

			iw6_asset->trigger.count = asset->trigger.count;
			iw6_asset->trigger.models = reinterpret_cast<IW6::TriggerModel*>(asset->trigger.models);
			iw6_asset->trigger.hullCount = asset->trigger.hullCount;
			iw6_asset->trigger.hulls = reinterpret_cast<IW6::TriggerHull*>(asset->trigger.hulls);
			iw6_asset->trigger.slabCount = asset->trigger.slabCount;
			iw6_asset->trigger.slabs = reinterpret_cast<IW6::TriggerSlab*>(asset->trigger.slabs);

			return iw6_asset;
		}

		IW6::AddonMapEnts* convert(AddonMapEnts* asset, allocator& allocator)
		{
			// generate IW6 mapents
			return GenerateIW6MapEnts(asset, allocator);
		}
	}
}