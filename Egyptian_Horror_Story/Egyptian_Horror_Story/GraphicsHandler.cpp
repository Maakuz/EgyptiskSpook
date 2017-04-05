#include "GraphicsHandler.h"

void GraphicsHandler::createDepthStencil()
{
	ID3D11Texture2D* texture;

	D3D11_TEXTURE2D_DESC descTex;
	ZeroMemory(&descTex, sizeof(D3D11_TEXTURE2D_DESC));
	descTex.ArraySize = descTex.MipLevels = 1;
	descTex.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descTex.Format = DXGI_FORMAT_D32_FLOAT;
	descTex.Height = HEIGHT;
	descTex.Width = WIDTH;
	descTex.SampleDesc.Count = 4;
	
	HRESULT hr = this->mDevice->CreateTexture2D(&descTex, NULL, &texture);
	if (FAILED(hr))
	{
		MessageBox(0, L"Depth texture creation failed", L"error", MB_OK);
	}

	D3D11_DEPTH_STENCIL_DESC descSten;
	ZeroMemory(&descSten, sizeof(D3D11_DEPTH_STENCIL_DESC));
	descSten.DepthEnable = true;
	descSten.DepthFunc = D3D11_COMPARISON_LESS;
	descSten.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	descSten.StencilEnable = false;

	hr = this->mDevice->CreateDepthStencilState(&descSten, &this->mDSS);
	if (FAILED(hr))
	{
		MessageBox(0, L"Depth stencil state creation failed", L"error", MB_OK);
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descStenV;
	ZeroMemory(&descStenV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descStenV.Format = DXGI_FORMAT_D32_FLOAT;
	descStenV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	hr = this->mDevice->CreateDepthStencilView(texture, &descStenV, &this->mDSV);
	if (FAILED(hr))
	{
		MessageBox(0, L"Depth stencil view creation failed", L"error", MB_OK);
	}

	this->mContext->OMSetDepthStencilState(this->mDSS, 0);

	texture->Release();

}

GraphicsHandler::GraphicsHandler()
{
	mSwapChain = nullptr;
	mBackBufferRTV = nullptr;
	mDSS = nullptr;
	mDSV = nullptr;
	mSamplerState = nullptr;

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

	if (mVertexBuffer2)
		mVertexBuffer2->Release();
	//end of test

	if (mDSS)
		mDSS->Release();

	if (mDSV)
		mDSV->Release();

	if (mSamplerState)
		mSamplerState->Release();

	//Krashar för Entity tar bort sin entityRenderer

	//Lösning är att antingen låta alla ta bort sina egna renderers
	//eller att alla tas bort här. Det första vore att föredra
	for (auto *renderer : mRenderers) {
			//delete renderer;
	}
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
			this->createDepthStencil();

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

void GraphicsHandler::setupFloor()
{
	float testData[] = {
		-10.f, -2.f, -10.f,
		0.f, 1.f,

		-10.f, -2.f, 10.f,
		0.f, 0.f,

		10.f, -2.f, 10.f,
		1.f, 0.f,

		-10.f, -2.f, -10.f,
		0.f, 1.f,

		10.f, -2.f, -10.f,
		1.f, 1.f,

		10.f, -2.f, 10.f,
		1.f, 0.f,
	};

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(testData);
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = testData;

	mDevice->CreateBuffer(&desc, &data, &mVertexBuffer2);

	UINT stride = sizeof(float) * 5, offset = 0;
	mContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
}

void GraphicsHandler::setupBasicShaders() {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	mShaderHandler.setupVertexShader(mDevice, 0, L"SimpleVS.hlsl", "main", desc, ARRAYSIZE(desc));
	mShaderHandler.setupPixelShader(mDevice, 0, L"SimplePS.hlsl", "main");
	mShaderHandler.setupGeometryShader(mDevice, 0, L"SimpleGS.hlsl", "main");

	// render target, input layout and topology set
	mContext->OMSetRenderTargets(1, &mBackBufferRTV, this->mDSV);
	mContext->IASetInputLayout(mShaderHandler.getInputLayout(0));
	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void GraphicsHandler::setupSamplerState() {
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = desc.AddressV =
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	desc.MaxAnisotropy = 16; //max
	desc.ComparisonFunc = D3D11_COMPARISON_LESS; // idk

	mDevice->CreateSamplerState(&desc, &mSamplerState);
	mContext->PSSetSamplers(0, 1, &mSamplerState);
}

void GraphicsHandler::addRenderer(Renderer *renderer) {
	mRenderers.push_back(renderer);
}

void GraphicsHandler::setupRenderers() {
	for (const auto& renderer : mRenderers) {
		renderer->setup(mDevice, mShaderHandler);
	}
}

void GraphicsHandler::renderRenderers(ID3D11Buffer* WVP) {
	for (const auto& renderer : mRenderers) {

		this->mContext->VSSetConstantBuffers(0, 1, &WVP);
		this->mContext->OMSetRenderTargets(1, &this->mBackBufferRTV, this->mDSV);
		this->mContext->RSSetViewports(1, &this->mViewport);
		renderer->render(mContext, mShaderHandler);
	}
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
	// render test data, should be moved to a separate renderer
	float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };


	UINT stride = sizeof(float) * 5, offset = 0;

	this->mContext->RSSetViewports(1, &mViewport);

	mShaderHandler.setShaders(mContext, 0, 0, 0);

	mContext->VSSetConstantBuffers(0, 1, &WVP);
	mContext->ClearRenderTargetView(mBackBufferRTV, clear);
	mContext->ClearDepthStencilView(this->mDSV, D3D11_CLEAR_DEPTH, 1.f, 0);

	this->mContext->OMSetRenderTargets(1, &this->mBackBufferRTV, this->mDSV);

	mContext->IASetVertexBuffers(0, 1, &this->mVertexBuffer, &stride, &offset);
	mContext->Draw(6, 0);

	mContext->IASetVertexBuffers(0, 1, &this->mVertexBuffer2, &stride, &offset);
	mContext->Draw(6, 0);
}

void GraphicsHandler::clear()
{
	float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	mContext->ClearRenderTargetView(mBackBufferRTV, clear);
	mContext->ClearDepthStencilView(this->mDSV, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void GraphicsHandler::present() {
	mSwapChain->Present(0, 0);
}