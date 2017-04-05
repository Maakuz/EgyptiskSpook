#include "EntityRenderer.h"

EntityRenderer::EntityRenderer()
{
}

EntityRenderer::~EntityRenderer()
{
	delete[] this->mVertices;
}

void EntityRenderer::setup(ID3D11Device* device, ShaderHandler& shaderHandler)
{
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	shaderHandler.setupVertexShader(device, 20, L"EntityVS.hlsl", "main", desc, ARRAYSIZE(desc));

	shaderHandler.setupPixelShader(device, 20, L"EntityPS.hlsl", "main");
}

void EntityRenderer::render(ID3D11DeviceContext* context, ShaderHandler& shaderHandler)
{
	shaderHandler.setShaders(context, 20, 20, -1);
	ID3D11Buffer* temp = this->mGraphicsData.getBuffer("0");
	UINT stride = sizeof(EntityStruct::VertexStruct), offset = 0;

	context->IASetVertexBuffers(0, 1, &temp, &stride, &offset);

	context->Draw(this->mNrOfVertices, 0);
}

bool EntityRenderer::loadObject(ID3D11Device* device, EntityStruct::VertexStruct* vertices, int nrOfVertices)
{
	this->mNrOfVertices = nrOfVertices;
	this->mVertices = new EntityStruct::VertexStruct[nrOfVertices];

	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->mVertices[i] = vertices[i];
	}

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = this->mVertices;

	if (FAILED(this->mGraphicsData.createVertexBuffer("0", this->mNrOfVertices * sizeof(EntityStruct::VertexStruct), &data, device)))
	{
		MessageBox(0, L"Entity vertex buffer creation failed", L"error", MB_OK);
		return false;
	}

	return true;
}
