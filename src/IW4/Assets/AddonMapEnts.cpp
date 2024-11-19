#include "stdafx.hpp"
#include "IW5/Assets/AddonMapEnts.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IAddonMapEnts::dump(AddonMapEnts* asset)
		{
			allocator allocator;
			auto* new_asset = allocator.allocate<IW5::AddonMapEnts>();
			new_asset->name = asset->name;
			new_asset->entityString = asset->entityString;
			new_asset->numEntityChars = asset->numEntityChars;
			memcpy(&new_asset->trigger, &asset->trigger, sizeof(MapTriggers)); static_assert(sizeof(IW4::MapTriggers) == sizeof(IW5::MapTriggers));

			IW5::IAddonMapEnts::dump(new_asset);
		}
	}
}
