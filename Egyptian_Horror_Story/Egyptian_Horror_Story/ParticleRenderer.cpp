#include "ParticleRenderer.h"
#define SHADERS 30

using namespace DirectX::SimpleMath;

ParticleRenderer::ParticleRenderer(CameraClass *camera) 
	: mCamera(camera) {
	this->mSize = 1000;
	this->mParticles = new Vector3[mSize];
	this->mDirection = new Vector3[mSize];
	this->mGraphicsData = new GraphicsData();
}

ParticleRenderer::~ParticleRenderer() {
	delete this->mGraphicsData;
	delete[] this->mParticles;
	delete[] this->mDirection;

	blendState->Release();
}

void ParticleRenderer::setup(ID3D11Device *device, ShaderHandler &shaders) {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shaders.setupVertexShader(device, SHADERS, L"ParticleVS.hlsl", "main", desc, ARRAYSIZE(desc));
	shaders.setupPixelShader(device, SHADERS, L"ParticlePS.hlsl", "main");
	shaders.setupGeometryShader(device, SHADERS, L"ParticleGS.hlsl", "main");

	for (int i = 0; i < this->mSize; i++) {
		this->mParticles[i] = Vector3(rand() % 30 - 5.f, rand() % 15, rand() % 30 - 5.f);
		this->mDirection[i] = Vector3(rand() % 4 - 1, rand() % 4 - 1, rand() % 4 - 1);
	}

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &this->mParticles[0];

	mGraphicsData->createVertexBuffer(0, this->mSize * sizeof(Vector3), &data, device, true);
	mGraphicsData->createConstantBuffer(1, sizeof(Vector4), nullptr, device, true);
	mGraphicsData->loadTexture(0, L"../Resource/Textures/sand.png", device);

	setupBlendState(device);
}

void ParticleRenderer::setupBlendState(ID3D11Device *device) {
	D3D11_RENDER_TARGET_BLEND_DESC rtbDesc;
	ZeroMemory(&rtbDesc, sizeof(rtbDesc));
	rtbDesc.BlendEnable = true;
	rtbDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	rtbDesc.DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	rtbDesc.BlendOp = D3D11_BLEND_OP_ADD;
	rtbDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbDesc.RenderTargetWriteMask = 0x0f;

	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = true;
	desc.IndependentBlendEnable = true;
	desc.RenderTarget[0] = rtbDesc;

	device->CreateBlendState(&desc, &this->blendState);
}

void ParticleRenderer::updateCameraBuffer(ID3D11DeviceContext *context) {
	Vector4 cam = this->mCamera->getPos();

	D3D11_MAPPED_SUBRESOURCE res;
	context->Map(this->mGraphicsData->getBuffer(1), 0, D3D11_MAP_WRITE_DISCARD, NULL, &res);
	memcpy(res.pData, &cam, sizeof(Vector4));
	context->Unmap(this->mGraphicsData->getBuffer(1), 0);
}

void ParticleRenderer::updateParticles(ID3D11DeviceContext *context) {
	for (int i = 0; i < this->mSize; i++) {
		Vector3 dir = this->mDirection[i];
		this->mParticles[i].x += dir.x / 5000.f;
		this->mParticles[i].x += dir.y / 5000.f;
		this->mParticles[i].x += dir.z / 5000.f;
		
		if (rand() % 100 == 0) {
			this->mDirection[i].x = rand() % 4 - 1;
			this->mDirection[i].y = rand() % 4 - 1;
			this->mDirection[i].z = rand() % 4 - 1;
		}
	}

	D3D11_MAPPED_SUBRESOURCE res;
	context->Map(this->mGraphicsData->getBuffer(0), 0, D3D11_MAP_WRITE_DISCARD, NULL, &res);
	memcpy(res.pData, &mParticles[0], this->mSize * sizeof(Vector3));
	context->Unmap(this->mGraphicsData->getBuffer(0), 0);
}

void ParticleRenderer::render(ID3D11DeviceContext *context, ShaderHandler &shaders) {
	UINT stride = sizeof(Vector3), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getBuffer(0), *cam = this->mGraphicsData->getBuffer(1)
		, *vp = this->mCamera->getMatrixBuffer();
	ID3D11ShaderResourceView *srv = this->mGraphicsData->getSRV(0);
	shaders.setShaders(context, SHADERS, SHADERS, SHADERS);

	updateCameraBuffer(context);
	updateParticles(context);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	context->IASetInputLayout(shaders.getInputLayout(SHADERS));
	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	context->PSSetShaderResources(0, 1, &srv);
	context->GSSetConstantBuffers(0, 1, &vp);
	context->GSSetConstantBuffers(1, 1, &cam);

	context->Draw(this->mSize, 0);
}