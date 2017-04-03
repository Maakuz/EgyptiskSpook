#include "ShadowRenderer.h"

ShadowRenderer::ShadowRenderer(Light* light)
{
	this->mLight = light;

	this->mViewport.Height = light->getHeight();
	this->mViewport.Width = light->getWidth();
	this->mViewport.MaxDepth = 1.f;
	this->mViewport.MinDepth = 0.f;
	this->mViewport.TopLeftX = 0;
	this->mViewport.TopLeftY = 0;

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
	ID3D11Texture2D* texture;

	D3D11_TEXTURE2D_DESC descTex;
	ZeroMemory(&descTex, sizeof(D3D11_TEXTURE2D_DESC));
	descTex.ArraySize = descTex.MipLevels = 1;
	descTex.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	descTex.Format = DXGI_FORMAT_R32_TYPELESS;
	descTex.Height = this->mViewport.Height;
	descTex.Width = this->mViewport.Width;
	descTex.SampleDesc.Count = 4;

	HRESULT hr = device->CreateTexture2D(&descTex, NULL, &texture);
	if (FAILED(hr))
	{
		MessageBox(0, L"Shadow texture creation failed", L"error", MB_OK);
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descStenV;
	ZeroMemory(&descStenV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descStenV.Format = DXGI_FORMAT_D32_FLOAT;
	descStenV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	hr = device->CreateDepthStencilView(texture, &descStenV, &this->mDSV);
	if (FAILED(hr))
	{
		MessageBox(0, L"Shadow stencil view creation failed", L"error", MB_OK);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	srvDesc.Texture2D.MipLevels = descTex.MipLevels;

	hr = device->CreateShaderResourceView(texture, &srvDesc, &this->mSRV);
	if (FAILED(hr))
	{
		MessageBox(0, L"Shadow srv view creation failed", L"error", MB_OK);
	}
	texture->Release();


	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	shaders.setupVertexShader(device, 10, L"ShadowVS.hlsl", "main", desc, ARRAYSIZE(desc));
}

void ShadowRenderer::render(ID3D11DeviceContext* context, ShaderHandler& shaders)
{

	context->ClearDepthStencilView(this->mDSV, D3D11_CLEAR_DEPTH, 1, 0);

	context->OMSetRenderTargets(0, nullptr, this->mDSV);

	ID3D11Buffer* temp = this->mLight->getMatrixBuffer();

	context->RSSetViewports(1, &this->mViewport);

	context->VSSetConstantBuffers(0, 1, &temp);
	
	context->VSSetShader(shaders.getVertexShader(10), nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

	context->Draw(6, 0);
}
