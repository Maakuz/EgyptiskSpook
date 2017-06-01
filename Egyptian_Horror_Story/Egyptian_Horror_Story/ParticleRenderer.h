#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include "CameraClass.h"
#include <SimpleMath.h>
#include <vector>

enum ParticleType {
	AREAGREJS,
	FALLING
};

struct ParticleVertex {
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector2 dimensions;
};

struct ParticleData {
	DirectX::SimpleMath::Vector3 direction;
	float timeLeft;
	bool kill;
	ParticleType type;
};

class ParticleEmitter;

class ParticleRenderer : public Renderer {
private:


	GraphicsData *mGraphicsData;

	std::vector<ParticleVertex> mParticleVertices;
	std::vector<ParticleData> mParticleData;
	std::vector<ParticleEmitter*> mPEs;
	CameraClass *mCamera;
	UINT frame;
	void updateCameraBuffer(ID3D11DeviceContext *context);
	void updateParticles(ID3D11DeviceContext * context);

	UINT getSize() const;
	void addRandomParticle(bool timeIsRandom = false);

	//check life time, if <= 0, remove and add new one
	void timeCheck(int start, int piece);
public:
	ParticleRenderer(CameraClass *camera, GAMESTATE identifier);
	ParticleRenderer(ParticleRenderer const &renderer) = delete;
	virtual ~ParticleRenderer();

	void addParticle(ParticleVertex pv, ParticleData pd);
	void setup(ID3D11Device *device, ShaderHandler &shaders);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaders, GAMESTATE const &state);
	void removeAt(int index);
	CameraClass* getCamera();

	ParticleRenderer* operator=(ParticleRenderer const &renderer) = delete;
};



#endif