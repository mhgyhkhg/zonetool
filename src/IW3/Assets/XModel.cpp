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
		void dump_xmodel(XModel* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString)
		{
			assert(sizeof(IW6::XModel) == 600);

			AssetDumper dump;
			dump.open("XModel\\"s + asset->name + ".xme6");
			
			dump.dump_single(asset);
			
			// name
			dump.dump_string(asset->name);

			// tags
			dump.dump_array(asset->boneNames, asset->numBones);
			for (int i = 0; i < asset->numBones; i++)
			{
				dump.dump_string(SL_ConvertToString(asset->boneNames[i]));
			}
			dump.dump_array(asset->parentList, asset->numBones - asset->numRootBones);
			dump.dump_array(asset->tagAngles, asset->numBones - asset->numRootBones);
			dump.dump_array(asset->tagPositions, asset->numBones - asset->numRootBones);
			dump.dump_array(asset->partClassification, asset->numBones);
			dump.dump_array(asset->baseMat, asset->numBones);
			dump.dump_array(asset->reactiveMotionParts, asset->numReactiveMotionParts);
			dump.dump_array(asset->collSurfs, asset->numCollSurfs);
			dump.dump_array(asset->boneInfo, asset->numBones);
			dump.dump_array(asset->__unk, asset->numsurfs);
			
			// surfaces
			dump.dump_array(asset->materialHandles, asset->numsurfs);
			for (int i = 0; i < asset->numsurfs; i++)
			{
				dump.dump_asset(asset->materialHandles[i]);
			}

			// lods
			for (int i = 0; i < 6; i++)
			{
				dump.dump_asset(asset->lodInfo[i].modelSurfs);
			}

			// subassets
			dump.dump_asset(asset->physPreset);
			dump.dump_asset(asset->physCollmap);

			dump.close();
		}

		void dump_xsurface(XModelSurfs* asset)
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

	namespace IW3
	{
		IW6::XSurface* GenerateIW6Surface(XSurface* asset, ZoneMemory* mem)
		{
			// allocate IW6 XSurface structure
			const auto xsurface = mem->Alloc<IW6::XSurface>();
			
			xsurface->flags = 0;
			//xsurface->tileMode = asset->tileMode;
			//xsurface->deformed = asset->deformed;
			xsurface->vertCount = asset->vertCount;
			xsurface->triCount = asset->triCount;
			xsurface->rigidVertListCount = asset->vertListCount;
			//xsurface->zoneHandle = asset->zoneHandle;
			//xsurface->baseTriIndex = asset->baseTriIndex;
			//xsurface->baseVertIndex = asset->baseVertIndex; 

			// triIndices
			xsurface->triIndices = reinterpret_cast<IW6::Face*>(asset->triIndices);
			//xsurface->triIndices = mem->Alloc<IW6::Face>(asset->triCount);
			//for (auto i = 0; i < asset->triCount; i++)
			//{
			//	xsurface->triIndices[i].v1 = asset->triIndices[3 * i + 0];
			//	xsurface->triIndices[i].v2 = asset->triIndices[3 * i + 1];
			//	xsurface->triIndices[i].v3 = asset->triIndices[3 * i + 2];
			//}

			// blend verts
			memcpy(&xsurface->blendVertCounts, &asset->vertInfo.vertCount, sizeof(short[4]));
			auto count = (xsurface->blendVertCounts[0]
				+ 7 * xsurface->blendVertCounts[3]
				+ 11 * xsurface->blendVertCounts[5]
				+ 13 * xsurface->blendVertCounts[6]
				+ 3 * (xsurface->blendVertCounts[1] + 3 * xsurface->blendVertCounts[4])
				+ 5 * (xsurface->blendVertCounts[2] + 3 * xsurface->blendVertCounts[7]));
			xsurface->blendVerts = mem->Alloc<unsigned short>();
			for (auto i = 0; i < count; i++)
			{
				xsurface->blendVerts[i] = asset->vertInfo.vertsBlend[i];
			}

			// verts
			xsurface->verts0.packedVerts0 = reinterpret_cast<IW6::GfxPackedVertex*>(asset->verts0);
			//xsurface->verts0.verts0 = mem->Alloc<IW6::GfxPackedVertex>(asset->vertCount);
			//for (auto i = 0; i < asset->vertCount; i++)
			//{
			//	memcpy(&xsurface->verts0.packedVerts0[i], &asset->verts0[i], sizeof(IW6::GfxPackedVertex));
			//}

			// rigidVertLists
			if (asset->vertList)
			{
				xsurface->rigidVertLists = mem->Alloc<IW6::XRigidVertList>(asset->vertListCount);
				for (auto i = 0; i < asset->vertListCount; i++)
				{
					memcpy(&xsurface->rigidVertLists[i], &asset->vertList[i], sizeof(unsigned short) * 4);
					xsurface->rigidVertLists[i].collisionTree = mem->Alloc<IW6::XSurfaceCollisionTree>();
					memcpy(xsurface->rigidVertLists[i].collisionTree, asset->vertList[i].collisionTree, sizeof(float[3]) * 2);
					xsurface->rigidVertLists[i].collisionTree->nodeCount = asset->vertList[i].collisionTree->nodeCount;
					xsurface->rigidVertLists[i].collisionTree->leafCount = asset->vertList[i].collisionTree->leafCount;
					if (asset->vertList[i].collisionTree->nodes)
					{
						xsurface->rigidVertLists[i].collisionTree->nodes = mem->Alloc<IW6::XSurfaceCollisionNode>(asset->vertList[i].collisionTree->nodeCount);
						for (auto n = 0; n < asset->vertList[i].collisionTree->nodeCount; n++)
						{
							memcpy(&xsurface->rigidVertLists[i].collisionTree->nodes[n], &asset->vertList[i].collisionTree->nodes[n], sizeof(IW6::XSurfaceCollisionNode));
						}
					}
					if (asset->vertList[i].collisionTree->leafs)
					{
						xsurface->rigidVertLists[i].collisionTree->leafs = mem->Alloc<IW6::XSurfaceCollisionLeaf>(asset->vertList[i].collisionTree->leafCount);
						for (auto l = 0; l < asset->vertList[i].collisionTree->nodeCount; l++)
						{
							xsurface->rigidVertLists[i].collisionTree->leafs[l].triangleBeginIndex = asset->vertList[i].collisionTree->leafs[l].triangleBeginIndex;
						}
					}
				}
			}
			// partBits
			memcpy(&xsurface->partBits, &asset->partBits, sizeof(int[4]));

			return xsurface;
		}

		IW6::XModel* GenerateIW6Model(XModel* asset, ZoneMemory* mem)
		{
			// allocate IW6 XModel structure
			const auto xmodel = mem->Alloc<IW6::XModel>();

			// copy data over
			xmodel->name = const_cast<char*>(asset->name);
			xmodel->numBones = asset->numBones;
			xmodel->numRootBones = asset->numRootBones;
			xmodel->numsurfs = asset->numsurfs;
			xmodel->lodRampType = asset->lodRampType;
			xmodel->scale = 0.0f;
			memset(&xmodel->noScalePartBits, 0, sizeof(xmodel->noScalePartBits));

			if(asset->boneNames)
			{
				xmodel->boneNames = mem->Alloc<IW6::scr_string_t>(asset->numBones);
				for (auto i = 0; i < asset->numBones; i++)
				{
					xmodel->boneNames[i] = static_cast<IW6::scr_string_t>(asset->boneNames[i]);
				}
			}

			if (asset->parentList)
			{
				//xmodel->parentList = mem->Alloc<unsigned char>(asset->numBones - asset->numRootBones);
				//memcpy(xmodel->parentList, asset->parentList, sizeof(unsigned char) * (asset->numBones - asset->numRootBones));
				xmodel->parentList = reinterpret_cast<unsigned char*>(asset->parentList);
			}

			if (asset->quats)
			{
				//xmodel->tagAngles = mem->Alloc<IW6::XModelAngle>(asset->numBones - asset->numRootBones);
				//for (auto i = 0; i < asset->numBones - asset->numRootBones; i++)
				//{
				//	xmodel->tagAngles[i].x = asset->quats[4 * i + 0];
				//	xmodel->tagAngles[i].y = asset->quats[4 * i + 1];
				//	xmodel->tagAngles[i].z = asset->quats[4 * i + 2];
				//	xmodel->tagAngles[i].base = asset->quats[4 * i + 3];
				//}
				xmodel->tagAngles = reinterpret_cast<IW6::XModelAngle*>(asset->quats);
			}

			if (asset->trans)
			{
				//xmodel->tagPositions = mem->Alloc<IW6::XModelTagPos>(asset->numBones - asset->numRootBones);
				//for (auto i = 0; i < asset->numBones - asset->numRootBones; i++)
				//{
				//	xmodel->tagPositions[i].x = asset->trans[3 * i + 0];
				//	xmodel->tagPositions[i].y = asset->trans[3 * i + 1];
				//	xmodel->tagPositions[i].z = asset->trans[3 * i + 2];
				//}
				xmodel->tagPositions = reinterpret_cast<IW6::XModelTagPos*>(asset->trans);
			}

			if (asset->partClassification)
			{
				//xmodel->partClassification = mem->Alloc<unsigned char>(asset->numBones);
				//memcpy(xmodel->partClassification, asset->partClassification, sizeof(unsigned char) * asset->numBones);
				xmodel->partClassification = reinterpret_cast<unsigned char*>(asset->partClassification);
			}

			if (asset->baseMat)
			{
				//xmodel->baseMat = mem->Alloc<IW6::DObjAnimMat>(asset->numBones);
				//for(auto i = 0; i < asset->numBones; i++)
				//{
				//	memcpy(&xmodel->baseMat[i], &asset->baseMat[i], sizeof(IW6::DObjAnimMat));
				//}
				xmodel->baseMat = reinterpret_cast<IW6::DObjAnimMat*>(asset->baseMat);
			}

			xmodel->reactiveMotionParts = nullptr;
			
			if (asset->materialHandles)
			{
				xmodel->materialHandles = mem->Alloc<IW6::Material* __ptr64>(asset->numsurfs);
				for (auto i = 0; i < asset->numsurfs; i++)
				{
					if (asset->materialHandles[i])
					{
						xmodel->materialHandles[i] = mem->Alloc<IW6::Material>();
						xmodel->materialHandles[i]->name = mem->StrDup(asset->materialHandles[i]->name);
					}
				}
			}

			for (auto i = 0; i < 6; i++)
			{
				xmodel->lodInfo[i].dist = 1000000;
			}

			// convert level of detail data
			for (int i = 0; i < asset->numLods; i++)
			{
				xmodel->lodInfo[i].dist = asset->lodInfo[i].dist += 200.0f; // LOD distance is increased so that the models look nicer in iw6
				xmodel->lodInfo[i].numsurfs = asset->lodInfo[i].numsurfs;
				xmodel->lodInfo[i].surfIndex = asset->lodInfo[i].surfIndex;
				memcpy(&xmodel->lodInfo[i].partBits, &asset->lodInfo[i].partBits, sizeof(int[4]));

				// generate ModelSurface object
				xmodel->lodInfo[i].modelSurfs = mem->Alloc<IW6::XModelSurfs>();
				auto name = va("zonetool_%s_%i", reinterpret_cast<const char*>(xmodel->name), i);
				xmodel->lodInfo[i].modelSurfs->name = mem->StrDup(name.data());
				xmodel->lodInfo[i].modelSurfs->numsurfs = xmodel->lodInfo[i].numsurfs;
				memcpy(&xmodel->lodInfo[i].modelSurfs->partBits, &asset->lodInfo[i].partBits, sizeof(int[4]));

				// allocate xsurficies
				xmodel->lodInfo[i].modelSurfs->surfs = mem->Alloc<IW6::XSurface>(xmodel->lodInfo[i].numsurfs);

				// loop through surfaces in current Level-of-Detail
				for (int surf = xmodel->lodInfo[i].surfIndex; surf <
					xmodel->lodInfo[i].surfIndex + xmodel->lodInfo[i].numsurfs; surf++)
				{
					// generate iw6 surface
					const auto surface = GenerateIW6Surface(&asset->surfs[surf], mem);

					// copy XSurface into iw6 structure
					memcpy(
						&xmodel->lodInfo[i].modelSurfs->surfs[surf - xmodel->lodInfo[i].surfIndex],
						surface,
						sizeof IW6::XSurface
					);
				}
			}

			xmodel->maxLoadedLod = 0;
			xmodel->numLods = static_cast<char>(asset->numLods);
			xmodel->collLod = static_cast<char>(asset->collLod);
			xmodel->flags = static_cast<unsigned char>(asset->flags);
			
			if (asset->collSurfs)
			{
				xmodel->collSurfs = mem->Alloc<IW6::XModelCollSurf_s>(asset->numCollSurfs);
				for (auto i = 0; i < asset->numCollSurfs; i++)
				{
					memcpy(&xmodel->collSurfs[i], &asset->collSurfs[i].mins, sizeof(IW6::XModelCollSurf_s));
					// convert colsurf bounds
					xmodel->collSurfs[i].bounds.compute();
				}
			}
			xmodel->numCollSurfs = asset->numCollSurfs;
			xmodel->contents = asset->contents;
			
			if (asset->boneInfo)
			{
				// convert boneinfo
				xmodel->boneInfo = mem->Alloc<IW6::XBoneInfo>(asset->numBones);
				for (int i = 0; i < asset->numBones; i++)
				{
					xmodel->boneInfo[i].bounds.compute(asset->boneInfo[i].bounds[0], asset->boneInfo[i].bounds[1]);
					xmodel->boneInfo[i].radiusSquared = asset->boneInfo[i].radiusSquared;
				}
			}

			xmodel->radius = asset->radius;
			xmodel->bounds.compute(asset->mins, asset->maxs);
			xmodel->memUsage = 0;

			xmodel->physPreset = reinterpret_cast<IW6::PhysPreset*>(asset->physPreset);
			xmodel->physCollmap = nullptr;

			xmodel->quantization = 1.0f;

			// idk
			xmodel->__unk = mem->Alloc<unsigned short>(asset->numsurfs);
			memset(xmodel->__unk, 0, sizeof(unsigned short) * asset->numsurfs);

			return xmodel;
		}

		void IXModel::dump(XModel* asset, ZoneMemory* mem)
		{
			// generate iw6 model
			auto iw6_model = GenerateIW6Model(asset, mem);

			// dump iw6 model
			IW6::dump_xmodel(iw6_model, SL_ConvertToString);

			// dump all xsurfaces
			for (int i = 0; i < iw6_model->numLods; i++)
			{
				IW6::dump_xsurface(iw6_model->lodInfo[i].modelSurfs);
			}
		}
	}
}