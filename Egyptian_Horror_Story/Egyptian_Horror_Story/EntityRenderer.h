#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include "SimpleMath.h"

namespace EntityStruct
{
	struct VertexStruct
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector3 normal;
		DirectX::SimpleMath::Vector2 uv;
	};
}


class EntityRenderer : public Renderer
{
private:
	GraphicsData mGraphicsData;
	EntityStruct::VertexStruct* mVertices;
	int mNrOfVertices;

public:
	EntityRenderer();
	virtual ~EntityRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler);

	bool loadObject(ID3D11Device *device, EntityStruct::VertexStruct* vertices, int nrOfVertices, wchar_t* texturePath = L"../Resource/Textures/placeholder.png");

};



#endif