#ifndef CAMERACLASS_H
#define CAMERACLASS_H

//För att kunna använda M_PI
#define _USE_MATH_DEFINES

#include <math.h>
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")

struct WVP
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};

class CameraClass
{
private:
	WVP matrices;
	DirectX::XMFLOAT3 mPos;
	DirectX::XMFLOAT3 mForward;
	DirectX::XMFLOAT3 mRight;
	DirectX::XMFLOAT3 mUp;

public:
	CameraClass(float width, float height);
	virtual ~CameraClass();

};



#endif