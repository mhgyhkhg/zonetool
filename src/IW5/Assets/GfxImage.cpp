#include "stdafx.hpp"
#include "IW6/Assets/GfxImage.hpp"

#include <DirectXTex.h>

namespace ZoneTool
{
	namespace IW5
	{
		enum IMG_FLAGS_IW6 : std::uint32_t
		{
			IMG_FLAG_NOPICMIP = 0x1,
			IMG_FLAG_NOMIPMAPS = 0x2,
			IMG_FLAG_STREAMING = 0x4,
			IMG_FLAG_LEGACY_NORMALS = 0x8,
			IMG_FLAG_CLAMP_U = 0x10,
			IMG_FLAG_CLAMP_V = 0x20,
			IMG_FLAG_ALPHA_WEIGHTED_COLORS = 0x40,
			IMG_FLAG_DXTC_APPROX_WEIGHTS = 0x80,
			IMG_FLAG_GAMMA_NONE = 0x0,
			IMG_FLAG_GAMMA_SRGB = 0x100,
			IMG_FLAG_GAMMA_PWL = 0x200,
			IMG_FLAG_GAMMA_2 = 0x300,
			IMG_FLAG_CPU_READ = 0x800,
			IMG_FLAG_CPU_WRITE = 0x1000,
			IMG_FLAG_POM = 0x2000,
			IMG_FLAG_AUTODISPLACEMENT = 0x4000,
			IMG_FLAG_MAPTYPE_2D = 0x0,
			IMG_FLAG_MAPTYPE_CUBE = 0x8000,
			IMG_FLAG_MAPTYPE_3D = 0x10000,
			IMG_FLAG_MAPTYPE_1D = 0x18000,
			IMG_FLAG_MAPTYPE_ARRAY = 0x20000,
			IMG_FLAG_MODE_NONE = 0x0,
			IMG_FLAG_MODE_NORMAL_MAP = 0x40000,
			IMG_FLAG_MODE_DISPLACEMENT_MAP = 0xC0000,
			IMG_FLAG_MODE_OCEAN_DISPLACEMENT_MAP = 0x80000,
			IMG_FLAG_MIPGEN_ORIGINAL = 0x0,
			IMG_FLAG_MIPGEN_LANCZOS2 = 0x100000,
			IMG_FLAG_MIPGEN_LANCZOS3 = 0x200000,
			IMG_FLAG_MIPGEN_MITCHELL = 0x300000,
			IMG_FLAG_MIPGEN_CATMULL_ROM = 0x400000,
			IMG_FLAG_MIPGEN_CUBIC_BSPLINE = 0x500000,
			IMG_FLAG_MIPGEN_HERMITE = 0x600000,
			IMG_FLAG_MIPGEN_BOX = 0x700000,
			IMG_FLAG_GENMIPMAPS = 0x800000,
			IMG_FLAG_DYNAMIC = 0x1000000,
			IMG_FLAG_RENDER_TARGET = 0x2000000,
			IMG_FLAG_FLOATING_POINT = 0x8000000,
			IMG_FLAG_PARABOLOID = 0x10000000,
			IMG_FLAG_STAGING = 0x20000000,
			IMG_FLAG_DEPTH = 0x40000000,
			IMG_FLAG_TYPELESS = 0x80000000,
		};

		enum class IMG_FLAGS_IW5 : std::uint32_t
		{
			IMG_FLAG_NOPICMIP = 0x1,
			IMG_FLAG_NOMIPMAPS = 0x2,
			IMG_FLAG_STREAMING = 0x4,
			IMG_FLAG_LEGACY_NORMALS = 0x8,
			IMG_FLAG_CLAMP_U = 0x10,
			IMG_FLAG_CLAMP_V = 0x20,
			IMG_FLAG_ALPHA_WEIGHTED_COLORS = 0x40,
			IMG_FLAG_DXTC_APPROX_WEIGHTS = 0x80,
			IMG_FLAG_GAMMA_NONE = 0x0,
			IMG_FLAG_GAMMA_SRGB = 0x100,
			IMG_FLAG_GAMMA_PWL = 0x200,
			IMG_FLAG_GAMMA_2 = 0x300,
			IMG_FLAG_MAPTYPE_2D = 0x0,
			IMG_FLAG_MAPTYPE_CUBE = 0x10000,
			IMG_FLAG_MAPTYPE_3D = 0x20000,
			IMG_FLAG_MAPTYPE_1D = 0x30000,
			IMG_FLAG_NORMALMAP = 0x40000,
			IMG_FLAG_INTENSITY_TO_ALPHA = 0x80000,
			IMG_FLAG_DYNAMIC = 0x1000000,
			IMG_FLAG_RENDER_TARGET = 0x2000000,
			IMG_FLAG_SYSTEMMEM = 0x4000000,
		};

		IW6::GfxImage* GenerateIW6GfxImage(GfxImage* asset, ZoneMemory* mem)
		{
			// allocate IW6 GfxImage structure
			const auto iw6_asset = mem->Alloc<IW6::GfxImage>();

			iw6_asset->name = asset->name;
			iw6_asset->imageFormat = MFMapDX9FormatToDXGIFormat(asset->texture->format);
			iw6_asset->mapType = static_cast<IW6::MapType>(asset->mapType);
			iw6_asset->sematic = asset->semantic;
			iw6_asset->category = asset->category;
			iw6_asset->flags = asset->flags;
			iw6_asset->dataLen1 = asset->texture->dataSize;
			iw6_asset->dataLen2 = asset->texture->dataSize;
			iw6_asset->width = asset->width;
			iw6_asset->height = asset->height;
			iw6_asset->depth = asset->depth;
			iw6_asset->numElements = asset->texture->levelCount;
			iw6_asset->unknown = asset->mapType == 5 ? 7 : 1;
			iw6_asset->streamed = false;
			iw6_asset->pixelData = reinterpret_cast<unsigned char*>(&asset->texture->texture);

			return iw6_asset;
		}

		std::string clean_name(const std::string& name)
		{
			auto newName = name;

			for (auto i = 0u; i < name.size(); i++)
			{
				switch (newName[i])
				{
				case '*':
					newName[i] = '_';
					break;
				}
			}

			return newName;
		}

		void dump_image(GfxImage* image)
		{
			auto newName = clean_name(image->name);

			DirectX::Image img = {};
			img.pixels = reinterpret_cast<std::uint8_t*>(&image->texture->texture);
			img.width = image->width;
			img.height = image->height;

			auto format = MFMapDX9FormatToDXGIFormat(image->texture->format);
			//ZONETOOL_INFO("%s format (%d) -> (%d)", image->name, image->texture->format, format);
			if (format == DXGI_FORMAT_UNKNOWN)
			{
				ZONETOOL_WARNING("Unknown DX9 format for image \"%s\" (%d)", image->name, image->texture->format);
			}
			img.format = DXGI_FORMAT(format);

			size_t rowPitch;
			size_t slicePitch;
			DirectX::ComputePitch(img.format, img.width, img.height, rowPitch, slicePitch);

			img.rowPitch = rowPitch;
			img.slicePitch = slicePitch;

			std::filesystem::path path = ("dump\\" + FileSystem::GetFastFile() + "\\images\\" + newName + ".dds");

			FileSystem::CreateDirectory(path.parent_path().string());

			std::string str = path.string();
			std::wstring str2(str.begin(), str.end());

			auto result = DirectX::SaveToDDSFile(img, DirectX::DDS_FLAGS_NONE, str2.data());
			if (FAILED(result))
			{
				ZONETOOL_WARNING("Failed to dump image \"%s.dds\"", image->name);
			}
		}

		void DumpIW5GfxImageDDS(GfxImage* image)
		{
			dump_image(image);
		}

		void IGfxImage::dump(GfxImage* asset, ZoneMemory* mem)
		{
			assert(sizeof(IW6::GfxImage) == 104);

			std::string name = asset->name;

			bool isMapImage = (name.size() >= 6)
				? ((name.substr(0, 6) == "*light" || name.substr(0, 6) == "*refle" ||
					name == "$outdoor")
					? true
					: false)
				: false;

			if (!isMapImage) return;

			if (!asset->texture->dataSize)
			{
				ZONETOOL_INFO("Not dumping image %s", asset->name);
				return;
			}

			// NOT CORRECT!

			// generate iw6 gfximage
			auto iw6_asset = GenerateIW6GfxImage(asset, mem);

			// dump image as dds
			//DumpIW5GfxImageDDS(asset);

			// dump iw6 glassworld
			IW6::IGfxImage::dump(iw6_asset);
		}
	}
}