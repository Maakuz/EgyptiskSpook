#include "ParticleRenderer.h"
#define SHADERS 30

using namespace DirectX::SimpleMath;

ParticleRenderer::ParticleRenderer() {
	this->mSize = 1;
	this->mParticles = new Vector3[mSize];
	this->mGraphicsData = new GraphicsData();
}

ParticleRenderer::~ParticleRenderer() {
	delete this->mGraphicsData;
	delete[] this->mParticles;
}

void ParticleRenderer::setup(ID3D11Device *device, ShaderHandler &shaders) {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shaders.setupVertexShader(device, SHADERS, L"ParticleVS.hlsl", "main", desc, ARRAYSIZE(desc));
	shaders.setupPixelShader(device, SHADERS, L"ParticlePS.hlsl", "main");
	shaders.setupGeometryShader(device, SHADERS, L"ParticleGS.hlsl", "main");

	this->mParticles[0] = Vector3(-0.95f, 0.55f, 0);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &this->mParticles[0];

	mGraphicsData->createVertexBuffer(0, this->mSize * sizeof(Vector3), &data, device);
	mGraphicsData->loadTexture(0, L"../Resource/Textures/placeholder.png", device);
}

void ParticleRenderer::render(ID3D11DeviceContext *context, ShaderHandler &shaders) {
	UINT stride = sizeof(Vector3), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getBuffer(0);
	ID3D11ShaderResourceView *srv = this->mGraphicsData->getSRV(0);
	shaders.setShaders(context, SHADERS, SHADERS, SHADERS);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	context->IASetInputLayout(shaders.getInputLayout(SHADERS));
	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	context->PSSetShaderResources(0, 1, &srv);

	context->Draw(this->mSize, 0);
}