#include "Light.h"

void Light::createLightMatrixBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(VP);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = &this->mMatrices;

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->mLightMatixBuffer);

}

Light::Light(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 direction, ID3D11Device* device)
{
	this->mPos = pos;
	this->mDirection = direction;

	this->mLightFOV = M_PI * 0.23f;
	this->mWidth = 8000;
	this->mHeight = 8000;

	this->mMatrices.view = DirectX::XMMatrixLookToLH(pos, direction, DirectX::SimpleMath::Vector3(0, 1, 0));

	this->mMatrices.projection = DirectX::XMMatrixPerspectiveFovLH(mLightFOV, this->mWidth / this->mHeight, 0.1, 200);

	this->createLightMatrixBuffer(device);
}

Light::~Light()
{
	if (this->mLightMatixBuffer)
		this->mLightMatixBuffer->Release();
}

float Light::getHeight() const
{
	return this->mHeight;
}

float Light::getWidth() const
{
	return this->mWidth;
}

ID3D11Buffer* Light::getMatrixBuffer() const
{
	return this->mLightMatixBuffer;
}
