#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		void dump(ComWorld* asset)
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

	namespace IW5
	{
		IW6::ComWorld* GenerateIW6ComWorld(ComWorld* asset, ZoneMemory* mem)
		{
			// allocate IW6 clipMap_t structure
			const auto iw6_asset = mem->Alloc<IW6::ComWorld>();

			iw6_asset->name = asset->name;
			iw6_asset->isInUse = 0;
			iw6_asset->primaryLightCount = asset->primaryLightCount;
			iw6_asset->primaryLights = mem->Alloc<IW6::ComPrimaryLight>(iw6_asset->primaryLightCount);
			for (unsigned int i = 0; i < iw6_asset->primaryLightCount; i++)
			{
				iw6_asset->primaryLights[i].type = asset->primaryLights[i].type;
				iw6_asset->primaryLights[i].canUseShadowMap = asset->primaryLights[i].canUseShadowMap;
				iw6_asset->primaryLights[i].exponent = asset->primaryLights[i].exponent;
				iw6_asset->primaryLights[i].unused = asset->primaryLights[i].unused;
				memcpy(&iw6_asset->primaryLights[i].color, &asset->primaryLights[i].color, sizeof(float[3]));
				memcpy(&iw6_asset->primaryLights[i].dir, &asset->primaryLights[i].dir, sizeof(float[3]));
				memcpy(&iw6_asset->primaryLights[i].up, &asset->primaryLights[i].up, sizeof(float[3]));
				memcpy(&iw6_asset->primaryLights[i].origin, &asset->primaryLights[i].origin, sizeof(float[3]));
				iw6_asset->primaryLights[i].radius = asset->primaryLights[i].radius;
				iw6_asset->primaryLights[i].cosHalfFovOuter = asset->primaryLights[i].cosHalfFovOuter;
				iw6_asset->primaryLights[i].cosHalfFovInner = asset->primaryLights[i].cosHalfFovInner;
				iw6_asset->primaryLights[i].cosHalfFovExpanded = asset->primaryLights[i].cosHalfFovExpanded;
				iw6_asset->primaryLights[i].rotationLimit = asset->primaryLights[i].rotationLimit;
				iw6_asset->primaryLights[i].translationLimit = asset->primaryLights[i].translationLimit;
				iw6_asset->primaryLights[i].cucRotationOffsetRad = 0;
				iw6_asset->primaryLights[i].cucRotationSpeedRad = 0;
				memset(&iw6_asset->primaryLights[i].cucScrollVector, 0, sizeof(float[2]));
				memset(&iw6_asset->primaryLights[i].cucScaleVector, 0, sizeof(float[2]));
				memset(&iw6_asset->primaryLights[i].cucTransVector, 0, sizeof(float[2]));
				iw6_asset->primaryLights[i].defName = asset->primaryLights[i].defName;
			}
			iw6_asset->primaryLightEnvCount = iw6_asset->primaryLightCount;
			iw6_asset->primaryLightEnvs = mem->Alloc<IW6::ComPrimaryLightEnv>(iw6_asset->primaryLightEnvCount);
			for (unsigned int i = 1; i < iw6_asset->primaryLightEnvCount; i++)
			{
				iw6_asset->primaryLightEnvs[i].numIndices = 1;
				iw6_asset->primaryLightEnvs[i].primaryLightIndices[0] = i;
			}

			return iw6_asset;
		}

		void IComWorld::dump(ComWorld* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::ComWorld) == 40);

			// generate iw6 comworld
			auto iw6_asset = GenerateIW6ComWorld(asset, mem);

			// dump iw6 comworld
			IW6::dump(iw6_asset);
		}
	}
}