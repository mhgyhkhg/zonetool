#include "stdafx.hpp"
#include "../Include.hpp"

#include "PathData.hpp"

namespace ZoneTool::IW5
{
	namespace S1Converter
	{
		namespace
		{
			std::unordered_map<std::uint16_t, std::uint16_t> node_type_map =
			{
				{NODE_ERROR, S1::NODE_ERROR},
				{NODE_PATHNODE, S1::NODE_PATHNODE},
				{NODE_COVER_STAND, S1::NODE_COVER_STAND},
				{NODE_COVER_CROUCH, S1::NODE_COVER_CROUCH},
				{NODE_COVER_CROUCH_WINDOW, S1::NODE_COVER_CROUCH_WINDOW},
				{NODE_COVER_PRONE, S1::NODE_COVER_PRONE},
				{NODE_COVER_RIGHT, S1::NODE_COVER_RIGHT},
				{NODE_COVER_LEFT, S1::NODE_COVER_LEFT},
				{NODE_AMBUSH, S1::NODE_AMBUSH},
				{NODE_EXPOSED, S1::NODE_EXPOSED},
				{NODE_CONCEALMENT_STAND, S1::NODE_CONCEALMENT_STAND},
				{NODE_CONCEALMENT_CROUCH, S1::NODE_CONCEALMENT_CROUCH},
				{NODE_CONCEALMENT_PRONE, S1::NODE_CONCEALMENT_PRONE},
				{NODE_DOOR, S1::NODE_DOOR},
				{NODE_DOOR_INTERIOR, S1::NODE_DOOR_INTERIOR},
				{NODE_SCRIPTED, S1::NODE_SCRIPTED},
				{NODE_NEGOTIATION_BEGIN, S1::NODE_NEGOTIATION_BEGIN},
				{NODE_NEGOTIATION_END, S1::NODE_NEGOTIATION_END},
				{NODE_TURRET, S1::NODE_TURRET},
				{NODE_GUARD, S1::NODE_GUARD},
				{NODE_DONTLINK, S1::NODE_DONTLINK},
			};

			std::uint16_t convert_node_type(const std::uint16_t type)
			{
				const auto iter = node_type_map.find(type);
				if (iter == node_type_map.end())
				{
					ZONETOOL_ERROR("Invalid iw5 to s1 node type %i", type);
				}

				return iter->second;
			}

			S1::pathnode_tree_t* convert_node_tree(S1::PathData* asset, pathnode_tree_t* node)
			{
				const auto h1_node = &asset->nodeTree[asset->nodeTreeCount++];
				h1_node->axis = node->axis;
				h1_node->dist = node->dist;

				if (node->axis < 0)
				{
					h1_node->u.s.nodeCount = node->u.s.nodeCount;
					h1_node->u.s.nodes = node->u.s.nodes;
				}
				else
				{
					for (auto i = 0; i < 2; i++)
					{
						h1_node->u.child[i] = convert_node_tree(asset, node->u.child[i]);
					}
				}

				return h1_node;
			}
		}

		S1::PathData* GenerateS1PathData(PathData* asset, allocator& mem)
		{
			const auto s1_asset = mem.allocate<S1::PathData>();

			s1_asset->name = asset->name;
			s1_asset->nodeCount = asset->nodeCount;
			s1_asset->nodes = mem.allocate<S1::pathnode_t>(s1_asset->nodeCount);

			for (auto i = 0u; i < s1_asset->nodeCount; i++)
			{
				auto target = &s1_asset->nodes[i].constant;
				auto source = &asset->nodes[i].constant;

				target->type = convert_node_type(source->type);
				target->spawnflags = source->spawnflags;
				target->targetname = source->targetname;
				target->script_linkName = source->script_linkName;
				target->script_noteworthy = source->script_noteworthy;
				target->target = source->target;
				target->animscript = source->animscript;
				target->animscriptfunc = source->animscriptfunc;
				std::memcpy(&target->vLocalOrigin, source->vOrigin, sizeof(float[3]));
				target->___u9.yaw_orient.fLocalAngle = source->fAngle;
				std::memcpy(&target->___u9.yaw_orient.localForward, &source->forward, sizeof(float[2]));
				target->___u11.minUseDistSq = source->___u12.minUseDistSq;
				target->___u11.error = static_cast<S1::PathNodeErrorCode>(source->___u12.error);
				std::memcpy(&target->wOverlapNode, &source->wOverlapNode, sizeof(std::uint16_t[2]));
				target->totalLinkCount = source->totalLinkCount;
				target->Links = mem.allocate<S1::pathlink_s>(target->totalLinkCount);

				for (auto o = 0u; o < target->totalLinkCount; o++)
				{
					std::memcpy(&target->Links[o], &source->Links[o], sizeof(pathlink_s));
				}
			}

			s1_asset->visBytes = asset->visBytes;
			s1_asset->pathVis = asset->pathVis;

			s1_asset->nodeTreeCount = 0;
			s1_asset->nodeTree = mem.allocate<S1::pathnode_tree_t>(asset->nodeTreeCount);
			s1_asset->nodeTree = convert_node_tree(s1_asset, asset->nodeTree);

			return s1_asset;
		}

		S1::PathData* convert(PathData* asset, allocator& allocator)
		{
			return GenerateS1PathData(asset, allocator);
		}
	}
}
