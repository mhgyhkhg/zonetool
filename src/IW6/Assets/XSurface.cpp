#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		void IXSurface::dump(XModelSurfs* asset)
		{
			assert(sizeof(XModelSurfs) == 56);
			assert(sizeof(XSurface) == 232);

			AssetDumper dump;
			dump.open("XSurface\\"s + asset->name + ".xse");

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

				dump.dump_array(asset->surfs[i].blendVerts, (asset->surfs[i].blendVertCounts[0]
					+ 7 * asset->surfs[i].blendVertCounts[3]
					+ 11 * asset->surfs[i].blendVertCounts[5]
					+ 13 * asset->surfs[i].blendVertCounts[6]
					+ 3 * (asset->surfs[i].blendVertCounts[1] + 3 * asset->surfs[i].blendVertCounts[4])
					+ 5 * (asset->surfs[i].blendVertCounts[2] + 3 * asset->surfs[i].blendVertCounts[7])));
			}

			dump.close();
		}
	}
}