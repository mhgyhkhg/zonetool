#pragma once

namespace ZoneTool::S1
{
	class IAddonMapEnts
	{
	public:
		static void dump(AddonMapEnts* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);
	};
}
