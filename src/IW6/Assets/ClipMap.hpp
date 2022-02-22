#pragma once

namespace ZoneTool
{
	namespace IW6
	{
		class IClipMap
		{
		public:
			static void dump(clipMap_t* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);
		};
	}
}