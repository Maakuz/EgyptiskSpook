#ifndef CAMERACLASS_H
#define CAMERACLASS_H

//För att kunna använda M_PI
#define _USE_MATH_DEFINES

#include "Direct3DHeader.h"
#include "GraphicsData.h"

#include <math.h>
#include"Structs.h"


class CameraClass
{
private:
	const double DEGTORADIANS = M_PI / 180;
	
	camera::WVP mMatrices;

	ID3D11Buffer* mWVPBuffer;
	GraphicsData* mGraphicsData;
	GraphicsData* mGraphicsData2;
	static const int CAMPOSKEY = 302;

	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mForward;
	DirectX::SimpleMath::Vector3 mRight;
	DirectX::SimpleMath::Vector3 mUp;

	float mPitch;
	float mYaw;

public:
	CameraClass(ID3D11Device* device, GraphicsData* gData, GraphicsData* gData2, float width, float height);
	virtual ~CameraClass();

	void createVWPBuffer(ID3D11Device* device);
	void update(ID3D11DeviceContext* context);
	void updateRotation(ID3D11DeviceContext* context);

	ID3D11Buffer* getMatrixBuffer();

	DirectX::SimpleMath::Vector3 getPos() const;
	DirectX::SimpleMath::Vector3 getForward() const;
	DirectX::SimpleMath::Vector3 getUp() const;
	DirectX::SimpleMath::Vector3 getRight() const;
	float getYaw() const;
	float getPitch() const;

	void setPos(DirectX::SimpleMath::Vector3 pos);
	void setForward(DirectX::SimpleMath::Vector3 forward);
	void setUp(DirectX::SimpleMath::Vector3 up);
	void setRight(DirectX::SimpleMath::Vector3 right);
	void setYaw(float yaw);
	void setPitch(float pitch);
};



#endif