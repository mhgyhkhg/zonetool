#include "stdafx.hpp"

#include "IW5/Assets/PathData.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void IGameWorldSp::dump(GameWorldSp* asset)
		{
			allocator allocator;

			auto* mp_asset = allocator.allocate<GameWorldMp>();
			memset(mp_asset, 0, sizeof GameWorldMp);

			mp_asset->name = asset->name;
			mp_asset->g_glassData = asset->g_glassData;

			IGameWorldMp::dump(mp_asset);

			auto* path_asset = allocator.allocate<IW5::PathData>();

			path_asset->name = asset->name;
			std::memcpy(&path_asset->nodeCount, &asset->path.nodeCount, sizeof(PathData));

			IW5::IPathData::dump(path_asset);
		}
	}
}
