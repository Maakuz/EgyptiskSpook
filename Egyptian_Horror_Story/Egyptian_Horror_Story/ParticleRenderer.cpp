#include "ParticleRenderer.h"
#define SHADERS 30

using namespace DirectX::SimpleMath;

ParticleRenderer::ParticleRenderer(CameraClass *camera) 
	: mCamera(camera) {
	this->mSize = 10;
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

	for (int i = 0; i < this->mSize; i++) {
		this->mParticles[i] = Vector3(i * 2, i * 3, i * 4);
	}

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &this->mParticles[0];

	mGraphicsData->createVertexBuffer(0, this->mSize * sizeof(Vector3), &data, device, true);
	mGraphicsData->createConstantBuffer(1, sizeof(Matrix), nullptr, device, true);
	mGraphicsData->loadTexture(0, L"../Resource/Textures/placeholder.png", device);
}

void ParticleRenderer::updateCameraBuffer(ID3D11DeviceContext *context) {
	Matrix view = XMMatrixLookAtLH(this->mCamera->getPos(), this->mCamera->getForward(), this->mCamera->getUp());

	D3D11_MAPPED_SUBRESOURCE res;
	context->Map(this->mGraphicsData->getBuffer(1), 0, D3D11_MAP_WRITE_DISCARD, NULL, &res);
	memcpy(res.pData, &view.Invert(), sizeof(Matrix));
	context->Unmap(this->mGraphicsData->getBuffer(1), 0);
}

void ParticleRenderer::render(ID3D11DeviceContext *context, ShaderHandler &shaders) {
	UINT stride = sizeof(Vector3), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getBuffer(0), *cam = this->mGraphicsData->getBuffer(1)
		, *vp = this->mCamera->getMatrixBuffer();
	ID3D11ShaderResourceView *srv = this->mGraphicsData->getSRV(0);
	shaders.setShaders(context, SHADERS, SHADERS, SHADERS);

	updateCameraBuffer(context);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	context->IASetInputLayout(shaders.getInputLayout(SHADERS));
	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	context->PSSetShaderResources(0, 1, &srv);
	context->GSSetConstantBuffers(0, 1, &vp);
	context->GSSetConstantBuffers(1, 1, &cam);

	context->Draw(this->mSize, 0);
}