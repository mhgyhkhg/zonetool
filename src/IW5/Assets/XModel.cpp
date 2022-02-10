#include "stdafx.hpp"
#include "IW6/Assets/XModel.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		IW6::XModel* GenerateIW6Model(XModel* asset, ZoneMemory* mem)
		{
			// allocate IW6 XModel structure
			const auto iw6_asset = mem->Alloc<IW6::XModel>();

			iw6_asset->name = asset->name;
			iw6_asset->numBones = asset->numBones;
			iw6_asset->numRootBones = asset->numRootBones;
			iw6_asset->numsurfs = asset->numSurfaces;
			iw6_asset->numReactiveMotionParts = 0;
			iw6_asset->lodRampType = asset->lodRampType;
			iw6_asset->scale = asset->scale;
			memcpy(&iw6_asset->noScalePartBits, &asset->noScalePartBits, sizeof(asset->noScalePartBits));

			iw6_asset->boneNames = mem->Alloc<IW6::scr_string_t>(asset->numBones);
			for (auto i = 0; i < asset->numBones; i++)
			{
				iw6_asset->boneNames[i] = static_cast<IW6::scr_string_t>(asset->boneNames[i]);
			}

			//iw6_asset->parentList = mem->Alloc<unsigned char>(asset->numBones - asset->numRootBones);
			//for (auto i = 0; i < asset->numBones - asset->numRootBones; i++)
			//{
			//	iw6_asset->parentList[i] = asset->parentList[i];
			//}
			iw6_asset->parentList = reinterpret_cast<unsigned char*>(asset->parentList);

			iw6_asset->tagAngles = reinterpret_cast<IW6::XModelAngle*>(asset->tagAngles);

			iw6_asset->tagPositions = reinterpret_cast<IW6::XModelTagPos*>(asset->tagPositions);

			iw6_asset->partClassification = reinterpret_cast<unsigned char*>(asset->partClassification);

			iw6_asset->baseMat = reinterpret_cast<IW6::DObjAnimMat*>(asset->animMatrix);

			iw6_asset->reactiveMotionParts = nullptr;

			iw6_asset->materialHandles = mem->Alloc<IW6::Material* __ptr64>(asset->numSurfaces);
			for (auto i = 0; i < asset->numSurfaces; i++)
			{
				if (asset->materials[i])
				{
					iw6_asset->materialHandles[i] = mem->Alloc<IW6::Material>();
					iw6_asset->materialHandles[i]->name = mem->StrDup(asset->materials[i]->name);
				}
			}

			for (auto i = 0; i < 6; i++)
			{
				iw6_asset->lodInfo[i].dist = 1000000;
			}

			// level of detail data
			for (int i = 0; i < asset->numLods; i++)
			{
				iw6_asset->lodInfo[i].dist = asset->lods[i].dist += 200.0f; // LOD distance is increased so that the models look nicer in iw6
				iw6_asset->lodInfo[i].numsurfs = asset->lods[i].numSurfacesInLod;
				iw6_asset->lodInfo[i].surfIndex = asset->lods[i].surfIndex;
				memcpy(&iw6_asset->lodInfo[i].partBits, &asset->lods[i].partBits, sizeof(int[4]));

				// allocate xsurficies
				iw6_asset->lodInfo[i].modelSurfs = mem->Alloc<IW6::XModelSurfs>(asset->lods[i].numSurfacesInLod);
				for (int j = 0; j < asset->lods[i].numSurfacesInLod; j++)
				{
					iw6_asset->lodInfo[i].modelSurfs[j].name = mem->StrDup(asset->lods[i].surfaces[j].name);
				}

				// idk about these
				iw6_asset->lodInfo[i].unknown[0] = asset->lods[i].lod;
				iw6_asset->lodInfo[i].unknown[1] = asset->lods[i].smcBaseIndexPlusOne;
				iw6_asset->lodInfo[i].unknown[2] = asset->lods[i].smcSubIndexMask;
				iw6_asset->lodInfo[i].unknown[3] = asset->lods[i].smcBucket;
			}

			iw6_asset->maxLoadedLod = asset->maxLoadedLod;
			iw6_asset->numLods = asset->numLods;
			iw6_asset->collLod = asset->collLod;
			iw6_asset->flags = asset->flags;

			iw6_asset->numCollSurfs = asset->numColSurfs;
			iw6_asset->collSurfs = mem->Alloc<IW6::XModelCollSurf_s>(asset->numColSurfs);
			for (auto i = 0; i < asset->numColSurfs; i++)
			{
				iw6_asset->collSurfs[i].bounds.compute(asset->colSurf[i].mins, asset->colSurf[i].maxs);

				iw6_asset->collSurfs[i].boneIdx = asset->colSurf[i].boneIdx;
				iw6_asset->collSurfs[i].contents = asset->colSurf[i].contents;
				iw6_asset->collSurfs[i].surfFlags = asset->colSurf[i].surfFlags;
			}

			iw6_asset->contents = asset->contents;
			
			iw6_asset->boneInfo = mem->Alloc<IW6::XBoneInfo>(asset->numBones);
			for (int i = 0; i < asset->numBones; i++)
			{
				iw6_asset->boneInfo[i].bounds.compute(asset->boneInfo[i].bounds[0], asset->boneInfo[i].bounds[1]);
				iw6_asset->boneInfo[i].radiusSquared = asset->boneInfo[i].radiusSquared;
			}

			iw6_asset->radius = asset->radius;
			memcpy(&iw6_asset->bounds, &asset->bounds, sizeof(asset->bounds));
			iw6_asset->memUsage = asset->memUsage;

			if (asset->physPreset)
			{
				iw6_asset->physPreset = mem->Alloc<IW6::PhysPreset>();
				iw6_asset->physPreset->name = mem->StrDup(asset->physPreset->name);
			}

			if (asset->physCollmap)
			{
				iw6_asset->physCollmap = mem->Alloc<IW6::PhysCollmap>();
				iw6_asset->physCollmap->name = mem->StrDup(asset->physCollmap->name);
			}

			// idk
			iw6_asset->__unk = mem->Alloc<unsigned short>(asset->numSurfaces);
			memset(iw6_asset->__unk, 0, sizeof(unsigned short) * asset->numSurfaces);

			iw6_asset->quantization = asset->unk; //1.0f;

			return iw6_asset;
		}

		void IXModel::dump(XModel* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::XModel) == 600);

			// generate iw6 model
			auto iw6_asset = GenerateIW6Model(asset, mem);

			// dump iw6 model
			IW6::IXModel::dump(iw6_asset, SL_ConvertToString);
		}
	}
}