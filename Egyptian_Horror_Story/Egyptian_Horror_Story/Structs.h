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

	struct lightInfo
	{
		DirectX::SimpleMath::Vector4 pos;
		DirectX::SimpleMath::Vector4 dir;
		bool flashlightOn;
		DirectX::SimpleMath::Vector3 padding;
	};
}

namespace camera 
{
	struct VP
	{
		DirectX::SimpleMath::Matrix view, projection;
	};
}


namespace settings
{
	struct GraphicSettings
	{
		int width;
		int height;
		float fov;
		float brightness;
		float farPlane;
	};
}


#endif
