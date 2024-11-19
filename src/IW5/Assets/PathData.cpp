#include "stdafx.hpp"

#include "Dumper/H1/Assets/PathData.hpp"
#include "Dumper/S1/Assets/PathData.hpp"

namespace ZoneTool::IW5
{
	void IPathData::dump(PathData* asset)
	{
		if (zonetool::dumping_target == zonetool::dump_target::h1 || zonetool::dumping_target == zonetool::dump_target::s1)
		{
			return H1Dumper::dump(asset);
		}
		else if (zonetool::dumping_target == zonetool::dump_target::s1)
		{
			return S1Dumper::dump(asset);
		}
	}
}