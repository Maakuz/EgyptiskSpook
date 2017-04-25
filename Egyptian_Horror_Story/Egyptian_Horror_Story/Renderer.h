#ifndef RENDERER_H
#define RENDERER_H

#include "Direct3DHeader.h"
#include "ShaderHandler.h"

class Renderer {
protected:
	int mIdentifier;
public:
	Renderer(int identifier);
	virtual ~Renderer();
	Renderer(Renderer const &renderer) = delete;

	virtual void setup(ID3D11Device *device, ShaderHandler &shaderHandler) = 0;
	virtual void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler) = 0;
	int getID() { return this->mIdentifier; }
	Renderer* operator=(Renderer const &renderer) = delete;
};

enum GAMESTATE{
	MAIN_MENU,
	PLAY,
};


#endif