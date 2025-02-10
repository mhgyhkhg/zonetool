#include "stdafx.hpp"
#include "IW5/Assets/LoadedSound.hpp"

namespace ZoneTool
{
	namespace IW4
	{
		void ILoadedSound::dump(LoadedSound* asset)
		{
			IW5::ILoadedSound::dump(reinterpret_cast<IW5::LoadedSound*>(asset));
		}
	}
}