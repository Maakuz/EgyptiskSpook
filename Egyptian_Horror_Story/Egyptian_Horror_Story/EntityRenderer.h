#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "Renderer.h"

class EntityRenderer : public Renderer
{
private:

public:
	EntityRenderer();
	virtual ~EntityRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler);

};



#endif