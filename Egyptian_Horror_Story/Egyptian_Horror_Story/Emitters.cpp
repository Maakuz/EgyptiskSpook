#include "Emitters.h"
#include <math.h> 
#include <stdio.h>

#define SAND_SPEED 20.f
#define LIFE_TIME 30.f

inline float getRandomNr() {
	return rand() / (RAND_MAX + 1.f);
}

void AreaStuff::updatePerFrame() {
	if(this->nrOfParticles < 2048)
		this->addRandomParticle();
}

void AreaStuff::handleTimePerParticle(ParticleVertex* pv, ParticleData* pd, int index) {
	pd->timeLeft -= 0.01f * 2;
	if (pd->timeLeft <= 0) {
		pd->kill = true;
		nrOfParticles--;
	}
}

void AreaStuff::update(ParticleVertex * pv, ParticleData * pd) {
	pv->position += pd->direction / 120.f;
	float temp = 0;

	if (rand() % 1000 == 0) {
		temp = getRandomNr() * 2 - 1;
		pd->direction = DirectX::SimpleMath::Vector3(temp, temp, temp);
	}

}

void AreaStuff::particleRemoved() {

}

void AreaStuff::addRandomParticle() {
	ParticleVertex particle;
	ParticleData partData;

	particle.position = DirectX::SimpleMath::Vector3(getRandomNr() * 20 - 10, getRandomNr() * 15 - 3, getRandomNr() * 20 - 10);
	particle.position += this->pr->getCamera()->getPos();
	particle.dimensions = DirectX::SimpleMath::Vector2(0.01f, 0.01f);
	partData.type = AREAGREJS;
	partData.kill = false;
	partData.direction = DirectX::SimpleMath::Vector3(getRandomNr() * 2 - 1, getRandomNr() * 2 - 1, getRandomNr() * 2 - 1);
	partData.timeLeft = true ? getRandomNr() * 3.5f : 2.f;

	this->createParticle(particle, partData);
	this->nrOfParticles++;
}

void ParticleEmitter::initialize(int key, GraphicsData * g, ID3D11Device * dev) {
}

void ParticleEmitter::createParticle(ParticleVertex pv, ParticleData pd) {
	this->pr->addParticle(pv, pd);
}

void FallingEmitterHandler::createEmitter(int index) {
	if (getRandomNr() < 0.5) {
		DirectX::SimpleMath::Vector3 pos = this->c->getPos();
		DirectX::SimpleMath::Vector3 offset = DirectX::SimpleMath::Vector3(((getRandomNr() * 2) - 1) * 4, 3, ((getRandomNr() * 2) - 1) * 4); 
		pos += offset; 
		this->emitters[index] = new FallingEmitter(pos);
	}
	else {
		DirectX::SimpleMath::Vector3 pos = this->c->getPos();
		DirectX::SimpleMath::Vector3 forward = this->c->getRight();
		forward = forward.Cross(DirectX::SimpleMath::Vector3(0, 1, 0));
		DirectX::SimpleMath::Vector3 offset = DirectX::SimpleMath::Vector3(((getRandomNr() * 2) - 1) * 2, 3, ((getRandomNr() * 2) - 1) * 2);
		pos += offset + forward * (getRandomNr() * 3 + 30);
		this->emitters[index] = new FallingEmitter(pos);
	}

}

FallingEmitterHandler::FallingEmitterHandler(CameraClass* c, ParticleType pt, ParticleRenderer * pr) : ParticleEmitter(pt, pr){
	this->maxSize = 500;
	this->nrOfEmitters = 20;
	this->c = c;
	this->emitters = new FallingEmitter*[this->nrOfEmitters];
	for (int i = 0; i < this->nrOfEmitters; i++)
		this->createEmitter(i);
}

FallingEmitterHandler::~FallingEmitterHandler() {
	for (int i = 0; i < this->nrOfEmitters; i++) {
		if (emitters[i])
			delete this->emitters[i];
	}
	delete[] emitters;
}

void FallingEmitterHandler::updatePerFrame() {

	for (int i = 0; i < this->nrOfEmitters; i++) {

		if (this->emitters[i]->getLifeTime() <= 0) {
			delete this->emitters[i];
			this->createEmitter(i);
		}
	}


	for (int i = 0; i < this->nrOfEmitters; i++) {
		if(this->emitters[i])
			this->emitters[i]->update(this);
	}
}

void FallingEmitterHandler::handleTimePerParticle(ParticleVertex * pv, ParticleData * pd, int index) {
	pd->timeLeft -= 0.01f * 2;
	if (pd->timeLeft <= 0) {
		pd->kill = true;
		this->nrOfParticles--;
	}
}

void FallingEmitterHandler::update(ParticleVertex * pv, ParticleData * pd) {
	pv->position += pd->direction / SAND_SPEED;
}

void FallingEmitterHandler::particleRemoved() {
}

void FallingEmitterHandler::addRandomParticle() {
}

FallingEmitterHandler::FallingEmitter::FallingEmitter(DirectX::SimpleMath::Vector3 pos) {
	this->pos = pos;
	this->lifeTime = getRandomNr() * LIFE_TIME;
}

bool FallingEmitterHandler::FallingEmitter::update(FallingEmitterHandler * feh)
{
	this->timeLeft -= 0.01f * 2;
	this->lifeTime -= 0.01f * 2;
	if (this->timeLeft < 0) {
		this->timeLeft = getRandomNr() / 3;
		ParticleVertex pv;
		pv.dimensions = DirectX::SimpleMath::Vector2(0.01f, 0.01f);
		pv.position = this->pos;
		DirectX::SimpleMath::Vector3 offset = DirectX::SimpleMath::Vector3(((getRandomNr() * 2) - 1) / 10, 1, ((getRandomNr() * 2) - 1) / 10);
		pv.position += offset;
		ParticleData pd;
		pd.direction = DirectX::SimpleMath::Vector3(0, -1.f, 0);
		pd.timeLeft = 3.f;
		pd.kill = false;
		pd.type = ParticleType::FALLING;

		feh->createParticle(pv, pd);
		return true;
	}
	return false;
}
