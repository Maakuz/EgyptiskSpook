#pragma once
#include "ShaderHandler.h"
#include "GraphicsData.h"

class GraphicsHandler {
private:
	ShaderHandler shaderHandler;
	GraphicsData mGraphicsData;

	IDXGISwapChain *swapChain;
	ID3D11RenderTargetView *backBufferRTV;
	ID3D11Device *device;
	ID3D11DeviceContext *context;

	D3D11_VIEWPORT viewport;

	// 4 Testing
	ID3D11Buffer *vertexBuffer;
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