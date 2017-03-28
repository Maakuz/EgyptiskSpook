#pragma once
#include "ShaderHandler.h"

class GraphicsHandler {
private:
	ShaderHandler shaderHandler;
	IDXGISwapChain *swapChain;
	ID3D11RenderTargetView *backBufferRTV;
	ID3D11Device *device;
	ID3D11DeviceContext *context;

	D3D11_VIEWPORT viewport;
public:
	GraphicsHandler();
	GraphicsHandler(GraphicsHandler const &gh) = delete;
	~GraphicsHandler();

	HRESULT setupSwapChain();
	void setupViewport(int width, int height);
	void setupBasicShaders();

	void render();
	void present();

	GraphicsHandler* operator=(GraphicsHandler const &gh) = delete;
};