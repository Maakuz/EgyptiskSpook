#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler() {
	swapChain = nullptr;
	backBufferRTV = nullptr;

	device = nullptr;
	context = nullptr;

	//test
	vertexBuffer = nullptr;
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

	//test
	if (vertexBuffer)
		vertexBuffer->Release();
}

HRESULT GraphicsHandler::setupSwapChain() {
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetActiveWindow(); //get window from SDL2
	swapChainDesc.Windowed = TRUE;

	swapChainDesc.SampleDesc.Count = 4;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device,
		nullptr, &context
	);

	if (SUCCEEDED(hr)) {
		ID3D11Texture2D* backBuffer = nullptr;
		hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backBuffer);

		if (SUCCEEDED(hr)) {
			hr = device->CreateRenderTargetView(backBuffer, nullptr, &backBufferRTV);
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

void GraphicsHandler::setupTestData() {
	float testData[] = { 
						-1.f, -1.f, 0.f,
						0.f, 1.f,

						-1.f, 1.f, 0.f,
						0.f, 0.f,

						1.f, -1.f, 0.f,
						1.f, 1.f,

						1.f, -1.f, 0.f,
						1.f, 1.f,

						1.f, 1.f, 0.f,
						1.f, 0.f,

						-1.f, 1.f, 0.f,
						0.f, 0.f,
					   };

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(testData);
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = testData;

	device->CreateBuffer(&desc, &data, &vertexBuffer);

	UINT stride = sizeof(float) * 5, offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	this->mGraphicsData.loadTexture("test", L"../Resource/Textures/normalMap.png", device);

	ID3D11ShaderResourceView* temp = this->mGraphicsData.getSRV("test");

	context->PSSetShaderResources(0, 1, &temp);
}

void GraphicsHandler::setupBasicShaders() {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	shaderHandler.setupVertexShader(device, 0, L"SimpleVS.hlsl", "main", desc, ARRAYSIZE(desc));
	shaderHandler.setupPixelShader(device, 0, L"SimplePS.hlsl", "main");
	shaderHandler.setupGeometryShader(device, 0, L"SimpleGS.hlsl", "main");

	context->VSSetShader(shaderHandler.getVertexShader(0), nullptr, 0);
	context->PSSetShader(shaderHandler.getPixelShader(0), nullptr, 0);
	context->GSSetShader(shaderHandler.getGeometryShader(0), nullptr, 0);

	// render target, input layout and topology set
	context->OMSetRenderTargets(1, &backBufferRTV, nullptr); // depth stencil test l8
	context->IASetInputLayout(shaderHandler.getInputLayout(0));
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

ID3D11Device* GraphicsHandler::getDevice()
{
	return this->device;
}

ID3D11DeviceContext* GraphicsHandler::getDeviceContext()
{
	return this->context;
}

void GraphicsHandler::render(ID3D11Buffer* WVP) {
	float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	context->VSSetConstantBuffers(0, 1, &WVP);
	context->ClearRenderTargetView(backBufferRTV, clear);
	context->Draw(6, 0);
}

void GraphicsHandler::present() {
	swapChain->Present(0, 0);
}