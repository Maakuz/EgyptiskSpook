#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include "SimpleMath.h"


class EntityRenderer : public Renderer
{
private:
	GraphicsData mGraphicsData;
	bool shadowPass;

public:
	EntityRenderer();
	virtual ~EntityRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler);

	//Cbuffersize should for most cases be size of a 4x4 matrix
	bool loadObject(ID3D11Device *device, int key, EntityStruct::VertexStruct* vertices, int nrOfVertices, UINT cbufferSize, wchar_t* texturePath = L"../Resource/Textures/placeholder.png", bool isDynamic = true);
	void setShadowPass(bool value);


	GraphicsData* getGraphicsData();

};



#endif