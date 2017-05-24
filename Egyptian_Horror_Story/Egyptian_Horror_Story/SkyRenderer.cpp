#include "SkyRenderer.h"

#define SHADERKEY 60
#define GRAPHICSKEY 0

SkyRenderer::SkyRenderer()
{
}

SkyRenderer::~SkyRenderer()
{
	if (this->srv)
		this->srv->Release();

	if (this->mDepthStateLessEqual)
		this->mDepthStateLessEqual->Release();
}

void SkyRenderer::updateTransform(DirectX::SimpleMath::Vector3 pos, ID3D11DeviceContext* context)
{
	using namespace DirectX::SimpleMath;

	Matrix transform = Matrix::CreateTranslation(pos);

	transform = transform.Transpose();

	D3D11_MAPPED_SUBRESOURCE data;

	context->Map(this->mGraphicsData.getConstantBuffer(GRAPHICSKEY), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &transform, sizeof(DirectX::XMFLOAT4X4));

	context->Unmap(this->mGraphicsData.getConstantBuffer(GRAPHICSKEY), 0);
}

void SkyRenderer::setup(ID3D11Device* device, ShaderHandler& shaderHandler)
{
	using namespace DirectX::SimpleMath;

	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

	shaderHandler.setupVertexShader(device, SHADERKEY, L"SkymapVS.hlsl", "main", desc, ARRAYSIZE(desc));

	shaderHandler.setupPixelShader(device, SHADERKEY, L"SkymapPS.hlsl", "main");

	HRESULT hr = DirectX::CreateDDSTextureFromFile(
	device, L"../Resource/Textures/skyBox.dds", nullptr, &srv);

	if (FAILED(hr))
		exit(-55);

	//this was very annoying, it better be right.
	Vector3 cube[]
	{
		//front
		Vector3(-1, -1, -1),
		Vector3(1, 1, -1),
		Vector3(-1, 1, -1),

		Vector3(1, 1, -1),
		Vector3(-1, -1, -1),
		Vector3(1, -1, -1),

		//back
		Vector3(-1, -1, 1),
		Vector3(1, 1, 1),
		Vector3(1, -1, 1),

		Vector3(1, 1, 1),
		Vector3(-1, -1, 1),
		Vector3(-1, 1, 1),

		//top
		Vector3(-1, 1, -1),
		Vector3(1, 1, 1),
		Vector3(-1, 1, 1),

		Vector3(1, 1, 1),
		Vector3(-1, 1, -1),
		Vector3(1, 1, -1),

		//bottom
		Vector3(-1, -1, -1),
		Vector3(1, -1, 1),
		Vector3(1, -1, -1),

		Vector3(1, -1, 1),
		Vector3(-1, -1, -1),
		Vector3(-1, -1, 1),

		//Left
		Vector3(-1, -1, 1),
		Vector3(-1, 1, -1),
		Vector3(-1, 1, 1),

		Vector3(-1, 1, -1),
		Vector3(-1, -1, 1),
		Vector3(-1, -1, -1),

		//Right
		Vector3(1, -1, -1),
		Vector3(1, 1, 1),
		Vector3(1, 1, -1),

		Vector3(1, 1, 1),
		Vector3(1, -1, -1),
		Vector3(1, -1, 1),
	};

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = &cube[0];

	this->mGraphicsData.createVertexBuffer(GRAPHICSKEY, sizeof(Vector3) * 36, &data, device);

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	device->CreateDepthStencilState(&dssDesc, &this->mDepthStateLessEqual);

	this->mGraphicsData.createConstantBuffer(GRAPHICSKEY, sizeof(DirectX::XMFLOAT4X4), nullptr, device, true);
}

void SkyRenderer::render(ID3D11DeviceContext* context, ShaderHandler& shaderHandler, GAMESTATE const & state)
{
	using namespace DirectX::SimpleMath;

	UINT stride = sizeof(Vector3), offset = 0;

	ID3D11Buffer* temp = this->mGraphicsData.getVertexBuffer(GRAPHICSKEY);
	context->IASetVertexBuffers(0, 1, &temp, &stride, &offset);
	context->IASetInputLayout(shaderHandler.getInputLayout(SHADERKEY));
	temp = this->mGraphicsData.getConstantBuffer(GRAPHICSKEY);
	context->VSSetConstantBuffers(1, 1, &temp);
	context->PSSetShaderResources(0, 1, &this->srv);

	shaderHandler.setShaders(context, SHADERKEY, SHADERKEY, -1);
	context->OMSetDepthStencilState(this->mDepthStateLessEqual, 0);

	context->Draw(36, 0);
}
