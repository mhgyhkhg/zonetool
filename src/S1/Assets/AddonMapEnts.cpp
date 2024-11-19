#include "stdafx.hpp"

#include "AddonMapEnts.hpp"

#include <H1\Assets\AddonMapEnts.hpp>

namespace ZoneTool::S1
{
	void IAddonMapEnts::dump(AddonMapEnts* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString)
	{
		H1::IAddonMapEnts::dump_entityStrings(asset->name, asset->entityString, asset->numEntityChars);
		H1::IAddonMapEnts::dump_triggers(asset->name, reinterpret_cast<H1::MapTriggers*>(&asset->trigger));
	}
}
