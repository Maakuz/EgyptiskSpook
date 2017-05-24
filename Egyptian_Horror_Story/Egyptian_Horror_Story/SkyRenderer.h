#pragma once

#include "Renderer.h"
#include "GraphicsData.h"
#include "DDSTextureLoader.h"

class SkyRenderer : public Renderer
{
private:
	GraphicsData mGraphicsData;

	int mSphereFaces;
	int mSphereVertices;

	ID3D11DepthStencilState* mDepthStateLessEqual;
	ID3D11ShaderResourceView* srv;

public:
	SkyRenderer();
	virtual ~SkyRenderer();

	void updateTransform(DirectX::SimpleMath::Vector3 pos, ID3D11DeviceContext* context);

	void setup(ID3D11Device *device, ShaderHandler &shaderHandler);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaderHandler, GAMESTATE const &state);

};