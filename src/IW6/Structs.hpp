#pragma once

#pragma pack(push, 8)

namespace ZoneTool
{
	namespace IW6
	{
		typedef float vec_t;
		typedef vec_t vec2_t[2];
		typedef vec_t vec3_t[3];
		typedef vec_t vec4_t[4];

		template <std::size_t N>
		struct VecInternal
		{
			float data[N];
		};

		struct dummy
		{
		};

		enum scr_string_t : std::int32_t
		{
		};

		enum XAssetType : std::int32_t
		{
			ASSET_TYPE_PHYSPRESET = 0x0,
			ASSET_TYPE_PHYSCOLLMAP = 0x1,
			ASSET_TYPE_XANIMPARTS = 0x2,
			ASSET_TYPE_XMODEL_SURFS = 0x3,
			ASSET_TYPE_XMODEL = 0x4,
			ASSET_TYPE_MATERIAL = 0x5,
			ASSET_TYPE_COMPUTESHADER = 0x6,
			ASSET_TYPE_VERTEXSHADER = 0x7,
			ASSET_TYPE_HULLSHADER = 0x8,
			ASSET_TYPE_DOMAINSHADER = 0x9,
			ASSET_TYPE_PIXELSHADER = 0xA,
			ASSET_TYPE_VERTEXDECL = 0xB,
			ASSET_TYPE_TECHNIQUE_SET = 0xC,
			ASSET_TYPE_IMAGE = 0xD,
			ASSET_TYPE_SOUND = 0xE,
			ASSET_TYPE_SOUND_CURVE = 0xF,
			ASSET_TYPE_LPF_CURVE = 0x10,
			ASSET_TYPE_REVERB_CURVE = 0x11,
			ASSET_TYPE_LOADED_SOUND = 0x12,
			ASSET_TYPE_CLIPMAP = 0x13,
			ASSET_TYPE_COMWORLD = 0x14,
			ASSET_TYPE_GLASSWORLD = 0x15,
			ASSET_TYPE_PATHDATA = 0x16,
			ASSET_TYPE_VEHICLE_TRACK = 0x17,
			ASSET_TYPE_MAP_ENTS = 0x18,
			ASSET_TYPE_FXWORLD = 0x19,
			ASSET_TYPE_GFXWORLD = 0x1A,
			ASSET_TYPE_LIGHT_DEF = 0x1B,
			ASSET_TYPE_UI_MAP = 0x1C,
			ASSET_TYPE_FONT = 0x1D,
			ASSET_TYPE_MENULIST = 0x1E,
			ASSET_TYPE_MENU = 0x1F,
			ASSET_TYPE_ANIMCLASS = 0x20,
			ASSET_TYPE_LOCALIZE_ENTRY = 0x21,
			ASSET_TYPE_ATTACHMENT = 0x22,
			ASSET_TYPE_WEAPON = 0x23,
			ASSET_TYPE_SNDDRIVER_GLOBALS = 0x24,
			ASSET_TYPE_FX = 0x25,
			ASSET_TYPE_IMPACT_FX = 0x26,
			ASSET_TYPE_SURFACE_FX = 0x27,
			ASSET_TYPE_AITYPE = 0x28,
			ASSET_TYPE_MPTYPE = 0x29,
			ASSET_TYPE_CHARACTER = 0x2A,
			ASSET_TYPE_XMODELALIAS = 0x2B,
			ASSET_TYPE_RAWFILE = 0x2C,
			ASSET_TYPE_SCRIPTFILE = 0x2D,
			ASSET_TYPE_STRINGTABLE = 0x2E,
			ASSET_TYPE_LEADERBOARD = 0x2F,
			ASSET_TYPE_STRUCTURED_DATA_DEF = 0x30,
			ASSET_TYPE_TRACER = 0x31,
			ASSET_TYPE_VEHICLE = 0x32,
			ASSET_TYPE_ADDON_MAP_ENTS = 0x33,
			ASSET_TYPE_NET_CONST_STRINGS = 0x34,
			ASSET_TYPE_REVERB_PRESET = 0x35,
			ASSET_TYPE_LUA_FILE = 0x36,
			ASSET_TYPE_SCRIPTABLE = 0x37,
			ASSET_TYPE_COLORIZATION = 0x38,
			ASSET_TYPE_COLORIZATIONSET = 0x39,
			ASSET_TYPE_TONEMAPPING = 0x3A,
			ASSET_TYPE_EQUIPMENT_SND_TABLE = 0x3B,
			ASSET_TYPE_VECTORFIELD = 0x3C,
			ASSET_TYPE_DOPPLER_PRESET = 0x3D,
			ASSET_TYPE_PARTICLE_SIM_ANIMATION = 0x3E,
			ASSET_TYPE_COUNT = 0x3F,
			ASSET_TYPE_STRING = 0x3F,
			ASSET_TYPE_ASSETLIST = 0x40,
			max = 0x3F
		};

		enum PhysPresetScaling
		{
			PHYSPRESET_SCALING_LINEAR = 0x0,
			PHYSPRESET_SCALING_QUADRATIC = 0x1,
			PHYSPRESET_SCALING_COUNT = 0x2,
		};

		struct PhysPreset
		{
			const char* __ptr64 name;
			int type;
			float mass;
			float bounce;
			float friction;
			float bulletForceScale;
			float explosiveForceScale;
			const char* __ptr64 sndAliasPrefix;
			float piecesSpreadFraction;
			float piecesUpwardVelocity;
			float minMomentum;
			float maxMomentum;
			float minVolume;
			float maxVolume;
			float minPitch;
			float maxPitch;
			PhysPresetScaling volumeType;
			PhysPresetScaling pitchType;
			bool tempDefaultToCylinder;
			bool perSurfaceSndAlias;
		};

		struct Bounds
		{
			vec3_t midPoint;
			vec3_t halfSize;

			void compute()
			{
				compute(midPoint, halfSize);
			}

			void compute(vec3_t mins, vec3_t maxs)
			{
				for (int i = 0; i < 3; ++i)
				{
					this->halfSize[i] = (maxs[i] - mins[i]) / 2;
					this->midPoint[i] = this->halfSize[i] + mins[i];
				}
			}
		};

		struct GfxDrawSurfFields
		{
			unsigned __int64 objectId : 16;
			unsigned __int64 reflectionProbeIndex : 8;
			unsigned __int64 hasGfxEntIndex : 1;
			unsigned __int64 customIndex : 5;
			unsigned __int64 materialSortedIndex : 13;
			unsigned __int64 tessellation : 3;
			unsigned __int64 prepass : 2;
			unsigned __int64 useHeroLighting : 1;
			unsigned __int64 sceneLightEnvIndex : 16;
			unsigned __int64 viewModelRender : 1;
			unsigned __int64 surfType : 4;
			unsigned __int64 primarySortKey : 6;
			unsigned __int64 unused : 30;
		};

		struct Packed128
		{
			unsigned __int64 p0;
			unsigned __int64 p1;
		};

		union GfxDrawSurf
		{
			GfxDrawSurfFields fields;
			Packed128 packed;
		};

		struct MaterialInfo
		{
			const char* __ptr64 name; // 0
			unsigned char gameFlags; // 8
			unsigned char sortKey; // 9
			unsigned char textureAtlasRowCount; // 10
			unsigned char textureAtlasColumnCount; // 11
			unsigned char textureAtlasFrameBlend; // 12
			unsigned char textureAtlasAsArray; /// 13
			unsigned char renderFlags; // 14
			GfxDrawSurf drawSurf; // 16
			unsigned int surfaceTypeBits; // 32
			unsigned short hashIndex; // 36
		};

		struct GfxVertexShaderLoadDef
		{
			char* __ptr64 program;
			unsigned int programSize;
			unsigned short loadForRenderer;
			unsigned int microCodeCrc;
		};

		struct MaterialVertexShaderProgram
		{
			void* __ptr64 vs; //ID3D11VertexShader* __ptr64 vs;
			GfxVertexShaderLoadDef loadDef;
		};

		struct MaterialVertexShader
		{
			const char* __ptr64 name;
			MaterialVertexShaderProgram prog;
		};

		struct MaterialStreamRouting
		{
			unsigned char source;
			unsigned char dest;
			unsigned char mask;
		};

		struct MaterialVertexStreamRouting
		{
			MaterialStreamRouting data[31];
			void* __ptr64 decl[249]; //ID3D11InputLayout* __ptr64 decl[242];
		};

		struct MaterialVertexDeclaration
		{
			const char* __ptr64 name;
			unsigned char streamCount;
			bool hasOptionalSource;
			MaterialVertexStreamRouting routing;
		};

		struct GfxHullShaderLoadDef
		{
			char* __ptr64 program;
			unsigned int programSize;
			unsigned short loadForRenderer;
		};

		struct MaterialHullShaderProgram
		{
			void* __ptr64 hs; //ID3D11HullShader* __ptr64 hs;
			GfxHullShaderLoadDef loadDef;
		};

		struct MaterialHullShader
		{
			const char* __ptr64 name;
			MaterialHullShaderProgram prog;
		};

		struct GfxDomainShaderLoadDef
		{
			char* __ptr64 program;
			unsigned int programSize;
			unsigned short loadForRenderer;
		};

		struct MaterialDomainShaderProgram
		{
			void* __ptr64 ds; //ID3D11DomainShader* __ptr64 ds;
			GfxDomainShaderLoadDef loadDef;
		};

		struct MaterialDomainShader
		{
			const char* __ptr64 name;
			MaterialDomainShaderProgram prog;
		};

		struct GfxPixelShaderLoadDef
		{
			char* __ptr64 program;
			unsigned int programSize;
			unsigned short loadForRenderer;
			unsigned int microCodeCrc;
		};

		struct MaterialPixelShaderProgram
		{
			void* __ptr64 ps; //ID3D11PixelShader* __ptr64 ps;
			GfxPixelShaderLoadDef loadDef;
		};

		struct MaterialPixelShader
		{
			const char* __ptr64 name;
			MaterialPixelShaderProgram prog;
		};

		struct MaterialArgumentCodeConst
		{
			unsigned short index;
			unsigned char firstRow;
			unsigned char rowCount;
		};

		union MaterialArgumentDef
		{
			const float* __ptr64 literalConst;
			MaterialArgumentCodeConst codeConst;
			unsigned int codeSampler;
			unsigned int nameHash;
		};

		struct MaterialShaderArgument
		{
			unsigned char type;
			unsigned char shader;
			unsigned short dest;
			MaterialArgumentDef u;
		};

		struct MaterialPass
		{
			MaterialVertexShader* __ptr64 vertexShader;
			MaterialVertexDeclaration* __ptr64 vertexDecl;
			MaterialHullShader* __ptr64 hullShader;
			MaterialDomainShader* __ptr64 domainShader;
			MaterialPixelShader* __ptr64 pixelShader;
			unsigned char pixelOutputMask;
			unsigned char perPrimArgCount;
			unsigned char perObjArgCount;
			unsigned char stableArgCount;
			unsigned short perPrimArgSize;
			unsigned short perObjArgSize;
			unsigned short stableArgSize;
			unsigned char zone;
			unsigned char perPrimConstantBuffer;
			unsigned char perObjConstantBuffer;
			unsigned char stableConstantBuffer;
			unsigned int customBufferFlags;
			unsigned char customSamplerFlags;
			unsigned char precompiledIndex;
			unsigned char stageConfig;
			MaterialShaderArgument* __ptr64 args;
		};

		struct MaterialTechniqueHeader
		{
			const char* __ptr64 name;
			unsigned short flags;
			unsigned short passCount;
		};

		struct MaterialTechnique
		{
			//const char* __ptr64 name;
			//unsigned short flags;
			//unsigned short passCount;
			MaterialTechniqueHeader hdr;
			MaterialPass passArray[1];
		};

		struct MaterialTechniqueSet
		{
			const char* __ptr64 name;
			unsigned short flags;
			unsigned char worldVertFormat;
			unsigned char preDisplacementOnlyCount;
			MaterialTechnique* __ptr64 techniques[412];
		};

		struct GfxTexture
		{
			unsigned char levelCount;
			unsigned char numElements;
			int flags;
			int format;
			int resourceSize;
			unsigned char* __ptr64 data;
		};

		struct GfxImageLoadDef
		{
			unsigned char levelCount;
			unsigned char numElements;
			unsigned char pad[2];
			int flags;
			int format;
			int resourceSize;
			unsigned char data[1];
		};

		/*struct GfxTexture
		{
			GfxImageLoadDef* __ptr64 loadDef;
			void* __ptr64 shaderView;
			void* __ptr64 shaderViewAlternate;
		};*/

		struct Picmip
		{
			unsigned char platform[2];
		};

		struct GfxMip
		{
			unsigned short width;
			unsigned short height;

			unsigned char padding[4];
		};

		enum MapType : std::uint8_t
		{
			MAPTYPE_NONE = 0x0,
			MAPTYPE_INVALID1 = 0x1,
			MAPTYPE_1D = 0x2,
			MAPTYPE_2D = 0x3,
			MAPTYPE_3D = 0x4,
			MAPTYPE_CUBE = 0x5,
			MAPTYPE_ARRAY = 0x6,
			MAPTYPE_COUNT = 0x7,
		};

		struct GfxImage
		{
			GfxTexture texture; // 0
			int imageFormat; // 24
			MapType mapType; // 28
			unsigned char sematic; // 29
			unsigned char category; // 30
			unsigned char flags; // 31
			Picmip picmip; // 32
			char __pad2[2]; // 34
			int dataLen1; // 36
			int dataLen2; // 40
			unsigned short width; // 44
			unsigned short height; // 46
			unsigned short depth; // 48
			unsigned short numElements; // 50
			unsigned char unknown; // 52
			unsigned char streamed; // 53
			char __pad3[2]; // 54
			unsigned char* __ptr64 pixelData; // 56
			unsigned short lowestStreamedWidth; // 64
			unsigned short lowestStreamedHeight; // 66
			GfxMip miplevels[3]; // 68
			unsigned short miplevels4Width; // 92
			unsigned short miplevels4Height; // 94
			const char* __ptr64 name; // 96
		};

		struct GfxColorFloat
		{
			float array[4];
		};

		struct GfxLightImage
		{
			GfxImage* __ptr64 image;
			unsigned char samplerState;
		};

		struct GfxLightDef
		{
			const char* __ptr64 name;
			GfxLightImage attenuation;
			GfxLightImage cucoloris;
			int lmapLookupStart;
		};

		struct WaterWritable
		{
			float floatTime;
		};

		struct water_t
		{
			WaterWritable writable;
			float* __ptr64 H0X;
			float* __ptr64 H0Y;
			float* __ptr64 wTerm;
			int M;
			int N;
			float Lx;
			float Lz;
			float gravity;
			float windvel;
			float winddir[2];
			float amplitude;
			GfxImage* __ptr64 image;
			GfxImage* __ptr64 stagingImage;
		};

		union MaterialTextureDefInfo
		{
			GfxImage* __ptr64 image;
			water_t* __ptr64 water;
		};

		struct MaterialTextureDef
		{
			unsigned int nameHash;
			char nameStart;
			char nameEnd;
			unsigned char samplerState;
			unsigned char semantic;
			MaterialTextureDefInfo u;
		};

		struct MaterialConstantDef
		{
			unsigned int nameHash;
			char name[12];
			float literal[4];
		};

		struct GfxStateBits
		{
			unsigned int loadBits[3];
			unsigned char zone;
			unsigned char depthStencilState[11];
			unsigned char blendState;
			unsigned char rasterizerState;
		};

		struct MaterialConstantBufferDef
		{
			unsigned int vsDataSize;
			unsigned int hsDataSize;
			unsigned int dsDataSize;
			unsigned int psDataSize;
			unsigned int vsOffsetDataSize;
			unsigned int hsOffsetDataSize;
			unsigned int dsOffsetDataSize;
			unsigned int psOffsetDataSize;
			unsigned __int8* __ptr64 vsData;
			unsigned __int8* __ptr64 hsData;
			unsigned __int8* __ptr64 dsData;
			unsigned __int8* __ptr64 psData;
			unsigned short* __ptr64 vsOffsetData;
			unsigned short* __ptr64 hsOffsetData;
			unsigned short* __ptr64 dsOffsetData;
			unsigned short* __ptr64 psOffsetData;
			void* __ptr64 vsConstantBuffer; //ID3D11Buffer* __ptr64 vsConstantBuffer;
			void* __ptr64 hsConstantBuffer; //ID3D11Buffer* __ptr64 hsConstantBuffer;
			void* __ptr64 dsConstantBuffer; //ID3D11Buffer* __ptr64 dsConstantBuffer;
			void* __ptr64 psConstantBuffer; //ID3D11Buffer* __ptr64 psConstantBuffer;
		};

		struct Material
		{
			//MaterialInfo info;
			const char* __ptr64 name; // 0
			unsigned char gameFlags; // 8
			unsigned char sortKey; // 9
			unsigned char textureAtlasRowCount; // 10
			unsigned char textureAtlasColumnCount; // 11
			unsigned char textureAtlasFrameBlend; // 12
			unsigned char textureAtlasAsArray; /// 13
			unsigned char renderFlags; // 14
			GfxDrawSurf drawSurf; // 16
			unsigned int surfaceTypeBits; // 32
			unsigned short hashIndex; // 36
			char __pad[2]; // 38 - 40
			char stateBitsEntry[412]; // 40
			unsigned char textureCount; // 452
			unsigned char constantCount; // 453
			unsigned char stateBitsCount; // 454
			unsigned char stateFlags; // 455
			unsigned char cameraRegion; // 456
			unsigned char materialType; // 457
			unsigned char stringCount; // 458
			unsigned char assetFlags; // 459
			char __pad2[4]; // 460 - 464
			MaterialTechniqueSet* __ptr64 techniqueSet; // 464
			MaterialTextureDef* __ptr64 textureTable; // 472
			MaterialConstantDef* __ptr64 constantTable; // 480
			GfxStateBits* __ptr64 stateMap; // 488 (stateBitsTable)
			unsigned char constantBufferIndex[412]; // 496
			char __pad3[4]; // 500
			MaterialConstantBufferDef* __ptr64 constantBufferTable; // 912
			unsigned char constantBufferCount; // 920
			char __pad4[7]; // 921-928
			const char* __ptr64 * __ptr64 xStringArray; // 928
		};

		union XAnimDynamicFrames
		{
			unsigned char(* __ptr64 _1)[3];
			unsigned short(* __ptr64 _2)[3];
		};

		union XAnimDynamicIndices
		{
			unsigned char _1[1];
			unsigned short _2[1];
		};

		struct XAnimPartTransFrames
		{
			float mins[3];
			float size[3];
			XAnimDynamicFrames frames;
			XAnimDynamicIndices indices;
		};

		union XAnimPartTransData
		{
			XAnimPartTransFrames frames;
			float frame0[3];
		};

		struct XAnimPartTrans
		{
			unsigned short size;
			unsigned char smallTrans;
			XAnimPartTransData u;
		};

		struct XAnimDeltaPartQuatDataFrames2
		{
			short(* __ptr64 frames)[2];
			XAnimDynamicIndices indices;
		};

		union XAnimDeltaPartQuatData2
		{
			XAnimDeltaPartQuatDataFrames2 frames;
			short frame0[2];
		};

		struct XAnimDeltaPartQuat2
		{
			unsigned short size;
			XAnimDeltaPartQuatData2 u;
		};

		struct XAnimDeltaPartQuatDataFrames
		{
			short(* __ptr64 frames)[4];
			XAnimDynamicIndices indices;
		};

		union XAnimDeltaPartQuatData
		{
			XAnimDeltaPartQuatDataFrames frames;
			short frame0[4];
		};

		struct XAnimDeltaPartQuat
		{
			unsigned short size;
			XAnimDeltaPartQuatData u;
		};

		struct XAnimDeltaPart
		{
			XAnimPartTrans* __ptr64 trans;
			XAnimDeltaPartQuat2* __ptr64 quat2;
			XAnimDeltaPartQuat* __ptr64 quat;
		};

		union XAnimIndices
		{
			unsigned char* __ptr64 _1;
			unsigned short* __ptr64 _2;
			void* __ptr64 data;
		};

		struct XAnimNotifyInfo
		{
			scr_string_t name;
			float time;
		};

		enum XAnimPartsFlags : std::int32_t
		{
			ANIM_LOOP = 0x1,
			ANIM_DELTA = 0x2,
			ANIM_DELTA_3D = 0x4,
			ANIM_DEFAULT = 0x8,
			ANIM_SHMEM = 0x10,
		};

		struct XAnimParts
		{
			const char* __ptr64 name; // 0
			unsigned short dataByteCount; // 8
			unsigned short dataShortCount; // 10
			unsigned short dataIntCount; // 12
			unsigned short randomDataByteCount; // 14
			unsigned short randomDataIntCount; // 16
			unsigned short numframes; // 18
			unsigned char flags; // 20
			unsigned char boneCount[10]; // 21
			unsigned char notifyCount; // 31
			unsigned char assetType; // 32
			unsigned char ikType; // 33
			unsigned int randomDataShortCount; // 36
			unsigned int indexCount; // 40
			float framerate;  // 44
			float frequency; // 48
			scr_string_t* __ptr64 names; // 56
			char* __ptr64 dataByte; // 64
			short* __ptr64 dataShort; // 72
			int* __ptr64 dataInt; // 80
			short* __ptr64 randomDataShort; // 88
			unsigned char* __ptr64 randomDataByte; // 96
			int* __ptr64 randomDataInt; // 104
			XAnimIndices indices; // 112
			XAnimNotifyInfo* __ptr64 notify; // 120
			XAnimDeltaPart* __ptr64 deltaPart; // 128
		};

		struct DObjAnimMat
		{
			float quat[4];
			float trans[3];
			float transWeight;
		};

		struct ReactiveMotionModelPart
		{
			float center[3];
			float stiffness;
		};

		struct XSurfaceCollisionAabb
		{
			unsigned short mins[3];
			unsigned short maxs[3];
		};

		struct XSurfaceCollisionNode
		{
			XSurfaceCollisionAabb aabb;
			unsigned short childBeginIndex;
			unsigned short childCount;
		};

		struct XSurfaceCollisionLeaf
		{
			unsigned short triangleBeginIndex;
		};

		struct XSurfaceCollisionTree
		{
			float trans[3];
			float scale[3];
			unsigned int nodeCount;
			XSurfaceCollisionNode* __ptr64 nodes;
			unsigned int leafCount;
			XSurfaceCollisionLeaf* __ptr64 leafs;
		};

		struct XRigidVertList
		{
			unsigned short boneOffset;
			unsigned short vertCount;
			unsigned short triOffset;
			unsigned short triCount;
			XSurfaceCollisionTree* __ptr64 collisionTree;
		};

		union PackedUnitVec
		{
			unsigned int packed;
		};

		union PackedTexCoords
		{
			unsigned int packed;
		};

		union GfxColor
		{
			unsigned char array[4];
			unsigned int packed;
		};

		struct GfxQuantizedNoColorMotionVertex
		{
			short xyz[3];
			short binormalSignAndHeight;
			PackedUnitVec normal;
			PackedUnitVec tangent;
			PackedTexCoords texCoord;
			GfxColor pieceIndex;
		};

		struct GfxQuantizedNoColorVertex
		{
			short xyz[3];
			short binormalSign;
			PackedUnitVec normal;
			PackedUnitVec tangent;
			PackedTexCoords texCoord;
		};

		struct GfxQuantizedVertex
		{
			short xyz[3];
			short binormalSign;
			PackedUnitVec normal;
			PackedUnitVec tangent;
			PackedTexCoords texCoord;
			GfxColor color;
		};

		struct GfxQuantizedMotionVertex
		{
			short xyz[3];
			short binormalSignAndHeight;
			PackedUnitVec normal;
			PackedUnitVec tangent;
			PackedTexCoords texCoord;
			GfxColor pieceIndex;
		};

		struct GfxPackedVertex
		{
			float xyz[3];
			float binormalSign;
			GfxColor color;
			PackedTexCoords texCoord;
			PackedUnitVec normal;
			PackedUnitVec tangent;
		};

		struct GfxPackedMotionVertex
		{
			float xyz[3];
			float binormalSignAndHeight;
			GfxColor pieceIndex;
			PackedTexCoords texCoord;
			PackedUnitVec normal;
			PackedUnitVec tangent;
		};

		union GfxVertexUnion0
		{
			GfxQuantizedNoColorVertex* __ptr64 quantizedNoColorVerts0;
			GfxQuantizedNoColorMotionVertex* __ptr64 quantizedNoColorMotionVerts0;
			GfxQuantizedVertex* __ptr64 quantizedVerts0;
			GfxQuantizedMotionVertex* __ptr64 quantizedMotionVerts0;
			GfxPackedVertex* __ptr64 packedVerts0;
			GfxPackedMotionVertex* __ptr64 packedMotionVerts0;
			void* __ptr64 verts0;
		};

		struct Face
		{
			unsigned short v1;
			unsigned short v2;
			unsigned short v3;
		};

		struct XSurface
		{
			unsigned short flags; // 0
			unsigned short vertCount; // 2
			unsigned short triCount; // 4
			unsigned char rigidVertListCount; // 6
			char unknown; // 7
			short blendVertCounts[8]; // 8
			GfxVertexUnion0 verts0; // 24
			Face* __ptr64 triIndices; // 32
			void* __ptr64 vb0; // 40
			void* __ptr64 vb0View; // 48
			void* __ptr64 indexBuffer; // 56
			XRigidVertList* __ptr64 rigidVertLists; // 64
			unsigned short* __ptr64 blendVerts; // 72
			unsigned short* __ptr64 blendVertsTable; // 80
			void* __ptr64 blendVertsBuffer; // 88
			void* __ptr64 blendVertsView; // 96
			float(* __ptr64 lmapUnwrap)[2]; // 104
			void* __ptr64 vblmap; // 112
			void* __ptr64 vblmapView; // 120
			void* __ptr64 subdivCache_; // 128
			float* __ptr64 tensionData; // 136
			unsigned short* __ptr64 tensionAccumTable; // 144
			void* __ptr64 tensionAccumTableBuffer; // 152
			void* __ptr64 tensionAccumTableView; // 160
			void* __ptr64 tensionDataBuffer; // 168
			void* __ptr64 tensionDataView; // 176
			void* __ptr64 indexBufferView; // 184
			unsigned int vertexLightingIndex; // 192
			int partBits[8]; // 196
		};

		struct XModelSurfs
		{
			const char* __ptr64 name;
			XSurface* __ptr64 surfs;
			unsigned short numsurfs;
			int partBits[8];
		};

		struct XModelLodInfo
		{
			float dist;
			unsigned short numsurfs;
			unsigned short surfIndex;
			XModelSurfs* __ptr64 modelSurfs;
			int partBits[8];
			XSurface* __ptr64 surfs;
			char unknown[8];
		};

		struct XModelCollSurf_s
		{
			Bounds bounds;
			int boneIdx;
			int contents;
			int surfFlags;
		};

		struct XBoneInfo
		{
			Bounds bounds;
			union
			{
				float radiusSquared;
				unsigned int radiusSquaredAsInt;
			};
		};

		struct cplane_s
		{
			float normal[3];
			float dist;
			unsigned char type;
			//unsigned char pad[3];
		};

		struct cbrushside_t
		{
			cplane_s* __ptr64 plane;
			unsigned short materialNum;
			unsigned char firstAdjacentSideOffset;
			unsigned char edgeCount;
		};

		typedef unsigned char cbrushedge_t;

		struct cbrush_t
		{
			unsigned short numsides;
			unsigned short glassPieceIndex;
			cbrushside_t* __ptr64 sides;
			cbrushedge_t* __ptr64 baseAdjacentSide;
			short axialMaterialNum[2][3];
			unsigned char firstAdjacentSideOffsets[2][3];
			unsigned char edgeCount[2][3];
		};

		struct BrushWrapper
		{
			Bounds bounds;
			cbrush_t brush;
			int totalEdgeCount;
			cplane_s* __ptr64 planes;
		};

		struct PhysGeomInfo
		{
			BrushWrapper* __ptr64 brushWrapper;
			int type;
			float orientation[3][3];
			Bounds bounds;
		};

		struct PhysMass
		{
			float centerOfMass[3];
			float momentsOfInertia[3];
			float productsOfInertia[3];
		};

		struct PhysCollmap
		{
			const char* __ptr64 name;
			unsigned int count;
			PhysGeomInfo* __ptr64 geoms;
			PhysMass mass;
			Bounds bounds;
		};

		struct XModelAngle
		{
			short x;
			short y;
			short z;
			short base;
		};

		struct XModelTagPos
		{
			float x;
			float y;
			float z;
		};

		struct XModel
		{
			const char* __ptr64 name; // 0
			unsigned char numBones; // 8
			unsigned char numRootBones; // 9
			unsigned char numsurfs; // 10
			unsigned char numReactiveMotionParts; // 11
			unsigned char lodRampType; // 12
			float scale; // 16
			unsigned int noScalePartBits[6]; // 20
			scr_string_t* __ptr64 boneNames; // 48
			unsigned char* __ptr64 parentList; // 56
			XModelAngle* __ptr64 tagAngles; // 64
			XModelTagPos* __ptr64 tagPositions; // 72
			unsigned char* __ptr64 partClassification; // 80
			DObjAnimMat* __ptr64 baseMat; // 88
			ReactiveMotionModelPart* __ptr64 reactiveMotionParts; // 96
			Material* __ptr64 * __ptr64 materialHandles; // 104
			XModelLodInfo lodInfo[6]; // 112
			char maxLoadedLod; // 496
			char numLods; // 497
			char collLod; // 498
			unsigned char flags; // 499
			int numCollSurfs; // 500
			XModelCollSurf_s* __ptr64 collSurfs; // 504
			int contents; // 512
			XBoneInfo* __ptr64 boneInfo; // 520
			float radius; // 528
			Bounds bounds; // 532
			int memUsage; // 556
			unsigned short* __ptr64 __unk; // 560
			char __unk2[8]; // 568
			PhysPreset* __ptr64 physPreset; // 576
			PhysCollmap* __ptr64 physCollmap; // 584
			float quantization; // 592
		};

		enum snd_alias_type_t
		{
			SAT_UNKNOWN = 0x0,
			SAT_LOADED = 0x1,
			SAT_STREAMED = 0x2,
			SAT_PRIMED = 0x3,
			SAT_COUNT = 0x4,
		};

		struct RiffAudioInfo
		{
			unsigned int sampleRate;
			unsigned int dataByteCount;
			unsigned int numSamples;
			unsigned int avgBytesPerSec;
			unsigned short channels;
			unsigned short numBits;
			unsigned short blockAlign;
			char format;
		};

		struct XA2Sound
		{
			char* __ptr64 data;
			char* __ptr64 seekTable;
			RiffAudioInfo format;
			int loadedSize;
			int seekTableSize;
		};

		struct LoadedSound
		{
			const char* __ptr64 name;
			XA2Sound sound;
		};

		struct StreamFileNameRaw
		{
			const char* __ptr64 dir;
			const char* __ptr64 name;
		};

		struct StreamFileNamePacked
		{
			unsigned __int64 offset;
			unsigned __int64 length;
		};

		union StreamFileInfo
		{
			StreamFileNameRaw raw;
			StreamFileNamePacked packed;
		};

		struct StreamFileName
		{
			unsigned short isLocalized;
			unsigned short fileIndex;
			StreamFileInfo info;
		};

		struct StreamedSound
		{
			StreamFileName filename;
			unsigned int totalMsec;
		};

		struct PrimedSound
		{
			StreamFileName filename;
			LoadedSound* __ptr64 loadedPart;
			int dataOffset;
			int totalSize;
			unsigned int primedCrc;
		};

		union SoundFileRef
		{
			LoadedSound* __ptr64 loadSnd;
			StreamedSound streamSnd;
			PrimedSound primedSnd;
		};

		struct SoundFile
		{
			unsigned char type;
			unsigned char exists;
			SoundFileRef u;
		};

		struct SndCurve
		{
			bool isDefault;
			union
			{
				const char* __ptr64 filename;
				const char* __ptr64 name;
			};
			unsigned short knotCount;
			float knots[16][2];
		};

		struct SpeakerLevels
		{
			int speaker;
			int numLevels;
			float levels[2];
		};

		struct ChannelMap
		{
			int speakerCount;
			SpeakerLevels speakers[6];
		};

		struct SpeakerMap
		{
			bool isDefault;
			const char* __ptr64 name;
			ChannelMap channelMaps[2][2];
		};

		struct OcclusionShape
		{
			bool isDefault;
			const char* __ptr64 name;
			int shapeKind;
			float innerAngle;
			float outerAngle;
			float occludedVolume;
		};

		struct DopplerPreset
		{
			union
			{
				const char* __ptr64 p_name;
				const char* __ptr64 name;
			};
			float speedOfSound;
			float playerVelocityScale;
			float minPitch;
			float maxPitch;
			float smoothing;
		};

		struct snd_alias_t
		{
			union
			{
				const char* __ptr64 aliasName;
				const char* __ptr64 name;
			};
			const char* __ptr64 subtitle;
			const char* __ptr64 secondaryAliasName;
			const char* __ptr64 chainAliasName;
			const char* __ptr64 mixerGroup;
			SoundFile* __ptr64 soundFile;
			int sequence;
			float volMin;
			float volMax;
			int volModIndex;
			float pitchMin;
			float pitchMax;
			float distMin;
			float distMax;
			float velocityMin;
			int flags;
			unsigned char masterPriority;
			float masterPercentage;
			float slavePercentage;
			float probability;
			float lfePercentage;
			float centerPercentage;
			int startDelay;
			SndCurve* __ptr64 volumeFalloffCurve;
			SndCurve* __ptr64 lpfCurve;
			SndCurve* __ptr64 reverbSendCurve;
			float envelopMin;
			float envelopMax;
			float envelopPercentage;
			SpeakerMap* __ptr64 speakerMap;
			float wetMixOverride;
			OcclusionShape* __ptr64 occlusionShape;
			unsigned char allowDoppler;
			DopplerPreset* __ptr64 dopplerPreset;
		};

		struct snd_alias_list_t
		{
			union
			{
				const char* __ptr64 aliasName;
				const char* __ptr64 name;
			};
			snd_alias_t* __ptr64 head;
			int count;
		};

		struct ComPrimaryLight
		{
			unsigned char type;
			unsigned char canUseShadowMap;
			unsigned char exponent;
			unsigned char unused;
			float color[3];
			float dir[3];
			float up[3];
			float origin[3];
			float radius;
			float cosHalfFovOuter;
			float cosHalfFovInner;
			float cosHalfFovExpanded;
			float rotationLimit;
			float translationLimit;
			float cucRotationOffsetRad;
			float cucRotationSpeedRad;
			float cucScrollVector[2];
			float cucScaleVector[2];
			float cucTransVector[2];
			const char* __ptr64 defName;
		};

		struct ComPrimaryLightEnv
		{
			unsigned short primaryLightIndices[4];
			unsigned char numIndices;
		};

		struct ComWorld
		{
			const char* __ptr64 name;
			int isInUse;
			unsigned int primaryLightCount;
			ComPrimaryLight* __ptr64 primaryLights;
			unsigned int primaryLightEnvCount;
			ComPrimaryLightEnv* __ptr64 primaryLightEnvs;
		};

		struct G_GlassPiece
		{
			unsigned __int16 damageTaken;
			unsigned __int16 collapseTime;
			int lastStateChangeTime;
			unsigned __int8 impactDir;
			unsigned __int8 impactPos[2];
		};

		struct G_GlassName
		{
			char* __ptr64 nameStr;
			scr_string_t name;
			unsigned __int16 pieceCount;
			unsigned __int16* __ptr64 pieceIndices;
		};

		struct G_GlassData
		{
			G_GlassPiece* __ptr64 glassPieces;
			unsigned int pieceCount;
			unsigned __int16 damageToWeaken;
			unsigned __int16 damageToDestroy;
			unsigned int glassNameCount;
			G_GlassName* __ptr64 glassNames;
			unsigned __int8 pad[108];
		};

		struct GlassWorld
		{
			const char* __ptr64 name;
			G_GlassData* __ptr64 g_glassData;
		};

		struct Glyph
		{
			unsigned short letter;
			char x0;
			char y0;
			unsigned char dx;
			unsigned char pixelWidth;
			unsigned char pixelHeight;
			float s0;
			float t0;
			float s1;
			float t1;
		};

		struct TriggerModel
		{
			int contents;
			unsigned short hullCount;
			unsigned short firstHull;
		};

		struct TriggerHull
		{
			Bounds bounds;
			int contents;
			unsigned short slabCount;
			unsigned short firstSlab;
		};

		struct TriggerSlab
		{
			float dir[3];
			float midPoint;
			float halfSize;
		};

		struct MapTriggers
		{
			unsigned int count;
			TriggerModel* __ptr64 models;
			unsigned int hullCount;
			TriggerHull* __ptr64 hulls;
			unsigned int slabCount;
			TriggerSlab* __ptr64 slabs;
		};

		struct ClientTriggerAabbNode
		{
			Bounds bounds;
			unsigned short firstChild;
			unsigned short childCount;
		};

		struct ClientTriggers
		{
			MapTriggers trigger;
			unsigned short numClientTriggerNodes;
			ClientTriggerAabbNode* __ptr64 clientTriggerAabbTree;
			unsigned int triggerStringLength;
			char* __ptr64 triggerString;
			short* __ptr64 visionSetTriggers;
			char* __ptr64 triggerType;
			float(* __ptr64 origins)[3];
			float* __ptr64 scriptDelay;
			short* __ptr64 audioTriggers;
			short* __ptr64 blendLookup;
			short* __ptr64 npcTriggers;
		};

		struct ClientTriggerBlendNode
		{
			float pointA[3];
			float pointB[3];
			unsigned short triggerA;
			unsigned short triggerB;
		};

		struct ClientTriggerBlend
		{
			unsigned short numClientTriggerBlendNodes;
			ClientTriggerBlendNode* __ptr64 blendNodes;
		};

		struct SpawnPointEntityRecord
		{
			unsigned short index;
			scr_string_t name;
			scr_string_t target;
			scr_string_t script_noteworthy;
			float origin[3];
			float angles[3];
		};

		struct SpawnPointRecordList
		{
			unsigned short spawnsCount;
			SpawnPointEntityRecord* __ptr64 spawns;
		};

		struct SplinePointEntityRecord
		{
			int splineId;
			int splineNodeId;
			char* __ptr64 splineNodeLabel;
			float splineNodeTension;
			float origin[3];
			float corridorDims[2];
			float tangent[3];
			float distToNextNode;
			VecInternal<3>* __ptr64 positionCubic;
			VecInternal<3>* __ptr64 tangentQuadratic;
		};

		struct SplinePointRecordList
		{
			unsigned short splinePointCount;
			float splineLength;
			SplinePointEntityRecord* __ptr64 splinePoints;
		};

		struct SplineRecordList
		{
			unsigned short splineCount;
			SplinePointRecordList* __ptr64 splines;
		};

		struct MapEnts
		{
			const char* __ptr64 name;
			char* __ptr64 entityString;
			int numEntityChars;
			MapTriggers trigger;
			ClientTriggers clientTrigger;
			ClientTriggerBlend clientTriggerBlend;
			SpawnPointRecordList spawnList;
			SplineRecordList splineList;
		};

		struct FxEffectDef;
		struct FxGlassDef
		{
			float halfThickness;
			float texVecs[2][2];
			GfxColor color;
			Material* __ptr64 material;
			Material* __ptr64 materialShattered;
			PhysPreset* __ptr64 physPreset;
			FxEffectDef* __ptr64 pieceBreakEffect;
			FxEffectDef* __ptr64 shatterEffect;
			FxEffectDef* __ptr64 shatterSmallEffect;
			FxEffectDef* __ptr64 crackDecalEffect;
			snd_alias_list_t* __ptr64 damagedSound;
			snd_alias_list_t* __ptr64 destroyedSound;
			snd_alias_list_t* __ptr64 destroyedQuietSound;
			char __pad[8];
			int numCrackRings;
			bool isOpaque;
		};

		struct FxSpatialFrame
		{
			float quat[4];
			float origin[3];
		};

		struct $03A8A7B39FA20F64B5AB79125E07CD62
		{
			FxSpatialFrame frame;
			float radius;
		};

		union FxGlassPiecePlace
		{
			$03A8A7B39FA20F64B5AB79125E07CD62 __s0;
			unsigned int nextFree;
		};

		struct FxGlassPieceState
		{
			float texCoordOrigin[2];
			unsigned int supportMask;
			unsigned short initIndex;
			unsigned short geoDataStart;
			unsigned short lightingIndex;
			unsigned char defIndex;
			unsigned char pad[3];
			unsigned char vertCount;
			unsigned char holeDataCount;
			unsigned char crackDataCount;
			unsigned char fanDataCount;
			unsigned short flags;
			float areaX2;
		};

		struct FxGlassPieceDynamics
		{
			int fallTime;
			__int64 physObjId;
			__int64 physJointId;
			float vel[3];
			float avel[3];
		};

		struct FxGlassVertex
		{
			short x;
			short y;
		};

		struct FxGlassHoleHeader
		{
			unsigned short uniqueVertCount;
			unsigned char touchVert;
			unsigned char pad[1];
		};

		struct FxGlassCrackHeader
		{
			unsigned short uniqueVertCount;
			unsigned char beginVertIndex;
			unsigned char endVertIndex;
		};

		union FxGlassGeometryData
		{
			FxGlassVertex vert;
			FxGlassHoleHeader hole;
			FxGlassCrackHeader crack;
			unsigned char asBytes[4];
			short anonymous[2];
		};

		struct FxGlassInitPieceState
		{
			FxSpatialFrame frame;
			float radius;
			float texCoordOrigin[2];
			unsigned int supportMask;
			float areaX2;
			unsigned short lightingIndex;
			unsigned char defIndex;
			unsigned char vertCount;
			unsigned char fanDataCount;
			unsigned char pad[1];
		};

		struct FxGlassSystem
		{
			int time;
			int prevTime;
			unsigned int defCount;
			unsigned int pieceLimit;
			unsigned int pieceWordCount;
			unsigned int initPieceCount;
			unsigned int cellCount;
			unsigned int activePieceCount;
			unsigned int firstFreePiece;
			unsigned int geoDataLimit;
			unsigned int geoDataCount;
			unsigned int initGeoDataCount;
			FxGlassDef* __ptr64 defs;
			FxGlassPiecePlace* __ptr64 piecePlaces;
			FxGlassPieceState* __ptr64 pieceStates;
			FxGlassPieceDynamics* __ptr64 pieceDynamics;
			FxGlassGeometryData* __ptr64 geoData;
			unsigned int* __ptr64 isInUse;
			unsigned int* __ptr64 cellBits;
			unsigned char* __ptr64 visData;
			VecInternal<3>* __ptr64 linkOrg; //float(* __ptr64 linkOrg)[3];
			float* __ptr64 halfThickness;
			unsigned short* __ptr64 lightingHandles;
			FxGlassInitPieceState* __ptr64 initPieceStates;
			FxGlassGeometryData* __ptr64 initGeoData;
			bool needToCompactData;
			unsigned char initCount;
			float effectChanceAccum;
			int lastPieceDeletionTime;
		};

		struct FxWorld
		{
			const char* __ptr64 name;
			FxGlassSystem glassSys;
		};

		struct GfxSky
		{
			int skySurfCount;
			int* __ptr64 skyStartSurfs;
			GfxImage* __ptr64 skyImage;
			unsigned __int8 skySamplerState;
		};

		struct GfxWorldDpvsPlanes
		{
			int cellCount;
			cplane_s* __ptr64 planes;
			unsigned __int16* __ptr64 nodes;
			unsigned int* __ptr64 sceneEntCellBits;
		};

		struct GfxCellTreeCount
		{
			int aabbTreeCount;
		};

		struct GfxAabbTree
		{
			Bounds bounds;
			unsigned __int16 childCount;
			unsigned __int16 surfaceCount;
			unsigned int startSurfIndex;
			unsigned __int16 smodelIndexCount;
			unsigned __int16* __ptr64 smodelIndexes;
			int childrenOffset;
		};

		struct GfxCellTree
		{
			GfxAabbTree* __ptr64 aabbTree;
		};

		struct GfxPortal;

		struct GfxPortalWritable
		{
			bool isQueued;
			bool isAncestor;
			unsigned __int8 recursionDepth;
			unsigned __int8 hullPointCount;
			float(* __ptr64 hullPoints)[2];
			GfxPortal* __ptr64 queuedParent;
		};

		struct DpvsPlane
		{
			float coeffs[4];
		};

		struct GfxPortal
		{
			GfxPortalWritable writable;
			DpvsPlane plane;
			float(* __ptr64 vertices)[3];
			unsigned __int16 cellIndex;
			unsigned __int16 closeDistance;
			unsigned __int8 vertexCount;
			float hullAxis[2][3];
		};

		struct GfxCell
		{
			Bounds bounds;
			int portalCount;
			GfxPortal* __ptr64 portals;
			unsigned __int8 reflectionProbeCount;
			unsigned __int8* __ptr64 reflectionProbes;
			unsigned __int8 reflectionProbeReferenceCount;
			unsigned __int8* __ptr64 reflectionProbeReferences;
		};

		struct GfxReflectionProbeVolumeData
		{
			float volumePlanes[6][4];
		};

		struct GfxReflectionProbe
		{
			float origin[3];
			GfxReflectionProbeVolumeData* __ptr64 probeVolumes;
			unsigned int probeVolumeCount;
		};

		struct GfxReflectionProbeReferenceOrigin
		{
			float origin[3];
		};

		struct GfxReflectionProbeReference
		{
			unsigned __int8 index;
		};

		struct GfxLightmapArray
		{
			GfxImage* __ptr64 primary;
			GfxImage* __ptr64 secondary;
		};

		struct GfxWorldVertex
		{
			float xyz[3];
			float binormalSign;
			GfxColor color;
			float texCoord[2];
			float lmapCoord[2];
			PackedUnitVec normal;
			PackedUnitVec tangent;
		};

		struct GfxWorldVertexData
		{
			GfxWorldVertex* __ptr64 vertices;
			void* __ptr64 worldVb; //ID3D11Buffer* __ptr64 worldVb;
		};

		struct GfxWorldVertexLayerData
		{
			unsigned __int8* __ptr64 data;
			void* __ptr64 layerVb; //ID3D11Buffer* __ptr64 layerVb;
		};

		struct GfxWorldDraw
		{
			unsigned int reflectionProbeCount;
			GfxImage* __ptr64* __ptr64 reflectionProbes;
			GfxReflectionProbe* __ptr64 reflectionProbeOrigins;
			GfxTexture* __ptr64 reflectionProbeTextures;
			unsigned int reflectionProbeReferenceCount;
			GfxReflectionProbeReferenceOrigin* __ptr64 reflectionProbeReferenceOrigins;
			GfxReflectionProbeReference* __ptr64 reflectionProbeReferences;
			int lightmapCount;
			GfxLightmapArray* __ptr64 lightmaps;
			GfxTexture* __ptr64 lightmapPrimaryTextures;
			GfxTexture* __ptr64 lightmapSecondaryTextures;
			GfxImage* __ptr64 lightmapOverridePrimary;
			GfxImage* __ptr64 lightmapOverrideSecondary;
			unsigned int trisType;
			unsigned int vertexCount;
			GfxWorldVertexData vd;
			unsigned int vertexLayerDataSize;
			GfxWorldVertexLayerData vld;
			unsigned int indexCount;
			unsigned __int16* __ptr64 indices;
			void* __ptr64 indexBuffer; //ID3D11Buffer* __ptr64 indexBuffer;
		};

		struct GfxLightGridEntry
		{
			unsigned int colorsIndex;
			unsigned __int16 primaryLightEnvIndex;
			unsigned __int8 unused;
			unsigned __int8 needsTrace;
		};

		struct GfxLightGridColors
		{
			unsigned __int8 rgb[56][3];
		};

		struct GfxLightGridColorsHDR
		{
			float colorVec3[56][3];
		};

		struct GfxLightGridTree
		{
			unsigned __int8 maxDepth;
			int nodeCount;
			int leafCount;
			int coordMinGridSpace[3];
			int coordMaxGridSpace[3];
			int coordHalfSizeGridSpace[3];
			int defaultColorIndexBitCount;
			int defaultLightIndexBitCount;
			unsigned int* __ptr64 p_nodeTable;
			int leafTableSize;
			unsigned __int8* __ptr64 p_leafTable;
		};

		struct GfxLightGrid
		{
			bool hasLightRegions;
			bool useSkyForLowZ;
			unsigned int lastSunPrimaryLightIndex;
			unsigned __int16 mins[3];
			unsigned __int16 maxs[3];
			unsigned int rowAxis;
			unsigned int colAxis;
			unsigned __int16* __ptr64 rowDataStart;
			unsigned int rawRowDataSize;
			unsigned __int8* __ptr64 rawRowData;
			unsigned int entryCount;
			GfxLightGridEntry* __ptr64 entries;
			unsigned int colorCount;
			GfxLightGridColors* __ptr64 colors;
			unsigned int missingGridColorIndex;
			int tableVersion;
			int paletteVersion;
			char rangeExponent8BitsEncoding;
			char rangeExponent12BitsEncoding;
			char rangeExponent16BitsEncoding;
			unsigned __int8 stageCount;
			float* __ptr64 stageLightingContrastGain;
			unsigned int paletteEntryCount;
			int* __ptr64 paletteEntryAddress;
			unsigned int paletteBitstreamSize;
			unsigned __int8* __ptr64 paletteBitstream;
			GfxLightGridColorsHDR skyLightGridColors;
			GfxLightGridColorsHDR defaultLightGridColors;
			GfxLightGridTree tree;
		};

		struct GfxBrushModelWritable
		{
			Bounds bounds;
		};

		struct GfxBrushModel
		{
			GfxBrushModelWritable writable;
			Bounds bounds;
			float radius;
			unsigned int startSurfIndex;
			unsigned __int16 surfaceCount;
		};

		struct MaterialMemory
		{
			Material* __ptr64 material;
			int memory;
		};

		struct sunflare_t
		{
			bool hasValidData;
			Material* __ptr64 spriteMaterial;
			Material* __ptr64 flareMaterial;
			float spriteSize;
			float flareMinSize;
			float flareMinDot;
			float flareMaxSize;
			float flareMaxDot;
			float flareMaxAlpha;
			int flareFadeInTime;
			int flareFadeOutTime;
			float blindMinDot;
			float blindMaxDot;
			float blindMaxDarken;
			int blindFadeInTime;
			int blindFadeOutTime;
			float glareMinDot;
			float glareMaxDot;
			float glareMaxLighten;
			int glareFadeInTime;
			int glareFadeOutTime;
			float sunFxPosition[3];
		};

		struct XModelDrawInfo
		{
			unsigned __int8 hasGfxEntIndex;
			unsigned __int8 lod;
			unsigned __int16 surfId;
		};

		struct GfxSceneDynModel
		{
			XModelDrawInfo info;
			unsigned __int16 dynEntId;
		};

		struct BModelDrawInfo
		{
			unsigned __int16 surfId;
		};

		struct GfxSceneDynBrush
		{
			BModelDrawInfo info;
			unsigned __int16 dynEntId;
		};

		struct GfxShadowGeometry
		{
			unsigned __int16 surfaceCount;
			unsigned __int16 smodelCount;
			unsigned int* __ptr64 sortedSurfIndex;
			unsigned __int16* __ptr64 smodelIndex;
		};

		struct GfxLightRegionAxis
		{
			float dir[3];
			float midPoint;
			float halfSize;
		};

		struct GfxLightRegionHull
		{
			float kdopMidPoint[9];
			float kdopHalfSize[9];
			unsigned int axisCount;
			GfxLightRegionAxis* __ptr64 axis;
		};

		struct GfxLightRegion
		{
			unsigned int hullCount;
			GfxLightRegionHull* __ptr64 hulls;
		};

		struct GfxStaticModelInst
		{
			Bounds bounds;
			float lightingOrigin[3];
		};

		struct srfTriangles_t
		{
			unsigned int vertexLayerData;
			unsigned int firstVertex;
			float maxEdgeLength;
			unsigned __int16 vertexCount;
			unsigned __int16 triCount;
			unsigned int baseIndex;
		};

		struct GfxSurfaceLightingAndFlagsFields
		{
			unsigned __int8 lightmapIndex;
			unsigned __int8 reflectionProbeIndex;
			unsigned __int16 primaryLightEnvIndex;
			unsigned __int8 flags;
			unsigned __int8 unused[3];
		};

		union GfxSurfaceLightingAndFlags
		{
			GfxSurfaceLightingAndFlagsFields fields;
			unsigned __int64 packed;
		};

		struct GfxSurface
		{
			srfTriangles_t tris;
			Material* __ptr64 material;
			GfxSurfaceLightingAndFlags laf;
		};

		struct GfxSurfaceBounds
		{
			Bounds bounds;
			unsigned __int8 flags;
			char __pad[8];
		};

		struct GfxPackedPlacement
		{
			float origin[3];
			float axis[3][3];
			float scale;
		};

		struct GfxStaticModelVertexLighting
		{
			unsigned __int8 visibility[4];
			unsigned __int16 ambientColorFloat16[4];
			unsigned __int16 highlightColorFloat16[4];
		};

		struct GfxStaticModelVertexLightingInfo
		{
			GfxStaticModelVertexLighting* __ptr64 lightingValues;
			void* __ptr64 lightingValuesVb; //ID3D11Buffer* __ptr64 lightingValuesVb;
			int flags;
			char __pad[4];
			struct unk
			{
				char __pad[24];
			};
			unk unk;
			char __pad2[4];
			unsigned int numLightingValues;
		};

		struct GfxStaticModelLightmapInfo
		{
			float offset[2];
			float scale[2];
			unsigned int lightmapIndex;
		};

		struct GfxStaticModelDrawInst
		{
			GfxPackedPlacement placement;
			XModel* __ptr64 model;
			float groundLighting[4];
			GfxStaticModelVertexLightingInfo vertexLightingInfo;
			GfxStaticModelLightmapInfo modelLightmapInfo;
			unsigned __int16 lightingHandle;
			unsigned __int16 cullDist;
			unsigned __int16 flags;
			unsigned __int16 staticModelId;
			unsigned __int16 primaryLightEnvIndex;
			unsigned __int8 reflectionProbeIndex;
			unsigned __int8 firstMtlSkinIndex;
			unsigned __int8 sunShadowFlags;
		};

		struct GfxWorldDpvsStatic
		{
			unsigned int smodelCount; // 0
			unsigned int staticSurfaceCount; // 4
			unsigned int litOpaqueSurfsBegin; // 8
			unsigned int litOpaqueSurfsEnd; // 12
			unsigned int litDecalSurfsBegin; // 16
			unsigned int litDecalSurfsEnd; // 20
			unsigned int litTransSurfsBegin; // 24
			unsigned int litTransSurfsEnd; // 28
			unsigned int shadowCasterSurfsBegin; // 32
			unsigned int shadowCasterSurfsEnd; // 36
			unsigned int emissiveSurfsBegin; // 40
			unsigned int emissiveSurfsEnd; // 44
			unsigned int smodelVisDataCount; // 48
			unsigned int surfaceVisDataCount; // 52
			unsigned int* __ptr64 smodelVisData[3]; // 56
			unsigned int* __ptr64 surfaceVisData[3]; // 80
			unsigned int* __ptr64 tessellationCutoffVisData[3]; // 104
			unsigned int* __ptr64 unknownData[3]; // 128
			unsigned int* __ptr64 lodData; // 152
			unsigned int* __ptr64 unknownData2[3]; // 160
			unsigned int* __ptr64 sortedSurfIndex; // 184
			GfxStaticModelInst* __ptr64 smodelInsts; // 192
			GfxSurface* __ptr64 surfaces; // 200
			GfxSurfaceBounds* __ptr64 surfacesBounds; // 208
			GfxStaticModelDrawInst* __ptr64 smodelDrawInsts; // 216
			GfxDrawSurf* __ptr64 surfaceMaterials; // 224
			unsigned int* __ptr64 surfaceCastsSunShadow; // 232
			unsigned int sunShadowOptCount; // 240
			unsigned int sunSurfVisDataCount; // 244
			unsigned int* __ptr64 surfaceCastsSunShadowOpt; // 248
			char* __ptr64 * __ptr64 constantBuffersLit; // 256
			char* __ptr64 * __ptr64 constantBuffersAmbient; // 264
			volatile int usageCount; // 272
		};

		struct GfxWorldDpvsDynamic
		{
			unsigned int dynEntClientWordCount[2];
			unsigned int dynEntClientCount[2];
			unsigned int* __ptr64 dynEntCellBits[2];
			unsigned __int8* __ptr64 dynEntVisData[2][3];
		};

		struct GfxHeroOnlyLight
		{
			unsigned __int8 type;
			unsigned __int8 unused[3];
			float color[3];
			float dir[3];
			float up[3];
			float origin[3];
			float radius;
			float cosHalfFovOuter;
			float cosHalfFovInner;
			int exponent;
		};

		struct GfxWorld
		{
			const char* __ptr64 name; // 0
			const char* __ptr64 baseName; // 8
			unsigned int bspVersion; // 16
			int planeCount; // 20
			int nodeCount; // 24
			unsigned int surfaceCount; // 28
			int skyCount; // 32
			GfxSky* __ptr64 skies; // 40
			unsigned int lastSunPrimaryLightIndex; // 48
			unsigned int primaryLightCount; // 52
			unsigned int primaryLightEnvCount; // 56
			unsigned int sortKeyLitDecal; // 60
			unsigned int sortKeyEffectDecal; // 64
			unsigned int sortKeyTopDecal; // 68
			unsigned int sortKeyEffectAuto; // 72
			unsigned int sortKeyDistortion; // 76
			GfxWorldDpvsPlanes dpvsPlanes; // 80
			GfxCellTreeCount* __ptr64 aabbTreeCounts; // 112
			GfxCellTree* __ptr64 aabbTrees; // 120
			GfxCell* __ptr64 cells; // 128
			GfxWorldDraw draw; // 136
			GfxLightGrid lightGrid; // 312
			int modelCount; // 1880
			GfxBrushModel* __ptr64 models; // 1888
			Bounds bounds; // 1896
			unsigned int checksum; // 1920
			int materialMemoryCount; // 1924
			MaterialMemory* __ptr64 materialMemory; // 1928
			sunflare_t sun; // 1936
			float outdoorLookupMatrix[4][4]; // 2160
			GfxImage* __ptr64 outdoorImage; // 2176
			unsigned int* __ptr64 cellCasterBits; // 2120
			unsigned int* __ptr64 cellHasSunLitSurfsBits; // 2128
			GfxSceneDynModel* __ptr64 sceneDynModel; // 2136
			GfxSceneDynBrush* __ptr64 sceneDynBrush; // 2144
			unsigned int* __ptr64 primaryLightEntityShadowVis; // 2152
			unsigned int* __ptr64 primaryLightDynEntShadowVis[2]; // 2160
			unsigned __int16* __ptr64 nonSunPrimaryLightForModelDynEnt; // 2176
			GfxShadowGeometry* __ptr64 shadowGeom; // 2184
			GfxShadowGeometry* __ptr64 shadowGeomOptimized; // 2192
			GfxLightRegion* __ptr64 lightRegion; // 2200
			GfxWorldDpvsStatic dpvs; // 2208
			GfxWorldDpvsDynamic dpvsDyn; // 2488
			unsigned int mapVtxChecksum; // 2512
			unsigned int heroOnlyLightCount; // 2520
			GfxHeroOnlyLight* __ptr64 heroOnlyLights; // 2520
			unsigned __int8 fogTypesAllowed; // 2528
			unsigned int unknownCount; // 2588
			char* __ptr64 unknown; // 2592
			char* __ptr64 * __ptr64 unknownBuffer; // 2600
		};

		struct ClipMaterial
		{
			const char* __ptr64 name;
			int surfaceFlags;
			int contents;
		};

		struct cLeafBrushNodeLeaf_t
		{
			unsigned __int16* __ptr64 brushes;
		};

		struct cLeafBrushNodeChildren_t
		{
			float dist;
			float range;
			unsigned __int16 childOffset[2];
		};

		union cLeafBrushNodeData_t
		{
			cLeafBrushNodeLeaf_t leaf;
			cLeafBrushNodeChildren_t children;
		};

		struct cLeafBrushNode_s
		{
			unsigned __int8 axis;
			__int16 leafBrushCount;
			int contents;
			cLeafBrushNodeData_t data;
		};

		struct ClipInfo
		{
			int planeCount;
			cplane_s* __ptr64 planes;
			unsigned int numMaterials;
			ClipMaterial* __ptr64 materials;
			unsigned int numBrushSides;
			cbrushside_t* __ptr64 brushsides;
			unsigned int numBrushEdges;
			cbrushedge_t* __ptr64 brushEdges;
			unsigned int leafbrushNodesCount;
			cLeafBrushNode_s* __ptr64 leafbrushNodes;
			unsigned int numLeafBrushes;
			unsigned __int16* __ptr64 leafbrushes;
			unsigned __int16 numBrushes;
			cbrush_t* __ptr64 brushes;
			Bounds* __ptr64 brushBounds;
			int* __ptr64 brushContents;
		};

		struct cStaticModel_s
		{
			XModel* __ptr64 xmodel;
			float origin[3];
			float invScaledAxis[3][3];
			Bounds absBounds;
		};

		struct cNode_t
		{
			cplane_s* __ptr64 plane;
			__int16 children[2];
		};

		struct cLeaf_t
		{
			unsigned __int16 firstCollAabbIndex;
			unsigned __int16 collAabbCount;
			int brushContents;
			int terrainContents;
			Bounds bounds;
			int leafBrushNode;
		};

		struct CollisionBorder
		{
			float distEq[3];
			float zBase;
			float zSlope;
			float start;
			float length;
		};

		struct CollisionPartition
		{
			unsigned __int8 triCount;
			unsigned __int8 borderCount;
			unsigned __int8 firstVertSegment;
			int firstTri;
			CollisionBorder* __ptr64 borders;
		};

		union CollisionAabbTreeIndex
		{
			int firstChildIndex;
			int partitionIndex;
		};

		struct CollisionAabbTree
		{
			float midPoint[3];
			unsigned __int16 materialIndex;
			unsigned __int16 childCount;
			float halfSize[3];
			CollisionAabbTreeIndex u;
		};

		struct cmodel_t
		{
			Bounds bounds;
			float radius;
			ClipInfo* __ptr64 info;
			cLeaf_t leaf;
		};

		struct Stage
		{
			const char* __ptr64 name;
			float origin[3];
			unsigned __int16 triggerIndex;
			unsigned __int8 sunPrimaryLightIndex;
		};

		struct SModelAabbNode
		{
			Bounds bounds;
			unsigned __int16 firstChild;
			unsigned __int16 childCount;
		};

		enum DynEntityType : __int32
		{
			DYNENT_TYPE_INVALID = 0x0,
			DYNENT_TYPE_CLUTTER = 0x1,
			DYNENT_TYPE_DESTRUCT = 0x2,
			DYNENT_TYPE_HINGE = 0x3,
			DYNENT_TYPE_SCRIPTABLEINST = 0x4,
			DYNENT_TYPE_SCRIPTABLEPHYSICS = 0x5,
			DYNENT_TYPE_LINKED = 0x6,
			DYNENT_TYPE_LINKED_NOSHADOW = 0x7,
			DYNENT_TYPE_COUNT = 0x8,
		};

		struct GfxPlacement
		{
			float quat[4];
			float origin[3];
		};

		struct DynEntityHingeDef
		{
			float axisOrigin[3];
			float axisDir[3];
			bool isLimited;
			float angleMin;
			float angleMax;
			float momentOfInertia;
			float friction;
		};

		struct DynEntityLinkToDef
		{
			int anchorIndex;
			float originOffset[3];
			float angleOffset[3];
		};

		struct DynEntityDef
		{
			DynEntityType type;
			GfxPlacement pose;
			XModel* __ptr64 baseModel; //const XModel* __ptr64 baseModel;
			unsigned __int16 brushModel;
			unsigned __int16 physicsBrushModel;
			unsigned __int16 scriptableIndex;
			unsigned __int16 health;
			FxEffectDef* __ptr64 destroyFx; //const FxEffectDef* __ptr64 destroyFx;
			PhysPreset* __ptr64 physPreset;
			DynEntityHingeDef* __ptr64 hinge;
			DynEntityLinkToDef* __ptr64 linkTo;
			PhysMass mass;
			int contents;
		};

		struct DynEntityPose
		{
			GfxPlacement pose;
			float radius;
		};

		struct Hinge
		{
			float angle;
			float quat[4];
			float angularVel;
			float torqueAccum;
			bool active;
			float autoDisableTimeLeft;
			DynEntityHingeDef* __ptr64 def; //const DynEntityHingeDef* __ptr64 def;
			PhysPreset* __ptr64 physPreset; //const PhysPreset* __ptr64 physPreset;
			float centerOfMassRelToAxisOriginAtAngleZero[3];
		};

		struct DynEntityClient
		{
			__int64 physObjId;
			unsigned __int16 flags;
			unsigned __int16 lightingHandle;
			unsigned __int16 health;
			Hinge* __ptr64 hinge;
			XModel* __ptr64 activeModel; //const XModel* __ptr64 activeModel;
			int contents;
		};

		struct DynEntityColl
		{
			unsigned __int16 sector;
			unsigned __int16 nextEntInSector;
			float linkMins[2];
			float linkMaxs[2];
		};

		enum ScriptableEventType : __int32
		{
			SCRIPTABLE_EVENT_MODEL = 0x0,
			SCRIPTABLE_EVENT_FX = 0x1,
			SCRIPTABLE_EVENT_SOUND = 0x2,
			SCRIPTABLE_EVENT_ANIMATION = 0x3,
			SCRIPTABLE_EVENT_EXPLODE = 0x4,
			SCRIPTABLE_EVENT_HEALTHDRAIN = 0x5,
			SCRIPTABLE_EVENT_PHYSICSLAUNCH = 0x6,
			SCRIPTABLE_EVENT_LIGHTSETTINGS = 0x7,
			SCRIPTABLE_EVENT_SUNLIGHTSETTINGS = 0x8,
			SCRIPTABLE_EVENT_SHAKE = 0x9,
			SCRIPTABLE_EVENT_STATECHANGE = 0xA,
			SCRIPTABLE_EVENT_COUNT = 0xB,
		};

		struct ScriptableEventStateChangeDef
		{
			unsigned __int8 targetIndex;
			unsigned __int8 delayStreamIndex;
			unsigned __int16 delayMin;
			unsigned __int16 delayMax;
		};

		struct ScriptableEventModelDef
		{
			XModel* __ptr64 model;
		};

		struct ScriptableEventFxDef
		{
			FxEffectDef* __ptr64 handle; //const FxEffectDef* __ptr64 handle;
			scr_string_t tagName;
			unsigned __int16 loopTime;
			unsigned __int8 loopTimeStreamIndex;
			bool tagUseAngles;
		};

		struct ScriptableEventSoundDef
		{
			snd_alias_list_t* __ptr64 alias;
			bool looping;
		};

		struct ScriptableEventAnimationDef
		{
			const char* __ptr64 animName;
			bool override;
			bool stateful;
			unsigned __int8 animEntryIndex;
			unsigned __int8 animPlaybackStreamIndex;
			unsigned __int16 timeOffsetMin;
			unsigned __int16 timeOffsetMax;
			unsigned __int16 playbackRateMin;
			unsigned __int16 playbackRateMax;
			unsigned __int16 blendTime;
		};

		struct ScriptableEventExplodeDef
		{
			unsigned __int16 forceMin;
			unsigned __int16 forceMax;
			unsigned __int16 radius;
			unsigned __int16 damageMin;
			unsigned __int16 damageMax;
			bool aiAvoid;
		};

		struct ScriptableEventHealthDef
		{
			unsigned __int16 amount;
			unsigned __int16 interval;
			unsigned __int16 badPlaceRadius;
			unsigned __int8 streamIndex;
		};

		struct ScriptableEventPhysicsDef
		{
			XModel* __ptr64 model;
			unsigned __int8 launchDirX;
			unsigned __int8 launchDirY;
			unsigned __int8 launchDirZ;
			unsigned __int16 explForceScale;
			unsigned __int16 bulletForceScale;
		};

		struct ScriptableEventLightSettingsDef
		{
			unsigned __int8 color[4];
			unsigned __int8 lightIndexConstIndex;
			unsigned __int8 transStateStreamIndex;
			unsigned __int8 useColor;
			unsigned __int8 useStateTransitionTime;
			unsigned __int16 intensityScaleMin;
			unsigned __int16 intensityScaleMax;
			unsigned __int16 radiusScaleMin;
			unsigned __int16 radiusScaleMax;
			const char* __ptr64 noteworthy;
			unsigned __int16 transitionTimeMin;
			unsigned __int16 transitionTimeMax;
		};

		struct ScriptableEventSunlightSettingsDef
		{
			unsigned __int8 color[4];
			unsigned __int8 transStateStreamIndex;
			unsigned __int8 flags;
			unsigned __int16 intensityScaleMin;
			unsigned __int16 intensityScaleMax;
			unsigned __int16 pitchMin;
			unsigned __int16 pitchMax;
			unsigned __int16 headingMin;
			unsigned __int16 headingMax;
			unsigned __int16 transitionTimeMin;
			unsigned __int16 transitionTimeMax;
		};

		struct ScriptableEventShakeDef
		{
			const char* __ptr64 rumbleName;
			unsigned __int16 duration;
			unsigned __int16 durationFadeUp;
			unsigned __int16 durationFadeDown;
			unsigned __int16 radius;
			unsigned __int16 exponent;
			unsigned __int16 scaleEarthquake;
			unsigned __int8 scalePitch;
			unsigned __int8 scaleYaw;
			unsigned __int8 scaleRoll;
			unsigned __int8 frequencyPitch;
			unsigned __int8 frequencyYaw;
			unsigned __int8 frequencyRoll;
			unsigned __int8 flags;
		};

		union ScriptableEventDataUnion
		{
			ScriptableEventStateChangeDef stateChange;
			ScriptableEventModelDef setModel;
			ScriptableEventFxDef playFx;
			ScriptableEventSoundDef playSound;
			ScriptableEventAnimationDef playAnim;
			ScriptableEventExplodeDef doExplosion;
			ScriptableEventHealthDef healthDrain;
			ScriptableEventPhysicsDef physicsLaunch;
			ScriptableEventLightSettingsDef lightSettings;
			ScriptableEventSunlightSettingsDef sunlightSettings;
			ScriptableEventShakeDef shake;
		};

		struct ScriptableEventDef
		{
			ScriptableEventType type;
			ScriptableEventDataUnion data;
		};

		struct ScriptableStateDef
		{
			scr_string_t name;
			scr_string_t tagName;
			ScriptableEventDef* __ptr64 onEnterEvents;
			unsigned __int8 onEnterEventCount;
			unsigned __int8 damageFlags;
			unsigned __int8 damageParentTransferRate;
			unsigned __int8 damageParentReceiveRate;
			unsigned __int16 maxHealth;
		};

		struct ScriptablePartDef
		{
			ScriptableStateDef* __ptr64 states;
			scr_string_t name;
			unsigned __int8 stateCount;
			unsigned __int8 flags;
			unsigned __int8 eventStreamTimeRemainIndex;
			unsigned __int8 eventStreamNextChangeTimeIndex;
		};

		enum ScriptableNotetrackType : __int32
		{
			SCRIPTABLE_NT_FX = 0x0,
			SCRIPTABLE_NT_SOUND = 0x1,
			SCRIPTABLE_NT_COUNT = 0x2,
		};

		struct ScriptableNotetrackFxDef
		{
			FxEffectDef* __ptr64 handle; //const FxEffectDef* __ptr64 handle;
			scr_string_t tagName;
			bool useAngles;
		};

		struct ScriptableNotetrackSoundDef
		{
			snd_alias_list_t* __ptr64 alias;
		};

		union ScriptableNotetrackDataUnion
		{
			ScriptableNotetrackFxDef playFx;
			ScriptableNotetrackSoundDef playSound;
		};

		struct ScriptableNotetrackDef
		{
			scr_string_t name;
			ScriptableNotetrackType type;
			ScriptableNotetrackDataUnion data;
		};

		enum ScriptableType : __int32
		{
			SCRIPTABLE_TYPE_GENERAL = 0x0,
			SCRIPTABLE_TYPE_CHARACTER = 0x1,
			SCRIPTABLE_TYPE_COUNT = 0x2,
		};

		struct ScriptableDef
		{
			const char* __ptr64 name;
			XModel* __ptr64 baseModel;
			const char* __ptr64 baseCollisionBrush;
			const char* __ptr64 destroyedCollisionBrush;
			ScriptablePartDef* __ptr64 parts;
			ScriptableNotetrackDef* __ptr64 notetracks;
			ScriptableType type;
			unsigned __int8 flags;
			unsigned __int8 partCount;
			unsigned __int8 serverInstancePartCount;
			unsigned __int8 serverControlledPartCount;
			unsigned __int8 notetrackCount;
			unsigned __int8 eventStreamSize;
			unsigned __int8 eventConstantsSize;
		};

		struct ScriptableInstancePartState
		{
			unsigned __int16 curHealth;
			unsigned __int8 lastExecutedStateIndex;
			unsigned __int8 stateIndex;
		};

		struct ScriptableInstance
		{
			ScriptableDef* __ptr64 def;
			unsigned __int8* __ptr64 eventConstantsBuf;
			float origin[3];
			float angles[3];
			scr_string_t targetname;
			unsigned __int16 preBrushModel;
			unsigned __int16 postBrushModel;
			unsigned __int8 flags;
			XModel* __ptr64 currentModel;
			ScriptableInstancePartState* __ptr64 partStates;
			unsigned __int8* __ptr64 eventStreamBuf;
			unsigned int currentPartBits[8];
			unsigned int damageOwnerEntHandle;
			unsigned __int16 updateNextInstance;
			unsigned __int16 linkedObject;
		};

		struct ScriptableAnimationEntry
		{
			const char* __ptr64 animName;
			unsigned __int64 runtimeBuf;
		};

		struct ScriptableMapEnts
		{
			unsigned int instanceStateSize;
			unsigned int instanceCount;
			unsigned int reservedInstanceCount;
			ScriptableInstance* __ptr64 instances;
			unsigned int animEntryCount;
			ScriptableAnimationEntry* __ptr64 animEntries;
			unsigned int replicatedInstanceCount;
		};

		struct clipMap_t // alignas(128)
		{
			const char* __ptr64 name;
			int isInUse;
			ClipInfo info;
			ClipInfo* __ptr64 pInfo;
			unsigned int numStaticModels;
			cStaticModel_s* __ptr64 staticModelList;
			unsigned int numNodes;
			cNode_t* __ptr64 nodes;
			unsigned int numLeafs;
			cLeaf_t* __ptr64 leafs;
			unsigned int vertCount;
			VecInternal<3>* __ptr64 verts; //float(* __ptr64 verts)[3];
			int triCount;
			unsigned __int16* __ptr64 triIndices;
			unsigned __int8* __ptr64 triEdgeIsWalkable;
			int borderCount;
			CollisionBorder* __ptr64 borders;
			int partitionCount;
			CollisionPartition* __ptr64 partitions;
			int aabbTreeCount;
			CollisionAabbTree* __ptr64 aabbTrees;
			unsigned int numSubModels;
			cmodel_t* __ptr64 cmodels;
			MapEnts* __ptr64 mapEnts;
			Stage* __ptr64 stages;
			unsigned __int8 stageCount;
			MapTriggers stageTrigger;
			unsigned __int16 smodelNodeCount;
			SModelAabbNode* __ptr64 smodelNodes;
			unsigned __int16 dynEntCount[2];
			DynEntityDef* __ptr64 dynEntDefList[2];
			DynEntityPose* __ptr64 dynEntPoseList[2];
			DynEntityClient* __ptr64 dynEntClientList[2];
			DynEntityColl* __ptr64 dynEntCollList[2];
			unsigned int dynEntAnchorCount;
			scr_string_t* __ptr64 dynEntAnchorNames;
			ScriptableMapEnts scriptableMapEnts;
			unsigned int checksum;
			char __pad[108]; // alignment padding
		};

		struct Font_s
		{
			union
			{
				const char* __ptr64 fontName;
				const char* __ptr64 name;
			};
			int pixelHeight;
			int glyphCount;
			Material* __ptr64 material;
			Material* __ptr64 glowMaterial;
			Glyph* __ptr64 glyphs;
		};

		struct FxFloatRange
		{
			float base;
			float amplitude;
		};

		struct FxSpawnDefLooping
		{
			int intervalMsec;
			int count;
		};

		struct FxIntRange
		{
			int base;
			int amplitude;
		};

		struct FxSpawnDefOneShot
		{
			FxIntRange count;
		};

		union FxSpawnDef
		{
			FxSpawnDefLooping looping;
			FxSpawnDefOneShot oneShot;
		};

		struct FxElemAtlas
		{
			unsigned char behavior;
			unsigned char index;
			unsigned char fps;
			unsigned char loopCount;
			unsigned char colIndexBits;
			unsigned char rowIndexBits;
			short entryCount;
		};

		struct FxEffectDef;
		union FxEffectDefRef
		{
			FxEffectDef* __ptr64 handle;
			const char* __ptr64 name;
		};

		struct FxElemVec3Range
		{
			float base[3];
			float amplitude[3];
		};

		struct FxElemVelStateInFrame
		{
			FxElemVec3Range velocity;
			FxElemVec3Range totalDelta;
		};

		const struct FxElemVelStateSample
		{
			FxElemVelStateInFrame local;
			FxElemVelStateInFrame world;
		};

		struct FxElemVisualState
		{
			float color[4];
			float unlitHDRScale;
			float rotationDelta;
			float rotationTotal;
			float size[2];
			float scale;
		};

		const struct FxElemVisStateSample
		{
			FxElemVisualState base;
			FxElemVisualState amplitude;
		};

		struct FxParticleSimAnimationHeader
		{
			float playbackRate;
			float duration;
			unsigned int frameCount;
			float minX;
			float minY;
			float minZ;
			float boundsXDelta;
			float boundsYDelta;
			float boundsZDelta;
			float maxWidth;
			float maxHeight;
			unsigned int colorTableSize;
			unsigned int particleDataCount;
			bool evalVisStatePerParticle;
			bool sortParticlesAtRuntime;
		};

		struct FxParticleSimAnimationParticleData
		{
			unsigned short xNormalizedPos;
			unsigned short yNormalizedPos;
			unsigned short zNormalizedPos;
			unsigned short xNormalizedWidth;
			unsigned short yNormalizedHeight;
			unsigned short orientation;
			unsigned short lifetime;
			unsigned short particleID;
			unsigned short xNormalizedPosNextFrame;
			unsigned short yNormalizedPosNextFrame;
			unsigned short zNormalizedPosNextFrame;
			unsigned short xNormalizedWidthNextFrame;
			unsigned short yNormalizedHeightNextFrame;
			short orientationDelta;
			unsigned short colorTableIndex;
			unsigned short nextColorTableIndex;
		};

		struct FxParticleSimAnimationFrame
		{
			unsigned int particleDataOffset;
			unsigned int numActiveParticles;
		};

		struct FxParticleSimAnimation
		{
			const char* __ptr64 name;
			Material* __ptr64 material;
			FxParticleSimAnimationHeader header;
			FxParticleSimAnimationParticleData* __ptr64 particleData;
			FxParticleSimAnimationFrame* __ptr64 frames;
			GfxColorFloat* __ptr64 colorTable;
		};

		union FxElemVisuals
		{
			const void* __ptr64 anonymous;
			Material* __ptr64 material;
			XModel* __ptr64 model;
			FxEffectDefRef effectDef;
			const char* __ptr64 soundName;
			const char* __ptr64 vectorFieldName;
			GfxLightDef* __ptr64 lightDef;
			FxParticleSimAnimation* __ptr64 particleSimAnimation;
		};

		struct FxElemMarkVisuals
		{
			Material* __ptr64 materials[3];
		};

		union FxElemDefVisuals
		{
			FxElemMarkVisuals* __ptr64 markArray;
			FxElemVisuals* __ptr64 array;
			FxElemVisuals instance;
		};

		struct FxTrailVertex
		{
			float pos[2];
			float normal[2];
			float texCoord[2];
		};

		struct FxTrailDef
		{
			int scrollTimeMsec;
			int repeatDist;
			float invSplitDist;
			float invSplitArcDist;
			float invSplitTime;
			int vertCount;
			FxTrailVertex* __ptr64 verts;
			int indCount;
			unsigned short* __ptr64 inds;
		};

		struct FxSparkFountainDef
		{
			float gravity;
			float bounceFrac;
			float bounceRand;
			float sparkSpacing;
			float sparkLength;
			int sparkCount;
			float loopTime;
			float velMin;
			float velMax;
			float velConeFrac;
			float restSpeed;
			float boostTime;
			float boostFactor;
		};

		struct FxSpotLightDef
		{
			float fovInnerFraction;
			float startRadius;
			float endRadius;
			float brightness;
			float maxLength;
			int exponent;
		};

		struct FxFlareDef
		{
			float position;
			int angularRotCount;
			int flags;
			FxFloatRange depthScaleRange;
			FxFloatRange depthScaleValue;
			FxFloatRange radialRot;
			FxFloatRange radialScaleX;
			FxFloatRange radialScaleY;
			float dir[3];
			int intensityXIntervalCount;
			int intensityYIntervalCount;
			int srcCosIntensityIntervalCount;
			int srcCosScaleIntervalCount;
			float* __ptr64 intensityX;
			float* __ptr64 intensityY;
			float* __ptr64 srcCosIntensity;
			float* __ptr64 srcCosScale;
		};

		union FxElemExtendedDefPtr
		{
			FxTrailDef* __ptr64 trailDef;
			FxSparkFountainDef* __ptr64 sparkFountainDef;
			FxSpotLightDef* __ptr64 spotLightDef;
			FxFlareDef* __ptr64 flareDef;
			char* __ptr64 unknownDef;
		};

		const struct FxElemDef
		{
			int flags;
			int flags2;
			FxSpawnDef spawn;
			FxFloatRange spawnRange;
			FxFloatRange fadeInRange;
			FxFloatRange fadeOutRange;
			float spawnFrustumCullRadius;
			FxIntRange spawnDelayMsec;
			FxIntRange lifeSpanMsec;
			FxFloatRange spawnOrigin[3];
			FxFloatRange spawnOffsetRadius;
			FxFloatRange spawnOffsetHeight;
			FxFloatRange spawnAngles[3];
			FxFloatRange angularVelocity[3];
			FxFloatRange initialRotation;
			FxFloatRange gravity;
			FxFloatRange reflectionFactor;
			FxElemAtlas atlas;
			unsigned char elemType;
			unsigned char elemLitType;
			unsigned char visualCount;
			unsigned char velIntervalCount;
			unsigned char visStateIntervalCount;
			FxElemVelStateSample* __ptr64 velSamples;
			FxElemVisStateSample* __ptr64 visSamples;
			FxElemDefVisuals visuals;
			Bounds collBounds;
			FxEffectDefRef effectOnImpact;
			FxEffectDefRef effectOnDeath;
			FxEffectDefRef effectEmitted;
			FxFloatRange emitDist;
			FxFloatRange emitDistVariance;
			FxElemExtendedDefPtr extended;
			unsigned char sortOrder;
			unsigned char lightingFrac;
			unsigned char useItemClip;
			unsigned char fadeInfo;
			int randomSeed;
			float litMaxColorChangePerSec;
			float unlitHDRScalar;
			float litHDRScalar;
			float litUnlitBlendFactor;
		};

		struct FxEffectDef
		{
			const char* __ptr64 name;
			int flags;
			int totalSize;
			int msecLoopingLife;
			int elemDefCountLooping;
			int elemDefCountOneShot;
			int elemDefCountEmission;
			float elemMaxRadius;
			float occlusionQueryDepthBias;
			int occlusionQueryFadeIn;
			int occlusionQueryFadeOut;
			FxFloatRange occlusionQueryScaleRange;
			FxElemDef* __ptr64 elemDefs;
		};

		enum weaponIconRatioType_t : std::int32_t
		{
			WEAPON_ICON_RATIO_1TO1 = 0x0,
			WEAPON_ICON_RATIO_2TO1 = 0x1,
			WEAPON_ICON_RATIO_4TO1 = 0x2,
			WEAPON_ICON_RATIO_COUNT = 0x3,
		};

		enum ammoCounterClipType_t : std::int32_t
		{
			AMMO_COUNTER_CLIP_NONE = 0x0,
			AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
			AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
			AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
			AMMO_COUNTER_CLIP_ROCKET = 0x4,
			AMMO_COUNTER_CLIP_BELTFED = 0x5,
			AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
			AMMO_COUNTER_CLIP_COUNT = 0x7,
		};

		enum ImpactType : std::int32_t
		{
			IMPACT_TYPE_NONE = 0x0,
			IMPACT_TYPE_BULLET_SMALL = 0x1,
			IMPACT_TYPE_BULLET_LARGE = 0x2,
			IMPACT_TYPE_BULLET_AP = 0x3,
			IMPACT_TYPE_BULLET_EXPLODE = 0x4,
			IMPACT_TYPE_SHOTGUN = 0x5,
			IMPACT_TYPE_SHOTGUN_EXPLODE = 0x6,
			IMPACT_TYPE_GRENADE_BOUNCE = 0x7,
			IMPACT_TYPE_GRENADE_EXPLODE = 0x8,
			IMPACT_TYPE_ROCKET_EXPLODE = 0x9,
			IMPACT_TYPE_PROJECTILE_DUD = 0xA,
			IMPACT_TYPE_COUNT = 0xB,
		};

		enum weapType_t : std::int32_t
		{
			WEAPTYPE_NONE = 0x0,
			WEAPTYPE_BULLET = 0x1,
			WEAPTYPE_GRENADE = 0x2,
			WEAPTYPE_PROJECTILE = 0x3,
			WEAPTYPE_RIOTSHIELD = 0x4,
			WEAPTYPE_NUM = 0x5,
		};

		enum weapClass_t : std::int32_t
		{
			WEAPCLASS_RIFLE = 0x0,
			WEAPCLASS_SNIPER = 0x1,
			WEAPCLASS_MG = 0x2,
			WEAPCLASS_SMG = 0x3,
			WEAPCLASS_SPREAD = 0x4,
			WEAPCLASS_PISTOL = 0x5,
			WEAPCLASS_GRENADE = 0x6,
			WEAPCLASS_ROCKETLAUNCHER = 0x7,
			WEAPCLASS_TURRET = 0x8,
			WEAPCLASS_THROWINGKNIFE = 0x9,
			WEAPCLASS_NON_PLAYER = 0xA,
			WEAPCLASS_ITEM = 0xB,
			WEAPCLASS_NUM = 0xC,
		};

		enum PenetrateType : std::int32_t
		{
			PENETRATE_TYPE_NONE = 0x0,
			PENETRATE_TYPE_SMALL = 0x1,
			PENETRATE_TYPE_MEDIUM = 0x2,
			PENETRATE_TYPE_LARGE = 0x3,
			PENETRATE_TYPE_COUNT = 0x4,
		};

		enum weapInventoryType_t : std::int32_t
		{
			WEAPINVENTORY_PRIMARY = 0x0,
			WEAPINVENTORY_OFFHAND = 0x1,
			WEAPINVENTORY_ITEM = 0x2,
			WEAPINVENTORY_ALTMODE = 0x3,
			WEAPINVENTORY_EXCLUSIVE = 0x4,
			WEAPINVENTORY_SCAVENGER = 0x5,
			WEAPINVENTORYCOUNT = 0x6,
		};

		enum weapFireType_t : std::int32_t
		{
			WEAPON_FIRETYPE_FULLAUTO = 0x0,
			WEAPON_FIRETYPE_SINGLESHOT = 0x1,
			WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
			WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
			WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
			WEAPON_FIRETYPE_DOUBLEBARREL = 0x5,
			WEAPON_FIRETYPECOUNT = 0x6,
			WEAPON_FIRETYPE_BURSTFIRE_FIRST = 0x2,
			WEAPON_FIRETYPE_BURSTFIRE_LAST = 0x4,
		};

		enum OffhandClass : std::int32_t
		{
			OFFHAND_CLASS_NONE = 0x0,
			OFFHAND_CLASS_FRAG_GRENADE = 0x1,
			OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
			OFFHAND_CLASS_FLASH_GRENADE = 0x3,
			OFFHAND_CLASS_THROWINGKNIFE = 0x4,
			OFFHAND_CLASS_OTHER = 0x5,
			OFFHAND_CLASS_COUNT = 0x6,
		};

		enum weapStance_t : std::int32_t
		{
			WEAPSTANCE_STAND = 0x0,
			WEAPSTANCE_DUCK = 0x1,
			WEAPSTANCE_PRONE = 0x2,
			WEAPSTANCE_NUM = 0x3,
		};

		enum activeReticleType_t : std::int32_t
		{
			VEH_ACTIVE_RETICLE_NONE = 0x0,
			VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
			VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
			VEH_ACTIVE_RETICLE_COUNT = 0x3,
		};

		enum weapOverlayReticle_t : std::int32_t
		{
			WEAPOVERLAYRETICLE_NONE = 0x0,
			WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
			WEAPOVERLAYRETICLE_NUM = 0x2,
		};

		enum WeapOverlayInteface_t : std::int32_t
		{
			WEAPOVERLAYINTERFACE_NONE = 0x0,
			WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
			WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
			WEAPOVERLAYINTERFACECOUNT = 0x3,
		};

		enum weapProjExposion_t : std::int32_t
		{
			WEAPPROJEXP_GRENADE = 0x0,
			WEAPPROJEXP_ROCKET = 0x1,
			WEAPPROJEXP_FLASHBANG = 0x2,
			WEAPPROJEXP_NONE = 0x3,
			WEAPPROJEXP_DUD = 0x4,
			WEAPPROJEXP_SMOKE = 0x5,
			WEAPPROJEXP_HEAVY = 0x6,
			WEAPPROJEXP_NUM = 0x7,
		};

		enum WeapStickinessType : std::int32_t
		{
			WEAPSTICKINESS_NONE = 0x0,
			WEAPSTICKINESS_ALL = 0x1,
			WEAPSTICKINESS_ALL_ORIENT = 0x2,
			WEAPSTICKINESS_GROUND = 0x3,
			WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
			WEAPSTICKINESS_KNIFE = 0x5,
			WEAPSTICKINESS_COUNT = 0x6,
		};

		enum guidedMissileType_t : std::int32_t
		{
			MISSILE_GUIDANCE_NONE = 0x0,
			MISSILE_GUIDANCE_SIDEWINDER = 0x1,
			MISSILE_GUIDANCE_HELLFIRE = 0x2,
			MISSILE_GUIDANCE_JAVELIN = 0x3,
			MISSILE_GUIDANCE_COUNT = 0x4,
		};

		struct StateTimers
		{
			int iFireDelay;
			int iMeleeDelay;
			int meleeChargeDelay;
			int iDetonateDelay;
			int iRechamberTime;
			int rechamberTimeOneHanded;
			int iRechamberBoltTime;
			int iHoldFireTime;
			int iHoldPrimeTime;
			int iDetonateTime;
			int iMeleeTime;
			int meleeChargeTime;
			int iReloadTime;
			int reloadShowRocketTime;
			int iReloadEmptyTime;
			int iReloadAddTime;
			int iReloadEmptyAddTime;
			int iReloadStartTime;
			int iReloadStartAddTime;
			int iReloadEndTime;
			int iDropTime;
			int iRaiseTime;
			int iAltDropTime;
			int quickDropTime;
			int quickRaiseTime;
			int iBreachRaiseTime;
			int iEmptyRaiseTime;
			int iEmptyDropTime;
			int sprintInTime;
			int sprintLoopTime;
			int sprintOutTime;
			int stunnedTimeBegin;
			int stunnedTimeLoop;
			int stunnedTimeEnd;
			int nightVisionWearTime;
			int nightVisionWearTimeFadeOutEnd;
			int nightVisionWearTimePowerUp;
			int nightVisionRemoveTime;
			int nightVisionRemoveTimePowerDown;
			int nightVisionRemoveTimeFadeInStart;
			int fuseTime;
			int aiFuseTime;
			int primeTime;
			bool bHoldFullPrime;
			int blastFrontTime;
			int blastRightTime;
			int blastBackTime;
			int blastLeftTime;
			int slideInTime;
			int slideLoopTime;
			int slideOutTime;
		};

		struct ADSOverlay
		{
			Material* __ptr64 shader;
			Material* __ptr64 shaderLowRes;
			Material* __ptr64 shaderEMP;
			Material* __ptr64 shaderEMPLowRes;
			weapOverlayReticle_t reticle;
			float width;
			float height;
			float widthSplitscreen;
			float heightSplitscreen;
		};

		struct TracerDef
		{
			const char* __ptr64 name;
			Material* __ptr64 material;
			unsigned int drawInterval;
			float speed;
			float beamLength;
			float beamWidth;
			float screwRadius;
			float screwDist;
			float colors[5][4];
		};

		struct AddonMapEnts
		{
			const char* __ptr64 name;
			char* __ptr64 entityString;
			int numEntityChars;
			MapTriggers trigger;
			ClipInfo* __ptr64 info;
			unsigned int numSubModels;
			cmodel_t* __ptr64 cmodels;
			GfxBrushModel* __ptr64 models;
		};

		struct WeaponDef
		{
			const char* __ptr64 szOverlayName;
			XModel* __ptr64 * __ptr64 gunXModel;
			XModel* __ptr64 handXModel;
			XModel* __ptr64 camoWorldModel;
			XModel* __ptr64 camoViewModel;
			Material* __ptr64 camoWorldModelMaterialOverride;
			Material* __ptr64 camoViewModelMaterialOverride;
			Material* __ptr64 * __ptr64 camoMaterialTarget;
			XAnimParts* __ptr64 * __ptr64 szXAnimsRightHanded;
			XAnimParts* __ptr64 * __ptr64 szXAnimsLeftHanded;
			const char* __ptr64 szModeName;
			scr_string_t* __ptr64 notetrackSoundMapKeys;
			scr_string_t* __ptr64 notetrackSoundMapValues;
			scr_string_t* __ptr64 notetrackRumbleMapKeys;
			scr_string_t* __ptr64 notetrackRumbleMapValues;
			scr_string_t* __ptr64 notetrackFXMapKeys;
			FxEffectDef* __ptr64 * __ptr64 notetrackFXMapValues; // const FxEffectDef**
			scr_string_t* __ptr64 notetrackFXMapTagValues;
			int playerAnimType;
			weapType_t weapType;
			weapClass_t weapClass;
			PenetrateType penetrateType;
			weapInventoryType_t inventoryType;
			weapFireType_t fireType;
			float burstFireCooldown;
			OffhandClass offhandClass;
			weapStance_t stance;
			unsigned __int8 rattleSoundType;
			const FxEffectDef* __ptr64 viewFlashEffect;
			const FxEffectDef* __ptr64 worldFlashEffect;
			const FxEffectDef* __ptr64 viewFlashADSEffect;
			snd_alias_list_t* __ptr64 pickupSound;
			snd_alias_list_t* __ptr64 pickupSoundPlayer;
			snd_alias_list_t* __ptr64 ammoPickupSound;
			snd_alias_list_t* __ptr64 ammoPickupSoundPlayer;
			snd_alias_list_t* __ptr64 projectileSound;
			snd_alias_list_t* __ptr64 pullbackSound;
			snd_alias_list_t* __ptr64 pullbackSoundPlayer;
			snd_alias_list_t* __ptr64 fireSound;
			snd_alias_list_t* __ptr64 fireSoundPlayer;
			snd_alias_list_t* __ptr64 fireSoundPlayerAkimbo;
			snd_alias_list_t* __ptr64 fireLoopSound;
			snd_alias_list_t* __ptr64 fireLoopSoundPlayer;
			snd_alias_list_t* __ptr64 fireStopSound;
			snd_alias_list_t* __ptr64 fireStopSoundPlayer;
			snd_alias_list_t* __ptr64 fireLastSound;
			snd_alias_list_t* __ptr64 fireLastSoundPlayer;
			snd_alias_list_t* __ptr64 emptyFireSound;
			snd_alias_list_t* __ptr64 emptyFireSoundPlayer;
			snd_alias_list_t* __ptr64 meleeSwipeSound;
			snd_alias_list_t* __ptr64 meleeSwipeSoundPlayer;
			snd_alias_list_t* __ptr64 meleeHitSound;
			snd_alias_list_t* __ptr64 meleeMissSound;
			snd_alias_list_t* __ptr64 rechamberSound;
			snd_alias_list_t* __ptr64 rechamberSoundPlayer;
			snd_alias_list_t* __ptr64 reloadSound;
			snd_alias_list_t* __ptr64 reloadSoundPlayer;
			snd_alias_list_t* __ptr64 reloadEmptySound;
			snd_alias_list_t* __ptr64 reloadEmptySoundPlayer;
			snd_alias_list_t* __ptr64 reloadStartSound;
			snd_alias_list_t* __ptr64 reloadStartSoundPlayer;
			snd_alias_list_t* __ptr64 reloadEndSound;
			snd_alias_list_t* __ptr64 reloadEndSoundPlayer;
			snd_alias_list_t* __ptr64 detonateSound;
			snd_alias_list_t* __ptr64 detonateSoundPlayer;
			snd_alias_list_t* __ptr64 nightVisionWearSound;
			snd_alias_list_t* __ptr64 nightVisionWearSoundPlayer;
			snd_alias_list_t* __ptr64 nightVisionRemoveSound;
			snd_alias_list_t* __ptr64 nightVisionRemoveSoundPlayer;
			snd_alias_list_t* __ptr64 altSwitchSound;
			snd_alias_list_t* __ptr64 altSwitchSoundPlayer;
			snd_alias_list_t* __ptr64 raiseSound;
			snd_alias_list_t* __ptr64 raiseSoundPlayer;
			snd_alias_list_t* __ptr64 firstRaiseSound;
			snd_alias_list_t* __ptr64 firstRaiseSoundPlayer;
			snd_alias_list_t* __ptr64 putawaySound;
			snd_alias_list_t* __ptr64 putawaySoundPlayer;
			snd_alias_list_t* __ptr64 scanSound;
			snd_alias_list_t* __ptr64 changeVariableZoomSound;
			snd_alias_list_t* __ptr64 * __ptr64 bounceSound;
			snd_alias_list_t* __ptr64 * __ptr64 rollingSound;
			const FxEffectDef* __ptr64 viewShellEjectEffect;
			const FxEffectDef* __ptr64 worldShellEjectEffect;
			const FxEffectDef* __ptr64 viewLastShotEjectEffect;
			const FxEffectDef* __ptr64 worldLastShotEjectEffect;
			const FxEffectDef* __ptr64 viewMagEjectEffect;
			Material* __ptr64 reticleCenter;
			Material* __ptr64 reticleSide;
			int iReticleCenterSize;
			int iReticleSideSize;
			int iReticleMinOfs;
			activeReticleType_t activeReticleType;
			float vStandMove[3];
			float vStandRot[3];
			float strafeMove[3];
			float strafeRot[3];
			float vDuckedOfs[3];
			float vDuckedMove[3];
			float vDuckedRot[3];
			float vProneOfs[3];
			float vProneMove[3];
			float vProneRot[3];
			float fPosMoveRate;
			float fPosProneMoveRate;
			float fStandMoveMinSpeed;
			float fDuckedMoveMinSpeed;
			float fProneMoveMinSpeed;
			float fPosRotRate;
			float fPosProneRotRate;
			float fStandRotMinSpeed;
			float fDuckedRotMinSpeed;
			float fProneRotMinSpeed;
			XModel* __ptr64 * __ptr64 worldModel;
			XModel* __ptr64 worldClipModel;
			XModel* __ptr64 rocketModel;
			XModel* __ptr64 knifeModel;
			XModel* __ptr64 worldKnifeModel;
			Material* __ptr64 hudIcon;
			weaponIconRatioType_t hudIconRatio;
			Material* __ptr64 pickupIcon;
			weaponIconRatioType_t pickupIconRatio;
			Material* __ptr64 ammoCounterIcon;
			weaponIconRatioType_t ammoCounterIconRatio;
			ammoCounterClipType_t ammoCounterClip;
			int iStartAmmo;
			const char* __ptr64 szAmmoName;
			int iAmmoIndex;
			const char* __ptr64 szClipName;
			int iClipIndex;
			int iMaxAmmo;
			int shotCount;
			const char* __ptr64 szSharedAmmoCapName;
			int iSharedAmmoCapIndex;
			int iSharedAmmoCap;
			int damage;
			int playerDamage;
			int iMeleeDamage;
			int iDamageType;
			StateTimers stateTimers;
			StateTimers akimboStateTimers;
			float autoAimRange;
			float aimAssistRange;
			float aimAssistRangeAds;
			float aimPadding;
			float enemyCrosshairRange;
			float moveSpeedScale;
			float adsMoveSpeedScale;
			float sprintDurationScale;
			float fAdsZoomInFrac;
			float fAdsZoomOutFrac;
			ADSOverlay overlay;
			WeapOverlayInteface_t overlayInterface;
			float fAdsBobFactor;
			float fAdsViewBobMult;
			float fHipSpreadStandMin;
			float fHipSpreadDuckedMin;
			float fHipSpreadProneMin;
			float hipSpreadStandMax;
			float hipSpreadDuckedMax;
			float hipSpreadProneMax;
			float fHipSpreadDecayRate;
			float fHipSpreadFireAdd;
			float fHipSpreadTurnAdd;
			float fHipSpreadMoveAdd;
			float fHipSpreadDuckedDecay;
			float fHipSpreadProneDecay;
			float fHipReticleSidePos;
			float fAdsIdleAmount;
			float fHipIdleAmount;
			float adsIdleSpeed;
			float hipIdleSpeed;
			float fIdleCrouchFactor;
			float fIdleProneFactor;
			float fGunMaxPitch;
			float fGunMaxYaw;
			float adsIdleLerpStartTime;
			float adsIdleLerpTime;
			float swayMaxAngleSteadyAim;
			float swayMaxAngle;
			float swayLerpSpeed;
			float swayPitchScale;
			float swayYawScale;
			float swayHorizScale;
			float swayVertScale;
			float swayShellShockScale;
			float adsSwayMaxAngle;
			float adsSwayLerpSpeed;
			float adsSwayPitchScale;
			float adsSwayYawScale;
			float adsSwayHorizScale;
			float adsSwayVertScale;
			float adsFireRateScale;
			float adsDamageRangeScale;
			float adsFireAnimFrac;
			PhysCollmap* __ptr64 physCollmap;
			float dualWieldViewModelOffset;
			float fScopeDriftDelay;
			float fScopeDriftLerpInTime;
			float fScopeDriftSteadyTime;
			float fScopeDriftLerpOutTime;
			float fScopeDriftSteadyFactor;
			float fScopeDriftUnsteadyFactor;
			weaponIconRatioType_t killIconRatio;
			int iReloadAmmoAdd;
			int iReloadStartAdd;
			int ammoDropStockMin;
			int ammoDropClipPercentMin;
			int ammoDropClipPercentMax;
			int iExplosionRadius;
			int iExplosionRadiusMin;
			int iExplosionInnerDamage;
			int iExplosionOuterDamage;
			float damageConeAngle;
			float bulletExplDmgMult;
			float bulletExplRadiusMult;
			int iProjectileSpeed;
			int iProjectileSpeedUp;
			int iProjectileSpeedForward;
			int iProjectileActivateDist;
			float projLifetime;
			float timeToAccelerate;
			float projectileCurvature;
			const char* __ptr64 projectileName;
			XModel* __ptr64 projectileModel;
			weapProjExposion_t projExplosion;
			const FxEffectDef* __ptr64 projExplosionEffect;
			const FxEffectDef* __ptr64 projDudEffect;
			snd_alias_list_t* __ptr64 projExplosionSound;
			snd_alias_list_t* __ptr64 projDudSound;
			WeapStickinessType stickiness;
			float lowAmmoWarningThreshold;
			float ricochetChance;
			bool riotShieldEnableDamage;
			int riotShieldHealth;
			float riotShieldDamageMult;
			float* __ptr64 parallelBounce;
			float* __ptr64 perpendicularBounce;
			const FxEffectDef* __ptr64 projTrailEffect;
			const FxEffectDef* __ptr64 projBeaconEffect;
			float vProjectileColor[3];
			guidedMissileType_t guidedMissileType;
			float maxSteeringAccel;
			int projIgnitionDelay;
			const FxEffectDef* __ptr64 projIgnitionEffect;
			snd_alias_list_t* __ptr64 projIgnitionSound;
			float fAdsAimPitch;
			float fAdsCrosshairInFrac;
			float fAdsCrosshairOutFrac;
			bool adsShouldShowCrosshair;
			int adsGunKickReducedKickBullets;
			float adsGunKickReducedKickPercent;
			float fAdsGunKickPitchMin;
			float fAdsGunKickPitchMax;
			float fAdsGunKickYawMin;
			float fAdsGunKickYawMax;
			float fAdsGunKickMagMin;
			float fAdsGunKickAccel;
			float fAdsGunKickSpeedMax;
			float fAdsGunKickSpeedDecay;
			float fAdsGunKickStaticDecay;
			float fAdsViewKickPitchMin;
			float fAdsViewKickPitchMax;
			float fAdsViewKickYawMin;
			float fAdsViewKickYawMax;
			float fAdsViewKickMagMin;
			float fAdsViewScatterMin;
			float fAdsViewScatterMax;
			float fAdsSpread;
			int hipGunKickReducedKickBullets;
			float hipGunKickReducedKickPercent;
			float fHipGunKickPitchMin;
			float fHipGunKickPitchMax;
			float fHipGunKickYawMin;
			float fHipGunKickYawMax;
			float fHipGunKickMagMin;
			float fHipGunKickAccel;
			float fHipGunKickSpeedMax;
			float fHipGunKickSpeedDecay;
			float fHipGunKickStaticDecay;
			float fHipViewKickPitchMin;
			float fHipViewKickPitchMax;
			float fHipViewKickYawMin;
			float fHipViewKickYawMax;
			float fHipViewKickMagMin;
			float fHipViewScatterMin;
			float fHipViewScatterMax;
			float fightDist;
			float maxDist;
			const char* __ptr64 accuracyGraphName[2];
			float(* __ptr64 originalAccuracyGraphKnots[2])[2];
			unsigned short originalAccuracyGraphKnotCount[2];
			int iPositionReloadTransTime;
			float leftArc;
			float rightArc;
			float topArc;
			float bottomArc;
			float accuracy;
			float aiSpread;
			float playerSpread;
			float minTurnSpeed[2];
			float maxTurnSpeed[2];
			float pitchConvergenceTime;
			float yawConvergenceTime;
			float suppressTime;
			float maxRange;
			float fAnimHorRotateInc;
			float fPlayerPositionDist;
			const char* __ptr64 szUseHintString;
			const char* __ptr64 dropHintString;
			unsigned int iUseHintStringIndex;
			unsigned int dropHintStringIndex;
			float horizViewJitter;
			float vertViewJitter;
			float scanSpeed;
			float scanAccel;
			int scanPauseTime;
			const char* __ptr64 szScript;
			float fOOPosAnimLength[2];
			int minDamage;
			int minPlayerDamage;
			float fMaxDamageRange;
			float fMinDamageRange;
			float destabilizationRateTime;
			float destabilizationCurvatureMax;
			int destabilizeDistance;
			float* __ptr64 locationDamageMultipliers;
			const char* __ptr64 fireRumble;
			const char* __ptr64 meleeImpactRumble;
			TracerDef* __ptr64 tracerType;
			bool turretADSEnabled;
			float turretADSTime;
			float turretFov;
			float turretFovADS;
			float turretScopeZoomRate;
			float turretScopeZoomMin;
			float turretScopeZoomMax;
			float turretOverheatUpRate;
			float turretOverheatDownRate;
			float turretOverheatPenalty;
			snd_alias_list_t* __ptr64 turretOverheatSound;
			const FxEffectDef* __ptr64 turretOverheatEffect;
			const char* __ptr64 turretBarrelSpinRumble;
			float turretBarrelSpinSpeed;
			float turretBarrelSpinUpTime;
			float turretBarrelSpinDownTime;
			snd_alias_list_t* __ptr64 turretBarrelSpinMaxSnd;
			snd_alias_list_t* __ptr64 turretBarrelSpinUpSnd[4];
			snd_alias_list_t* __ptr64 turretBarrelSpinDownSnd[4];
			snd_alias_list_t* __ptr64 missileConeSoundAlias;
			snd_alias_list_t* __ptr64 missileConeSoundAliasAtBase;
			float missileConeSoundRadiusAtTop;
			float missileConeSoundRadiusAtBase;
			float missileConeSoundHeight;
			float missileConeSoundOriginOffset;
			float missileConeSoundVolumescaleAtCore;
			float missileConeSoundVolumescaleAtEdge;
			float missileConeSoundVolumescaleCoreSize;
			float missileConeSoundPitchAtTop;
			float missileConeSoundPitchAtBottom;
			float missileConeSoundPitchTopSize;
			float missileConeSoundPitchBottomSize;
			float missileConeSoundCrossfadeTopSize;
			float missileConeSoundCrossfadeBottomSize;
			scr_string_t knifeAttachTagOverride;
			bool knifeAlwaysAttached;
			bool meleeOverrideValues;
			float aim_automelee_lerp;
			float aim_automelee_range;
			float aim_automelee_region_height;
			float aim_automelee_region_width;
			float player_meleeHeight;
			float player_meleeRange;
			float player_meleeWidth;
			bool sharedAmmo;
			bool lockonSupported;
			bool requireLockonToFire;
			bool isAirburstWeapon;
			bool bigExplosion;
			bool noAdsWhenMagEmpty;
			bool avoidDropCleanup;
			bool inheritsPerks;
			bool crosshairColorChange;
			bool bRifleBullet;
			bool armorPiercing;
			bool bBoltAction;
			bool aimDownSight;
			bool canHoldBreath;
			bool meleeOnly;
			bool canVariableZoom;
			bool bRechamberWhileAds;
			bool bBulletExplosiveDamage;
			bool bCookOffHold;
			bool reticleSpin45;
			bool bClipOnly;
			bool noAmmoPickup;
			bool adsFireOnly;
			bool cancelAutoHolsterWhenEmpty;
			bool disableSwitchToWhenEmpty;
			bool suppressAmmoReserveDisplay;
			bool laserSightDuringNightvision;
			bool markableViewmodel;
			bool noDualWield;
			bool flipKillIcon;
			bool bNoPartialReload;
			bool bSegmentedReload;
			bool bMultipleReload;
			bool blocksProne;
			bool silenced;
			bool isRollingGrenade;
			bool projExplosionEffectForceNormalUp;
			bool projExplosionEffectInheritParentDirection;
			bool bProjImpactExplode;
			bool bProjTrajectoryEvents;
			bool bProjWhizByEnabled;
			bool stickToPlayers;
			bool stickToVehicles;
			bool stickToTurrets;
			bool thrownSideways;
			bool hasDetonator;
			bool disableFiring;
			bool timedDetonation;
			bool rotate;
			bool holdButtonToThrow;
			bool freezeMovementWhenFiring;
			bool thermalScope;
			bool thermalToggle;
			bool outlineEnemies;
			bool altModeSameWeapon;
			bool turretBarrelSpinEnabled;
			bool missileConeSoundEnabled;
			bool missileConeSoundPitchshiftEnabled;
			bool missileConeSoundCrossfadeEnabled;
			bool offhandHoldIsCancelable;
			bool doNotAllowAttachmentsToOverrideSpread;
			bool useFastReloadAnims;
			bool useScopeDrift;
			bool alwaysShatterGlassOnImpact;
			bool oldWeapon;
			scr_string_t stowTag;
			XModel* __ptr64 stowOffsetModel;
		};

		enum AttachmentType : std::int32_t
		{
			ATTACHMENT_SCOPE = 0x0,
			ATTACHMENT_UNDERBARREL = 0x1,
			ATTACHMENT_OTHER = 0x2,
			ATTACHMENT_COUNT = 0x3,
		};

		struct AttAmmoGeneral
		{
			PenetrateType penetrateType;
			float penetrateMultiplier;
			ImpactType impactType;
			weapFireType_t fireType;
			TracerDef* __ptr64 tracerType;
			bool rifleBullet;
			bool armorPiercing;
		};

		struct AttSight
		{
			bool aimDownSight;
			bool adsFire;
			bool rechamberWhileAds;
			bool noAdsWhenMagEmpty;
			bool canHoldBreath;
			bool canVariableZoom;
			bool hideRailWithThisScope;
			bool useScopeDrift;
			bool useDualFOV;
		};

		struct AttReload
		{
			bool noPartialReload;
			bool segmentedReload;
		};

		struct AttAddOns
		{
			bool motionTracker;
			bool silenced;
			bool riotShield;
		};

		struct AttGeneral
		{
			bool boltAction;
			bool inheritsPerks;
			bool reticleSpin45;
			float enemyCrosshairRange;
			Material* __ptr64 reticleCenter;
			Material* __ptr64 reticleSide;
			int reticleCenterSize;
			int reticleSideSize;
			float moveSpeedScale;
			float adsMoveSpeedScale;
		};

		struct AttAimAssist
		{
			float autoAimRange;
			float aimAssistRange;
			float aimAssistRangeAds;
		};

		struct AttAmmunition
		{
			int maxAmmo;
			int startAmmo;
			int clipSize;
			int shotCount;
			int reloadAmmoAdd;
			int reloadStartAdd;
		};

		struct AttDamage
		{
			int damage;
			int minDamage;
			int meleeDamage;
			float maxDamageRange;
			float minDamageRange;
			int playerDamage;
			int minPlayerDamage;
		};

		struct AttLocationDamage
		{
			float locNone;
			float locHelmet;
			float locHead;
			float locNeck;
			float locTorsoUpper;
			float locTorsoLower;
			float locRightArmUpper;
			float locRightArmLower;
			float locRightHand;
			float locLeftArmUpper;
			float locLeftArmLower;
			float locLeftHand;
			float locRightLegUpper;
			float locRightLegLower;
			float locRightFoot;
			float locLeftLegUpper;
			float locLeftLegLower;
			float locLeftFoot;
			float locGun;
		};

		struct AttIdleSettings
		{
			float hipIdleAmount;
			float hipIdleSpeed;
			float idleCrouchFactor;
			float idleProneFactor;
			float adsIdleLerpStartTime;
			float adsIdleLerpTime;
		};

		struct AttADSSettings
		{
			float adsSpread;
			float adsAimPitch;
			float adsTransInTime;
			float adsTransOutTime;
			int adsReloadTransTime;
			float adsCrosshairInFrac;
			float adsCrosshairOutFrac;
			float adsZoomFov;
			float adsZoomInFrac;
			float adsZoomOutFrac;
			float adsFovLerpTime;
			float adsBobFactor;
			float adsViewBobMult;
			float adsFireRateScale;
			float adsDamageRangeScale;
			float adsFireAnimFrac;
		};

		struct AttScopeDriftSettings
		{
			float fScopeDriftDelay;
			float fScopeDriftLerpInTime;
			float fScopeDriftSteadyTime;
			float fScopeDriftLerpOutTime;
			float fScopeDriftSteadyFactor;
			float fScopeDriftUnsteadyFactor;
		};

		struct AttHipSpread
		{
			float hipSpreadStandMin;
			float hipSpreadDuckedMin;
			float hipSpreadProneMin;
			float hipSpreadMax;
			float hipSpreadDuckedMax;
			float hipSpreadProneMax;
			float hipSpreadFireAdd;
			float hipSpreadTurnAdd;
			float hipSpreadMoveAdd;
			float hipSpreadDecayRate;
			float hipSpreadDuckedDecay;
			float hipSpreadProneDecay;
		};

		struct AttGunKick
		{
			int hipGunKickReducedKickBullets;
			float hipGunKickReducedKickPercent;
			float hipGunKickPitchMin;
			float hipGunKickPitchMax;
			float hipGunKickYawMin;
			float hipGunKickYawMax;
			float hipGunKickMagMin;
			float hipGunKickAccel;
			float hipGunKickSpeedMax;
			float hipGunKickSpeedDecay;
			float hipGunKickStaticDecay;
			int adsGunKickReducedKickBullets;
			float adsGunKickReducedKickPercent;
			float adsGunKickPitchMin;
			float adsGunKickPitchMax;
			float adsGunKickYawMin;
			float adsGunKickYawMax;
			float adsGunKickMagMin;
			float adsGunKickAccel;
			float adsGunKickSpeedMax;
			float adsGunKickSpeedDecay;
			float adsGunKickStaticDecay;
		};

		struct AttViewKick
		{
			float hipViewKickPitchMin;
			float hipViewKickPitchMax;
			float hipViewKickYawMin;
			float hipViewKickYawMax;
			float hipViewKickMagMin;
			float hipViewKickCenterSpeed;
			float adsViewKickPitchMin;
			float adsViewKickPitchMax;
			float adsViewKickYawMin;
			float adsViewKickYawMax;
			float adsViewKickMagMin;
			float adsViewKickCenterSpeed;
		};

		struct AttADSOverlay
		{
			ADSOverlay overlay;
			bool hybridToggle;
			bool thermalScope;
			bool thermalToggle;
			bool outlineEnemies;
		};

		struct AttUI
		{
			Material* __ptr64 dpadIcon;
			Material* __ptr64 ammoCounterIcon;
			weaponIconRatioType_t dpadIconRatio;
			weaponIconRatioType_t ammoCounterIconRatio;
			ammoCounterClipType_t ammoCounterClip;
		};

		struct AttRumbles
		{
			const char* __ptr64 fireRumble;
			const char* __ptr64 meleeImpactRumble;
		};

		struct AttProjectile
		{
			int explosionRadius;
			int explosionInnerDamage;
			int explosionOuterDamage;
			float damageConeAngle;
			int projectileSpeed;
			int projectileSpeedUp;
			int projectileActivateDist;
			float projectileLifetime;
			const char* __ptr64 projectileName;
			XModel* __ptr64 projectileModel;
			weapProjExposion_t projExplosionType;
			const FxEffectDef* __ptr64 projExplosionEffect;
			bool projExplosionEffectForceNormalUp;
			snd_alias_list_t* __ptr64 projExplosionSound;
			const FxEffectDef* __ptr64 projDudEffect;
			snd_alias_list_t* __ptr64 projDudSound;
			bool projImpactExplode;
			float destabilizationRateTime;
			float destabilizationCurvatureMax;
			int destabilizeDistance;
			const FxEffectDef* __ptr64 projTrailEffect;
			int projIgnitionDelay;
			const FxEffectDef* __ptr64 projIgnitionEffect;
			snd_alias_list_t* __ptr64 projIgnitionSound;
		};

		struct WeaponAttachment
		{
			union
			{
				const char* __ptr64 szInternalName;
				const char* __ptr64 name;
			};
			const char* __ptr64 szDisplayName;
			AttachmentType type;
			weapType_t weaponType;
			weapClass_t weapClass;
			XModel* __ptr64 * __ptr64 worldModels;
			XModel* __ptr64 * __ptr64 viewModels;
			XModel* __ptr64 * __ptr64 reticleViewModels;
			AttAmmoGeneral* __ptr64 ammogeneral;
			AttSight* __ptr64 sight;
			AttReload* __ptr64 reload;
			AttAddOns* __ptr64 addOns;
			AttGeneral* __ptr64 general;
			AttAimAssist* __ptr64 aimAssist;
			AttAmmunition* __ptr64 ammunition;
			AttDamage* __ptr64 damage;
			AttLocationDamage* __ptr64 locationDamage;
			AttIdleSettings* __ptr64 idleSettings;
			AttADSSettings* __ptr64 adsSettings;
			AttADSSettings* __ptr64 adsSettingsMain;
			AttScopeDriftSettings* __ptr64 scopeDriftSettings;
			AttScopeDriftSettings* __ptr64 scopeDriftSettingsMain;
			AttHipSpread* __ptr64 hipSpread;
			AttGunKick* __ptr64 gunKick;
			AttViewKick* __ptr64 viewKick;
			AttADSOverlay* __ptr64 adsOverlay;
			AttUI* __ptr64 ui;
			AttRumbles* __ptr64 rumbles;
			AttProjectile* __ptr64 projectile;
			float ammunitionScale;
			float damageScale;
			float damageScaleMin;
			float stateTimersScale;
			float fireTimersScale;
			float idleSettingsScale;
			float adsSettingsScale;
			float adsSettingsScaleMain;
			float hipSpreadScale;
			float gunKickScale;
			float viewKickScale;
			float viewCenterScale;
			int loadIndex;
			bool hideIronSightsWithThisAttachment;
			bool shareAmmoWithAlt;
		};

		struct AnimOverrideEntry
		{
			unsigned short attachment1;
			unsigned short attachment2;
			XAnimParts* __ptr64 overrideAnim;
			XAnimParts* __ptr64 altmodeAnim;
			unsigned int animTreeType;
			int animTime;
			int altTime;
		};

		struct SoundOverrideEntry
		{
			unsigned short attachment1;
			unsigned short attachment2;
			snd_alias_list_t* __ptr64 overrideSound;
			snd_alias_list_t* __ptr64 altmodeSound;
			unsigned int soundType;
		};

		struct FXOverrideEntry
		{
			unsigned short attachment1;
			unsigned short attachment2;
			const FxEffectDef* __ptr64 overrideFX;
			const FxEffectDef* __ptr64 altmodeFX;
			unsigned int fxType;
		};

		struct ReloadStateTimerEntry
		{
			int attachment;
			int reloadAddTime;
			int reloadEmptyAddTime;
			int reloadStartAddTime;
		};

		struct NoteTrackToSoundEntry
		{
			int attachment;
			scr_string_t* __ptr64 notetrackSoundMapKeys;
			scr_string_t* __ptr64 notetrackSoundMapValues;
		};

		struct WeaponCompleteDef
		{
			union
			{
				const char* __ptr64 szInternalName;
				const char* __ptr64 name;
			};
			WeaponDef* __ptr64 weapDef;
			const char* __ptr64 szDisplayName;
			scr_string_t* __ptr64 hideTags;
			WeaponAttachment* __ptr64 * __ptr64 scopes;
			WeaponAttachment* __ptr64 * __ptr64 underBarrels;
			WeaponAttachment* __ptr64 * __ptr64 others;
			XAnimParts* __ptr64 * __ptr64 szXAnims; // XAnimParts* __ptr64 const*
			unsigned int numAnimOverrides;
			AnimOverrideEntry* __ptr64 animOverrides;
			unsigned int numSoundOverrides;
			SoundOverrideEntry* __ptr64 soundOverrides;
			unsigned int numFXOverrides;
			FXOverrideEntry* __ptr64 fxOverrides;
			unsigned int numReloadStateTimerOverrides;
			ReloadStateTimerEntry* __ptr64 reloadOverrides;
			unsigned int numNotetrackOverrides;
			NoteTrackToSoundEntry* __ptr64 notetrackOverrides;
			float fAdsZoomFov;
			int iAdsTransInTime;
			int iAdsTransOutTime;
			int iClipSize;
			ImpactType impactType;
			int iFireTime;
			int iFireTimeAkimbo;
			weaponIconRatioType_t dpadIconRatio;
			float penetrateMultiplier;
			float fAdsViewKickCenterSpeed;
			float fHipViewKickCenterSpeed;
			const char* __ptr64 szAltWeaponName;
			int altWeapon;
			int iAltRaiseTime;
			int iAltRaiseTimeAkimbo;
			Material* __ptr64 killIcon;
			Material* __ptr64 dpadIcon;
			int fireAnimLength;
			int fireAnimLengthAkimbo;
			int iFirstRaiseTime;
			int iFirstRaiseTimeAkimbo;
			int ammoDropStockMax;
			float adsDofStart;
			float adsDofEnd;
			unsigned short accuracyGraphKnotCount[2];
			float(* __ptr64 accuracyGraphKnots[2])[2];
			bool motionTracker;
			bool enhanced;
			bool dpadIconShowsAmmo;
			const char* __ptr64 szAdsrBaseSetting;
		};

		struct RawFile
		{
			const char* __ptr64 name;
			int compressedLen;
			int len;
			const char* __ptr64 buffer;
		};

		struct LuaFile
		{
			const char* __ptr64 name;
			int len;
			unsigned char strippingType;
			const unsigned char* __ptr64 buffer;
		};

		struct ScriptFile
		{
			const char* __ptr64 name;
			int compressedLen;
			int len;
			int bytecodeLen;
			const char* __ptr64 buffer;
			char* __ptr64 bytecode;
		};

		struct StringTableCell
		{
			const char* __ptr64 string;
			int hash;
		};

		struct StringTable
		{
			const char* __ptr64 name;
			int columnCount;
			int rowCount;
			StringTableCell* __ptr64 values;
		};

		struct StructuredDataEnumEntry
		{
			scr_string_t string;
			unsigned short index;
		};

		struct StructuredDataEnum
		{
			int entryCount;
			int reservedEntryCount;
			StructuredDataEnumEntry* __ptr64 entries;
		};

		enum StructuredDataTypeCategory
		{
			DATA_INT = 0x0,
			DATA_BYTE = 0x1,
			DATA_BOOL = 0x2,
			DATA_STRING = 0x3,
			DATA_ENUM = 0x4,
			DATA_STRUCT = 0x5,
			DATA_INDEXED_ARRAY = 0x6,
			DATA_ENUM_ARRAY = 0x7,
			DATA_FLOAT = 0x8,
			DATA_SHORT = 0x9,
			DATA_COUNT = 0xA,
		};

		union StructuredDataTypeUnion
		{
			unsigned int stringDataLength;
			int enumIndex;
			int structIndex;
			int indexedArrayIndex;
			int enumedArrayIndex;
			int index;
		};

		struct StructuredDataType
		{
			StructuredDataTypeCategory type;
			StructuredDataTypeUnion u;
		};

		enum StructuredDataValidationType
		{
			VALIDATION_NONE = 0x0,
			VALIDATION_CONSTANT = 0x1,
			VALIDATION_INCREASECLAMP = 0x2,
			VALIDATION_INCREASESTRICT = 0x3,
			VALIDATION_DELTACLAMP = 0x4,
			VALIDATION_DELTASTRICT = 0x5,
			VALIDATION_XP = 0x6,
			VALIDATION_COUNT = 0x7,
		};

		struct StructuredDataStructProperty
		{
			scr_string_t name;
			StructuredDataType type;
			unsigned int offset;
			StructuredDataValidationType validation;
		};

		struct StructuredDataStruct
		{
			int propertyCount;
			StructuredDataStructProperty* __ptr64 properties;
			int size;
			unsigned int bitOffset;
		};

		struct StructuredDataIndexedArray
		{
			int arraySize;
			StructuredDataType elementType;
			unsigned int elementSize;
		};

		struct StructuredDataEnumedArray
		{
			int enumIndex;
			StructuredDataType elementType;
			unsigned int elementSize;
		};

		struct StructuredDataDef
		{
			int version;
			unsigned int formatChecksum;
			int enumCount;
			StructuredDataEnum* __ptr64 enums;
			int structCount;
			StructuredDataStruct* __ptr64 structs;
			int indexedArrayCount;
			StructuredDataIndexedArray* __ptr64 indexedArrays;
			int enumedArrayCount;
			StructuredDataEnumedArray* __ptr64 enumedArrays;
			StructuredDataType rootType;
			unsigned int size;
		};

		struct StructuredDataDefSet
		{
			const char* __ptr64 name;
			unsigned int defCount;
			StructuredDataDef* __ptr64 defs;
		};

		enum NetConstStringType
		{
			NETCONSTSTRINGTYPE_XMODEL = 0x0,
			NETCONSTSTRINGTYPE_MATERIAL = 0x1,
			NETCONSTSTRINGTYPE_RUMBLE = 0x2,
			NETCONSTSTRINGTYPE_VEHICLES = 0x3,
			NETCONSTSTRINGTYPE_FX = 0x4,
			NETCONSTSTRINGTYPE_LOCSTRING = 0x5,
			NETCONSTSTRINGTYPE_SOUNDALIAS = 0x6,
			NETCONSTSTRINGTYPE_SOUNDALIAS_LOOPING = 0x7,
			NETCONSTSTRINGTYPE_SHOCK = 0x8,
			NETCONSTSTRINGTYPE_SCRIPTMENU = 0x9,
			NETCONSTSTRINGTYPE_CLIENT_TAGS = 0xA,
			NETCONSTSTRINGTYPE_HEADICON = 0xB,
			NETCONSTSTRINGTYPE_STATUSICON = 0xC,
			NETCONSTSTRINGTYPE_NAMEPLATE = 0xD,
			NETCONSTSTRINGTYPE_MINIMAPICON = 0xE,
			NETCONSTSTRINGTYPE_LOCSELMAT = 0xF,
			NETCONSTSTRINGTYPE_WEAPON = 0x10,
			NETCONSTSTRINGTYPE_HINTSTRING = 0x11,
			NETCONSTSTRINGTYPE_ANIM = 0x12,
			NETCONSTSTRINGTYPE_TAGS = 0x13,
			NETCONSTSTRINGTYPE_ANIMCLASS = 0x14,
			NETCONSTSTRINGTYPE_LUI = 0x15,
			NETCONSTSTRINGTYPE_ASSET_COUNT = 0x16,
			NETCONSTSTRINGTYPE_CODINFO_DVAR = 0x16,
			NETCONSTSTRINGTYPE_NETWORK_DVAR = 0x17,
			NETCONSTSTRINGTYPE_COUNT = 0x18,
			NETCONSTSTRINGTYPE_NONE = 0x18,
		};

		enum NetConstStringSource
		{
			NETCONSTSTRINGSOURCE_MAP = 0x0,
			NETCONSTSTRINGSOURCE_PRE_MAP = 0x1,
			NETCONSTSTRINGSOURCE_COMMON = 0x2,
			NETCONSTSTRINGSOURCE_COUNT = 0x3,
			NETCONSTSTRINGSOURCE_NONE = 0x3,
		};

		struct NetConstStrings
		{
			const char* __ptr64 name;
			NetConstStringType stringType;
			NetConstStringSource sourceType;
			unsigned int entryCount;
			const char* __ptr64 * __ptr64 stringList;
		};

		union XAssetHeader
		{
			PhysPreset* __ptr64 physPreset;
			PhysCollmap* __ptr64 physCollmap;
			XAnimParts* __ptr64 parts;
			XModelSurfs* __ptr64 modelSurfs;
			XModel* __ptr64 model;
			Material* __ptr64 material;
			//ComputeShader* __ptr64 computeShader;
			MaterialVertexShader* __ptr64 vertexShader;
			MaterialHullShader* __ptr64 hullShader;
			MaterialDomainShader* __ptr64 domainShader;
			MaterialPixelShader* __ptr64 pixelShader;
			MaterialVertexDeclaration* __ptr64 vertexDecl;
			MaterialTechniqueSet* __ptr64 techniqueSet;
			GfxImage* __ptr64 image;
			snd_alias_list_t* __ptr64 sound;
			SndCurve* __ptr64 sndCurve;
			SndCurve* __ptr64 lpfCurve;
			SndCurve* __ptr64 reverbCurve;
			LoadedSound* __ptr64 loadSnd;
			clipMap_t* __ptr64 clipMap;
			ComWorld* __ptr64 comWorld;
			GlassWorld* __ptr64 glassWorld;
			//PathData* __ptr64 pathData;
			//VehicleTrack* __ptr64 vehicleTrack;
			MapEnts* __ptr64 mapEnts;
			FxWorld* __ptr64 fxWorld;
			GfxWorld* __ptr64 gfxWorld;
			GfxLightDef* __ptr64 lightDef;
			Font_s* __ptr64 font;
			//MenuList* __ptr64 menuList;
			//menuDef_t* __ptr64 menu;
			//AnimationClass* __ptr64 animClass;
			//LocalizeEntry* __ptr64 localize;
			WeaponAttachment* __ptr64 attachment;
			WeaponCompleteDef* __ptr64 weapon;
			//SndDriverGlobals* __ptr64 sndDriverGlobals;
			FxEffectDef* __ptr64 fx;
			//FxImpactTable* __ptr64 impactFx;
			//SurfaceFxTable* __ptr64 surfaceFx;
			RawFile* __ptr64 rawfile;
			ScriptFile* __ptr64 scriptfile;
			StringTable* __ptr64 stringTable;
			//LeaderboardDef* __ptr64 leaderboardDef;
			StructuredDataDefSet* __ptr64 structuredDataDefSet;
			TracerDef* __ptr64 tracerDef;
			//VehicleDef* __ptr64 vehDef;
			AddonMapEnts* __ptr64 addonMapEnts;
			NetConstStrings* __ptr64 netConstStrings;
			//ReverbPreset* __ptr64 reverbPreset;
			LuaFile* __ptr64 luaFile;
			ScriptableDef* __ptr64 scriptable;
			//Colorization* __ptr64 colorization;
			//ColorizationSet* __ptr64 colorizationSet;
			//ToneMapping* __ptr64 toneMapping;
			//EquipmentSoundTable* __ptr64 equipSndTable;
			//VectorField* __ptr64 vectorField;
			DopplerPreset* __ptr64 dopplerPreset;
			FxParticleSimAnimation* __ptr64 particleSimAnimation;
			void* __ptr64 data;
		};

		struct XAsset
		{
			XAssetType type;
			XAssetHeader header;
		};

		struct XAssetEntry
		{
			XAsset asset;
			unsigned char zoneIndex;
			volatile char inuseMask;
			unsigned int nextHash;
			unsigned int nextOverride;
			unsigned int nextPoolEntry;
		};

		struct ScriptStringList
		{
			int count;
			const char* __ptr64 * __ptr64 strings;
		};

		union GfxZoneTableEntry
		{
			void* __ptr64 voidPtr;
			//ID3D11Buffer* __ptr64 buffer;
			//ID3D11DepthStencilState* __ptr64 depthStencilState;
			//ID3D11BlendState* __ptr64 blendState;
		};

		struct XGfxGlobals
		{
			unsigned int depthStencilStateCount; // 0
			unsigned int blendStateCount; // 4
			std::uint64_t* __ptr64 depthStencilStateBits; // 8
			unsigned int(* __ptr64 blendStateBits)[1]; // 16
			GfxZoneTableEntry* __ptr64 depthStencilStates; // 24
			GfxZoneTableEntry* __ptr64 blendStates; // 32
			unsigned int perPrimConstantBufferCount; // 40
			unsigned int perObjConstantBufferCount; // 44
			unsigned int stableConstantBufferCount; // 48
			unsigned int* __ptr64 perPrimConstantBufferSizes; // 56
			unsigned int* __ptr64 perObjConstantBufferSizes; // 64
			unsigned int* __ptr64 stableConstantBufferSizes; // 72
			GfxZoneTableEntry* __ptr64 perPrimConstantBuffers; // 80
			GfxZoneTableEntry* __ptr64 perObjConstantBuffers; // 88
			GfxZoneTableEntry* __ptr64 stableConstantBuffers; // 96
		};

		struct XGlobals
		{
			XGfxGlobals* __ptr64 gfxGlobals;
		};

		struct XAssetList
		{
			ScriptStringList stringList;
			int assetCount;
			XAsset* __ptr64 assets;
			XGlobals* __ptr64 globals;
		};

		struct XFile
		{
			unsigned __int64 size;
			unsigned __int64 externalSize;
			unsigned __int64 blockSize[7];
		};

		struct XBlock
		{
			unsigned __int8* __ptr64 data;
			unsigned __int64 size;
		};

		struct XZoneMemory_
		{
			XBlock blocks[7];
		};

		enum DBAllocFlags : std::int32_t
		{
			DB_ZONE_NONE = 0x0,
			DB_ZONE_COMMON = 0x1,
			DB_ZONE_UI = 0x2,
			DB_ZONE_GAME = 0x4,
			DB_ZONE_LOAD = 0x8,
			DB_ZONE_DEV = 0x10,
			DB_ZONE_BASEMAP = 0x20,
			DB_ZONE_TRANSIENT_POOL = 0x40,
			DB_ZONE_TRANSIENT_MASK = 0x40,
			DB_ZONE_CUSTOM = 0x80 // added for custom zone loading
		};

		struct XZoneInfo
		{
			const char* __ptr64 name;
			int allocFlags;
			int freeFlags;
		};

		struct XZoneInfoInternal
		{
			char name[64];
			int flags;
			int isBaseMap;
		};

		struct DBFile
		{
			void* __ptr64 handle;
			unsigned __int64 memoryBufferSize;
			char* __ptr64 memoryBuffer;
			char name[64];
		};

		enum DBSyncMode : std::int32_t
		{
			DB_LOAD_ASYNC = 0x0,
			DB_LOAD_SYNC = 0x1,
			DB_LOAD_ASYNC_WAIT_ALLOC = 0x2,
			DB_LOAD_ASYNC_FORCE_FREE = 0x3,
			DB_LOAD_ASYNC_NO_SYNC_THREADS = 0x4,
			DB_LOAD_SYNC_SKIP_ALWAYS_LOADED = 0x5,
		};
	}
}

#pragma pop()