// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "IW6/Structs.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		void dump(XAnimParts* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString)
		{
			assert(sizeof(IW6::XAnimParts) == 136);

			const auto path = "XAnim\\"s + asset->name + ".xae3";

			AssetDumper dump;
			if (!dump.open(path))
			{
				return;
			}

			dump.dump_single(asset);
			dump.dump_string(asset->name);

			if (asset->names)
			{
				for (auto bone = 0; bone < asset->boneCount[9]; bone++)
				{
					dump.dump_string(SL_ConvertToString(asset->names[bone]));
				}
			}

			if (asset->dataByte)
			{
				dump.dump_array(asset->dataByte, asset->dataByteCount);
			}
			if (asset->dataShort)
			{
				dump.dump_array(asset->dataShort, asset->dataShortCount);
			}
			if (asset->dataInt)
			{
				dump.dump_array(asset->dataInt, asset->dataIntCount);
			}
			if (asset->randomDataShort)
			{
				dump.dump_array(asset->randomDataShort, asset->randomDataShortCount);
			}
			if (asset->randomDataByte)
			{
				dump.dump_array(asset->randomDataByte, asset->randomDataByteCount);
			}
			if (asset->randomDataInt)
			{
				dump.dump_array(asset->randomDataInt, asset->randomDataIntCount);
			}

			if (asset->indices.data)
			{
				if (asset->numframes >= 256)
				{
					dump.dump_array(asset->indices._2, asset->indexCount);
				}
				else
				{
					dump.dump_array(asset->indices._1, asset->indexCount);
				}
			}

			if (asset->notify)
			{
				dump.dump_array(asset->notify, asset->notifyCount);

				for (auto i = 0; i < asset->notifyCount; i++)
				{
					dump.dump_string(SL_ConvertToString(asset->notify[i].name));
				}
			}

			if (asset->deltaPart)
			{
				dump.dump_single(asset->deltaPart);

				if (asset->deltaPart->trans)
				{
					auto extra_size = 0;

					if (asset->deltaPart->trans->size)
					{
						if (asset->numframes >= 256)
						{
							extra_size += (asset->deltaPart->trans->size * 2) + 2;
						}
						else
						{
							extra_size += asset->deltaPart->trans->size + 1;
						}
					}

					dump.dump_raw(asset->deltaPart->trans, sizeof(XAnimPartTrans) + extra_size);

					if (asset->deltaPart->trans->size)
					{
						if (asset->deltaPart->trans->u.frames.frames._1)
						{
							if (asset->deltaPart->trans->smallTrans)
							{
								dump.dump_raw(asset->deltaPart->trans->u.frames.frames._1, (3 * asset->deltaPart->trans->size) + 3);
							}
							else
							{
								dump.dump_raw(asset->deltaPart->trans->u.frames.frames._2, (6 * asset->deltaPart->trans->size) + 6);
							}
						}
					}
				}

				if (asset->deltaPart->quat2)
				{
					auto extra_size = 0;

					if (asset->deltaPart->quat2->size)
					{
						if (asset->numframes >= 256)
						{
							extra_size += (asset->deltaPart->quat2->size * 2) + 2;
						}
						else
						{
							extra_size += asset->deltaPart->quat2->size + 1;
						}
					}
					else
					{
						// no extra size required, quat2 data fits inside the frame0 buffer
						extra_size += 0;
					}

					dump.dump_raw(asset->deltaPart->quat2, sizeof(XAnimDeltaPartQuat2) + extra_size);

					if (asset->deltaPart->quat2->size && asset->deltaPart->quat2->u.frames.frames)
					{
						dump.dump_raw(asset->deltaPart->quat2->u.frames.frames, (asset->deltaPart->quat2->size * 4) + 4);
					}
				}

				if (asset->deltaPart->quat)
				{
					auto extra_size = 0;

					if (asset->deltaPart->quat->size)
					{
						if (asset->numframes >= 256)
						{
							extra_size += (asset->deltaPart->quat->size * 2) + 2;
						}
						else
						{
							extra_size += asset->deltaPart->quat->size + 1;
						}
					}
					else
					{
						// quat data contains 4 extra bytes
						extra_size += 4;
					}

					dump.dump_raw(asset->deltaPart->quat, sizeof(XAnimDeltaPartQuat) + extra_size);

					if (asset->deltaPart->quat->size && asset->deltaPart->quat->u.frames.frames)
					{
						dump.dump_raw(asset->deltaPart->quat->u.frames.frames, (asset->deltaPart->quat->size * 8) + 8);
					}
				}
			}

			dump.close();
		}
	}

	namespace IW3
	{
		void IXAnimParts::dump(XAnimParts* anim, ZoneMemory* mem)
		{
			if (anim)
			{
				auto asset = mem->Alloc<IW6::XAnimParts>();

#define XAE_CopyElement(name) asset->name = anim->name
#define XAE_CopyElementRename(name, rename) asset->rename = anim->name
#define XAE_CopyElementStaticCast(name, __cast__) asset->name = static_cast<__cast__>(anim->name)
#define XAE_CopyElementReinterpretCast(name, __cast__) asset->name = reinterpret_cast<__cast__>(anim->name)

				XAE_CopyElement(name);
				XAE_CopyElement(dataByteCount);
				XAE_CopyElement(dataShortCount);
				XAE_CopyElement(dataIntCount);
				XAE_CopyElement(randomDataByteCount);
				XAE_CopyElement(randomDataIntCount);
				XAE_CopyElementRename(framecount, numframes);

                asset->flags = 0;
                if (anim->bLoop)
                {
					asset->flags |= IW6::ANIM_LOOP;
                }
                if (anim->bDelta)
                {
					asset->flags |= IW6::ANIM_DELTA;
                }

				for (auto i = 0; i < 10; i++)
				{
					XAE_CopyElement(boneCount[i]);
				}

				XAE_CopyElement(notifyCount);
				XAE_CopyElement(assetType);
				XAE_CopyElementRename(isDefault, ikType);
				XAE_CopyElement(randomDataShortCount);
				XAE_CopyElementRename(indexcount, indexCount);
				XAE_CopyElement(framerate);
				XAE_CopyElement(frequency);
				if (anim->tagnames)
				{
					asset->names = mem->Alloc<IW6::scr_string_t>(anim->boneCount[9]);
					for (auto i = 0; i < anim->boneCount[9]; i++)
					{
						asset->names[i] = static_cast<IW6::scr_string_t>(anim->tagnames[i]);
					}
				}
				XAE_CopyElement(dataByte);
				XAE_CopyElement(dataShort);
				XAE_CopyElement(dataInt);
				XAE_CopyElement(randomDataShort);
				XAE_CopyElementReinterpretCast(randomDataByte, unsigned char* __ptr64);
				XAE_CopyElement(randomDataInt);
				XAE_CopyElement(indices.data);

				if (anim->notify)
				{
					asset->notify = mem->Alloc<IW6::XAnimNotifyInfo>(anim->notifyCount);
					for (auto i = 0; i < anim->notifyCount; i++)
					{
						asset->notify[i].name = static_cast<IW6::scr_string_t>(anim->notify[i].name);
						asset->notify[i].time = anim->notify[i].time;
					}
				}

				if (anim->delta)
				{
					asset->deltaPart = mem->Alloc<IW6::XAnimDeltaPart>();
					if (anim->delta->trans)
					{
						auto extra_size = 0;

						if (anim->delta->trans->size)
						{
							if (anim->framecount >= 256)
							{
								extra_size += (anim->delta->trans->size * 2) + 2;
							}
							else
							{
								extra_size += anim->delta->trans->size + 1;
							}
						}

						asset->deltaPart->trans = mem->ManualAlloc<IW6::XAnimPartTrans>(sizeof(IW6::XAnimPartTrans) + extra_size);

						asset->deltaPart->trans->size = anim->delta->trans->size;
						asset->deltaPart->trans->smallTrans = static_cast<unsigned short>(anim->delta->trans->smallTrans);

						if (anim->delta->trans->size)
						{
							for (auto i = 0; i < 3; i++)
							{
								asset->deltaPart->trans->u.frames.mins[i] = anim->delta->trans->u.frames.mins[i];
								asset->deltaPart->trans->u.frames.size[i] = anim->delta->trans->u.frames.size[i];
							}
							if (anim->framecount >= 256)
							{
								for (auto i = 0; i < anim->delta->trans->size + 1; i++)
								{
									asset->deltaPart->trans->u.frames.indices._2[i] = anim->delta->trans->u.frames.indices._2[i];
								}
							}
							else
							{
								for (auto i = 0; i < anim->delta->trans->size + 1; i++)
								{
									asset->deltaPart->trans->u.frames.indices._1[i] = static_cast<unsigned char>(anim->delta->trans->u.frames.indices._1[i]);
								}
							}
							if (anim->delta->trans->u.frames.frames._1)
							{
								if (anim->delta->trans->smallTrans)
								{
									asset->deltaPart->trans->u.frames.frames._1 = mem->Alloc<unsigned char[3]>(anim->delta->trans->size + 1);
									for (auto i = 0; i < anim->delta->trans->size + 1; i++)
									{
										asset->deltaPart->trans->u.frames.frames._1[i][0] = static_cast<unsigned char>(anim->delta->trans->u.frames.frames._1[i][0]);
										asset->deltaPart->trans->u.frames.frames._1[i][1] = static_cast<unsigned char>(anim->delta->trans->u.frames.frames._1[i][1]);
										asset->deltaPart->trans->u.frames.frames._1[i][2] = static_cast<unsigned char>(anim->delta->trans->u.frames.frames._1[i][2]);
									}
								}
								else
								{
									asset->deltaPart->trans->u.frames.frames._2 = mem->Alloc<unsigned short[3]>(anim->delta->trans->size + 1);
									for (auto i = 0; i < anim->delta->trans->size + 1; i++)
									{
										asset->deltaPart->trans->u.frames.frames._2[i][0] = anim->delta->trans->u.frames.frames._2[i][0];
										asset->deltaPart->trans->u.frames.frames._2[i][1] = anim->delta->trans->u.frames.frames._2[i][1];
										asset->deltaPart->trans->u.frames.frames._2[i][2] = anim->delta->trans->u.frames.frames._2[i][2];
									}
								}
							}
						}
						else
						{
							for (auto i = 0; i < 3; i++)
							{
								asset->deltaPart->trans->u.frame0[i] = anim->delta->trans->u.frame0[i];
							}
						}
					}

					if (anim->delta->quat)
					{
						auto extra_size = 0;

						if (anim->delta->quat->size)
						{
							if (anim->framecount >= 256)
							{
								extra_size += (anim->delta->quat->size * 2) + 2;
							}
							else
							{
								extra_size += anim->delta->quat->size + 1;
							}
						}
						else
						{
							// quat data contains 4 extra bytes
							extra_size += 4;
						}

						asset->deltaPart->quat = mem->ManualAlloc<IW6::XAnimDeltaPartQuat>(sizeof(IW6::XAnimDeltaPartQuat) + extra_size);
						asset->deltaPart->quat->size = anim->delta->quat->size;
					
						if(anim->delta->quat->size)
						{
							if (anim->framecount >= 256)
							{
								for (auto i = 0; i < anim->delta->quat->size + 1; i++)
								{
									asset->deltaPart->quat->u.frames.indices._2[i] = anim->delta->quat->u.frames.indices._2[i];
								}
							}
							else
							{
								for (auto i = 0; i < anim->delta->quat->size + 1; i++)
								{
									asset->deltaPart->quat->u.frames.indices._1[i] = static_cast<unsigned char>(anim->delta->quat->u.frames.indices._1[i]);
								}
							}
							if (anim->delta->quat->u.frames.frames)
							{
								asset->deltaPart->quat->u.frames.frames = mem->Alloc<short[4]>(anim->delta->quat->size + 1);
								for (auto i = 0; i < anim->delta->quat->size + 1; i++)
								{
									asset->deltaPart->quat->u.frames.frames[i][0] = anim->delta->quat->u.frames.frames[i][0];
									asset->deltaPart->quat->u.frames.frames[i][1] = anim->delta->quat->u.frames.frames[i][1];
								}
							}
						}
						else
						{
							for (auto i = 0; i < 2; i++)
							{
								asset->deltaPart->quat->u.frame0[i] = anim->delta->quat->u.frame0[i];
							}
						}
					}
				}
				
				// dump asset
				IW6::dump(asset, SL_ConvertToString);
			}
		}
	}
}
