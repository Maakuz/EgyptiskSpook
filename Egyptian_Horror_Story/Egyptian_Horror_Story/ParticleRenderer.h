#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include <SimpleMath.h>

class ParticleRenderer : public Renderer {
	private:
		GraphicsData *mGraphicsData;

		UINT mSize;
		DirectX::SimpleMath::Vector3 *mParticles;
	public:
		ParticleRenderer();
		ParticleRenderer(ParticleRenderer const &renderer) = delete;
		virtual ~ParticleRenderer();

		void setup(ID3D11Device *device, ShaderHandler &shaders);
		void render(ID3D11DeviceContext *context, ShaderHandler &shaders);

		ParticleRenderer* operator=(ParticleRenderer const &renderer) = delete;
};

#endif