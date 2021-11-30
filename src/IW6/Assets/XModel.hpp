// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#pragma once

namespace ZoneTool
{
	namespace IW6
	{
		class IXModel
		{
		public:
			static void dump(XModel* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString);
		};
	}
}