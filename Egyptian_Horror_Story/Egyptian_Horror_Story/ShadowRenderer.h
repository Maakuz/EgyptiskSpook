#pragma once

#include "Direct3DHeader.h"
#include "ShaderHandler.h"
#include "Light.h"

class ShadowRenderer
{
private:
	D3D11_VIEWPORT mViewport;

	ID3D11DepthStencilView* mDSV;
	ID3D11ShaderResourceView* mSRV;
	
	Light* mLight;


public:
	ShadowRenderer(Light* light);
	virtual ~ShadowRenderer();

	void setup(ID3D11Device* device, ShaderHandler& shaders);


	void render(ID3D11DeviceContext* context, ShaderHandler& shaders);
};