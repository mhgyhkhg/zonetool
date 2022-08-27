#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		void IXSurface::dump(XModelSurfs* asset)
		{
			AssetDumper dump;
			if (!dump.open("XSurface\\"s + asset->name + ".xse"))
			{
				return;
			}

			dump.dump_single(asset);
			dump.dump_string(asset->name);

			dump.dump_array(asset->surfs, asset->numsurfs);

			for (auto i = 0; i < asset->numsurfs; i++)
			{
				if ((asset->surfs[i].flags & 8) != 0)
				{
					dump.dump_array(asset->surfs[i].verts0.packedMotionVerts0, asset->surfs[i].vertCount);
				}
				else
				{
					dump.dump_array(asset->surfs[i].verts0.packedVerts0, asset->surfs[i].vertCount);
				}

				dump.dump_array(asset->surfs[i].triIndices, asset->surfs[i].triCount);

				dump.dump_array(asset->surfs[i].rigidVertLists, asset->surfs[i].rigidVertListCount);
				for (auto vert = 0; vert < asset->surfs[i].rigidVertListCount; vert++)
				{
					if (asset->surfs[i].rigidVertLists)
					{
						if (asset->surfs[i].rigidVertLists[vert].collisionTree)
						{
							dump.dump_single(asset->surfs[i].rigidVertLists[vert].collisionTree);

							if (asset->surfs[i].rigidVertLists[vert].collisionTree->leafs)
							{
								dump.dump_array(asset->surfs[i].rigidVertLists[vert].collisionTree->leafs,
									asset->surfs[i].rigidVertLists[vert].collisionTree->leafCount);
							}
							if (asset->surfs[i].rigidVertLists[vert].collisionTree->nodes)
							{
								dump.dump_array(asset->surfs[i].rigidVertLists[vert].collisionTree->nodes,
									asset->surfs[i].rigidVertLists[vert].collisionTree->nodeCount);
							}
						}
					}
				}

				dump.dump_raw(asset->surfs[i].blendVerts, 2 * (asset->surfs[i].blendVertCounts[0]
					+ 3 * asset->surfs[i].blendVertCounts[1]
					+ 5 * asset->surfs[i].blendVertCounts[2]
					+ 7 * asset->surfs[i].blendVertCounts[3]
					+ 9 * asset->surfs[i].blendVertCounts[4]
					+ 11 * asset->surfs[i].blendVertCounts[5]
					+ 13 * asset->surfs[i].blendVertCounts[6]
					+ 15 * asset->surfs[i].blendVertCounts[7]));
				dump.dump_raw(asset->surfs[i].blendVertsTable, 32 * asset->surfs[i].vertCount);

				dump.dump_raw(asset->surfs[i].lmapUnwrap, 8 * asset->surfs[i].vertCount);

				dump.dump_raw(asset->surfs[i].tensionData, 4 * (asset->surfs[i].blendVertCounts[0]
					+ asset->surfs[i].blendVertCounts[1]
					+ asset->surfs[i].blendVertCounts[2]
					+ asset->surfs[i].blendVertCounts[3]
					+ asset->surfs[i].blendVertCounts[4]
					+ asset->surfs[i].blendVertCounts[5]
					+ asset->surfs[i].blendVertCounts[6]
					+ asset->surfs[i].blendVertCounts[7]));
				dump.dump_raw(asset->surfs[i].tensionAccumTable, 32 * asset->surfs[i].vertCount);
			}

			dump.close();
		}
	}
}