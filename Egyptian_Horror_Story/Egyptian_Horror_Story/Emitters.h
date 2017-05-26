#pragma once
#include "ParticleRenderer.h"
#include <math.h> 

class ParticleEmitter {
private:
	int key;
protected:
	ParticleType id;
	ParticleRenderer* pr;
	int nrOfParticles;
	int maxSize;
public:
	ParticleEmitter(ParticleType id, ParticleRenderer* pr) { this->id = id; this->pr = pr; }
	void initialize(int key, GraphicsData*, ID3D11Device*);
	virtual void updatePerFrame() = 0;
	virtual void handleTimePerParticle(ParticleVertex* pv, ParticleData* pd, int index) = 0;
	virtual void update(ParticleVertex* pv, ParticleData* pd) = 0;
	virtual void particleRemoved() = 0;
	void createParticle(ParticleVertex pv, ParticleData pd);
	ParticleType getID() { return this->id; }
	int getSize() { return this->nrOfParticles; }
};

class AreaStuff : public ParticleEmitter {
private:
public:
	AreaStuff(ParticleType pt, ParticleRenderer* pr) : ParticleEmitter(pt, pr) { this->nrOfParticles = 0; this->maxSize = 2048; }

	void updatePerFrame();
	void handleTimePerParticle(ParticleVertex* pv, ParticleData* pd, int index);
	void update(ParticleVertex* pv, ParticleData* pd);
	void particleRemoved();
	void addRandomParticle();
};

class FallingEmitterHandler : public ParticleEmitter {
private:
	class FallingEmitter {
		DirectX::SimpleMath::Vector3 pos;
		float timeLeft;
		float lifeTime;
	public:
		FallingEmitter(DirectX::SimpleMath::Vector3 pos);
		void setPos(DirectX::SimpleMath::Vector3 pos) { this->pos = pos; }
		DirectX::SimpleMath::Vector3 getPos() { return this->pos; }
		bool update(FallingEmitterHandler* feh);
		float getLifeTime() { return this->lifeTime; }
	};
	FallingEmitter** emitters;
	int nrOfEmitters;
	CameraClass* c;
	void createEmitter(int index);
public:
	FallingEmitterHandler(CameraClass* c, ParticleType pt, ParticleRenderer* pr);

	void updatePerFrame();
	void handleTimePerParticle(ParticleVertex* pv, ParticleData* pd, int index);
	void update(ParticleVertex* pv, ParticleData* pd);
	void particleRemoved();
	void addRandomParticle();
};