// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		void IComWorld::dump(ComWorld* asset)
		{
			const auto path = asset->name + ".comworld"s;

			AssetDumper write;
			if (!write.open(path))
			{
				return;
			}

			write.dump_single(asset);
			write.dump_string(asset->name);

			write.dump_array(asset->primaryLights, asset->primaryLightCount);
			for (unsigned int i = 0; i < asset->primaryLightCount; i++)
			{
				write.dump_string(asset->primaryLights[i].defName);
			}
			write.dump_array(asset->primaryLightEnvs, asset->primaryLightEnvCount);

			write.close();
		}
	}
}