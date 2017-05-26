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
	float mFadeout;

public:
	EntityRenderer(GAMESTATE identifier);
	virtual ~EntityRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler, GAMESTATE const &state);

	//Cbuffersize should for most cases be size of a 4x4 matrix
	bool loadObject(ID3D11Device *device, int key, EntityStruct::VertexStruct* vertices, int nrOfVertices, UINT cbufferSize, wchar_t* texturePath = L"../Resource/Textures/placeholder.png", DirectX::SimpleMath::Vector3 translation = DirectX::SimpleMath::Vector3(0, 0, 0), bool isDynamic = true);
	void setShadowPass(bool value);

	//if a devicecontext is sent the fadeoutbuffer will be updated
	void setFadeout(float value, ID3D11DeviceContext* context = nullptr);
	float getFadeout() const;

	GraphicsData* getGraphicsData();

};



#endif