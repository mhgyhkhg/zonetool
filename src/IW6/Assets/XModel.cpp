#include "stdafx.hpp"

namespace ZoneTool
{
	namespace IW6
	{
		void IXModel::dump(XModel* asset, const std::function<const char* (std::uint16_t)>& SL_ConvertToString)
		{
			AssetDumper dump;
			dump.open("XModel\\"s + asset->name + ".xme6");

			dump.dump_single(asset);

			// name
			dump.dump_string(asset->name);

			// tags
			dump.dump_array(asset->boneNames, asset->numBones);
			for (int i = 0; i < asset->numBones; i++)
			{
				dump.dump_string(SL_ConvertToString(asset->boneNames[i]));
			}
			dump.dump_array(asset->parentList, asset->numBones - asset->numRootBones);
			dump.dump_array(asset->tagAngles, asset->numBones - asset->numRootBones);
			dump.dump_array(asset->tagPositions, asset->numBones - asset->numRootBones);
			dump.dump_array(asset->partClassification, asset->numBones);
			dump.dump_array(asset->baseMat, asset->numBones);
			dump.dump_array(asset->reactiveMotionParts, asset->numReactiveMotionParts);
			dump.dump_array(asset->collSurfs, asset->numCollSurfs);
			dump.dump_array(asset->boneInfo, asset->numBones);
			dump.dump_array(asset->__unk, asset->numsurfs);

			// surfaces
			dump.dump_array(asset->materialHandles, asset->numsurfs);
			for (int i = 0; i < asset->numsurfs; i++)
			{
				dump.dump_asset(asset->materialHandles[i]);
			}

			// lods
			for (int i = 0; i < 6; i++)
			{
				dump.dump_asset(asset->lodInfo[i].modelSurfs);
			}

			// subassets
			dump.dump_asset(asset->physPreset);
			dump.dump_asset(asset->physCollmap);

			dump.close();
		}
	}
}