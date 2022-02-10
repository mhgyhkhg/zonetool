#include "stdafx.hpp"
#include "IW6/Assets/XSurface.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		void GenerateIW6XSurface(IW6::XSurface* iw6_asset, XSurface* asset, ZoneMemory* mem)
		{
			iw6_asset->flags = 0;
			iw6_asset->vertCount = asset->vertCount;
			iw6_asset->triCount = asset->triCount;
			iw6_asset->rigidVertListCount = asset->vertListCount;

			iw6_asset->unknown = 0;

			// blend verts
			memcpy(&iw6_asset->blendVertCounts, &asset->vertexInfo.vertCount, sizeof(asset->vertexInfo.vertCount));
			iw6_asset->blendVerts = asset->vertexInfo.vertsBlend;

			// triIndices
			iw6_asset->triIndices = reinterpret_cast<IW6::Face*>(asset->triIndices);

			// verts
			iw6_asset->verts0.packedVerts0 = reinterpret_cast<IW6::GfxPackedVertex*>(asset->verticies);

			// rigidVertLists
			iw6_asset->rigidVertLists = mem->Alloc<IW6::XRigidVertList>(asset->vertListCount);
			for (auto i = 0; i < asset->vertListCount; i++)
			{
				iw6_asset->rigidVertLists[i].boneOffset = asset->rigidVertLists[i].boneOffset;
				iw6_asset->rigidVertLists[i].vertCount = asset->rigidVertLists[i].vertCount;
				iw6_asset->rigidVertLists[i].triOffset = asset->rigidVertLists[i].triOffset;
				iw6_asset->rigidVertLists[i].triCount = asset->rigidVertLists[i].triCount;

				if (asset->rigidVertLists[i].collisionTree)
				{
					iw6_asset->rigidVertLists[i].collisionTree = mem->Alloc<IW6::XSurfaceCollisionTree>();
					memcpy(&iw6_asset->rigidVertLists[i].collisionTree->trans, &asset->rigidVertLists[i].collisionTree->trans,
						sizeof(asset->rigidVertLists[i].collisionTree->trans));
					memcpy(&iw6_asset->rigidVertLists[i].collisionTree->scale, &asset->rigidVertLists[i].collisionTree->scale,
						sizeof(asset->rigidVertLists[i].collisionTree->scale));

					iw6_asset->rigidVertLists[i].collisionTree->nodeCount = asset->rigidVertLists[i].collisionTree->nodeCount;
					iw6_asset->rigidVertLists[i].collisionTree->nodes = mem->Alloc<IW6::XSurfaceCollisionNode>(
						asset->rigidVertLists[i].collisionTree->nodeCount);
					for (int j = 0; j < asset->rigidVertLists[i].collisionTree->nodeCount; j++)
					{
						memcpy(&iw6_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins,
							&asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins,
							sizeof(asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins));
						memcpy(&iw6_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs,
							&asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs,
							sizeof(asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs));

						iw6_asset->rigidVertLists[i].collisionTree->nodes[j].childBeginIndex =
							asset->rigidVertLists[i].collisionTree->nodes[j].childBeginIndex;
						iw6_asset->rigidVertLists[i].collisionTree->nodes[j].childCount =
							asset->rigidVertLists[i].collisionTree->nodes[j].childCount;
					}

					iw6_asset->rigidVertLists[i].collisionTree->leafCount = asset->rigidVertLists[i].collisionTree->leafCount;
					iw6_asset->rigidVertLists[i].collisionTree->leafs = mem->Alloc<IW6::XSurfaceCollisionLeaf>(
						asset->rigidVertLists[i].collisionTree->leafCount);
					for (int j = 0; j < asset->rigidVertLists[i].collisionTree->leafCount; j++)
					{
						iw6_asset->rigidVertLists[i].collisionTree->leafs[j].triangleBeginIndex =
							asset->rigidVertLists[i].collisionTree->leafs[j].triangleBeginIndex;
					}
				}
			}

			// partBits
			memcpy(&iw6_asset->partBits, &asset->partBits, sizeof(asset->partBits));
		}

		IW6::XModelSurfs* GenerateIW6XModelSurfs(ModelSurface* asset, ZoneMemory* mem)
		{
			// allocate IW6 XModelSurfs structure
			const auto iw6_asset = mem->Alloc<IW6::XModelSurfs>();

			iw6_asset->name = mem->StrDup(asset->name);
			iw6_asset->numsurfs = asset->xSurficiesCount;
			memcpy(&iw6_asset->partBits, &asset->partBits, sizeof(asset->partBits));

			iw6_asset->surfs = mem->Alloc<IW6::XSurface>(asset->xSurficiesCount);
			for (int i = 0; i < asset->xSurficiesCount; i++)
			{
				GenerateIW6XSurface(&iw6_asset->surfs[i], &asset->xSurficies[i], mem);
			}

			return iw6_asset;
		}

		void IXSurface::dump(ModelSurface* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::XSurface) == 232);

			// generate iw6 xsurface
			auto iw6_asset = GenerateIW6XModelSurfs(asset, mem);

			// dump iw6 xsurface
			IW6::IXSurface::dump(iw6_asset);
		}
	}
}