#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler() {
	swapChain = nullptr;
	backBufferRTV = nullptr;

	device = nullptr;
	context = nullptr;
}

GraphicsHandler::~GraphicsHandler() {
	if (swapChain)
		swapChain->Release();
	if (backBufferRTV)
		backBufferRTV->Release();

	if (device)
		device->Release();
	if (context)
		context->Release();
}

HRESULT GraphicsHandler::setupSwapChain() {
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetActiveWindow(); //get window from SDL2
	swapChainDesc.Windowed = TRUE;

	swapChainDesc.SampleDesc.Count = 4;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG,
		NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device,
		NULL, &context
	);

	if (SUCCEEDED(hr)) {
		ID3D11Texture2D* backBuffer = nullptr;
		hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backBuffer);

		if (SUCCEEDED(hr)) {
			hr = device->CreateRenderTargetView(backBuffer, NULL, &backBufferRTV);
			context->OMSetRenderTargets(1, &backBufferRTV, NULL); // depth stencil test l8

			backBuffer->Release();
		}
	}

	return hr;
}

void GraphicsHandler::setupViewport(int width, int height) {
	viewport.Width = width;
	viewport.Height = height;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.f;
	viewport.TopLeftX = viewport.TopLeftY = 0;
	context->RSSetViewports(1, &viewport);
}

void GraphicsHandler::setupBasicShaders() {
	shaderHandler.setupVertexShader(device, 0, L"SimpleVS.hlsl", "main");
	shaderHandler.setupPixelShader(device, 0, L"SimplePS.hlsl", "main");
	shaderHandler.setupGeometryShader(device, 0, L"SimpleGS.hlsl", "main");

	context->VSSetShader(shaderHandler.getVertexShader(0), nullptr, 0);
	context->PSSetShader(shaderHandler.getPixelShader(0), nullptr, 0);
	context->GSSetShader(shaderHandler.getGeometryShader(0), nullptr, 0);
}

void GraphicsHandler::render() {
	float clear[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
	context->ClearRenderTargetView(backBufferRTV, clear);
	present();
}

void GraphicsHandler::present() {
	swapChain->Present(0, 0);
}