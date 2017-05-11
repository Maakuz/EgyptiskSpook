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

	if (mDSS)
		mDSS->Release();

	if (mDSV)
		mDSV->Release();

	if (this->mDSVShadow)
		this->mDSVShadow->Release();

	if (this->mSRVShadow)
		this->mSRVShadow->Release();

	if (mSamplerState)
		mSamplerState->Release();

	for (auto *renderer : mRenderers) {
			delete renderer;
	}

	//this->mDebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	this->mDebugDevice->Release();
}

void GraphicsHandler::setOptions(OptionsHandler* options)
{
	this->mOptions = options;
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

			//Creating debug device
			HRESULT hr = this->mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast <void **>(&mDebugDevice));
			if (FAILED(hr))
			{
				MessageBox(0, L"Debug device creation failed", L"error", MB_OK);
			}
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

void GraphicsHandler::setupSamplerState() {
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = desc.AddressV =
		desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	desc.MaxAnisotropy = 16; //max
	desc.ComparisonFunc = D3D11_COMPARISON_LESS; // idk

	mDevice->CreateSamplerState(&desc, &mSamplerState);
	mContext->PSSetSamplers(0, 1, &mSamplerState);
}

void GraphicsHandler::setupLightViewport(Light* light)
{
	this->mViewportShadow.Height = this->mViewport.Height;//light->getHeight();
	this->mViewportShadow.Width = this->mViewport.Width;// light->getWidth();
	this->mViewportShadow.MaxDepth = 1.f;
	this->mViewportShadow.MinDepth = 0.f;
	this->mViewportShadow.TopLeftX = mViewport.TopLeftY = 0;
}

void GraphicsHandler::addRenderer(Renderer *renderer) {
	mRenderers.push_back(renderer);
}

void GraphicsHandler::setupRenderers() {
	for (const auto& renderer : mRenderers) {
		renderer->setup(mDevice, mShaderHandler);
	}
}

void GraphicsHandler::setupDSAndSRViews() {
	ID3D11Texture2D* texture;

	D3D11_TEXTURE2D_DESC descTex;
	ZeroMemory(&descTex, sizeof(D3D11_TEXTURE2D_DESC));
	descTex.ArraySize = 1;
	descTex.MipLevels = 1;
	descTex.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	descTex.Format = DXGI_FORMAT_R32_TYPELESS;
	descTex.Height = HEIGHT;
	descTex.Width = WIDTH;
	descTex.SampleDesc.Count = 1;

	if (FAILED(this->mDevice->CreateTexture2D(&descTex, NULL, &texture)))
		exit(-2);//MSG(L"Shadow texture creation failed");

	D3D11_DEPTH_STENCIL_VIEW_DESC descStenV;
	ZeroMemory(&descStenV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descStenV.Format = DXGI_FORMAT_D32_FLOAT;
	descStenV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	if (FAILED(this->mDevice->CreateDepthStencilView(texture, &descStenV, &this->mDSVShadow)))
		exit(-2);//MSG(L"Shadow stencil view creation failed");

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = descTex.MipLevels;

	if (FAILED(this->mDevice->CreateShaderResourceView(texture, &srvDesc, &this->mSRVShadow)))
		exit(-2); //MSG(L"Shadow srv view creation failed");
	texture->Release();
}

void GraphicsHandler::renderRenderers(ID3D11Buffer* WVP, ID3D11Buffer* lightWVP) {

	//Shadow prepass
	for (const auto& renderer : mRenderers) {
		EntityRenderer* ptr = dynamic_cast<EntityRenderer*>(renderer);

		if (ptr)
		{
			ptr->setShadowPass(true);

			//Needs to be null in order to be used as depthmap
			ID3D11ShaderResourceView* srvNull = nullptr;
			this->mContext->PSSetShaderResources(1, 1, &srvNull);

			this->mContext->VSSetConstantBuffers(0, 1, &lightWVP);
			this->mContext->OMSetRenderTargets(0, nullptr, this->mDSVShadow);
			this->mContext->RSSetViewports(1, &this->mViewportShadow);

			renderer->render(mContext, mShaderHandler);
			
			ptr->setShadowPass(false);
		}
	
	}

	this->mContext->VSSetConstantBuffers(0, 1, &WVP);
	this->mContext->OMSetRenderTargets(1, &this->mBackBufferRTV, this->mDSV);
	this->mContext->PSSetShaderResources(1, 1, &this->mSRVShadow);
	this->mContext->PSSetConstantBuffers(2, 1, &lightWVP);

	ID3D11Buffer* temp = mOptions->getBrightnessBuffer();
	this->mContext->PSSetConstantBuffers(3, 1, &temp);
	

	this->mContext->RSSetViewports(1, &this->mViewport);

	for (const auto& renderer : mRenderers) {
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

void GraphicsHandler::clear()
{
	float clear[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	mContext->ClearRenderTargetView(mBackBufferRTV, clear);
	mContext->ClearDepthStencilView(this->mDSV, D3D11_CLEAR_DEPTH, 1.f, 0);
	this->mContext->ClearDepthStencilView(this->mDSVShadow, D3D11_CLEAR_DEPTH, 1, 0);
}

void GraphicsHandler::present() {
	mSwapChain->Present(0, 0);
}