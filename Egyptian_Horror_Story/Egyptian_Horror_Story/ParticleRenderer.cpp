#include "ParticleRenderer.h"
#include <math.h> 
#include "Emitters.h"
#define SHADERS 30
#define DIVIDE 2 //should be divisible by 2
#define START_SIZE 2048  // should be divisible by 2
#define MAX_SIZE 100000

using namespace DirectX::SimpleMath;


ParticleRenderer::ParticleRenderer(CameraClass *camera, GAMESTATE identifier)
	: mCamera(camera), Renderer(identifier) {
	this->mGraphicsData = new GraphicsData();
	frame = 0;
}

ParticleRenderer::~ParticleRenderer() {
	delete this->mGraphicsData;

	for (int i = 0; i < this->mPEs.size(); i++) {
		if (this->mPEs[i])
			delete this->mPEs[i];
	}
}

void ParticleRenderer::addParticle(ParticleVertex pv, ParticleData pd) {
	if (this->mParticleVertices.size() < MAX_SIZE) {
		this->mParticleVertices.push_back(pv);
		this->mParticleData.push_back(pd);
	}
}

void ParticleRenderer::setup(ID3D11Device *device, ShaderHandler &shaders) {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIMENSIONS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shaders.setupVertexShader(device, SHADERS, L"ParticleVS.hlsl", "main", desc, ARRAYSIZE(desc));
	shaders.setupPixelShader(device, SHADERS, L"ParticlePS.hlsl", "main");
	shaders.setupGeometryShader(device, SHADERS, L"ParticleGS.hlsl", "main");


	this->mPEs.push_back(new AreaStuff(ParticleType::AREAGREJS, this));
	this->mPEs.push_back(new FallingEmitterHandler(this->mCamera, ParticleType::FALLING, this));
	
	for (int i = 0; i < this->mPEs.size(); i++) {
		this->mPEs[i]->initialize(i, this->mGraphicsData, device);
	}

	mGraphicsData->createVertexBuffer(0, MAX_SIZE * sizeof(ParticleVertex), NULL, device, true);
	mGraphicsData->createConstantBuffer(1, sizeof(Vector4), nullptr, device, true);
	mGraphicsData->loadTexture(0, L"sand.png", device);
}

void ParticleRenderer::updateCameraBuffer(ID3D11DeviceContext *context) {
	Vector4 cam = this->mCamera->getPos();

	D3D11_MAPPED_SUBRESOURCE res;
	context->Map(this->mGraphicsData->getConstantBuffer(1), 0, D3D11_MAP_WRITE_DISCARD, NULL, &res);
	memcpy(res.pData, &cam, sizeof(Vector4));
	context->Unmap(this->mGraphicsData->getConstantBuffer(1), 0);
}

void ParticleRenderer::updateParticles(ID3D11DeviceContext *context) {

	for (int i = 0; i < this->mPEs.size(); i++) {
		this->mPEs[i]->updatePerFrame();
	}

	frame++;
	float temp = 0;
	int mod = frame % DIVIDE;
	int piece = mParticleVertices.size() / DIVIDE;
	int start = piece * mod;

	for (int i = start; i < start + piece; i++) {
		ParticleVertex *particle = &this->mParticleVertices[i];
		ParticleData *data = &this->mParticleData[i];

		for (int j = 0; j < this->mPEs.size(); j++) {
			if (data->type == this->mPEs[j]->getID()) {
				this->mPEs[j]->update(particle, data);
			}
		}
	}
	piece = mParticleVertices.size() / DIVIDE;
	start = piece * mod;
	for (int i = start; i < start + piece; i++) {
		ParticleVertex *particle = &this->mParticleVertices[i];
		ParticleData *data = &this->mParticleData[i];

		for (int j = 0; j < this->mPEs.size(); j++) {
			if (data->type == this->mPEs[j]->getID()) {
				this->mPEs[j]->handleTimePerParticle(particle, data, i);
			}
		}
	}

	timeCheck(start, piece);

	D3D11_MAPPED_SUBRESOURCE res;
	context->Map(this->mGraphicsData->getVertexBuffer(0), 0, D3D11_MAP_WRITE_DISCARD, NULL, &res);
	char *ptr = static_cast<char*> (res.pData);
	memcpy(ptr, &this->mParticleVertices[0], getSize());
	context->Unmap(this->mGraphicsData->getVertexBuffer(0), 0);
}

void ParticleRenderer::render(ID3D11DeviceContext *context, ShaderHandler &shaders, GAMESTATE const &state) {

	UINT stride = sizeof(ParticleVertex), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getVertexBuffer(0),
						   *cam = this->mGraphicsData->getConstantBuffer(1),
						   *vp = this->mCamera->getMatrixBuffer();
	ID3D11ShaderResourceView *srv = this->mGraphicsData->getSRV(0);
	shaders.setShaders(context, SHADERS, SHADERS, SHADERS); //20 is from entity shader, change later
	
	updateCameraBuffer(context);
	updateParticles(context);
	
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	context->IASetInputLayout(shaders.getInputLayout(SHADERS));
	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	context->PSSetShaderResources(0, 1, &srv);
	context->GSSetConstantBuffers(0, 1, &vp);
	context->GSSetConstantBuffers(1, 1, &cam);
	
	context->Draw(this->mParticleVertices.size() - 1, 0);
}

void ParticleRenderer::removeAt(int i) {
	std::swap(this->mParticleData[i], this->mParticleData[this->mParticleData.size() - 1]);
	std::swap(this->mParticleVertices[i], this->mParticleVertices[this->mParticleVertices.size() - 1]);
	this->mParticleData.pop_back();
	this->mParticleVertices.pop_back();
}

CameraClass * ParticleRenderer::getCamera() {
	return this->mCamera;
}

UINT ParticleRenderer::getSize() const {
	return this->mParticleVertices.size() * sizeof(ParticleVertex);
}

//This function does litteraly nothing
void ParticleRenderer::addRandomParticle(bool timeIsRandom) {
	//ParticleVertex particle;
	//ParticleData partData;
	//
	////TEMP
	////particle.position = Vector3(getRandomNr() * 30 - 15, getRandomNr() * 20 - 5, getRandomNr() * 30 - 15);
	//particle.position = Vector3(getRandomNr() * 20 - 10, getRandomNr() * 15 - 3, getRandomNr() * 20 - 10);
	//particle.position += this->mCamera->getPos();
	//particle.dimensions = Vector2(0.01f, 0.01f);
	//partData.type = AREAGREJS;
	//partData.direction = Vector3(getRandomNr() * 2 - 1, getRandomNr() * 2 - 1,getRandomNr() * 2 - 1);
	//partData.timeLeft = timeIsRandom ? getRandomNr() * 3.5f : 2.f;
	//
	//this->mParticleVertices.push_back(particle);
	//this->mParticleData.push_back(partData);
}

void ParticleRenderer::timeCheck(int s, int p) {
	int mod = frame % DIVIDE;
	int piece = mParticleVertices.size() / DIVIDE;
	int start = piece * mod;

	for(int i = 0; i < mParticleData.size(); i++ ) {
		ParticleVertex *particle = &this->mParticleVertices[i];
		ParticleData *data = &this->mParticleData[i];
	
		if (data->kill) {
			if (data->type == FALLING) {
				data = data;
			}
			std::swap(this->mParticleData[i], this->mParticleData[this->mParticleData.size() - 1]);
			std::swap(this->mParticleVertices[i], this->mParticleVertices[this->mParticleVertices.size() - 1]);
			this->mParticleData.pop_back();
			this->mParticleVertices.pop_back();
			i--;
		}
	}
}


//--------------------------------------------------------------------------------------
