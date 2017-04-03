#ifndef LIGHT_H
#define LIGHT_H

#include "Direct3DHeader.h"
#include "SimpleMath.h"

#define _USE_MATH_DEFINES

#include <math.h>

class Light
{
private:
	struct VP
	{
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
	};

	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mDirection;

	float mLightFOV;
	float mWidth;
	float mHeight;

	VP mMatrices;
	ID3D11Buffer* mLightMatixBuffer;

	void createLightMatrixBuffer(ID3D11Device* device);

public:
	Light(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 direction, ID3D11Device* device);
	Light(const Light& other) = delete;
	virtual ~Light();

	void operator=(const Light& other) = delete;
	
	float getHeight() const;
	float getWidth() const;

	ID3D11Buffer* getMatrixBuffer() const;


};


#endif
