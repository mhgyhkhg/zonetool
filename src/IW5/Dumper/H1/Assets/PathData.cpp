#include "stdafx.hpp"

#include "PathData.hpp"
#include "Converter/H1/Assets/PathData.hpp"
#include "H1/Assets/PathData.hpp"

#include "IW3/Structs.hpp"
#include "IW3/Functions.hpp"

#include "IW4/Structs.hpp"
#include "IW4/Functions.hpp"

namespace ZoneTool::IW5::H1Dumper
{
	void dump(PathData* asset)
	{
		allocator allocator;
		auto* h1_asset = H1Converter::convert(asset, allocator);

		if (zonetool::dumping_source == zonetool::iw3)
		{
			H1::IPathData::dump(h1_asset, IW3::SL_ConvertToString);
		}
		else if (zonetool::dumping_source == zonetool::iw4)
		{
			H1::IPathData::dump(h1_asset, IW4::SL_ConvertToString);
		}
		else if (zonetool::dumping_source == zonetool::iw5)
		{
			H1::IPathData::dump(h1_asset, IW5::SL_ConvertToString);
		}
	}
}