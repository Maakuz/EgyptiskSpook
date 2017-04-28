#ifndef RIGGEDENTITYRENDERER_H
#define RIGGEDENTITYRENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include "SimpleMath.h"


class RiggedEntityRenderer : public Renderer
{
private:
	GraphicsData mGraphicsData;
	bool shadowPass;

public:
	RiggedEntityRenderer();
	virtual ~RiggedEntityRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler);

	void setShadowPass(bool value);
	bool loadObject(ID3D11Device *device, int key, EntityStruct::SkinnedVertexStruct* vertices, int nrOfVertices, UINT cbufferSize, wchar_t* texturePath = L"../Resource/Textures/placeholder.png", bool isDynamic = true);

	GraphicsData* getGraphicsData();

};



#endif