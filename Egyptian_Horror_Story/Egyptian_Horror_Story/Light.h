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
	float mWidth;
	float mHeight;

	lightStructs::VP mMatrices;
	lightStructs::lightPosDir mPosDir;

	GraphicsData* mGData;
	ID3D11DeviceContext* mContext;

	int mMatrixBufferKey;
	int mLightBufferKey;
	int mLightGraphicsKey;

public:
	Light(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 direction, ID3D11Device* device, ID3D11DeviceContext* context, GraphicsData* gData);
	Light(const Light& other) = delete;
	virtual ~Light();
	void update(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 offset, DirectX::SimpleMath::Vector3 dir);

	void operator=(const Light& other) = delete;
	
	float getHeight() const;
	float getWidth() const;

	int getGraphicsKey() const;

};


#endif
