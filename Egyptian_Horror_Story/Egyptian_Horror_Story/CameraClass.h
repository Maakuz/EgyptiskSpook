#ifndef CAMERACLASS_H
#define CAMERACLASS_H

#include "Direct3DHeader.h"
#include "GraphicsData.h"

#include"Structs.h"


class CameraClass
{
private:
	const double DEGTORADIANS = M_PI / 180;
	
	camera::VP mMatrices;

	ID3D11Buffer* mVPBuffer;
	GraphicsData* mGraphicsData;
	static const int CAMPOSKEY = 302;

	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mForward;
	DirectX::SimpleMath::Vector3 mRight;
	DirectX::SimpleMath::Vector3 mUp;

	float mPitch;
	float mYaw;

	bool mProjUpdated;

public:
	CameraClass(ID3D11Device* device, GraphicsData* gData, settings::GraphicSettings settings);
	virtual ~CameraClass();

	void createVPBuffer(ID3D11Device* device);
	void update(ID3D11DeviceContext* context);
	void updateRotation(ID3D11DeviceContext* context);
	void updateProjection(ID3D11DeviceContext* context, settings::GraphicSettings& settings);

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