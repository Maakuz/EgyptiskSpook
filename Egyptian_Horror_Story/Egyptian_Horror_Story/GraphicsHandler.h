#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H

#include "ShaderHandler.h"
#include "GraphicsData.h"
#include "Renderer.h"
#include <vector>

#define WIDTH 1080
#define HEIGHT 720

class GraphicsHandler {
private:
	ShaderHandler mShaderHandler;
	GraphicsData mGraphicsData;

	IDXGISwapChain *mSwapChain;
	ID3D11RenderTargetView *mBackBufferRTV;
	ID3D11Device *mDevice;
	ID3D11DeviceContext *mContext;

	D3D11_VIEWPORT mViewport;

	ID3D11DepthStencilView* mDSV;
	ID3D11DepthStencilState* mDSS;
	ID3D11SamplerState* mSamplerState;


	std::vector<Renderer*> mRenderers;

	void createDepthStencil();
public:
	GraphicsHandler();
	GraphicsHandler(GraphicsHandler const &gh) = delete;
	~GraphicsHandler();

	HRESULT setupSwapChain();
	void setupViewport(int width, int height);
	void setupBasicShaders();
	void setupSamplerState();

	//this class will delete the renderers!
	void addRenderer(Renderer *renderer);
	void setupRenderers();
	void renderRenderers(ID3D11Buffer* WVP);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void clear();
	void present();

	GraphicsHandler* operator=(GraphicsHandler const &gh) = delete;
};

#endif