#ifndef CAMERACLASS_H
#define CAMERACLASS_H

//För att kunna använda M_PI
#define _USE_MATH_DEFINES

#include "Direct3DHeader.h"

#include <math.h>
#include "SimpleMath.h"

struct WVP
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};

class CameraClass
{
private:
	WVP matrices;

	ID3D11Buffer* WVPBuffer;

	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mForward;
	DirectX::SimpleMath::Vector3 mRight;
	DirectX::SimpleMath::Vector3 mUp;

public:
	CameraClass(ID3D11Device* device, float width, float height);
	virtual ~CameraClass();

	void createVWPBuffer(ID3D11Device* device);

	ID3D11Buffer* getMatrixBuffer();

};



#endif