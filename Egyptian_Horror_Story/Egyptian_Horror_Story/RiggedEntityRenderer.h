#ifndef RIGGEDENTITYRENDERER_H
#define RIGGEDENTITYRENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include "SimpleMath.h"


class RiggedEntityRenderer : public Renderer
{
private:
	GraphicsData mGraphicsData;

public:
	RiggedEntityRenderer();
	virtual ~RiggedEntityRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler);

	bool loadObject(ID3D11Device *device, int key, EntityStruct::SkinnedVertexStruct* vertices, int nrOfVertices, wchar_t* texturePath = L"../Resource/Textures/placeholder.png");

	GraphicsData* getGraphicsData();

};



#endif