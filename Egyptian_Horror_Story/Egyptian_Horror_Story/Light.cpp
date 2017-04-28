#include "Light.h"

Light::Light(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 direction, ID3D11Device* device, ID3D11DeviceContext* context, GraphicsData* gData, GraphicsData* gData2)
{
	this->mPosDir.pos = DirectX::SimpleMath::Vector4(pos.x, pos.y, pos.z, 1);
	this->mPosDir.dir = DirectX::SimpleMath::Vector4(direction.x, direction.y, direction.z, 1);

	this->mLightFOV = M_PI * 0.50f;
	this->mWidth = 1000;
	this->mHeight = 1000;

	this->mMatrices.view = DirectX::XMMatrixLookToLH(pos, direction, DirectX::SimpleMath::Vector3(0, 1, 0));

	this->mMatrices.projection = DirectX::XMMatrixPerspectiveFovLH(mLightFOV, this->mWidth / this->mHeight, 0.1, 200);
	this->mMatrices.projection = this->mMatrices.projection.Transpose();

	this->mLightBufferKey = 300;
	this->mMatrixBufferKey = 301;

	this->mGData = gData;
	this->mGData2 = gData2;
	this->mContext = context;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = &this->mMatrices;

	gData->createConstantBuffer(this->mMatrixBufferKey, sizeof(lightStructs::VP), &data, device, true);
	gData2->createConstantBuffer(this->mMatrixBufferKey, sizeof(lightStructs::VP), &data, device, true);


	data.pSysMem = &this->mPosDir;
	gData->createConstantBuffer(this->mLightBufferKey, sizeof(lightStructs::lightPosDir), &data, device, true);
	gData2->createConstantBuffer(this->mLightBufferKey, sizeof(lightStructs::lightPosDir), &data, device, true);
}

Light::~Light()
{
}

void Light::update(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir)
{
	this->mPosDir.pos = DirectX::SimpleMath::Vector4(pos.x, pos.y, pos.z, 1);
	this->mPosDir.dir = DirectX::SimpleMath::Vector4(dir.x, dir.y, dir.z, 1);

	this->mMatrices.view = DirectX::XMMatrixLookToLH(this->mPosDir.pos, this->mPosDir.dir, DirectX::SimpleMath::Vector3(0, 1, 0));
	this->mMatrices.view = this->mMatrices.view.Transpose();

	D3D11_MAPPED_SUBRESOURCE data;

	this->mContext->Map(this->mGData->getConstantBuffer(this->mLightBufferKey), 
		0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &this->mPosDir, sizeof(lightStructs::lightPosDir));

	this->mContext->Unmap(this->mGData->getConstantBuffer(this->mLightBufferKey), 0);



	this->mContext->Map(this->mGData2->getConstantBuffer(this->mLightBufferKey),
		0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &this->mPosDir, sizeof(lightStructs::lightPosDir));

	this->mContext->Unmap(this->mGData2->getConstantBuffer(this->mLightBufferKey), 0);


	//Matrices
	this->mContext->Map(this->mGData->getConstantBuffer(this->mMatrixBufferKey),
		0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &this->mMatrices, sizeof(lightStructs::VP));

	this->mContext->Unmap(this->mGData->getConstantBuffer(this->mMatrixBufferKey), 0);



	this->mContext->Map(this->mGData2->getConstantBuffer(this->mMatrixBufferKey),
		0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &this->mMatrices, sizeof(lightStructs::VP));

	this->mContext->Unmap(this->mGData2->getConstantBuffer(this->mMatrixBufferKey), 0);
}

float Light::getHeight() const
{
	return this->mHeight;
}

float Light::getWidth() const
{
	return this->mWidth;
}