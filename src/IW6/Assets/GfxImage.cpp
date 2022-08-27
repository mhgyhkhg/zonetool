#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW6
	{
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

		void IGfxImage::dump(GfxImage* asset)
		{
			assert(sizeof(GfxImage) == 104);

			auto newName = clean_name(asset->name);

			auto path = "images\\"s + newName + ".iw6Image"s;
			assetmanager::dumper write;
			if (!write.open(path))
			{
				return;
			}

			if (asset->sematic == 11)
			{
				ZONETOOL_WARNING("GfxImage (%s) was not dumped succesfully!", asset->name);
				write.close();
				return;
			}

			write.dump_single(asset);
			write.dump_string(asset->name);

			if (asset->pixelData)
			{
				write.dump_array(asset->pixelData, asset->dataLen1);
			}

			if (asset->streamed)
			{
				asset->streamed = false;
			}
			write.close();
		}
	}
}