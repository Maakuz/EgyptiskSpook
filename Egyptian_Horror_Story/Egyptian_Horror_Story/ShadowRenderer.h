#ifndef SHADOWRENDERER_H
#define SHADOWRENDERER_H

#include "Light.h"
#include "Renderer.h"

class ShadowRenderer : public Renderer
{
private:
	D3D11_VIEWPORT mViewport;

	ID3D11DepthStencilView* mDSV;
	ID3D11ShaderResourceView* mSRV;
	
	Light* mLight;

	void setupViewport();
	void setupShaders(ID3D11Device* device, ShaderHandler &shaders);
	void setupDSAndSRViews(ID3D11Device* device, ShaderHandler &shaders);
public:
	ShadowRenderer(Light* light, int id);
	virtual ~ShadowRenderer();

	void setup(ID3D11Device* device, ShaderHandler& shaders);
	void render(ID3D11DeviceContext* context, ShaderHandler& shaders);
};

#endif