#include "stdafx.hpp"

#include "Json.hpp"
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace ZoneTool
{
	namespace IW6
	{
		void IMapEnts::dump_splineList(const std::string& name, SplineRecordList* splineList)
		{
			AssetDumper dumper;
			if (dumper.open(name + ".ents.splineList"s))
			{
				dumper.dump_int(splineList->splineCount);
				dumper.dump_array(splineList->splines, splineList->splineCount);
				for (unsigned short i = 0; i < splineList->splineCount; i++)
				{
					dumper.dump_array(splineList->splines[i].splinePoints, splineList->splines[i].splinePointCount);
					for (unsigned short j = 0; j < splineList->splines[i].splinePointCount; j++)
					{
						dumper.dump_array(splineList->splines[i].splinePoints[j].splineNodeLabel, 64);
						dumper.dump_array(splineList->splines[i].splinePoints[j].positionCubic, 4);
						dumper.dump_array(splineList->splines[i].splinePoints[j].tangentQuadratic, 3);
					}
				}
			}
		}

		void IMapEnts::dump_spawnList(const std::string& name, SpawnPointRecordList* spawnList, const std::function<const char* (std::uint16_t)>& SL_ConvertToString)
		{
			auto fp = FileSystem::FileOpen(name + ".ents.spawnList"s, "wb");

			if (!fp)
			{
				return;
			}

			ordered_json data;

			for (unsigned short i = 0; i < spawnList->spawnsCount; i++)
			{
				data[i]["name"] = SL_ConvertToString(spawnList->spawns[i].name);
				data[i]["target"] = SL_ConvertToString(spawnList->spawns[i].target);
				data[i]["script_noteworthy"] = SL_ConvertToString(spawnList->spawns[i].script_noteworthy);
				for (auto j = 0; j < 3; j++)
				{
					data[i]["origin"][j] = spawnList->spawns[i].origin[j];
					data[i]["angles"][j] = spawnList->spawns[i].angles[j];
				}
			}

			const auto json = data.dump(4);
			fwrite(json.data(), json.size(), 1, fp);

			FileSystem::FileClose(fp);
		}

		void IMapEnts::dump_clientBlendTriggers(const std::string& name, ClientTriggerBlend* clientTriggerBlend)
		{
			AssetDumper dumper;
			if (dumper.open(name + ".ents.clientBlendTriggers"s))
			{
				dumper.dump_int(clientTriggerBlend->numClientTriggerBlendNodes);
				dumper.dump_array(clientTriggerBlend->blendNodes, clientTriggerBlend->numClientTriggerBlendNodes);
			}
		}

		void IMapEnts::dump_clientTriggers(const std::string& name, ClientTriggers* clientTrigger)
		{
			AssetDumper dumper;
			if (dumper.open(name + ".ents.clientTriggers"))
			{
				dumper.dump_single(clientTrigger);

				dumper.dump_array<TriggerModel>(clientTrigger->trigger.models, clientTrigger->trigger.count);
				dumper.dump_array<TriggerHull>(clientTrigger->trigger.hulls, clientTrigger->trigger.hullCount);
				dumper.dump_array<TriggerSlab>(clientTrigger->trigger.slabs, clientTrigger->trigger.slabCount);

				dumper.dump_array(clientTrigger->clientTriggerAabbTree, clientTrigger->numClientTriggerNodes);
				dumper.dump_array(clientTrigger->triggerString, clientTrigger->triggerStringLength);
				dumper.dump_array(clientTrigger->visionSetTriggers, clientTrigger->trigger.count);
				dumper.dump_array(clientTrigger->triggerType, clientTrigger->trigger.count);
				dumper.dump_array(clientTrigger->origins, clientTrigger->trigger.count * 3);
				dumper.dump_array(clientTrigger->scriptDelay, clientTrigger->trigger.count);
				dumper.dump_array(clientTrigger->audioTriggers, clientTrigger->trigger.count);
				dumper.dump_array(clientTrigger->blendLookup, clientTrigger->trigger.count);
				dumper.dump_array(clientTrigger->npcTriggers, clientTrigger->trigger.count);
			}
		}

		void IMapEnts::dump_triggers(const std::string& name, MapTriggers* trigger)
		{
			AssetDumper trigger_dumper;
			if (trigger_dumper.open(name + ".ents.triggers"s))
			{
				trigger_dumper.dump_int(trigger->count);
				trigger_dumper.dump_array<TriggerModel>(trigger->models, trigger->count);

				trigger_dumper.dump_int(trigger->hullCount);
				trigger_dumper.dump_array<TriggerHull>(trigger->hulls, trigger->hullCount);

				trigger_dumper.dump_int(trigger->slabCount);
				trigger_dumper.dump_array<TriggerSlab>(trigger->slabs, trigger->slabCount);

				trigger_dumper.close();
			}
		}

		void IMapEnts::dump_entityStrings(const std::string& name, char* entityString, int numEntityChars)
		{
			auto fp = FileSystem::FileOpen(name + ".ents"s, "wb");
			if (fp)
			{
				fwrite(entityString, numEntityChars ? numEntityChars - 1 : 0, 1, fp);
				FileSystem::FileClose(fp);
			}
		}

		void IMapEnts::dump(MapEnts* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString)
		{
			dump_entityStrings(asset->name, asset->entityString, asset->numEntityChars);
			dump_triggers(asset->name, &asset->trigger);
			dump_clientTriggers(asset->name, &asset->clientTrigger);
			dump_clientBlendTriggers(asset->name, &asset->clientTriggerBlend);
			dump_spawnList(asset->name, &asset->spawnList, SL_ConvertToString);
			dump_splineList(asset->name, &asset->splineList);
		}
	}
}