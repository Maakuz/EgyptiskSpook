#include "RiggedEntityRenderer.h"

RiggedEntityRenderer::RiggedEntityRenderer()
{
}

RiggedEntityRenderer::~RiggedEntityRenderer()
{
}

void RiggedEntityRenderer::setup(ID3D11Device* device, ShaderHandler & shaderHandler)
{
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHT", 0, DXGI_FORMAT_R32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "INDEX", 0, DXGI_FORMAT_R32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	HRESULT hr = shaderHandler.setupVertexShader(device, 50, L"SkinnedEntityVS.hlsl", "main", desc, ARRAYSIZE(desc));
}

void RiggedEntityRenderer::render(ID3D11DeviceContext* context, ShaderHandler& shaderHandler)
{
	UINT stride = sizeof(EntityStruct::SkinnedVertexStruct), offset = 0;

	shaderHandler.setShaders(context, 50, 20, -1);

	ID3D11Buffer* temp;
	temp = mGraphicsData.getBuffer(300);
	context->PSSetConstantBuffers(0, 1, &temp);

	temp = mGraphicsData.getBuffer(302);
	context->PSSetConstantBuffers(1, 1, &temp);

	context->IASetInputLayout(shaderHandler.getInputLayout(50));
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int key = 0;

	for (auto const &item : *this->mGraphicsData.getSrvMap())
	{
		key = item.first;

		temp = this->mGraphicsData.getBuffer(key);
		context->IASetVertexBuffers(0, 1, &temp, &stride, &offset);



		ID3D11ShaderResourceView* texTemp = this->mGraphicsData.getSRV(key);
		context->PSSetShaderResources(0, 1, &texTemp);

		context->Draw(this->mGraphicsData.getNrOfVertices(key), 0);
	}
}

bool RiggedEntityRenderer::loadObject(ID3D11Device* device, int key, EntityStruct::SkinnedVertexStruct* vertices, int nrOfVertices, wchar_t* texturePath)
{
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices;

	this->mGraphicsData.loadTexture(key, texturePath, device);
	this->mGraphicsData.setNrOfVertices(key, nrOfVertices);

	if (FAILED(this->mGraphicsData.createVertexBuffer(key, nrOfVertices * sizeof(EntityStruct::SkinnedVertexStruct), &data, device)))
	{
		MessageBox(0, L"Rigged entity vertex buffer creation failed", L"error", MB_OK);
		return false;
	}

	return true;
}

GraphicsData* RiggedEntityRenderer::getGraphicsData()
{
	return &this->mGraphicsData;
}
