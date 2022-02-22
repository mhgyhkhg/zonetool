#include "stdafx.hpp"
#include "IW6/Assets/FxWorld.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		IW6::FxWorld* GenerateIW6FxWorld(FxWorld* asset, ZoneMemory* mem)
		{
			// allocate IW6 FxWorld structure
			const auto iw6_asset = mem->Alloc<IW6::FxWorld>();

			iw6_asset->name = asset->name;

			iw6_asset->glassSys.time = asset->glassSys.time;
			iw6_asset->glassSys.prevTime = asset->glassSys.prevTime;
			iw6_asset->glassSys.defCount = asset->glassSys.defCount;
			iw6_asset->glassSys.pieceLimit = asset->glassSys.pieceLimit;
			iw6_asset->glassSys.pieceWordCount = asset->glassSys.pieceWordCount;
			iw6_asset->glassSys.initPieceCount = asset->glassSys.initPieceCount;
			iw6_asset->glassSys.cellCount = asset->glassSys.cellCount;
			iw6_asset->glassSys.activePieceCount = asset->glassSys.activePieceCount;
			iw6_asset->glassSys.firstFreePiece = asset->glassSys.firstFreePiece;
			iw6_asset->glassSys.geoDataLimit = asset->glassSys.geoDataLimit;
			iw6_asset->glassSys.geoDataCount = asset->glassSys.geoDataCount;
			iw6_asset->glassSys.initGeoDataCount = asset->glassSys.initGeoDataCount;

			iw6_asset->glassSys.defs = mem->Alloc<IW6::FxGlassDef>(iw6_asset->glassSys.defCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.defCount; i++)
			{
				iw6_asset->glassSys.defs[i].halfThickness = asset->glassSys.defs[i].halfThickness;
				memcpy(&iw6_asset->glassSys.defs[i].texVecs, &asset->glassSys.defs[i].texVecs, sizeof(float[2][2]));
				iw6_asset->glassSys.defs[i].color.packed = asset->glassSys.defs[i].color.packed;
				iw6_asset->glassSys.defs[i].material = reinterpret_cast<IW6::Material*>(asset->glassSys.defs[i].material);
				iw6_asset->glassSys.defs[i].materialShattered = reinterpret_cast<IW6::Material*>(asset->glassSys.defs[i].materialShattered);
				iw6_asset->glassSys.defs[i].physPreset = reinterpret_cast<IW6::PhysPreset*>(asset->glassSys.defs[i].physPreset);

				iw6_asset->glassSys.defs[i].pieceBreakEffect = nullptr;
				iw6_asset->glassSys.defs[i].shatterEffect = nullptr;
				iw6_asset->glassSys.defs[i].shatterSmallEffect = nullptr;
				iw6_asset->glassSys.defs[i].crackDecalEffect = nullptr;
				iw6_asset->glassSys.defs[i].damagedSound = nullptr;
				iw6_asset->glassSys.defs[i].destroyedSound = nullptr;
				iw6_asset->glassSys.defs[i].destroyedQuietSound = nullptr;
				iw6_asset->glassSys.defs[i].numCrackRings = 0;
				iw6_asset->glassSys.defs[i].isOpaque = 0;
			}

			iw6_asset->glassSys.piecePlaces = mem->Alloc<IW6::FxGlassPiecePlace>(iw6_asset->glassSys.pieceLimit);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceLimit; i++)
			{
				memcpy(&iw6_asset->glassSys.piecePlaces[i], &asset->glassSys.piecePlaces[i], sizeof(IW5::FxGlassPiecePlace));
			}

			iw6_asset->glassSys.pieceDynamics = mem->Alloc<IW6::FxGlassPieceDynamics>(iw6_asset->glassSys.pieceLimit);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceLimit; i++)
			{
				iw6_asset->glassSys.pieceDynamics[i].fallTime = asset->glassSys.pieceDynamics[i].fallTime;
				iw6_asset->glassSys.pieceDynamics[i].physObjId = asset->glassSys.pieceDynamics[i].physObjId;
				iw6_asset->glassSys.pieceDynamics[i].physJointId = asset->glassSys.pieceDynamics[i].physJointId;
				memcpy(&iw6_asset->glassSys.pieceDynamics[i].vel, &asset->glassSys.pieceDynamics[i].vel, sizeof(float[3]));
				memcpy(&iw6_asset->glassSys.pieceDynamics[i].avel, &asset->glassSys.pieceDynamics[i].avel, sizeof(float[3]));
			}

			iw6_asset->glassSys.geoData = mem->Alloc<IW6::FxGlassGeometryData>(iw6_asset->glassSys.geoDataLimit);
			for (unsigned int i = 0; i < iw6_asset->glassSys.geoDataLimit; i++)
			{
				memcpy(&iw6_asset->glassSys.geoData[i], &asset->glassSys.geoData[i], sizeof(IW5::FxGlassGeometryData));
			}

			iw6_asset->glassSys.isInUse = mem->Alloc<unsigned int>(iw6_asset->glassSys.pieceWordCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceWordCount; i++)
			{
				iw6_asset->glassSys.isInUse[i] = asset->glassSys.isInUse[i];
			}

			iw6_asset->glassSys.cellBits = mem->Alloc<unsigned int>(iw6_asset->glassSys.pieceWordCount * iw6_asset->glassSys.cellCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.pieceWordCount * iw6_asset->glassSys.cellCount; i++)
			{
				iw6_asset->glassSys.cellBits[i] = asset->glassSys.cellBits[i];
			}

			iw6_asset->glassSys.visData = mem->Alloc<unsigned char>((iw6_asset->glassSys.pieceLimit + 15) & 0xFFFFFFF0);
			for (unsigned int i = 0; i < ((iw6_asset->glassSys.pieceLimit + 15) & 0xFFFFFFF0); i++)
			{
				iw6_asset->glassSys.visData[i] = asset->glassSys.visData[i];
			}
			
			iw6_asset->glassSys.linkOrg = reinterpret_cast<IW6::VecInternal<3>*>(asset->glassSys.linkOrg);


			iw6_asset->glassSys.halfThickness = mem->Alloc<float>((iw6_asset->glassSys.pieceLimit + 3) & 0xFFFFFFFC);
			for (unsigned int i = 0; i < ((iw6_asset->glassSys.pieceLimit + 3) & 0xFFFFFFFC); i++)
			{
				iw6_asset->glassSys.halfThickness[i] = asset->glassSys.halfThickness[i];
			}
			
			iw6_asset->glassSys.lightingHandles = mem->Alloc<unsigned short>(iw6_asset->glassSys.initPieceCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.initPieceCount; i++)
			{
				iw6_asset->glassSys.lightingHandles[i] = asset->glassSys.lightingHandles[i];
			}

			iw6_asset->glassSys.initPieceStates = mem->Alloc<IW6::FxGlassInitPieceState>(iw6_asset->glassSys.initPieceCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.initPieceCount; i++)
			{
				// iw5 struct maybe wrong
				memcpy(&iw6_asset->glassSys.initPieceStates[i].frame, &asset->glassSys.initPieceStates[i].frame, sizeof(IW5::FxSpatialFrame));
				iw6_asset->glassSys.initPieceStates[i].radius = asset->glassSys.initPieceStates[i].radius;
				iw6_asset->glassSys.initPieceStates[i].texCoordOrigin[0] = asset->glassSys.initPieceStates[i].texCoordOrigin[0];
				iw6_asset->glassSys.initPieceStates[i].texCoordOrigin[1] = asset->glassSys.initPieceStates[i].texCoordOrigin[1];
				iw6_asset->glassSys.initPieceStates[i].supportMask = asset->glassSys.initPieceStates[i].supportMask;
				iw6_asset->glassSys.initPieceStates[i].areaX2 = 0;
				iw6_asset->glassSys.initPieceStates[i].lightingIndex = asset->glassSys.initPieceStates[i].lightingIndex;
				iw6_asset->glassSys.initPieceStates[i].defIndex = asset->glassSys.initPieceStates[i].defIndex;
				iw6_asset->glassSys.initPieceStates[i].vertCount = asset->glassSys.initPieceStates[i].vertCount;
				iw6_asset->glassSys.initPieceStates[i].fanDataCount = asset->glassSys.initPieceStates[i].fanDataCount;
			}

			iw6_asset->glassSys.initGeoData = mem->Alloc<IW6::FxGlassGeometryData>(iw6_asset->glassSys.initGeoDataCount);
			for (unsigned int i = 0; i < iw6_asset->glassSys.initGeoDataCount; i++)
			{
				memcpy(&iw6_asset->glassSys.initGeoData[i], &asset->glassSys.initGeoData[i], sizeof(IW5::FxGlassGeometryData));
			}

			iw6_asset->glassSys.needToCompactData = asset->glassSys.needToCompactData;
			iw6_asset->glassSys.initCount = asset->glassSys.initCount;
			iw6_asset->glassSys.effectChanceAccum = asset->glassSys.effectChanceAccum;
			iw6_asset->glassSys.lastPieceDeletionTime = asset->glassSys.lastPieceDeletionTime;

			return iw6_asset;
		}

		void IFxWorld::dump(FxWorld* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::FxWorld) == 176);

			// generate iw6 fxworld
			auto iw6_asset = GenerateIW6FxWorld(asset, mem);

			// dump iw6 glassworld
			IW6::IFxWorld::dump(iw6_asset);
		}
	}
}