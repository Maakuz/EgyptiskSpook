#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H

#include "EntityRenderer.h"
#include "Light.h"
#include "OptionsHandler.h"
#include <vector>

class GraphicsHandler {
private:
	ShaderHandler mShaderHandler;

	IDXGISwapChain *mSwapChain;
	ID3D11RenderTargetView *mBackBufferRTV;
	ID3D11Device *mDevice;
	ID3D11DeviceContext *mContext;

	D3D11_VIEWPORT mViewport;

	ID3D11DepthStencilView* mDSV;
	ID3D11DepthStencilState* mDSS;
	ID3D11SamplerState* mSamplerState;

	ID3D11Debug* mDebugDevice;

	ID3D11DepthStencilView* mDSVShadow;
	ID3D11ShaderResourceView* mSRVShadow;
	OptionsHandler* mOptions;


	std::vector<Renderer*> mRenderers;

	void createDepthStencil();
public:
	GraphicsHandler(OptionsHandler* options);
	GraphicsHandler(GraphicsHandler const &gh) = delete;
	~GraphicsHandler();

	HRESULT setupSwapChain();
	void setupViewport(int width, int height);

	void setupSamplerState();
	void setupDSAndSRViews();

	//this class will delete the renderers!
	void addRenderer(Renderer *renderer);
	void setupRenderers();
	void renderRenderers(ID3D11Buffer* WVP, ID3D11Buffer* lightVP, GAMESTATE const &state);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void clear();
	void present();

	GraphicsHandler* operator=(GraphicsHandler const &gh) = delete;
};

#endif