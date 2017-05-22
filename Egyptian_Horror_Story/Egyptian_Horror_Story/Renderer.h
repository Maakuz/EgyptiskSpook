#ifndef RENDERER_H
#define RENDERER_H

#include "Direct3DHeader.h"
#include "ShaderHandler.h"

enum GAMESTATE {
	DEFAULT,
	MAIN_MENU,
	PLAY,
	GAME_OVER,
	UNDEFINED //Renderer can be used for multiple purposes
};

class Renderer {
private:
	GAMESTATE mIdentifier;
public:
	Renderer(GAMESTATE state = UNDEFINED);
	virtual ~Renderer();
	Renderer(Renderer const &renderer) = delete;

	virtual void setup(ID3D11Device *device, ShaderHandler &shaderHandler) = 0;
	virtual void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler, GAMESTATE const &state) = 0;
		
	void setIdentifier(GAMESTATE state);
	GAMESTATE getIdentifier();

	Renderer* operator=(Renderer const &renderer) = delete;
};

#endif