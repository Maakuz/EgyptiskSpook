#pragma once
#include "ShaderHandler.h"
#include "GraphicsData.h"
#include "ShadowRenderer.h"

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

	// 4 Testing
	ID3D11Buffer *mVertexBuffer;
	ID3D11Buffer *mVertexBuffer2;

	ShadowRenderer* shadow;
	

	void createDepthStencil();
public:
	GraphicsHandler();
	GraphicsHandler(GraphicsHandler const &gh) = delete;
	~GraphicsHandler();

	HRESULT setupSwapChain();
	void setupTestData();
	void setupFloor();
	void setupViewport(int width, int height);
	void setupBasicShaders();
	void setupShadow(Light* light);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void render(ID3D11Buffer* WVP);
	void present();

	GraphicsHandler* operator=(GraphicsHandler const &gh) = delete;
};