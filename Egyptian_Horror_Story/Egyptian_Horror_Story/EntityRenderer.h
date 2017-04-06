#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include "SimpleMath.h"


class EntityRenderer : public Renderer
{
private:
	GraphicsData mGraphicsData;

public:
	EntityRenderer();
	virtual ~EntityRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler);

	bool loadObject(ID3D11Device *device, int key, EntityStruct::VertexStruct* vertices, int nrOfVertices, wchar_t* texturePath = L"../Resource/Textures/placeholder.png");

};



#endif