#include "stdafx.hpp"
#include "IW6/Assets/MapEnts.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		IW6::MapEnts* GenerateIW6MapEnts(MapEnts* asset, ZoneMemory* mem)
		{
			// allocate IW6 GlassWorld structure
			const auto iw6_asset = mem->Alloc<IW6::MapEnts>();

			iw6_asset->name = asset->name;

			// TODO: fixup these from iw5->iw6
			iw6_asset->entityString = asset->entityString;
			iw6_asset->numEntityChars = asset->numEntityChars;

			iw6_asset->trigger.count = asset->trigger.modelCount;
			iw6_asset->trigger.models = reinterpret_cast<IW6::TriggerModel*>(asset->trigger.models);
			iw6_asset->trigger.hullCount = asset->trigger.hullCount;
			iw6_asset->trigger.hulls = reinterpret_cast<IW6::TriggerHull*>(asset->trigger.hulls);
			iw6_asset->trigger.slabCount = asset->trigger.slabCount;
			iw6_asset->trigger.slabs = reinterpret_cast<IW6::TriggerSlab*>(asset->trigger.slabs);

			iw6_asset->clientTrigger.trigger.count = asset->clientTrigger.trigger.modelCount;
			iw6_asset->clientTrigger.trigger.models = reinterpret_cast<IW6::TriggerModel*>(asset->clientTrigger.trigger.models);
			iw6_asset->clientTrigger.trigger.hullCount = asset->clientTrigger.trigger.hullCount;
			iw6_asset->clientTrigger.trigger.hulls = reinterpret_cast<IW6::TriggerHull*>(asset->clientTrigger.trigger.hulls);
			iw6_asset->clientTrigger.trigger.slabCount = asset->clientTrigger.trigger.slabCount;
			iw6_asset->clientTrigger.trigger.slabs = reinterpret_cast<IW6::TriggerSlab*>(asset->clientTrigger.trigger.slabs);
			iw6_asset->clientTrigger.numClientTriggerNodes = asset->clientTrigger.numClientTriggerNodes;
			iw6_asset->clientTrigger.clientTriggerAabbTree = reinterpret_cast<IW6::ClientTriggerAabbNode*>(asset->clientTrigger.clientTriggerAabbTree);
			iw6_asset->clientTrigger.triggerStringLength = asset->clientTrigger.triggerStringLength;
			iw6_asset->clientTrigger.triggerString = asset->clientTrigger.triggerString;
			iw6_asset->clientTrigger.visionSetTriggers = asset->clientTrigger.visionSetTriggers;
			iw6_asset->clientTrigger.triggerType = asset->clientTrigger.triggerType;
			iw6_asset->clientTrigger.origins = reinterpret_cast<float(*__ptr64)[3]>(asset->clientTrigger.origins);
			iw6_asset->clientTrigger.scriptDelay = asset->clientTrigger.scriptDelay;
			iw6_asset->clientTrigger.audioTriggers = asset->clientTrigger.audioTriggers;
			iw6_asset->clientTrigger.blendLookup = nullptr;
			iw6_asset->clientTrigger.npcTriggers = nullptr;

			iw6_asset->clientTriggerBlend.numClientTriggerBlendNodes = 0;
			iw6_asset->clientTriggerBlend.blendNodes = nullptr;

			// TODO: maybe add spawns in this instead of entityStrings?
			iw6_asset->spawnList.spawnsCount = 0;
			iw6_asset->spawnList.spawns = nullptr;

			iw6_asset->splineList.splineCount = 0;
			iw6_asset->splineList.splines = nullptr;

			return iw6_asset;
		}

		void IMapEnts::dump(MapEnts* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::MapEnts) == 256);

			// generate iw6 mapents
			auto iw6_asset = GenerateIW6MapEnts(asset, mem);

			// dump iw6 glassworld
			IW6::IMapEnts::dump(iw6_asset, SL_ConvertToString);
		}
	}
}