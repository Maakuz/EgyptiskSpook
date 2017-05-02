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

	for (auto const &key : this->mCBuffers) {
		if (key.second)
			key.second->Release();
	}

	for (auto const &key : this->mSrvs) {
		if (key.second)
			key.second->Release();
	}

	for (auto const &key : this->mVertices) {
		if (key.second)
			delete[] key.second;
	}
}

bool GraphicsData::loadTexture(int key, wchar_t* fileName, ID3D11Device* device)
{
	std::wstring path(TEXTUREPATH);

	path += fileName;

	if (mSrvs[key])
		mSrvs[key]->Release();
	HRESULT hr = DirectX::CreateWICTextureFromFile(device, path.c_str(), nullptr, &mSrvs[key]);


	if (SUCCEEDED(hr))
		return true;
	else
		hr = DirectX::CreateWICTextureFromFile(device, L"../Resource/Textures/placeholder.png", nullptr, &mSrvs[key]);

	return false;
}

HRESULT GraphicsData::createConstantBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device, bool isDynamic)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = size;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;

	if (isDynamic)
	{
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.Usage = D3D11_USAGE_DYNAMIC;
	}

	HRESULT hr = device->CreateBuffer(&desc, data, &this->mCBuffers[key]);
	return hr;
}

HRESULT GraphicsData::createVertexBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device, bool isDynamic)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = size;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	
	if (isDynamic)
	{
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.Usage = D3D11_USAGE_DYNAMIC;
	}

	HRESULT hr = device->CreateBuffer(&desc, data, &this->mBuffers[key]);
	return hr;
}

void GraphicsData::createVerticeArray(int key, EntityStruct::VertexStruct* vertices, int nrOfVertices)
{
	this->mNrOfVertices[key] = nrOfVertices;
	this->mVertices[key] = new EntityStruct::VertexStruct[nrOfVertices];

	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->mVertices.at(key)[i] = vertices[i];
	}
}

void GraphicsData::setNrOfVertices(int key, int nrOfVertices)
{
	this->mNrOfVertices[key] = nrOfVertices;
}

ID3D11Buffer* GraphicsData::getVertexBuffer(int key)
{
	return this->mBuffers.at(key);
}

ID3D11Buffer* GraphicsData::getConstantBuffer(int key)
{
	return this->mCBuffers.at(key);
}

ID3D11ShaderResourceView* GraphicsData::getSRV(int key)
{
	return this->mSrvs.at(key);
}

EntityStruct::VertexStruct* GraphicsData::getVertices(int key)
{
	return this->mVertices.at(key);
}

int GraphicsData::getNrOfVertices(int key)
{
	return this->mNrOfVertices.at(key);
}

std::map<int, ID3D11Buffer*>* GraphicsData::getVertexBufferMap()
{
	return &this->mBuffers;
}

std::map<int, ID3D11Buffer*>* GraphicsData::getConstantBufferMap()
{
	return &this->mCBuffers;
}

std::map<int, ID3D11ShaderResourceView*>* GraphicsData::getSrvMap()
{
	return &this->mSrvs;
}

std::map<int, EntityStruct::VertexStruct*>* GraphicsData::getVertexMap()
{
	return &this->mVertices;
}

std::map<int, int>* GraphicsData::getNrOfVerticesMap()
{
	return &this->mNrOfVertices;
}
