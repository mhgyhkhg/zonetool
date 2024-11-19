// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		bool isDumpingComplete = false;
		bool isDumping = false;
		bool isVerifying = false;
		auto currentDumpingZone = ""s;

		const char* Linker::version()
		{
			return "IW4";
		}

		bool Linker::is_used()
		{
			return !strncmp(reinterpret_cast<char*>(0x71B85C), this->version(), 3);
		}

		void Linker::load_default_zones()
		{
			static std::vector<std::string> defaultzones =
			{
				"code_pre_gfx_mp",
				"localized_code_pre_gfx_mp",
				"code_post_gfx_mp",
				"localized_code_post_gfx_mp",
				"common_mp",
			};

			static XZoneInfo zones[16];
			memset(zones, 0, sizeof XZoneInfo * 16);

			// Load our custom zones
			for (std::size_t i = 0; i < defaultzones.size(); i++)
			{
				zones[i].zone = defaultzones[i].c_str();
				zones[i].loadFlags = 0;
				zones[i].unloadFlags = 0;
			}

			return DB_LoadXAssets(zones, defaultzones.size(), 0);
		}

		void Linker::run()
		{
			// function definitions
			typedef void (__cdecl * Win_InitLocalization_t)(int);
			typedef void (__cdecl * SL_Init_t)();
			typedef void (__cdecl * Swap_Init_t)();
			typedef void (__cdecl * Com_InitHunkMemory_t)();
			typedef void (__cdecl * Sys_InitializeCriticalSections_t)();
			typedef void (__cdecl * DB_InitThread_t)();
			typedef void (__cdecl * Com_InitDvars_t)();
			typedef void (__cdecl * PMem_Init_t)();
			typedef void (__cdecl * R_RegisterDvars_t)();
			typedef void (__cdecl * FS_Init_t)(); // wrong name, but lazy
			typedef void (__cdecl * LargeLocalInit_t)(); // guessed name
			typedef void (__cdecl * Cmd_ExecuteSingleCommand_t)(int controller, int a2, const char* cmd);

			SL_Init_t SL_Init = (SL_Init_t)0x4D2280;
			Swap_Init_t Swap_Init = (Swap_Init_t)0x47F390;
			Com_InitHunkMemory_t Com_InitHunkMemory = (Com_InitHunkMemory_t)0x420830;
			Sys_InitializeCriticalSections_t Sys_InitializeCriticalSections = (Sys_InitializeCriticalSections_t)
				0x42F0A0;
			Sys_InitializeCriticalSections_t Sys_InitMainThread = (Sys_InitializeCriticalSections_t)0x4301B0;
			DB_InitThread_t DB_InitThread = (DB_InitThread_t)0x4E0FB0;
			Com_InitDvars_t Com_InitDvars = (Com_InitDvars_t)0x60AD10;
			Win_InitLocalization_t Win_InitLocalization = (Win_InitLocalization_t)0x406D10;
			PMem_Init_t PMem_Init = (PMem_Init_t)0x64A020;
			R_RegisterDvars_t R_RegisterDvars = (R_RegisterDvars_t)0x5196C0;
			FS_Init_t FS_Init = (FS_Init_t)0x429080;
			LargeLocalInit_t LargeLocalInit = (LargeLocalInit_t)0x4A62A0;
			Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand = (Cmd_ExecuteSingleCommand_t)0x609540;
			DWORD G_SetupWeaponDef = 0x4E1F30;
			DWORD Scr_BeginLoadScripts = 0x4E1ED0;
			DWORD Scr_BeginLoadScripts2 = 0x4541F0;
			DWORD Scr_InitAllocNodes = 0x4B8740;

			Sys_InitializeCriticalSections();
			Sys_InitMainThread();
			Win_InitLocalization(0);
			SL_Init();
			Swap_Init();
			Com_InitHunkMemory();
			PMem_Init();
			DB_InitThread();
			Com_InitDvars();
			R_RegisterDvars();

			// gsc stuff
			__asm call Scr_BeginLoadScripts;
			__asm
			{
				push 0x201A45C;
				call Scr_BeginLoadScripts2;
				add esp, 4;
			}
			__asm call Scr_InitAllocNodes;
			
			LargeLocalInit();
			FS_Init();

			load_default_zones();

			// Cmd_RegisterCommands();
			// ZoneTool_LoadZones(nullptr, 0, 0);

			// menu stuff
			//DWORD Menu_Setup1 = 0x4454C0;
			//DWORD Menu_Setup2 = 0x501BC0;
			//__asm call Menu_Setup1;
			//__asm call Menu_Setup2;

			// load weapons
			__asm call G_SetupWeaponDef;

			while (true)
			{
			}
		}

		const char* Linker::get_asset_name(XAssetType type, XAssetHeader header)
		{
			// todo
			if (type == image)
			{
				return header.gfximage->name;
			}
			if (type == menu)
			{
				// 
			}
			else
			{
				return header.rawfile->name;
			}

			return "";
		}

		void* DB_FindXAssetHeader_Unsafe(const XAssetType type, const std::string& name)
		{
			const static auto DB_FindXAssetHeader_Internal = 0x5BB1B0;
			const auto name_ptr = name.data();
			const auto type_int = static_cast<std::int32_t>(type);

			const XAsset* asset_header = nullptr;

			__asm
			{
				mov edi, type_int;
				push name_ptr;
				call DB_FindXAssetHeader_Internal;
				add esp, 4;
				mov asset_header, eax;
			}

			return (asset_header) ? asset_header->ptr.data : nullptr;
		}
		
		void Linker::DB_AddXAsset(XAssetType type, XAssetHeader header)
		{
			static std::vector<std::pair<XAssetType, std::string>> referencedAssets;

			// nice meme
			if (isVerifying)
			{
				// print asset name to console
				ZONETOOL_INFO("Loading asset \"%s\" of type %s.", Linker::get_asset_name(type, header), reinterpret_cast<
char**>(0x00799278)[type]);
			}

#define DECLARE_ASSET(__TYPE__, __ASSET__) \
	if (type == __TYPE__) \
	{ \
		__ASSET__::dump(header.__TYPE__); \
	}

			// fastfile name
			auto fastfile = static_cast<std::string>((char*)(*(DWORD*)0x112A680 + 4));

			// generate CSV for fastfile
			static FILE* csvFile = nullptr;

			if (isVerifying || isDumping)
			{
				FileSystem::SetFastFile(fastfile);
				zonetool::filesystem::set_fastfile(fastfile);

				// open csv file for dumping 
				if (!csvFile)
				{
					csvFile = FileSystem::FileOpen(fastfile + ".csv", "wb");
				}

				// dump assets to disk
				if (csvFile)
				{
					auto xassettypes = reinterpret_cast<char**>(0x00799278);
					fprintf(csvFile, "%s,%s\n", xassettypes[type], get_asset_name(type, header));
				}
			}

			if (isDumping)
			{
				// check if we're done loading the fastfile
				if (type == rawfile && get_asset_name(type, header) == fastfile)
				{
					for (auto& ref : referencedAssets)
					{
						if (ref.second.length() <= 1 || ref.first == XAssetType::loaded_sound)
						{
							continue;
						}

						const auto asset_name = &ref.second[1];
						const auto ref_asset = DB_FindXAssetHeader_Unsafe(ref.first, asset_name);

						if (ref_asset == nullptr)
						{
							ZONETOOL_ERROR("Could not find referenced asset \"%s\"!", asset_name);
							continue;
						}

						ZONETOOL_INFO("Dumping additional asset \"%s\" because it is referenced by %s.", asset_name, currentDumpingZone.data());

						if (ref.first == XAssetType::xmodel)
						{
							auto* xmodel = reinterpret_cast<XModel*>(ref_asset);
							for (auto i = 0; i < xmodel->numSurfaces; i++)
							{
								XAsset material_asset;
								material_asset.type = XAssetType::material;
								material_asset.ptr.material = xmodel->materials[i];
								DB_AddXAsset(material_asset.type, material_asset.ptr);
							}
							for (auto i = 0; i < xmodel->numLods; i++)
							{
								XAsset surface_asset;
								surface_asset.type = XAssetType::xmodelsurfs;
								surface_asset.ptr.xsurface = xmodel->lods[i].surfaces;
								DB_AddXAsset(surface_asset.type, surface_asset.ptr);
							}
						}

						XAssetHeader header;
						header.data = ref_asset;
						
						DB_AddXAsset(ref.first, header);
					}

					ZONETOOL_INFO("Zone \"%s\" dumped.", &fastfile[0]);

					// clear referenced assets array because we are done dumping
					referencedAssets.clear();

					// clear csv file static variable for next dumps
					FileSystem::FileClose(csvFile);
					csvFile = nullptr;

					// mark dumping as complete to exit the process if it has been started using the command line
					if (currentDumpingZone == fastfile)
					{
						isDumpingComplete = true;
					}
				}

				if (get_asset_name(type, header)[0] == ',')
				{
					referencedAssets.push_back({ type, get_asset_name(type, header) });
				}
				else
				{
					try
					{
						DECLARE_ASSET(addon_map_ents, IAddonMapEnts);
						DECLARE_ASSET(xmodelsurfs, IXSurface);
						DECLARE_ASSET(xmodel, IXModel);
						DECLARE_ASSET(material, IMaterial);
						DECLARE_ASSET(xanim, IXAnimParts);
						DECLARE_ASSET(gfx_map, IGfxWorld);
						DECLARE_ASSET(col_map_mp, IClipMap);
						DECLARE_ASSET(map_ents, IMapEnts);
						DECLARE_ASSET(fx_map, IFxWorld);
						DECLARE_ASSET(com_map, IComWorld);
						DECLARE_ASSET(rawfile, IRawFile);
						DECLARE_ASSET(image, IGfxImage);
						DECLARE_ASSET(fx, IFxEffectDef);
						DECLARE_ASSET(game_map_mp, IGameWorldMp);
						DECLARE_ASSET(game_map_sp, IGameWorldSp);
						DECLARE_ASSET(physpreset, IPhysPreset);
						DECLARE_ASSET(sound, ISound);
						DECLARE_ASSET(sndcurve, ISoundCurve);
						DECLARE_ASSET(loaded_sound, ILoadedSound);
					}
					catch (std::exception& ex)
					{
						ZONETOOL_FATAL("A fatal exception occured while dumping asset \"%s\", exception was: %s\n", get_asset_name(type, header), ex.what());
					}
				}
			}
			else
			{
				/*std::string fastfile = static_cast<std::string>((char*)(*(DWORD*)0x112A680 + 4));
				if (fastfile.find("mp_") != std::string::npos || fastfile == "common_mp"s)
				{
					FileSystem::SetFastFile("");

					// dump everything techset related!
					DECLARE_ASSET(material, IMaterial);
					DECLARE_ASSET(techset, ITechset);
					DECLARE_ASSET(pixelshader, IPixelShader);
					DECLARE_ASSET(vertexshader, IVertexShader);
					DECLARE_ASSET(vertexdecl, IVertexDecl);
				}*/
			}
		}

		void __declspec(naked) Linker::DB_AddXAssetStub()
		{
			// return to original function
			__asm
			{
				// original code
				sub esp, 0x14;
				mov eax, [esp + 1Ch];
				mov ecx, [eax];
				push ebx;
				push ebp;
				mov ebp, [esp + 20h];

				// call our DB_AddXAsset function
				pushad;
				push ecx;
				push ebp;
				call DB_AddXAsset;
				add esp, 8;
				popad;

				// jump back
				push 0x005BB65F;
				retn;
			}
		}

		void** DB_XAssetPool = (void**)0x7998A8;
		unsigned int* g_poolSize = (unsigned int*)0x7995E8;

		void* ReallocateAssetPool(uint32_t type, unsigned int newSize)
		{
			int elSize = DB_GetXAssetSizeHandlers[type]();

			void* poolEntry = malloc(newSize * elSize);
			DB_XAssetPool[type] = poolEntry;
			g_poolSize[type] = newSize;

			return poolEntry;
		}

		void* ReallocateAssetPoolM(uint32_t type, int multiplier)
		{
			int elSize = DB_GetXAssetSizeHandlers[type]();
			int newSize = multiplier * g_poolSize[type];

			void* poolEntry = malloc(newSize * elSize);
			DB_XAssetPool[type] = poolEntry;
			g_poolSize[type] = newSize;

			return poolEntry;
		}

		int readPosition = 0;

		void logStreamPosition(int bytesRead)
		{
			if (isVerifying)
			{
				// ZONETOOL_INFO("Read %u bytes. (Currently at position 0x%08X in file)", bytesRead, readPosition - bytesRead);
			}
		}

		__declspec(naked) void Linker::IncreaseReadPointer()
		{
			__asm
			{
				// store read position
				add readPosition, ecx;
				mov DWORD PTR ds : 0x112a6c4, ecx;

				// log data
				pushad;
				push ecx;
				call logStreamPosition;
				add esp, 4;
				popad;

				// go back
				push 0x00445473;
				retn;
			}
		}

		__declspec(naked) void Linker::IncreaseReadPointer2()
		{
			__asm
			{
				// store read position
				add readPosition, esi;

				// original code
				mov eax, 0x006B4B80;
				call eax;

				// log data
				pushad;
				push esi;
				call logStreamPosition;
				add esp, 4;
				popad;

				// go back
				push 0x00470E56;
				retn;
			}
		}

		void Linker::ReadHeader(void* ptr, int size)
		{
			// reset readPosition
			readPosition = 0;

			// read header
			return Memory::func<void(void*, int)>(0x00445460)(ptr, size);
		}

		void Linker::Load_XSurfaceArray(int shouldLoad, int count)
		{
			// read the actual count from the varXModelSurfs ptr
			auto surface = *reinterpret_cast<XModelSurfs**>(0x0112A95C);

			// call original read function with the correct count
			return Memory::func<void(int, int)>(0x004925B0)(shouldLoad, surface->numsurfs);
		}

        const char* Linker::GetZonePath(const char* zoneName)
        {
            static std::string lastZonePath;
            static std::vector<std::string> zonePaths =
            {
                "zone\\dlc\\",
                "zone\\patch\\"
            };

            const std::string zoneFileName = zoneName;
            const char* languageName = Memory::func<const char* ()>(0x45CBA0)();

            // Priority 1: localized zone folder
            const std::string localizedZonePath = va("zone\\%s\\", languageName, zoneName);
            if(std::filesystem::exists(localizedZonePath + zoneFileName))
            {
                lastZonePath = localizedZonePath;
                return lastZonePath.c_str();
            }

            // Priority 2: custom zone paths
            for(auto customZonePath : zonePaths)
            {
                if (std::filesystem::exists(customZonePath + zoneFileName))
                {
                    lastZonePath = customZonePath;
                    return lastZonePath.c_str();
                }
            }

            // If no file could be found return the default location. The game will notice itself that there is no fastfile.
            lastZonePath = localizedZonePath;
            return lastZonePath.c_str();
        }

		void ExitZoneTool()
		{
			std::exit(0);
		}

		auto should_log = false;
		void LogFile(const std::string& log)
		{
			if (!should_log)
			{
				return;
			}

			static auto did_delete = false;
			if (!did_delete && std::filesystem::exists("Z:\\loading-zt.txt"))
			{
				did_delete = true;
				std::filesystem::remove("Z:\\loading-zt.txt");
			}

			static auto fp = fopen("Z:\\loading-zt.txt", "a");
			fprintf(fp, log.data());
			fflush(fp);
		}
		
		void __declspec(naked) Load_Stream(bool atStreamStart, char* data, int count)
		{
			static auto load_stream = 0x470E35;
			__asm
			{
				cmp byte ptr[esp + 4], 0;
				jmp load_stream;
			}
		}

		void Load_StreamHook(bool atStreamStart, char* data, int count)
		{
			if (atStreamStart)
			{
				LogFile(va("Load_Stream: Reading %u bytes.\n", count));
			}

			Load_Stream(atStreamStart, data, count);
		}

		void __declspec(naked) DB_PushStreamPos(int stream)
		{
			static auto db_pushstreampos = 0x458A25;
			__asm
			{
				mov eax, ds:0x16e5578
				jmp db_pushstreampos;
			}
		}

		void DB_PushStreamPosHook(int stream)
		{
			LogFile(va("DB_PushStreamPos: Setting stream to %u\n", stream));
			DB_PushStreamPos(stream);
		}

		void __declspec(naked) DB_PopStreamPos()
		{
			static auto db_popstreampos = 0x4D1D65;
			__asm
			{
				mov eax, ds:0x16E5548;
				jmp db_popstreampos;
			}
		}

		void DB_PopStreamPosHook()
		{
			LogFile(va("DB_PopStreamPos: Popped stream\n"));
			DB_PopStreamPos();
		}

		void log_align(int align)
		{
			LogFile(va("DB_AllocStreamPos: Aligning buffer by %i\n", align));
		}

#undef not

		void __declspec(naked) DB_AllocStreamPosHook()
		{
			__asm
			{
				mov ecx, [esp + 4];
				pushad;
				push ecx;
				call log_align;
				add esp, 4;
				popad;
				mov eax, ds:0x16e5554;
				add eax, ecx;
				not ecx;
				and eax, ecx;
				mov ds:0x16e5554, eax;
				retn;
			}
		}

		FS_FOpenFileReadForThread_t FS_FOpenFileReadForThread = FS_FOpenFileReadForThread_t(0x643270);
		FS_FCloseFile_t FS_FCloseFile = FS_FCloseFile_t(0x462000);
		FS_Read_t FS_Read = FS_Read_t(0x4A04C0);

		std::string filesystem_read_big_file(const char* filename)
		{
			std::string file_buffer{};

			int handle = -1;
			FS_FOpenFileReadForThread(filename, &handle, 2);

			if (handle > 0)
			{
				constexpr unsigned int BUFF_SIZE = 1024;

				while (true)
				{
					char buffer[BUFF_SIZE];
					auto size_read = FS_Read(buffer, BUFF_SIZE, handle);

					file_buffer.append(buffer, size_read);

					if (size_read < BUFF_SIZE)
					{
						// We're done!
						break;
					}
				}

				FS_FCloseFile(handle);
			}

			return file_buffer;
		}

		void Linker::startup()
		{
			if (this->is_used())
			{
				set_linker_mode(linker_mode::iw4);

				// 
				Memory(0x470E30).jump(Load_StreamHook);
				Memory(0x458A20).jump(DB_PushStreamPosHook);
				Memory(0x4D1D60).jump(DB_PopStreamPosHook);
				Memory(0x418380).jump(DB_AllocStreamPosHook);
				
				// do nothing with online sessions
				Memory(0x441650).set<std::uint8_t>(0xC3);

				// Realloc asset pools
				ReallocateAssetPoolM(localize, 2);
				ReallocateAssetPoolM(material, 2);
				ReallocateAssetPoolM(font, 2);
				ReallocateAssetPoolM(image, 2);
				ReallocateAssetPoolM(techset, 2);
				ReallocateAssetPoolM(fx, 2);
				ReallocateAssetPoolM(xanim, 2);
				ReallocateAssetPoolM(xmodel, 2);
				ReallocateAssetPoolM(physpreset, 2);
				ReallocateAssetPoolM(weapon, 2);
				ReallocateAssetPoolM(game_map_sp, 2);
				ReallocateAssetPoolM(game_map_mp, 2);
				ReallocateAssetPoolM(map_ents, 5);
				ReallocateAssetPoolM(com_map, 5);
				ReallocateAssetPoolM(col_map_mp, 5);
				ReallocateAssetPoolM(gfx_map, 5);
				ReallocateAssetPoolM(fx_map, 5);
				ReallocateAssetPoolM(xmodelsurfs, 2);
				ReallocateAssetPoolM(vertexshader, 2);
				ReallocateAssetPoolM(vertexdecl, 16);
				ReallocateAssetPoolM(pixelshader, 2);
				ReallocateAssetPoolM(rawfile, 2);
				ReallocateAssetPoolM(lightdef, 2);

				// Kill "missing asset" errors from the game to prevent confusion
				Memory(0x5BB380).set<std::uint8_t>(0xC3);
				
				// Kill Com_Error
				Memory(0x004B22D0).jump(ExitZoneTool);

				// Tool init func
				Memory(0x6BABA1).call(run);
				Memory(0x4AA88B).call(printf);

				// r_loadForRenderer
				Memory(0x519DDF).set<BYTE>(0x0);

				// dirty disk breakpoint
				// Memory(0x4CF7F0).Set<BYTE>(0xCC);

				// delay loading of images, disable it
				Memory(0x51F450).set<BYTE>(0xC3);

				// don't remove the 'texture data' pointer from GfxImage	
				Memory(0x51F4FA).nop(6);

				// needed for the above to make Image_Release not misinterpret the texture data as a D3D texture
				Memory(0x51F03D).set<BYTE>(0xEB);

				// don't zero out pixel shaders
				Memory(0x505AFB).nop(7);

				// don't zero out vertex shaders
				Memory(0x505BDB).nop(7);

				// don't memset vertex declarations (not needed?)
				Memory(0x00431B91).nop(5);

				// allow loading of IWffu (unsigned) files
				Memory(0x4158D9).set<BYTE>(0xEB); //main function
				Memory(0x4A1D97).nop(2); //DB_AuthLoad_InflateInit

				// basic checks (hash jumps, both normal and playlist)
				Memory(0x5B97A3).nop(2);
				Memory(0x5BA493).nop(2);

				Memory(0x5B991C).nop(2);
				Memory(0x5BA60C).nop(2);

				Memory(0x5B97B4).nop(2);
				Memory(0x5BA4A4).nop(2);

				// some other, unknown, check
				Memory(0x5B9912).set<BYTE>(0xB8);
				Memory(0x5B9913).set<DWORD>(1);

				Memory(0x5BA602).set<BYTE>(0xB8);
				Memory(0x5BA603).set<DWORD>(1);

				// something related to image loading
				Memory(0x54ADB0).set<BYTE>(0xC3);

				// dvar setting function, unknown stuff related to server thread sync
				Memory(0x647781).set<BYTE>(0xEB);

				// fs_basegame
				Memory(0x6431D1).set("zonetool");

				// hunk size (was 300 MiB)
				Memory(0x64A029).set<DWORD>(0x3F000000);
				Memory(0x64A057).set<DWORD>(0x3F000000); // 0x1C200000

				// allow loading of IWffu (unsigned) files
				Memory(0x4158D9).set<BYTE>(0xEB); // main function
				Memory(0x4A1D97).nop(2); // DB_AuthLoad_InflateInit

				// basic checks (hash jumps, both normal and playlist)
				Memory(0x5B97A3).nop(2);
				Memory(0x5BA493).nop(2);

				Memory(0x5B991C).nop(2);
				Memory(0x5BA60C).nop(2);

				Memory(0x5B97B4).nop(2);
				Memory(0x5BA4A4).nop(2);

				// Disabling loadedsound touching
				Memory(0x492EFC).nop(5);

				// weaponfile patches
				Memory(0x408228).nop(5); // find asset header
				Memory(0x408230).nop(5); // is asset default
				Memory(0x40823A).nop(2); // jump

				// menu stuff
				// disable the 2 new tokens in ItemParse_rect
				Memory(0x640693).set<BYTE>(0xEB);

				// Dont load ASSET_TYPE_MENU anymore, we dont need it.
				Memory(0x453406).nop(5);

				// DB_AddXAsset hook
				Memory(0x005BB650).jump(DB_AddXAssetStub);

				// Fix fucking XSurface assets
				Memory(0x0048E8A5).call(Load_XSurfaceArray);

				// Fastfile debugging
				Memory(0x0044546D).jump(IncreaseReadPointer);
				Memory(0x00470E51).jump(IncreaseReadPointer2);
				Memory(0x004159E2).call(ReadHeader);

                // Load fastfiles from custom zone folders
                Memory(0x44DA90).jump(GetZonePath);
			}
		}
		
		std::shared_ptr<IZone> Linker::alloc_zone(const std::string& zone)
		{
			ZONETOOL_ERROR("AllocZone called but IW4 is not intended to compile zones!");
			return nullptr;
		}

		std::shared_ptr<ZoneBuffer> Linker::alloc_buffer()
		{
			ZONETOOL_ERROR("AllocBuffer called but IW4 is not intended to compile zones!");
			return nullptr;
		}

		void Linker::load_zone(const std::string& name)
		{
			ZONETOOL_INFO("Loading zone \"%s\"...", name.data());

			XZoneInfo zone = {name.data(), 20, 0};
			DB_LoadXAssets(&zone, 1, 0);

			ZONETOOL_INFO("Zone \"%s\" loaded.", name.data());
		}

		void Linker::unload_zones()
		{
		}

		bool Linker::is_valid_asset_type(const std::string& type)
		{
			return this->type_to_int(type) >= 0;
		}

		std::int32_t Linker::type_to_int(std::string type)
		{
			auto xassettypes = reinterpret_cast<char**>(0x00799278);

			for (std::int32_t i = 0; i < max; i++)
			{
				if (xassettypes[i] == type)
					return i;
			}

			return -1;
		}

		std::string Linker::type_to_string(std::int32_t type)
		{
			auto xassettypes = reinterpret_cast<char**>(0x00799278);
			return xassettypes[type];
		}

		bool Linker::supports_building()
		{
			return false;
		}

		bool Linker::supports_version(const zone_target_version version)
		{
			return version == zone_target_version::iw4_release || version == zone_target_version::iw4_release_console || 
				version == zone_target_version::iw4_alpha_482 || version == zone_target_version::iw4_alpha_491;
		}

        void Linker::dump_zone(const std::string& name, zonetool::dump_target target)
		{
			zonetool::dumping_target = target;
			zonetool::dumping_source = zonetool::iw4;

			isDumpingComplete = false;
			isDumping = true;
			currentDumpingZone = name;
			load_zone(name);

			while (!isDumpingComplete)
			{
				Sleep(1);
			}
		}

		void Linker::verify_zone(const std::string& name)
		{
			//should_log = true;
			isVerifying = true;
			currentDumpingZone = name;
			load_zone(name);
		}
	}
}