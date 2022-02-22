#include "stdafx.hpp"
#include "IW6/Assets/XSurface.hpp"

namespace ZoneTool
{
	namespace PackedShit
	{
		using namespace IW5;

		#define _BYTE  uint8_t
		#define _WORD  uint16_t
		#define _DWORD uint32_t
		#define _QWORD uint64_t

		#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
		#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
		#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
		#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
		#define HIWORD(x)   (*((_WORD*)&(x)+1))
		#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
		#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
		#define WORDn(x, n)   (*((_WORD*)&(x)+n))
		#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
		#define BYTE2(x)   BYTEn(x,  2)

		PackedTexCoords Vec2PackTexCoords(float* in)
		{
			int v2; // eax
			int v3; // esi
			int v4; // eax
			int v5; // ecx
			PackedTexCoords result; // eax
			int v7; // [esp+8h] [ebp+8h]
			int v8; // [esp+8h] [ebp+8h]

			v7 = LODWORD(in[0]);
			v2 = (int)((2 * v7) ^ 0x80003FFF) >> 14;
			if (v2 < 0x3FFF)
			{
				if (v2 <= -16384)
					LOWORD(v2) = -16384;
			}
			else
			{
				LOWORD(v2) = 0x3FFF;
			}
			v3 = (v7 >> 16) & 0xC000 | v2 & 0x3FFF;
			v8 = LODWORD(in[1]);
			v4 = (int)((2 * v8) ^ 0x80003FFF) >> 14;
			v5 = (v8 >> 16) & 0xC000;
			if (v4 < 0x3FFF)
			{
				if (v4 <= -16384)
					LOWORD(v4) = -16384;
				result.packed = v3 + ((v5 | v4 & 0x3FFF) << 16);
			}
			else
			{
				result.packed = v3 + ((v5 | 0x3FFF) << 16);
			}
			return result;
		}

		void Vec2UnpackTexCoords(const PackedTexCoords in, float* out)
		{
			unsigned int val;

			if (LOWORD(in.packed))
				val = ((LOWORD(in.packed) & 0x8000) << 16) | (((((in.packed & 0x3FFF) << 14) - (~(LOWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
			else
				val = 0;

			out[0] = *reinterpret_cast<float*>(&val);

			if (HIWORD(in.packed))
				val = ((HIWORD(in.packed) & 0x8000) << 16) | (((((HIWORD(in.packed) & 0x3FFF) << 14)
					- (~(HIWORD(in.packed) << 14) & 0x10000000)) ^ 0x80000001) >> 1);
			else
				val = 0;

			out[1] = *reinterpret_cast<float*>(&val);
		}
	}

	namespace IW5
	{
		void GenerateIW6XSurface(IW6::XSurface* iw6_asset, XSurface* asset, ZoneMemory* mem)
		{
			iw6_asset->flags = 0;
			iw6_asset->vertCount = asset->vertCount;
			iw6_asset->triCount = asset->triCount;
			iw6_asset->rigidVertListCount = asset->vertListCount;

			iw6_asset->unknown = 0;

			// blend verts
			memcpy(&iw6_asset->blendVertCounts, &asset->vertexInfo.vertCount, sizeof(asset->vertexInfo.vertCount));
			iw6_asset->blendVerts = reinterpret_cast<unsigned short* __ptr64>(asset->vertexInfo.vertsBlend);

			// triIndices
			iw6_asset->triIndices = reinterpret_cast<IW6::Face* __ptr64>(asset->triIndices);

			// verts
			//iw6_asset->verts0.packedVerts0 = reinterpret_cast<IW6::GfxPackedVertex* __ptr64>(asset->verticies);
			iw6_asset->verts0.packedVerts0 = mem->Alloc<IW6::GfxPackedVertex>(asset->vertCount);
			for (unsigned short i = 0; i < asset->vertCount; i++)
			{
				memcpy(&iw6_asset->verts0.packedVerts0[i], &asset->verticies[i], sizeof(IW5::GfxPackedVertex));

				float texCoord_unpacked[2];
				PackedShit::Vec2UnpackTexCoords(asset->verticies[i].texCoord, texCoord_unpacked);
				std::swap(texCoord_unpacked[0], texCoord_unpacked[1]); // these are inverted...
				iw6_asset->verts0.packedVerts0[i].texCoord.packed = PackedShit::Vec2PackTexCoords(texCoord_unpacked).packed;

				// re-calculate these...
				//iw6_asset->verts0.packedVerts0[i].normal.packed = 0;
				//iw6_asset->verts0.packedVerts0[i].tangent.packed = 0;
			}

			// rigidVertLists
			iw6_asset->rigidVertLists = mem->Alloc<IW6::XRigidVertList>(asset->vertListCount);
			for (int i = 0; i < asset->vertListCount; i++)
			{
				iw6_asset->rigidVertLists[i].boneOffset = asset->rigidVertLists[i].boneOffset;
				iw6_asset->rigidVertLists[i].vertCount = asset->rigidVertLists[i].vertCount;
				iw6_asset->rigidVertLists[i].triOffset = asset->rigidVertLists[i].triOffset;
				iw6_asset->rigidVertLists[i].triCount = asset->rigidVertLists[i].triCount;

				if (asset->rigidVertLists[i].collisionTree)
				{
					iw6_asset->rigidVertLists[i].collisionTree = mem->Alloc<IW6::XSurfaceCollisionTree>();
					memcpy(&iw6_asset->rigidVertLists[i].collisionTree->trans, &asset->rigidVertLists[i].collisionTree->trans,
						sizeof(asset->rigidVertLists[i].collisionTree->trans));
					memcpy(&iw6_asset->rigidVertLists[i].collisionTree->scale, &asset->rigidVertLists[i].collisionTree->scale,
						sizeof(asset->rigidVertLists[i].collisionTree->scale));

					iw6_asset->rigidVertLists[i].collisionTree->nodeCount = asset->rigidVertLists[i].collisionTree->nodeCount;
					iw6_asset->rigidVertLists[i].collisionTree->nodes = mem->Alloc<IW6::XSurfaceCollisionNode>(
						asset->rigidVertLists[i].collisionTree->nodeCount);
					for (int j = 0; j < asset->rigidVertLists[i].collisionTree->nodeCount; j++)
					{
						memcpy(&iw6_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins,
							&asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins,
							sizeof(asset->rigidVertLists[i].collisionTree->nodes[j].aabb.mins));
						memcpy(&iw6_asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs,
							&asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs,
							sizeof(asset->rigidVertLists[i].collisionTree->nodes[j].aabb.maxs));

						iw6_asset->rigidVertLists[i].collisionTree->nodes[j].childBeginIndex =
							asset->rigidVertLists[i].collisionTree->nodes[j].childBeginIndex;
						iw6_asset->rigidVertLists[i].collisionTree->nodes[j].childCount =
							asset->rigidVertLists[i].collisionTree->nodes[j].childCount;
					}

					iw6_asset->rigidVertLists[i].collisionTree->leafCount = asset->rigidVertLists[i].collisionTree->leafCount;
					iw6_asset->rigidVertLists[i].collisionTree->leafs = mem->Alloc<IW6::XSurfaceCollisionLeaf>(
						asset->rigidVertLists[i].collisionTree->leafCount);
					for (int j = 0; j < asset->rigidVertLists[i].collisionTree->leafCount; j++)
					{
						iw6_asset->rigidVertLists[i].collisionTree->leafs[j].triangleBeginIndex =
							asset->rigidVertLists[i].collisionTree->leafs[j].triangleBeginIndex;
					}
				}
			}

			// partBits
			memcpy(&iw6_asset->partBits, &asset->partBits, sizeof(asset->partBits));
		}

		IW6::XModelSurfs* GenerateIW6XModelSurfs(ModelSurface* asset, ZoneMemory* mem)
		{
			// allocate IW6 XModelSurfs structure
			const auto iw6_asset = mem->Alloc<IW6::XModelSurfs>();

			iw6_asset->name = mem->StrDup(asset->name);
			iw6_asset->numsurfs = asset->xSurficiesCount;
			memcpy(&iw6_asset->partBits, &asset->partBits, sizeof(asset->partBits));

			iw6_asset->surfs = mem->Alloc<IW6::XSurface>(asset->xSurficiesCount);
			for (int i = 0; i < asset->xSurficiesCount; i++)
			{
				GenerateIW6XSurface(&iw6_asset->surfs[i], &asset->xSurficies[i], mem);
			}

			return iw6_asset;
		}

		void IXSurface::dump(ModelSurface* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::XSurface) == 232);

			// generate iw6 xsurface
			auto iw6_asset = GenerateIW6XModelSurfs(asset, mem);

			// dump iw6 xsurface
			IW6::IXSurface::dump(iw6_asset);
		}
	}
}