#include "GUIRenderer.h"
#define SHADERS 40

using namespace DirectX::SimpleMath;

GUIRenderer::GUIRenderer(int id) : Renderer(id){
	this->mSize = 1;
	this->mParticles = new Vector3[mSize];
	this->mGraphicsData = new GraphicsData();

	// for testing
	navTest = nullptr;
}

GUIRenderer::~GUIRenderer() {
	delete this->mGraphicsData;
	delete[] this->mParticles;

	if (navTest)
		navTest->Release();
}

void GUIRenderer::setup(ID3D11Device *device, ShaderHandler &shaders) {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shaders.setupVertexShader(device, SHADERS, L"GUIVS.hlsl", "main", desc, ARRAYSIZE(desc));
	shaders.setupPixelShader(device, SHADERS, L"GUIPS.hlsl", "main");
	shaders.setupGeometryShader(device, SHADERS, L"GUIGS.hlsl", "main");

	this->mParticles[0] = Vector3(-0.95f, 0.55f, 0);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &this->mParticles[0];

	mGraphicsData->createVertexBuffer(0, this->mSize * sizeof(Vector3), &data, device);
	mGraphicsData->loadTexture(0, L"../Resource/Textures/placeholder.png", device);
}

void GUIRenderer::render(ID3D11DeviceContext *context, ShaderHandler &shaders) {
	UINT stride = sizeof(Vector3), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getVertexBuffer(0);
	ID3D11ShaderResourceView *srv = this->mGraphicsData->getSRV(0);
	shaders.setShaders(context, SHADERS, SHADERS, SHADERS);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	context->IASetInputLayout(shaders.getInputLayout(SHADERS));
	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	context->PSSetShaderResources(0, 1, &srv);
	if (navTest)
		context->PSSetShaderResources(0, 1, &navTest);

	context->Draw(this->mSize, 0);
}

void GUIRenderer::setNavigationTest(ID3D11Device *device, void* pixels, int w, int h) {
	if (navTest)
		navTest->Release();
	mGraphicsData->loadTexture(0, L"NAVIGATION_TEST.bmp", device);

	/*
	ID3D11Texture2D *tex;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Format = DXGI_FORMAT_R8G8B8A8_SNORM;
	desc.Width = w;
	desc.Height = h;
	desc.ArraySize = desc.MipLevels = 1;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.SampleDesc.Count = 1;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = pixels;
	data.SysMemPitch = w * 4;

	HRESULT hr = device->CreateTexture2D(&desc, &data, &tex);

	D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
	ZeroMemory(&srDesc, sizeof(srDesc));
	srDesc.Format = desc.Format;
	srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MipLevels = 1;
	
	hr = device->CreateShaderResourceView(tex, &srDesc, &navTest);
	tex->Release();
	*/
}