// ======================= ZoneTool =======================
// zonetool, a fastfile linker for various
// Call of Duty titles. 
//
// Project: https://github.com/ZoneTool/zonetool
// Author: RektInator (https://github.com/RektInator)
// License: GNU GPL v3.0
// ========================================================
#include "stdafx.hpp"
#include "../IW5/Assets/GlassWorld.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		GameWorldMp* IGameWorldMp::parse(const std::string& name, ZoneMemory* mem)
		{
			return reinterpret_cast<GameWorldMp*>(IW5::IGlassWorld::parse(name, mem));
		}

		void IGameWorldMp::init(void* asset, ZoneMemory* mem)
		{
			this->asset_ = reinterpret_cast<GameWorldMp*>(asset);
			this->name_ = "maps/"s + (currentzone.substr(0, 3) == "mp_" ? "mp/" : "") + currentzone + ".d3dbsp"; // name;
		}

		void IGameWorldMp::init(const std::string& name, ZoneMemory* mem)
		{
			this->name_ = "maps/"s + (currentzone.substr(0, 3) == "mp_" ? "mp/" : "") + currentzone + ".d3dbsp"; // name;
			this->asset_ = this->parse(name, mem);

			if (!this->asset_)
			{
				this->asset_ = DB_FindXAssetHeader(this->type(), name.data()).gameworldmp;
			}
		}

		void IGameWorldMp::prepare(ZoneBuffer* buf, ZoneMemory* mem)
		{
		}

		void IGameWorldMp::load_depending(IZone* zone)
		{
		}

		std::string IGameWorldMp::name()
		{
			return this->name_;
		}

		std::int32_t IGameWorldMp::type()
		{
			return game_map_mp;
		}

		void IGameWorldMp::write(IZone* zone, ZoneBuffer* buf)
		{

		}

		void IGameWorldMp::dump(GameWorldMp* asset)
		{
			IW5::IGlassWorld::dump(reinterpret_cast<IW5::GlassWorld*>(asset));
		}
	}
}
