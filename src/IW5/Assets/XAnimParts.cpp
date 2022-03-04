#include "stdafx.hpp"
#include "IW6/Assets/XAnimParts.hpp"

namespace ZoneTool
{
	namespace IW5
	{
		IW6::XAnimParts* GenerateIW6XAnimParts(XAnimParts* asset, ZoneMemory* mem)
		{
			// allocate IW6 XAnimParts structure
			const auto iw6_asset = mem->Alloc<IW6::XAnimParts>();

			iw6_asset->name = asset->name;
			iw6_asset->dataByteCount = asset->dataByteCount;
			iw6_asset->dataShortCount = asset->dataShortCount;
			iw6_asset->dataIntCount = asset->dataIntCount;
			iw6_asset->randomDataByteCount = asset->randomDataByteCount;
			iw6_asset->randomDataIntCount = asset->randomDataIntCount;
			iw6_asset->numframes = asset->framecount;
			iw6_asset->flags = asset->flags;
			memcpy(&iw6_asset->boneCount, &asset->boneCount, sizeof(asset->boneCount));
			iw6_asset->notifyCount = asset->notetrackCount;
			iw6_asset->assetType = asset->assetType;
			iw6_asset->ikType = asset->ikType;
			iw6_asset->randomDataShortCount = asset->randomDataShortCount;
			iw6_asset->indexCount = asset->indexcount;
			iw6_asset->framerate = asset->framerate;
			iw6_asset->frequency = asset->frequency;
			iw6_asset->names = mem->Alloc<IW6::scr_string_t>(iw6_asset->boneCount[9]);
			for (auto i = 0; i < asset->boneCount[9]; i++)
			{
				iw6_asset->names[i] = static_cast<IW6::scr_string_t>(asset->tagnames[i]);
			}
			iw6_asset->dataByte = reinterpret_cast<char* __ptr64>(asset->dataByte);
			iw6_asset->dataShort = reinterpret_cast<short* __ptr64>(asset->dataShort);
			iw6_asset->dataInt = reinterpret_cast<int* __ptr64>(asset->dataInt);
			iw6_asset->randomDataShort = reinterpret_cast<short* __ptr64>(asset->randomDataShort);
			iw6_asset->randomDataByte = reinterpret_cast<unsigned char* __ptr64>(asset->randomDataByte);
			iw6_asset->randomDataInt = reinterpret_cast<int* __ptr64>(asset->randomDataInt);

			iw6_asset->indices.data = reinterpret_cast<void*>(asset->indices.data);

			iw6_asset->notify = mem->Alloc<IW6::XAnimNotifyInfo>(iw6_asset->notifyCount);
			for (auto i = 0; i < asset->notetrackCount; i++)
			{
				iw6_asset->notify[i].name = static_cast<IW6::scr_string_t>(asset->notetracks[i].name);
				iw6_asset->notify[i].time = asset->notetracks[i].time;
			}

			if (asset->delta)
			{
				iw6_asset->deltaPart = mem->Alloc<IW6::XAnimDeltaPart>();
				if (asset->delta->trans)
				{
					auto extra_size = 0;

					if (asset->delta->trans->size)
					{
						if (asset->framecount >= 256)
						{
							extra_size += (asset->delta->trans->size * 2) + 2;
						}
						else
						{
							extra_size += asset->delta->trans->size + 1;
						}
					}

					iw6_asset->deltaPart->trans = mem->ManualAlloc<IW6::XAnimPartTrans>(sizeof(IW6::XAnimPartTrans) + extra_size);

					iw6_asset->deltaPart->trans->size = asset->delta->trans->size;
					iw6_asset->deltaPart->trans->smallTrans = static_cast<unsigned short>(asset->delta->trans->smallTrans);

					if (asset->delta->trans->size)
					{
						for (auto i = 0; i < 3; i++)
						{
							iw6_asset->deltaPart->trans->u.frames.mins[i] = asset->delta->trans->u.frames.mins[i];
							iw6_asset->deltaPart->trans->u.frames.size[i] = asset->delta->trans->u.frames.size[i];
						}
						if (asset->framecount >= 256)
						{
							for (auto i = 0; i < asset->delta->trans->size + 1; i++)
							{
								iw6_asset->deltaPart->trans->u.frames.indices._2[i] = asset->delta->trans->u.frames.indices._2[i];
							}
						}
						else
						{
							for (auto i = 0; i < asset->delta->trans->size + 1; i++)
							{
								iw6_asset->deltaPart->trans->u.frames.indices._1[i] = static_cast<unsigned char>(asset->delta->trans->u.frames.indices._1[i]);
							}
						}
						if (asset->delta->trans->u.frames.frames._1)
						{
							if (asset->delta->trans->smallTrans)
							{
								iw6_asset->deltaPart->trans->u.frames.frames._1 = mem->Alloc<unsigned char[3]>(asset->delta->trans->size + 1);
								for (auto i = 0; i < asset->delta->trans->size + 1; i++)
								{
									iw6_asset->deltaPart->trans->u.frames.frames._1[i][0] = static_cast<unsigned char>(asset->delta->trans->u.frames.frames._1[i][0]);
									iw6_asset->deltaPart->trans->u.frames.frames._1[i][1] = static_cast<unsigned char>(asset->delta->trans->u.frames.frames._1[i][1]);
									iw6_asset->deltaPart->trans->u.frames.frames._1[i][2] = static_cast<unsigned char>(asset->delta->trans->u.frames.frames._1[i][2]);
								}
							}
							else
							{
								iw6_asset->deltaPart->trans->u.frames.frames._2 = mem->Alloc<unsigned short[3]>(asset->delta->trans->size + 1);
								for (auto i = 0; i < asset->delta->trans->size + 1; i++)
								{
									iw6_asset->deltaPart->trans->u.frames.frames._2[i][0] = asset->delta->trans->u.frames.frames._2[i][0];
									iw6_asset->deltaPart->trans->u.frames.frames._2[i][1] = asset->delta->trans->u.frames.frames._2[i][1];
									iw6_asset->deltaPart->trans->u.frames.frames._2[i][2] = asset->delta->trans->u.frames.frames._2[i][2];
								}
							}
						}
					}
					else
					{
						for (auto i = 0; i < 3; i++)
						{
							iw6_asset->deltaPart->trans->u.frame0[i] = asset->delta->trans->u.frame0[i];
						}
					}
				}

				if (asset->delta->quat)
				{
					auto extra_size = 0;

					if (asset->delta->quat->size)
					{
						if (asset->framecount >= 256)
						{
							extra_size += (asset->delta->quat->size * 2) + 2;
						}
						else
						{
							extra_size += asset->delta->quat->size + 1;
						}
					}
					else
					{
						// quat data contains 4 extra bytes
						extra_size += 4;
					}

					iw6_asset->deltaPart->quat = mem->ManualAlloc<IW6::XAnimDeltaPartQuat>(sizeof(IW6::XAnimDeltaPartQuat) + extra_size);
					iw6_asset->deltaPart->quat->size = asset->delta->quat->size;

					if (asset->delta->quat->size)
					{
						if (asset->framecount >= 256)
						{
							for (auto i = 0; i < asset->delta->quat->size + 1; i++)
							{
								iw6_asset->deltaPart->quat->u.frames.indices._2[i] = asset->delta->quat->u.frames.indices._2[i];
							}
						}
						else
						{
							for (auto i = 0; i < asset->delta->quat->size + 1; i++)
							{
								iw6_asset->deltaPart->quat->u.frames.indices._1[i] = static_cast<unsigned char>(asset->delta->quat->u.frames.indices._1[i]);
							}
						}
						if (asset->delta->quat->u.frames.frames)
						{
							iw6_asset->deltaPart->quat->u.frames.frames = mem->Alloc<short[4]>(asset->delta->quat->size + 1);
							for (auto i = 0; i < asset->delta->quat->size + 1; i++)
							{
								iw6_asset->deltaPart->quat->u.frames.frames[i][0] = asset->delta->quat->u.frames.frames[i][0];
								iw6_asset->deltaPart->quat->u.frames.frames[i][1] = asset->delta->quat->u.frames.frames[i][1];
							}
						}
					}
					else
					{
						for (auto i = 0; i < 2; i++)
						{
							iw6_asset->deltaPart->quat->u.frame0[i] = asset->delta->quat->u.frame0[i];
						}
					}
				}
			}

			return iw6_asset;
		}

		void IXAnimParts::dump(XAnimParts* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::XAnimParts) == 136);

			// generate iw6 model
			auto iw6_asset = GenerateIW6XAnimParts(asset, mem);

			// dump iw6 model
			IW6::IXAnimParts::dump(iw6_asset, SL_ConvertToString);
		}
	}
}