#pragma once
#include "ShaderHandler.h"
#include "GraphicsData.h"

class GraphicsHandler {
private:
	ShaderHandler mShaderHandler;
	GraphicsData mGraphicsData;

	IDXGISwapChain *mSwapChain;
	ID3D11RenderTargetView *mBackBufferRTV;
	ID3D11Device *mDevice;
	ID3D11DeviceContext *mContext;

	D3D11_VIEWPORT mViewport;

	// 4 Testing
	ID3D11Buffer *mVertexBuffer;
public:
	GraphicsHandler();
	GraphicsHandler(GraphicsHandler const &gh) = delete;
	~GraphicsHandler();

	HRESULT setupSwapChain();
	void setupTestData();
	void setupViewport(int width, int height);
	void setupBasicShaders();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void render(ID3D11Buffer* WVP);
	void present();

	GraphicsHandler* operator=(GraphicsHandler const &gh) = delete;
};