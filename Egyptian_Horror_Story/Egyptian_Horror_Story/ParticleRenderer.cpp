#include "ParticleRenderer.h"
#define SHADERS 30

using namespace DirectX::SimpleMath;

ParticleRenderer::ParticleRenderer() {
	this->size = 4;
	this->particles = new Vector3[size];
	this->mGraphicsData = new GraphicsData();
}

ParticleRenderer::~ParticleRenderer() {
	delete this->mGraphicsData;
}

void ParticleRenderer::setup(ID3D11Device *device, ShaderHandler &shaders) {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shaders.setupVertexShader(device, SHADERS, L"ParticleVS.hlsl", "main", desc, ARRAYSIZE(desc));
	shaders.setupPixelShader(device, SHADERS, L"ParticlePS.hlsl", "main");
	shaders.setupGeometryShader(device, SHADERS, L"ParticleGS.hlsl", "main");

	particles[0] = Vector3(0, 0, 0);
	particles[1] = Vector3(3, 13, 0);
	particles[2] = Vector3(6, 5, 0);
	particles[3] = Vector3(-3, -10, 0);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &particles;

	mGraphicsData->createVertexBuffer(0, size * sizeof(Vector3), &data, device);
}

void ParticleRenderer::render(ID3D11DeviceContext *context, ShaderHandler &shaders) {
	UINT stride = sizeof(Vector3), offset = 0;
	ID3D11Buffer *buffer = mGraphicsData->getBuffer(0);
	shaders.setShaders(context, SHADERS, SHADERS, SHADERS);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	context->IASetInputLayout(shaders.getInputLayout(SHADERS));
	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

	context->Draw(size, 0);
}