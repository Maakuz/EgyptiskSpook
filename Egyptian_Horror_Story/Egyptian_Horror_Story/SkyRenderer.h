#pragma once

#include "Renderer.h"
#include "GraphicsData.h"

class SkyRenderer : public Renderer
{
private:
	GraphicsData mGraphicsData;

public:
	SkyRenderer();
	virtual ~SkyRenderer();


	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler, GAMESTATE const &state);

};