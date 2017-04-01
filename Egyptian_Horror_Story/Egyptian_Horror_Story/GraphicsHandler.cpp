#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler() {
	mSwapChain = nullptr;
	mBackBufferRTV = nullptr;

	mDevice = nullptr;
	mContext = nullptr;

	//test
	mVertexBuffer = nullptr;
}

GraphicsHandler::~GraphicsHandler() {
	if (mSwapChain)
		mSwapChain->Release();
	if (mBackBufferRTV)
		mBackBufferRTV->Release();

	if (mDevice)
		mDevice->Release();
	if (mContext)
		mContext->Release();

	//test
	if (mVertexBuffer)
		mVertexBuffer->Release();
}

HRESULT GraphicsHandler::setupSwapChain() {
	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;
	ZeroMemory(&mSwapChainDesc, sizeof(mSwapChainDesc));
	mSwapChainDesc.BufferCount = 1;
	mSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	mSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	mSwapChainDesc.OutputWindow = GetActiveWindow(); //get window from SDL2
	mSwapChainDesc.Windowed = TRUE;

	mSwapChainDesc.SampleDesc.Count = 4;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, NULL, D3D11_SDK_VERSION, &mSwapChainDesc, &mSwapChain, &mDevice,
		nullptr, &mContext
	);

	if (SUCCEEDED(hr)) {
		ID3D11Texture2D* backBuffer = nullptr;
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backBuffer);

		if (SUCCEEDED(hr)) {
			hr = mDevice->CreateRenderTargetView(backBuffer, nullptr, &mBackBufferRTV);
			backBuffer->Release();
		}
	}

	return hr;
}

void GraphicsHandler::setupViewport(int width, int height) {
	mViewport.Width = static_cast<float> (width);
	mViewport.Height = static_cast<float> (height);
	mViewport.MaxDepth = 1.0f;
	mViewport.MinDepth = 0.f;
	mViewport.TopLeftX = mViewport.TopLeftY = 0;
	mContext->RSSetViewports(1, &mViewport);
}

void GraphicsHandler::setupTestData() {
	// for testing, (pos xyz, uv xy)
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

	mDevice->CreateBuffer(&desc, &data, &mVertexBuffer);

	UINT stride = sizeof(float) * 5, offset = 0;
	mContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	this->mGraphicsData.loadTexture("test", L"../Resource/Textures/normalMap.png", mDevice);

	ID3D11ShaderResourceView* temp = this->mGraphicsData.getSRV("test");
	mContext->PSSetShaderResources(0, 1, &temp);
}

void GraphicsHandler::setupBasicShaders() {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	mShaderHandler.setupVertexShader(mDevice, 0, L"SimpleVS.hlsl", "main", desc, ARRAYSIZE(desc));
	mShaderHandler.setupPixelShader(mDevice, 0, L"SimplePS.hlsl", "main");
	mShaderHandler.setupGeometryShader(mDevice, 0, L"SimpleGS.hlsl", "main");

	mContext->VSSetShader(mShaderHandler.getVertexShader(0), nullptr, 0);
	mContext->PSSetShader(mShaderHandler.getPixelShader(0), nullptr, 0);
	mContext->GSSetShader(mShaderHandler.getGeometryShader(0), nullptr, 0);

	// render target, input layout and topology set
	mContext->OMSetRenderTargets(1, &mBackBufferRTV, nullptr); // depth stencil test l8
	mContext->IASetInputLayout(mShaderHandler.getInputLayout(0));
	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

ID3D11Device* GraphicsHandler::getDevice()
{
	return this->mDevice;
}

ID3D11DeviceContext* GraphicsHandler::getDeviceContext()
{
	return this->mContext;
}

void GraphicsHandler::render(ID3D11Buffer* WVP) {
	float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	mContext->VSSetConstantBuffers(0, 1, &WVP);
	mContext->ClearRenderTargetView(mBackBufferRTV, clear);
	mContext->Draw(6, 0);
}

void GraphicsHandler::present() {
	mSwapChain->Present(0, 0);
}