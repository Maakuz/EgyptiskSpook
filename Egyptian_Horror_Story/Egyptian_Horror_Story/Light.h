#ifndef LIGHT_H
#define LIGHT_H

#include "Direct3DHeader.h"
#include "Structs.h"
#include "GraphicsData.h"

#define _USE_MATH_DEFINES

#include <math.h>


class Light
{
private:
	float mLightFOV;

	lightStructs::VP mMatrices;
	lightStructs::lightInfo mLightInfo;

	GraphicsData* mGData;
	ID3D11DeviceContext* mContext;

	int mMatrixBufferKey;
	int mLightBufferKey;
	int mLightGraphicsKey;

	bool lightOn;

public:
	Light(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 direction, ID3D11Device* device, ID3D11DeviceContext* context, GraphicsData* gData);
	Light(const Light& other) = delete;
	virtual ~Light();
	void update(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 forward, DirectX::SimpleMath::Vector3 right, DirectX::SimpleMath::Vector3 up);

	void operator=(const Light& other) = delete;

	int getGraphicsKey() const;
	void toggleFlashLight(bool onOrOff);
	bool getLightOn() const;

};


#endif
