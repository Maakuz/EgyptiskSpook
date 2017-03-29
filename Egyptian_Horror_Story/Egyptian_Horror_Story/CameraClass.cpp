#include "CameraClass.h"

CameraClass::CameraClass(float width, float height)
{
	float fovAngle = M_PI * 0.45;
	float aspectRatio = width / height;

	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(fovAngle, aspectRatio, 0.1f, 50.f);
	projection = DirectX::XMMatrixTranspose(projection);

	//DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH();
}

CameraClass::~CameraClass()
{
}
