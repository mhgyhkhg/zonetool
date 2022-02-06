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
	namespace IW5
	{
		MenuList* IMenuList::parse(const std::string& name, ZoneMemory* mem)
		{
			return nullptr;
		}

		void IMenuList::init(const std::string& name, ZoneMemory* mem)
		{
			this->name_ = name;
			this->asset_ = parse(name, mem);

			if (!this->asset_)
			{
				this->asset_ = DB_FindXAssetHeader(this->type(), this->name().data(), 1).menuList;
			}
		}

		void IMenuList::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
		}

		void IMenuList::load_depending(IZone* zone)
		{
			auto* data = this->asset_;
			if (data->menus)
			{
				for (int i = 0; i < data->menuCount; i++)
				{
					zone->add_asset_of_type_by_pointer(menu, data->menus[i]);
				}
			}
		}

		std::string IMenuList::name()
		{
			return this->name_;
		}

		std::int32_t IMenuList::type()
		{
			return menufile;
		}

		void IMenuList::write(IZone* zone, ZoneBuffer* buf)
		{
			auto data = this->asset_;
			auto dest = buf->write(data);

			buf->push_stream(3);

			dest->name = buf->write_str(this->name_);

			if (data->menus)
			{
				buf->align(3);
				auto* destMenus = buf->write(data->menus, data->menuCount);
				for (int i = 0; i < data->menuCount; i++)
				{
					destMenus[i] = reinterpret_cast<menuDef_t*>(zone->get_asset_pointer(menu, data->menus[i]->window.name));
				}
			}

			buf->pop_stream();
		}

		void IMenuList::dump(MenuList* asset)
		{
		}
	}
}
