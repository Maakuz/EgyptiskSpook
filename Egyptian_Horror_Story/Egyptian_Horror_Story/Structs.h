#ifndef STRUCTS_H
#define STRUCTS_H

#include "SimpleMath.h"

namespace EntityStruct
{
	struct VertexStruct
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector3 normal;
		DirectX::SimpleMath::Vector2 uv;
	};

	struct weightAndIndex
	{
		int index;
		float weight;
	};

	struct SkinnedVertexStruct
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector3 normal;
		DirectX::SimpleMath::Vector2 uv;
		weightAndIndex weightIndex[4];
	};
}

namespace animation
{
	struct Bone
	{
		DirectX::SimpleMath::Matrix relativeForm, absoluteForm, invBindPose;
		int parent;
	};
}

namespace lightStructs {
	struct VP
	{
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
	};

	struct lightPosDir
	{
		DirectX::SimpleMath::Vector4 pos;
		DirectX::SimpleMath::Vector4 dir;
	};
}

namespace camera 
{
	struct WVP
	{
		DirectX::SimpleMath::Matrix world, view, projection;
	};
}





#endif
