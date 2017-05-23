#include "SkyRenderer.h"

#define SHADERKEY 6
#define GRAPHICSKEY 0

SkyRenderer::SkyRenderer()
{
}

SkyRenderer::~SkyRenderer()
{
	this->srv->Release();
}

void SkyRenderer::setup(ID3D11Device* device, ShaderHandler& shaderHandler)
{
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

	shaderHandler.setupVertexShader(device, SHADERKEY, L"SkymapVS.hlsl", "main", desc, ARRAYSIZE(desc));

	shaderHandler.setupPixelShader(device, SHADERKEY, L"SkymapPS.hlsl", "main");

	ID3D11Texture2D* tex;
	
	D3D11_TEXTURE2D_DESC texDesc;

	HRESULT hr = DirectX::CreateWICTextureFromFileEx(
		device, 
		L"../Resource/Textures/skybox_texture.jpg",
		0, 
		D3D11_USAGE_DEFAULT, 
		D3D11_BIND_SHADER_RESOURCE,
		0,
		D3D11_RESOURCE_MISC_TEXTURECUBE,
		DirectX::WIC_LOADER_DEFAULT,
		(ID3D11Resource**)&tex,
		&srv);

	if (FAILED(hr))
		exit(-55);

	tex->Release();

	//TRYING WITHOUT THIS BECAUSE THAT WOULD BE SMART
	//tex->GetDesc(&texDesc);

	//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	//ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	//srvDesc.Format = texDesc.Format;
	//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	//srvDesc.TextureCube.MipLevels = texDesc.MipLevels;
	//srvDesc.TextureCube.MostDetailedMip = 0;


}

void SkyRenderer::render(ID3D11DeviceContext* context, ShaderHandler& shaderHandler, GAMESTATE const & state)
{
}
