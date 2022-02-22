#include "stdafx.hpp"
#include "IW6/Assets/GfxWorld.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		IW6::GfxWorld* GenerateIW6GfxWorld(GfxWorld* asset, ZoneMemory* mem)
		{
			// allocate IW6 clipMap_t structure
			const auto iw6_asset = mem->Alloc<IW6::GfxWorld>();

			iw6_asset->name = asset->name;
			iw6_asset->baseName = asset->baseName;

			iw6_asset->bspVersion = 74;
			iw6_asset->planeCount = asset->planeCount;
			iw6_asset->nodeCount = asset->nodeCount;
			iw6_asset->surfaceCount = asset->indexCount;
			iw6_asset->skyCount = asset->skyCount;

			iw6_asset->skies = mem->Alloc<IW6::GfxSky>(iw6_asset->skyCount);
			for (int i = 0; i < iw6_asset->skyCount; i++)
			{
				iw6_asset->skies[i].skySurfCount = asset->skies[i].skySurfCount;
				iw6_asset->skies[i].skyStartSurfs = reinterpret_cast<int* __ptr64>(asset->skies[i].skyStartSurfs);
				iw6_asset->skies[i].skyImage = mem->Alloc<IW6::GfxImage>();
				iw6_asset->skies[i].skyImage->name = asset->skies->skyImage->name;
				iw6_asset->skies[i].skySamplerState = asset->skies[i].skySamplerState;
			}

			iw6_asset->lastSunPrimaryLightIndex = asset->lastSunPrimaryLightIndex;
			iw6_asset->primaryLightCount = asset->primaryLightCount;
			iw6_asset->primaryLightEnvCount = asset->primaryLightCount;
			iw6_asset->sortKeyLitDecal = 6; //asset->sortKeyLitDecal;
			iw6_asset->sortKeyEffectDecal = 39; //asset->sortKeyEffectDecal;
			iw6_asset->sortKeyTopDecal = 16;
			iw6_asset->sortKeyEffectAuto = 48; //asset->sortKeyEffectAuto;
			iw6_asset->sortKeyDistortion = 43; //asset->sortKeyDistortion;

			iw6_asset->dpvsPlanes.cellCount = asset->dpvsPlanes.cellCount;
			iw6_asset->dpvsPlanes.planes = reinterpret_cast<IW6::cplane_s * __ptr64>(asset->dpvsPlanes.planes);

			iw6_asset->dpvsPlanes.nodes = reinterpret_cast<unsigned __int16* __ptr64>(asset->dpvsPlanes.nodes);

			iw6_asset->dpvsPlanes.sceneEntCellBits = mem->Alloc<unsigned int>(asset->dpvsPlanes.cellCount << 9);
			for (int i = 0; i < asset->dpvsPlanes.cellCount << 9; i++)
			{
				iw6_asset->dpvsPlanes.sceneEntCellBits[i] = asset->dpvsPlanes.sceneEntCellBits[i];
			}

			iw6_asset->aabbTreeCounts = reinterpret_cast<IW6::GfxCellTreeCount * __ptr64>(asset->aabbTreeCounts);
			iw6_asset->aabbTrees = mem->Alloc<IW6::GfxCellTree>(iw6_asset->dpvsPlanes.cellCount);
			for (int i = 0; i < iw6_asset->dpvsPlanes.cellCount; i++)
			{
				iw6_asset->aabbTrees[i].aabbTree = mem->Alloc<IW6::GfxAabbTree>(iw6_asset->aabbTreeCounts[i].aabbTreeCount);
				for (int j = 0; j < iw6_asset->aabbTreeCounts[i].aabbTreeCount; j++)
				{
					//iw6_asset->aabbTrees[i].aabbTree[j].bounds.compute(asset->aabbTree[i].aabbtree[j].mins, asset->aabbTree[i].aabbtree[j].maxs);
					memcpy(&iw6_asset->aabbTrees[i].aabbTree[j].bounds, &asset->aabbTree[i].aabbtree[j].mins, sizeof(float[2][3]));
					iw6_asset->aabbTrees[i].aabbTree[j].childCount = asset->aabbTree[i].aabbtree[j].childCount;
					iw6_asset->aabbTrees[i].aabbTree[j].surfaceCount = asset->aabbTree[i].aabbtree[j].surfaceCount;
					iw6_asset->aabbTrees[i].aabbTree[j].startSurfIndex = asset->aabbTree[i].aabbtree[j].startSurfIndex;
					iw6_asset->aabbTrees[i].aabbTree[j].smodelIndexCount = asset->aabbTree[i].aabbtree[j].smodelIndexCount;
					iw6_asset->aabbTrees[i].aabbTree[j].smodelIndexes = reinterpret_cast<unsigned short* __ptr64>(asset->aabbTree[i].aabbtree[j].smodelIndexes);
					iw6_asset->aabbTrees[i].aabbTree[j].childrenOffset = asset->aabbTree[i].aabbtree[j].childrenOffset;
				}
			}

			iw6_asset->cells = mem->Alloc<IW6::GfxCell>(iw6_asset->dpvsPlanes.cellCount);
			for (int i = 0; i < iw6_asset->dpvsPlanes.cellCount; i++)
			{
				//iw6_asset->cells[i].bounds.compute(asset->cells[i].mins, asset->cells[i].maxs);
				memcpy(&iw6_asset->cells[i].bounds, &asset->cells[i].mins, sizeof(float[2][3]));
				iw6_asset->cells[i].portalCount = asset->cells[i].portalCount;

				auto add_portal = [](IW6::GfxPortal* iw6_portal, IW5::GfxPortal* iw5_portal)
				{
					iw6_portal->writable.isQueued = iw5_portal->writable.isQueued;
					iw6_portal->writable.isAncestor = iw5_portal->writable.isAncestor;
					iw6_portal->writable.recursionDepth = iw5_portal->writable.recursionDepth;
					iw6_portal->writable.hullPointCount = iw5_portal->writable.hullPointCount;
					iw6_portal->writable.hullPoints = nullptr;
					//iw6_portal->writable.hullPoints = reinterpret_cast<float(* __ptr64)[2]>(iw5_portal->writable.hullPoints);
					//iw6_portal->writable.queuedParent = add_portal(iw5_portal->writable.queuedParent);

					memcpy(&iw6_portal->plane, &iw5_portal->plane, sizeof(float[4])); // lost data: float sides[3]
					iw6_portal->vertices = reinterpret_cast<float(*__ptr64)[3]>(iw5_portal->vertices);
					iw6_portal->cellIndex = 0;
					iw6_portal->closeDistance = iw5_portal->unknown2;
					memcpy(&iw6_portal->hullAxis, &iw5_portal->hullAxis, sizeof(float[2][3]));
				};
				iw6_asset->cells[i].portals = mem->Alloc<IW6::GfxPortal>(iw6_asset->cells[i].portalCount);
				for (int j = 0; j < iw6_asset->cells[i].portalCount; j++)
				{
					add_portal(&iw6_asset->cells[i].portals[j], &asset->cells[i].portals[j]);
				}

				iw6_asset->cells[i].reflectionProbeCount = asset->cells[i].reflectionProbeCount;
				iw6_asset->cells[i].reflectionProbes = reinterpret_cast<unsigned __int8* __ptr64>(asset->cells[i].reflectionProbes);
				iw6_asset->cells[i].reflectionProbeReferenceCount = asset->cells[i].reflectionProbeReferenceCount;
				iw6_asset->cells[i].reflectionProbeReferences = reinterpret_cast<unsigned __int8* __ptr64>(asset->cells[i].reflectionProbeReferences);
			}

			iw6_asset->draw.reflectionProbeCount = asset->worldDraw.reflectionProbeCount;
			iw6_asset->draw.reflectionProbes = mem->Alloc<IW6::GfxImage* __ptr64>(iw6_asset->draw.reflectionProbeCount);
			iw6_asset->draw.reflectionProbeOrigins = mem->Alloc<IW6::GfxReflectionProbe>(iw6_asset->draw.reflectionProbeCount);
			iw6_asset->draw.reflectionProbeTextures = mem->Alloc<IW6::GfxTexture>(iw6_asset->draw.reflectionProbeCount);
			for (unsigned int i = 0; i < iw6_asset->draw.reflectionProbeCount; i++)
			{
				iw6_asset->draw.reflectionProbes[i] = mem->Alloc<IW6::GfxImage>();
				iw6_asset->draw.reflectionProbes[i]->name = asset->worldDraw.reflectionImages[i]->name;
				memcpy(&iw6_asset->draw.reflectionProbeOrigins[i].origin, &asset->worldDraw.reflectionProbes[i].offset, sizeof(float[3]));
				iw6_asset->draw.reflectionProbeOrigins[i].probeVolumeCount = 0;
				iw6_asset->draw.reflectionProbeOrigins[i].probeVolumes = nullptr;
				memcpy(&iw6_asset->draw.reflectionProbeTextures[i], &asset->worldDraw.reflectionProbeTextures[i].loadDef, 20);
			}
			iw6_asset->draw.reflectionProbeReferenceCount = asset->worldDraw.reflectionProbeReferenceCount;
			iw6_asset->draw.reflectionProbeReferenceOrigins = reinterpret_cast<IW6::GfxReflectionProbeReferenceOrigin * __ptr64>(
				asset->worldDraw.reflectionProbeReferenceOrigins);
			iw6_asset->draw.reflectionProbeReferences = reinterpret_cast<IW6::GfxReflectionProbeReference * __ptr64>(
				asset->worldDraw.reflectionProbeReferences);

			iw6_asset->draw.lightmapCount = asset->worldDraw.lightmapCount;
			iw6_asset->draw.lightmaps = mem->Alloc<IW6::GfxLightmapArray>(iw6_asset->draw.lightmapCount);
			iw6_asset->draw.lightmapPrimaryTextures = mem->Alloc<IW6::GfxTexture>(iw6_asset->draw.lightmapCount);
			iw6_asset->draw.lightmapSecondaryTextures = mem->Alloc<IW6::GfxTexture>(iw6_asset->draw.lightmapCount);
			for (int i = 0; i < iw6_asset->draw.lightmapCount; i++)
			{
				iw6_asset->draw.lightmaps[i].primary = mem->Alloc<IW6::GfxImage>();
				iw6_asset->draw.lightmaps[i].primary->name = asset->worldDraw.lightmaps[i].primary->name;
				iw6_asset->draw.lightmaps[i].secondary = mem->Alloc<IW6::GfxImage>();
				iw6_asset->draw.lightmaps[i].secondary->name = asset->worldDraw.lightmaps[i].secondary->name;

				memcpy(&iw6_asset->draw.lightmapPrimaryTextures[i], &asset->worldDraw.lightmapPrimaryTextures[i].loadDef, 20);
				memcpy(&iw6_asset->draw.lightmapSecondaryTextures[i], &asset->worldDraw.lightmapSecondaryTextures[i].loadDef, 20);
			}
			iw6_asset->draw.lightmapOverridePrimary = nullptr; // skipped
			iw6_asset->draw.lightmapOverrideSecondary = nullptr; // skipped

			iw6_asset->draw.trisType = 0; // dunno

			iw6_asset->draw.vertexCount = asset->worldDraw.vertexCount;
			iw6_asset->draw.vd.vertices = reinterpret_cast<IW6::GfxWorldVertex * __ptr64>(asset->worldDraw.vd.vertices);

			iw6_asset->draw.vertexLayerDataSize = asset->worldDraw.vertexLayerDataSize;
			iw6_asset->draw.vld.data = reinterpret_cast<unsigned __int8* __ptr64>(asset->worldDraw.vld.data);

			iw6_asset->draw.indexCount = asset->worldDraw.indexCount;
			iw6_asset->draw.indices = reinterpret_cast<unsigned __int16* __ptr64>(asset->worldDraw.indices);
			iw6_asset->draw.indexBuffer = nullptr;

			iw6_asset->lightGrid.hasLightRegions = asset->lightGrid.hasLightRegions;
			iw6_asset->lightGrid.useSkyForLowZ = 0;
			memcpy(&iw6_asset->lightGrid.lastSunPrimaryLightIndex, &asset->lightGrid.sunPrimaryLightIndex,
				Difference(&asset->lightGrid.colAxis, &asset->lightGrid.sunPrimaryLightIndex) + sizeof(unsigned int));
			iw6_asset->lightGrid.rowDataStart = reinterpret_cast<unsigned __int16* __ptr64>(asset->lightGrid.rowDataStart);
			iw6_asset->lightGrid.rawRowDataSize = asset->lightGrid.rawRowDataSize;
			iw6_asset->lightGrid.rawRowData = reinterpret_cast<unsigned __int8* __ptr64>(asset->lightGrid.rawRowData);
			iw6_asset->lightGrid.entryCount = asset->lightGrid.entryCount;
			iw6_asset->lightGrid.entries = mem->Alloc<IW6::GfxLightGridEntry>(iw6_asset->lightGrid.entryCount);
			for (int i = 0; i < iw6_asset->lightGrid.entryCount; i++)
			{
				iw6_asset->lightGrid.entries[i].colorsIndex = asset->lightGrid.entries[i].colorsIndex;
				iw6_asset->lightGrid.entries[i].primaryLightEnvIndex = asset->lightGrid.entries[i].primaryLightIndex;
				iw6_asset->lightGrid.entries[i].unused = 0;
				iw6_asset->lightGrid.entries[i].needsTrace = asset->lightGrid.entries[i].needsTrace;
			}
			iw6_asset->lightGrid.colorCount = asset->lightGrid.colorCount;
			iw6_asset->lightGrid.colors = reinterpret_cast<IW6::GfxLightGridColors * __ptr64>(asset->lightGrid.colors);

			iw6_asset->lightGrid.missingGridColorIndex = 0;			// no such thing in iw5 {
			iw6_asset->lightGrid.tableVersion = 0;
			iw6_asset->lightGrid.paletteVersion = 0;
			iw6_asset->lightGrid.rangeExponent8BitsEncoding = 0;
			iw6_asset->lightGrid.rangeExponent12BitsEncoding = 0;
			iw6_asset->lightGrid.rangeExponent16BitsEncoding = 0;
			iw6_asset->lightGrid.stageCount = 0;
			iw6_asset->lightGrid.stageLightingContrastGain = 0;
			iw6_asset->lightGrid.paletteEntryCount = 0;
			iw6_asset->lightGrid.paletteEntryAddress = 0;
			iw6_asset->lightGrid.paletteBitstreamSize = 0;
			iw6_asset->lightGrid.paletteBitstream = 0;
			iw6_asset->lightGrid.skyLightGridColors.colorVec3;
			iw6_asset->lightGrid.defaultLightGridColors;
			iw6_asset->lightGrid.tree;								// }

			iw6_asset->modelCount = asset->modelCount;
			iw6_asset->models = mem->Alloc<IW6::GfxBrushModel>(iw6_asset->modelCount);
			for (int i = 0; i < iw6_asset->modelCount; i++)
			{
				//iw6_asset->models[i].writable.bounds.compute(asset->models[i].writable.mins, asset->models[i].writable.maxs);
				memcpy(&iw6_asset->models[i].writable.bounds, &asset->models[i].writable.mins, sizeof(float[2][3]));
				//# // lost data: asset->models[i].writable.mip1radiusSq
				//# memcpy(&iw6_asset->models[i].bounds, &asset->models[i].bounds, sizeof(float[2][3]));
				//# auto* half_size = iw6_asset->models[i].bounds.halfSize;
				//# iw6_asset->models[i].radius = std::sqrt(std::pow(half_size[0], 2) + std::pow(half_size[1], 2) + std::pow(half_size[2], 2));
				iw6_asset->models[i].radius = asset->models[i].writable.mip1radiusSq;
				iw6_asset->models[i].surfaceCount = asset->models[i].surfaceCount;
				iw6_asset->models[i].startSurfIndex = asset->models[i].startSurfIndex;
			}

			//iw6_asset->bounds.compute(asset->mins, asset->maxs);
			memcpy(&iw6_asset->bounds, &asset->mins, sizeof(float[2][3]));

			iw6_asset->checksum = asset->checksum;

			iw6_asset->materialMemoryCount = asset->materialMemoryCount;
			iw6_asset->materialMemory = mem->Alloc<IW6::MaterialMemory>(iw6_asset->materialMemoryCount);
			for (int i = 0; i < iw6_asset->materialMemoryCount; i++)
			{
				iw6_asset->materialMemory[i].material = reinterpret_cast<IW6::Material * __ptr64>(asset->materialMemory[i].material);
				iw6_asset->materialMemory[i].memory = asset->materialMemory[i].memory;
			}

			iw6_asset->sun.hasValidData = asset->sun.hasValidData;
			iw6_asset->sun.spriteMaterial = reinterpret_cast<IW6::Material * __ptr64>(asset->sun.spriteMaterial);
			iw6_asset->sun.flareMaterial = reinterpret_cast<IW6::Material * __ptr64>(asset->sun.flareMaterial);
			memcpy(&iw6_asset->sun.spriteSize, &asset->sun.spriteSize, Difference(&asset->sun.sunFxPosition, &asset->sun.spriteSize) + sizeof(float[3]));

			memcpy(&iw6_asset->outdoorLookupMatrix, &asset->outdoorLookupMatrix, sizeof(float[4][4]));
			iw6_asset->outdoorImage = mem->Alloc<IW6::GfxImage>();
			iw6_asset->outdoorImage->name = asset->outdoorImage->name;

			iw6_asset->cellCasterBits = mem->Alloc<unsigned int>(iw6_asset->dpvsPlanes.cellCount * ((iw6_asset->dpvsPlanes.cellCount + 31) >> 5));
			for (int i = 0; i < asset->dpvsPlanes.cellCount * ((asset->dpvsPlanes.cellCount + 31) >> 5); i++)
			{
				iw6_asset->cellCasterBits[i] = asset->cellCasterBits[0][i];
			}
			iw6_asset->cellHasSunLitSurfsBits = mem->Alloc<unsigned int>((iw6_asset->dpvsPlanes.cellCount + 31) >> 5);

			iw6_asset->sceneDynModel = mem->Alloc<IW6::GfxSceneDynModel>(asset->dpvsDyn.dynEntClientCount[0]);
			for (unsigned int i = 0; i < asset->dpvsDyn.dynEntClientCount[0]; i++)
			{
				iw6_asset->sceneDynModel[i].info.hasGfxEntIndex = 0;
				iw6_asset->sceneDynModel[i].info.lod = asset->sceneDynModel[i].info.lod;
				iw6_asset->sceneDynModel[i].info.surfId = asset->sceneDynModel[i].info.surfId;
				iw6_asset->sceneDynModel[i].dynEntId = asset->sceneDynModel[i].dynEntId;
			}

			iw6_asset->sceneDynBrush = reinterpret_cast<IW6::GfxSceneDynBrush * __ptr64>(asset->sceneDynBrush);

			//iw6_asset->primaryLightEntityShadowVis = reinterpret_cast<unsigned int* __ptr64>(asset->primaryLightEntityShadowVis);
			iw6_asset->primaryLightEntityShadowVis = mem->Alloc<unsigned int>(((iw6_asset->primaryLightCount - iw6_asset->lastSunPrimaryLightIndex - 1) << 13));
			for (unsigned int i = 0; i < ((iw6_asset->primaryLightCount - iw6_asset->lastSunPrimaryLightIndex - 1) << 13); i++)
			{
				iw6_asset->primaryLightEntityShadowVis[i] = asset->primaryLightEntityShadowVis[i];
			}

			iw6_asset->primaryLightDynEntShadowVis[0] = reinterpret_cast<unsigned int* __ptr64>(asset->primaryLightDynEntShadowVis[0]);
			iw6_asset->primaryLightDynEntShadowVis[1] = reinterpret_cast<unsigned int* __ptr64>(asset->primaryLightDynEntShadowVis[1]);

			//iw6_asset->nonSunPrimaryLightForModelDynEnt = reinterpret_cast<unsigned __int16* __ptr64>(asset->primaryLightForModelDynEnt);
			iw6_asset->nonSunPrimaryLightForModelDynEnt = mem->Alloc<unsigned short>(asset->dpvsDyn.dynEntClientCount[0]);
			for (unsigned int i = 0; i < asset->dpvsDyn.dynEntClientCount[0]; i++)
			{
				iw6_asset->nonSunPrimaryLightForModelDynEnt[i] = asset->primaryLightForModelDynEnt[i];
			}

			if (asset->shadowGeom)
			{
				iw6_asset->shadowGeom = mem->Alloc<IW6::GfxShadowGeometry>(iw6_asset->primaryLightCount);
				for (unsigned int i = 0; i < iw6_asset->primaryLightCount; i++)
				{
					iw6_asset->shadowGeom[i].surfaceCount = asset->shadowGeom[i].surfaceCount;
					iw6_asset->shadowGeom[i].smodelCount = asset->shadowGeom[i].smodelCount;

					iw6_asset->shadowGeom[i].sortedSurfIndex = mem->Alloc<unsigned int>(iw6_asset->shadowGeom[i].surfaceCount);
					for (unsigned int j = 0; j < iw6_asset->shadowGeom[i].surfaceCount; j++)
					{
						iw6_asset->shadowGeom[i].sortedSurfIndex[j] = asset->shadowGeom[i].sortedSurfIndex[j];
					}
					iw6_asset->shadowGeom[i].smodelIndex = mem->Alloc<unsigned short>(iw6_asset->shadowGeom[i].smodelCount);
					for (unsigned int j = 0; j < iw6_asset->shadowGeom[i].smodelCount; j++)
					{
						iw6_asset->shadowGeom[i].smodelIndex[j] = asset->shadowGeom[i].smodelIndex[j];
					}
				}
			}
			iw6_asset->shadowGeomOptimized = nullptr;

			iw6_asset->lightRegion = mem->Alloc<IW6::GfxLightRegion>(iw6_asset->primaryLightCount);
			for (unsigned int i = 0; i < iw6_asset->primaryLightCount; i++)
			{
				iw6_asset->lightRegion[i].hullCount = asset->lightRegion[i].hullCount;
				iw6_asset->lightRegion[i].hulls = mem->Alloc<IW6::GfxLightRegionHull>(iw6_asset->lightRegion[i].hullCount);
				for (unsigned int j = 0; j < iw6_asset->lightRegion[i].hullCount; j++)
				{
					memcpy(&iw6_asset->lightRegion[i].hulls[j].kdopMidPoint, &asset->lightRegion[i].hulls[j].kdopMidPoint,
						(sizeof(float[9]) * 2) + sizeof(unsigned int));
					iw6_asset->lightRegion[i].hulls[j].axis = reinterpret_cast<IW6::GfxLightRegionAxis * __ptr64>(
						asset->lightRegion[i].hulls[j].axis);
				}
			}

			iw6_asset->dpvs.smodelCount = asset->dpvs.smodelCount;
			iw6_asset->dpvs.staticSurfaceCount = asset->dpvs.staticSurfaceCount * 4;
			iw6_asset->dpvs.litOpaqueSurfsBegin = asset->dpvs.litOpaqueSurfsBegin;
			iw6_asset->dpvs.litOpaqueSurfsEnd = asset->dpvs.litOpaqueSurfsEnd;
			iw6_asset->dpvs.litDecalSurfsBegin = asset->dpvs.litOpaqueSurfsEnd; // skip ( doesn't exists )
			iw6_asset->dpvs.litDecalSurfsEnd = asset->dpvs.litOpaqueSurfsEnd; // skip ( doesn't exists )
			iw6_asset->dpvs.litTransSurfsBegin = asset->dpvs.litTransSurfsBegin;
			iw6_asset->dpvs.litTransSurfsEnd = asset->dpvs.litTransSurfsEnd;
			iw6_asset->dpvs.shadowCasterSurfsBegin = asset->dpvs.shadowCasterSurfsBegin;
			iw6_asset->dpvs.shadowCasterSurfsEnd = asset->dpvs.shadowCasterSurfsEnd;
			iw6_asset->dpvs.emissiveSurfsBegin = asset->dpvs.emissiveSurfsBegin;
			iw6_asset->dpvs.emissiveSurfsEnd = asset->dpvs.emissiveSurfsEnd;
			iw6_asset->dpvs.smodelVisDataCount = asset->dpvs.smodelVisDataCount;
			iw6_asset->dpvs.surfaceVisDataCount = asset->dpvs.surfaceVisDataCount;

			iw6_asset->dpvs.smodelVisData[0] = mem->Alloc<unsigned int>(iw6_asset->dpvs.smodelVisDataCount);
			iw6_asset->dpvs.smodelVisData[1] = mem->Alloc<unsigned int>(iw6_asset->dpvs.smodelVisDataCount);
			iw6_asset->dpvs.smodelVisData[2] = mem->Alloc<unsigned int>(iw6_asset->dpvs.smodelVisDataCount);
			for (unsigned int i = 0; i < iw6_asset->dpvs.smodelVisDataCount; i++)
			{
				iw6_asset->dpvs.smodelVisData[0][i] = asset->dpvs.smodelVisData[0][i];
				iw6_asset->dpvs.smodelVisData[1][i] = asset->dpvs.smodelVisData[1][i];
				iw6_asset->dpvs.smodelVisData[2][i] = asset->dpvs.smodelVisData[2][i];
			}

			iw6_asset->dpvs.surfaceVisData[0] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount);
			iw6_asset->dpvs.surfaceVisData[1] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount);
			iw6_asset->dpvs.surfaceVisData[2] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount);
			for (unsigned int i = 0; i < iw6_asset->dpvs.surfaceVisDataCount; i++)
			{
				iw6_asset->dpvs.surfaceVisData[0][i] = asset->dpvs.surfaceVisData[0][i];
				iw6_asset->dpvs.surfaceVisData[1][i] = asset->dpvs.surfaceVisData[1][i];
				iw6_asset->dpvs.surfaceVisData[2][i] = asset->dpvs.surfaceVisData[2][i];
			}

			iw6_asset->dpvs.tessellationCutoffVisData[0] = mem->Alloc<unsigned int>(iw6_asset->dpvs.smodelVisDataCount + 1); // idk if correct?
			iw6_asset->dpvs.tessellationCutoffVisData[1] = mem->Alloc<unsigned int>(iw6_asset->dpvs.smodelVisDataCount + 1);
			iw6_asset->dpvs.tessellationCutoffVisData[2] = mem->Alloc<unsigned int>(iw6_asset->dpvs.smodelVisDataCount + 1);
			/*for (unsigned int i = 0; i < iw6_asset->dpvs.smodelVisDataCount + 1; i++)
			{
				iw6_asset->dpvs.tessellationCutoffVisData[0][i] = 0;
				iw6_asset->dpvs.tessellationCutoffVisData[1][i] = 0;
				iw6_asset->dpvs.tessellationCutoffVisData[2][i] = 0;
			}*/

			iw6_asset->dpvs.unknownData[0] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount); // idk?
			iw6_asset->dpvs.unknownData[1] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount);
			iw6_asset->dpvs.unknownData[2] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount);
			/*for (unsigned int i = 0; i < iw6_asset->dpvs.surfaceVisDataCount; i++)
			{
				iw6_asset->dpvs.unknownData[0][i] = 0;
				iw6_asset->dpvs.unknownData[1][i] = 0;
				iw6_asset->dpvs.unknownData[2][i] = 0;
			}*/

			iw6_asset->dpvs.lodData = mem->Alloc<unsigned int>(iw6_asset->dpvs.smodelCount + 1); // idk?

			iw6_asset->dpvs.unknownData2[0] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount); // tesselationData?
			iw6_asset->dpvs.unknownData2[1] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount);
			iw6_asset->dpvs.unknownData2[2] = mem->Alloc<unsigned int>(iw6_asset->dpvs.surfaceVisDataCount);
			/*for (unsigned int i = 0; i < iw6_asset->dpvs.surfaceVisDataCount; i++)
			{
				iw6_asset->dpvs.unknownData2[0][i] = 0;
				iw6_asset->dpvs.unknownData2[1][i] = 0;
				iw6_asset->dpvs.unknownData2[2][i] = 0;
			}*/

			iw6_asset->dpvs.sortedSurfIndex = mem->Alloc<unsigned int>(iw6_asset->dpvs.staticSurfaceCount);
			for (unsigned int i = 0; i < iw6_asset->dpvs.staticSurfaceCount; i++)
			{
				iw6_asset->dpvs.sortedSurfIndex[i] = asset->dpvs.sortedSurfIndex[i];
			}

			iw6_asset->dpvs.smodelInsts = mem->Alloc<IW6::GfxStaticModelInst>(iw6_asset->dpvs.smodelCount);
			for (unsigned int i = 0; i < iw6_asset->dpvs.smodelCount; i++)
			{
				//iw6_asset->dpvs.smodelInsts[i].bounds.compute(asset->dpvs.smodelInsts[i].mins, asset->dpvs.smodelInsts[i].maxs);
				memcpy(&iw6_asset->dpvs.smodelInsts[i].bounds, &asset->dpvs.smodelInsts[i].mins, sizeof(float[2][3]));
				memcpy(&iw6_asset->dpvs.smodelInsts[i].lightingOrigin, &asset->dpvs.smodelInsts[i].lightingOrigin, sizeof(float[3]));
			}

			iw6_asset->dpvs.surfaces = mem->Alloc<IW6::GfxSurface>(iw6_asset->surfaceCount);
			for (unsigned int i = 0; i < iw6_asset->surfaceCount; i++)
			{
				iw6_asset->dpvs.surfaces[i].tris.vertexLayerData = asset->dpvs.surfaces[i].tris.vertexLayerData;
				iw6_asset->dpvs.surfaces[i].tris.firstVertex = asset->dpvs.surfaces[i].tris.firstVertex;
				iw6_asset->dpvs.surfaces[i].tris.maxEdgeLength = 0;
				iw6_asset->dpvs.surfaces[i].tris.vertexCount = asset->dpvs.surfaces[i].tris.vertexCount;
				iw6_asset->dpvs.surfaces[i].tris.triCount = asset->dpvs.surfaces[i].tris.triCount;
				iw6_asset->dpvs.surfaces[i].tris.baseIndex = asset->dpvs.surfaces[i].tris.baseIndex;
				iw6_asset->dpvs.surfaces[i].material = reinterpret_cast<IW6::Material * __ptr64>(asset->dpvs.surfaces[i].material);
				iw6_asset->dpvs.surfaces[i].laf.fields.lightmapIndex = asset->dpvs.surfaces[i].lightmapIndex;
				iw6_asset->dpvs.surfaces[i].laf.fields.reflectionProbeIndex = asset->dpvs.surfaces[i].reflectionProbeIndex;
				iw6_asset->dpvs.surfaces[i].laf.fields.primaryLightEnvIndex = asset->dpvs.surfaces[i].primaryLightIndex;
				iw6_asset->dpvs.surfaces[i].laf.fields.flags = 1; // not sure if correct
			}

			iw6_asset->dpvs.surfacesBounds = mem->Alloc<IW6::GfxSurfaceBounds>(iw6_asset->surfaceCount);
			for (unsigned int i = 0; i < iw6_asset->surfaceCount; i++)
			{
				memcpy(&iw6_asset->dpvs.surfacesBounds[i].bounds, &asset->dpvs.surfacesBounds[i].bounds, sizeof(IW5::Bounds));
				iw6_asset->dpvs.surfacesBounds[i].flags = 93; // idk
			}

			iw6_asset->dpvs.smodelDrawInsts = mem->Alloc<IW6::GfxStaticModelDrawInst>(iw6_asset->dpvs.smodelCount);
			for (unsigned int i = 0; i < iw6_asset->dpvs.smodelCount; i++)
			{
				memcpy(&iw6_asset->dpvs.smodelDrawInsts[i].placement, &asset->dpvs.smodelDrawInsts[i].placement, sizeof(IW5::GfxPackedPlacement));
				iw6_asset->dpvs.smodelDrawInsts[i].model = reinterpret_cast<IW6::XModel * __ptr64>(asset->dpvs.smodelDrawInsts[i].model);
				iw6_asset->dpvs.smodelDrawInsts[i].groundLighting[0] = asset->dpvs.smodelDrawInsts[i].smodelCacheIndex[0]; // not sure if correct
				iw6_asset->dpvs.smodelDrawInsts[i].groundLighting[1] = asset->dpvs.smodelDrawInsts[i].smodelCacheIndex[1]; // not sure if correct
				iw6_asset->dpvs.smodelDrawInsts[i].groundLighting[2] = asset->dpvs.smodelDrawInsts[i].smodelCacheIndex[2]; // not sure if correct
				iw6_asset->dpvs.smodelDrawInsts[i].groundLighting[3] = asset->dpvs.smodelDrawInsts[i].smodelCacheIndex[3]; // not sure if correct
				memset(&iw6_asset->dpvs.smodelDrawInsts[i].vertexLightingInfo, 0, sizeof(IW6::GfxStaticModelVertexLightingInfo));
				iw6_asset->dpvs.smodelDrawInsts[i].modelLightmapInfo.offset[0] = 0;
				iw6_asset->dpvs.smodelDrawInsts[i].modelLightmapInfo.offset[1] = 0;
				iw6_asset->dpvs.smodelDrawInsts[i].modelLightmapInfo.scale[0] = 0;
				iw6_asset->dpvs.smodelDrawInsts[i].modelLightmapInfo.scale[1] = 0;
				iw6_asset->dpvs.smodelDrawInsts[i].modelLightmapInfo.lightmapIndex = 0;
				iw6_asset->dpvs.smodelDrawInsts[i].lightingHandle = asset->dpvs.smodelDrawInsts[i].lightingHandle;
				iw6_asset->dpvs.smodelDrawInsts[i].cullDist = asset->dpvs.smodelDrawInsts[i].cullDist;
				iw6_asset->dpvs.smodelDrawInsts[i].flags = asset->dpvs.smodelDrawInsts[i].flags;
				iw6_asset->dpvs.smodelDrawInsts[i].staticModelId = 0;
				iw6_asset->dpvs.smodelDrawInsts[i].primaryLightEnvIndex = asset->dpvs.smodelDrawInsts[i].primaryLightIndex;
				iw6_asset->dpvs.smodelDrawInsts[i].reflectionProbeIndex = asset->dpvs.smodelDrawInsts[i].reflectionProbeIndex;
				iw6_asset->dpvs.smodelDrawInsts[i].firstMtlSkinIndex = 0;
				iw6_asset->dpvs.smodelDrawInsts[i].sunShadowFlags = 0;
			}

			iw6_asset->dpvs.surfaceMaterials = mem->Alloc<IW6::GfxDrawSurf>(iw6_asset->surfaceCount);
			for (unsigned int i = 0; i < iw6_asset->surfaceCount; i++)
			{
				iw6_asset->dpvs.surfaceMaterials[i].fields.objectId = asset->dpvs.surfaceMaterials[i].fields.objectId;
				iw6_asset->dpvs.surfaceMaterials[i].fields.reflectionProbeIndex = asset->dpvs.surfaceMaterials[i].fields.reflectionProbeIndex;
				iw6_asset->dpvs.surfaceMaterials[i].fields.hasGfxEntIndex = asset->dpvs.surfaceMaterials[i].fields.hasGfxEntIndex;
				iw6_asset->dpvs.surfaceMaterials[i].fields.customIndex = asset->dpvs.surfaceMaterials[i].fields.customIndex;
				iw6_asset->dpvs.surfaceMaterials[i].fields.materialSortedIndex = asset->dpvs.surfaceMaterials[i].fields.materialSortedIndex;
				iw6_asset->dpvs.surfaceMaterials[i].fields.tessellation = 0;
				iw6_asset->dpvs.surfaceMaterials[i].fields.prepass = asset->dpvs.surfaceMaterials[i].fields.prepass;
				iw6_asset->dpvs.surfaceMaterials[i].fields.useHeroLighting = asset->dpvs.surfaceMaterials[i].fields.useHeroLighting;
				iw6_asset->dpvs.surfaceMaterials[i].fields.sceneLightEnvIndex = asset->dpvs.surfaceMaterials[i].fields.sceneLightIndex;
				iw6_asset->dpvs.surfaceMaterials[i].fields.viewModelRender = asset->dpvs.surfaceMaterials[i].fields.viewModelRender;
				iw6_asset->dpvs.surfaceMaterials[i].fields.surfType = asset->dpvs.surfaceMaterials[i].fields.surfType;
				iw6_asset->dpvs.surfaceMaterials[i].fields.primarySortKey = asset->dpvs.surfaceMaterials[i].fields.primarySortKey;
				iw6_asset->dpvs.surfaceMaterials[i].fields.unused = asset->dpvs.surfaceMaterials[i].fields.unused;
			}

			iw6_asset->dpvs.surfaceCastsSunShadow = reinterpret_cast<unsigned int* __ptr64>(asset->dpvs.surfaceCastsSunShadow);
			iw6_asset->dpvs.sunShadowOptCount = 0;
			iw6_asset->dpvs.sunSurfVisDataCount = 0;
			iw6_asset->dpvs.surfaceCastsSunShadowOpt = nullptr;
			iw6_asset->dpvs.constantBuffersLit = mem->Alloc<char * __ptr64>(iw6_asset->dpvs.smodelCount); //nullptr;
			iw6_asset->dpvs.constantBuffersAmbient = mem->Alloc<char* __ptr64>(iw6_asset->dpvs.smodelCount); //nullptr;
			iw6_asset->dpvs.usageCount = asset->dpvs.usageCount;

			memcpy(&iw6_asset->dpvsDyn.dynEntClientWordCount, &asset->dpvsDyn.dynEntClientWordCount, sizeof(float[2]) * 2);
			iw6_asset->dpvsDyn.dynEntCellBits[0] = reinterpret_cast<unsigned int* __ptr64>(asset->dpvsDyn.dynEntCellBits[0]);
			iw6_asset->dpvsDyn.dynEntCellBits[1] = reinterpret_cast<unsigned int* __ptr64>(asset->dpvsDyn.dynEntCellBits[1]);
			iw6_asset->dpvsDyn.dynEntVisData[0][0] = reinterpret_cast<unsigned __int8* __ptr64>(asset->dpvsDyn.dynEntVisData[0][0]);
			iw6_asset->dpvsDyn.dynEntVisData[0][1] = reinterpret_cast<unsigned __int8* __ptr64>(asset->dpvsDyn.dynEntVisData[0][1]);
			iw6_asset->dpvsDyn.dynEntVisData[0][2] = reinterpret_cast<unsigned __int8* __ptr64>(asset->dpvsDyn.dynEntVisData[0][2]);
			iw6_asset->dpvsDyn.dynEntVisData[1][0] = reinterpret_cast<unsigned __int8* __ptr64>(asset->dpvsDyn.dynEntVisData[1][0]);
			iw6_asset->dpvsDyn.dynEntVisData[1][1] = reinterpret_cast<unsigned __int8* __ptr64>(asset->dpvsDyn.dynEntVisData[1][1]);
			iw6_asset->dpvsDyn.dynEntVisData[1][2] = reinterpret_cast<unsigned __int8* __ptr64>(asset->dpvsDyn.dynEntVisData[1][2]);

			iw6_asset->mapVtxChecksum = asset->mapVtxChecksum;

			iw6_asset->heroOnlyLightCount = asset->heroLightCount;
			iw6_asset->heroOnlyLights = reinterpret_cast<IW6::GfxHeroOnlyLight * __ptr64>(asset->heroLights);

			iw6_asset->fogTypesAllowed = asset->fogTypesAllowed;

			iw6_asset->unknownCount = 0;
			iw6_asset->unknown = nullptr;

			return iw6_asset;
		}

		void IGfxWorld::dump(GfxWorld* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::GfxWorld) == 2608);

			// generate iw6 gfxworld
			auto iw6_asset = GenerateIW6GfxWorld(asset, mem);

			// dump iw6 gfxworld
			IW6::IGfxWorld::dump(iw6_asset);
		}
	}
}