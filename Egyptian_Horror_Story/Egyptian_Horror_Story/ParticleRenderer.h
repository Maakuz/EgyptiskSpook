#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"

class ParticleRenderer : Renderer {
	private:
		GraphicsData *mGraphicsData;
	public:
		ParticleRenderer();
		ParticleRenderer(ParticleRenderer const &renderer) = delete;
		virtual ~ParticleRenderer();

		void setup(ID3D11Device *device, ShaderHandler &shaders);
		void render(ID3D11Device *context, ShaderHandler &shaders);

		ParticleRenderer* operator=(ParticleRenderer const &renderer) = delete;
};

#endif