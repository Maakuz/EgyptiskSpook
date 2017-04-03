#ifndef RENDERER_H
#define RENDERER_H

#include "Direct3DHeader.h"
#include "ShaderHandler.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();
	Renderer(Renderer const &renderer) = delete;

	virtual void setup(ID3D11Device *device, ShaderHandler &shaderHandler) = 0;
	virtual void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler) = 0;
		
	Renderer* operator=(Renderer const &renderer) = delete;
};

#endif