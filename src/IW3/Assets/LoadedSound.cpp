#include "stdafx.hpp"
#include "IW4/Assets/LoadedSound.hpp"

namespace ZoneTool
{
	namespace IW3
	{
		void ILoadedSound::dump(LoadedSound* asset)
		{
			IW4::ILoadedSound::dump(reinterpret_cast<IW4::LoadedSound*>(asset));
		}
	}
}