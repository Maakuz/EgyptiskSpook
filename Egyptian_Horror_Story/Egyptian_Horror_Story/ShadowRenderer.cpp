#include "ShadowRenderer.h"
#define VERTEX_SHADER 10
#define MSG(x) MessageBox(0, x, L"error", MB_OK);

ShadowRenderer::ShadowRenderer(Light* light)
{
	this->mLight = light;

	this->mDSV = nullptr;
	this->mSRV = nullptr;
}

ShadowRenderer::~ShadowRenderer()
{
	if (this->mDSV)
		this->mDSV->Release();

	if (this->mSRV)
		this->mSRV->Release();
}

void ShadowRenderer::setup(ID3D11Device* device, ShaderHandler& shaders)
{
	setupViewport();
	setupShaders(device, shaders);
	setupDSAndSRViews(device, shaders);
}

void ShadowRenderer::setupDSAndSRViews(ID3D11Device* device, ShaderHandler &shaders) {
	ID3D11Texture2D* texture;

	D3D11_TEXTURE2D_DESC descTex;
	ZeroMemory(&descTex, sizeof(D3D11_TEXTURE2D_DESC));
	descTex.ArraySize = descTex.MipLevels = 1;
	descTex.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	descTex.Format = DXGI_FORMAT_R32_TYPELESS;
	descTex.Height = static_cast<UINT> (this->mViewport.Height);
	descTex.Width = static_cast<UINT> (this->mViewport.Width);
	descTex.SampleDesc.Count = 4;

	if (FAILED(device->CreateTexture2D(&descTex, NULL, &texture)))
		MSG(L"Shadow texture creation failed");

	D3D11_DEPTH_STENCIL_VIEW_DESC descStenV;
	ZeroMemory(&descStenV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descStenV.Format = DXGI_FORMAT_D32_FLOAT;
	descStenV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	if (FAILED(device->CreateDepthStencilView(texture, &descStenV, &this->mDSV)))
		MSG(L"Shadow stencil view creation failed");

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	srvDesc.Texture2D.MipLevels = descTex.MipLevels;

	if (FAILED(device->CreateShaderResourceView(texture, &srvDesc, &this->mSRV)))
		MSG(L"Shadow srv view creation failed");
	texture->Release();
}

void ShadowRenderer::setupViewport() {
	this->mViewport.Height = mLight->getHeight();
	this->mViewport.Width = mLight->getWidth();
	this->mViewport.MaxDepth = 1.f;
	this->mViewport.MinDepth = 0.f;
	this->mViewport.TopLeftX = mViewport.TopLeftY = 0;
}

void ShadowRenderer::setupShaders(ID3D11Device *device, ShaderHandler &shaders) {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	shaders.setupVertexShader(device, VERTEX_SHADER, L"ShadowVS.hlsl", "main", desc, ARRAYSIZE(desc));
}

void ShadowRenderer::render(ID3D11DeviceContext* context, ShaderHandler& shaders)
{
	context->ClearDepthStencilView(this->mDSV, D3D11_CLEAR_DEPTH, 1, 0);
	context->OMSetRenderTargets(0, nullptr, this->mDSV);
	context->RSSetViewports(1, &this->mViewport);

	ID3D11Buffer* temp = this->mLight->getMatrixBuffer();
	context->VSSetConstantBuffers(0, 1, &temp);
	
	shaders.setShaders(context, VERTEX_SHADER,
		shaders.UNBIND_SHADER, shaders.UNBIND_SHADER);

	context->Draw(6, 0);
}
