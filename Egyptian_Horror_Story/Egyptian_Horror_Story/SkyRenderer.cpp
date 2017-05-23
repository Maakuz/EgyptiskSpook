#include "SkyRenderer.h"

#define SHADERKEY 6
#define GRAPHICSKEY 0

SkyRenderer::SkyRenderer()
{
}

SkyRenderer::~SkyRenderer()
{
	if (this->srv)
		this->srv->Release();
}

void SkyRenderer::setup(ID3D11Device* device, ShaderHandler& shaderHandler)
{
	using namespace DirectX::SimpleMath;

	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

	shaderHandler.setupVertexShader(device, SHADERKEY, L"SkymapVS.hlsl", "main", desc, ARRAYSIZE(desc));

	shaderHandler.setupPixelShader(device, SHADERKEY, L"SkymapPS.hlsl", "main");

	ID3D11Texture2D* tex;

	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		device, 
		L"../Resource/Textures/skybox_texture.dds",
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


	//this was very annoying, it better be right.
	Vector3 cube[]
	{
		//front
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		Vector3(1, 1, -1),
		
		Vector3(1, 1, -1),
		Vector3(1, -1, -1),
		Vector3(-1, -1, -1),

		//back
		Vector3(-1, -1, 1),
		Vector3(1, -1, 1),
		Vector3(1, 1, 1),

		Vector3(1, 1, 1),
		Vector3(-1, 1, 1),
		Vector3(-1, -1, 1),

		//top
		Vector3(-1, 1, -1),
		Vector3(-1, 1, 1),
		Vector3(1, 1, 1),

		Vector3(1, 1, 1),
		Vector3(1, 1, -1),
		Vector3(-1, 1, -1),

		//bottom
		Vector3(-1, -1, -1),
		Vector3(1, -1, -1),
		Vector3(1, -1, 1),

		Vector3(1, -1, 1),
		Vector3(-1, -1, 1),
		Vector3(-1, -1, -1),

		//Left
		Vector3(-1, -1, 1),
		Vector3(-1, 1, 1),
		Vector3(-1, 1, -1),

		Vector3(-1, 1, -1),
		Vector3(-1, -1, -1),
		Vector3(-1, -1, 1),
		
		//Right
		Vector3(1, -1, -1),
		Vector3(1, 1, -1),
		Vector3(1, 1, 1),
		
		Vector3(1, 1, 1),
		Vector3(1, -1, 1),
		Vector3(1, -1, -1),
	};

	//TODO: SAVE THIS IN A BUFFER AND ALL OTHER STUFFOKBYE
}

void SkyRenderer::render(ID3D11DeviceContext* context, ShaderHandler& shaderHandler, GAMESTATE const & state)
{
}
