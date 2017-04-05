#include "GraphicsData.h"

GraphicsData::GraphicsData()
{
}

GraphicsData::~GraphicsData()
{
	for (auto const &key : this->mBuffers) {
		if (key.second)
			key.second->Release();
	}

	for (auto const &key : this->mSrvs) {
		if (key.second)
			key.second->Release();
	}
}

bool GraphicsData::loadTexture(char* key, wchar_t* path, ID3D11Device* device)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(device, path, nullptr, &mSrvs[key]);

	if (SUCCEEDED(hr))
		return true;

	return false;
}

HRESULT GraphicsData::createConstantBuffer(char* key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = size;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	HRESULT hr = device->CreateBuffer(&desc, data, &this->mBuffers[key]);
	return hr;
}

HRESULT GraphicsData::createVertexBuffer(char* key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = size;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	

	HRESULT hr = device->CreateBuffer(&desc, data, &this->mBuffers[key]);
	return hr;
}

ID3D11Buffer* GraphicsData::getBuffer(char* key) const
{
	return this->mBuffers.at(key);
}

ID3D11ShaderResourceView* GraphicsData::getSRV(char* key)
{
	return this->mSrvs.at(key);
}
