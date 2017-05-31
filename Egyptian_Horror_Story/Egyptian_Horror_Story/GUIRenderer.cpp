#include "GUIRenderer.h"
#define SHADERS 40
#define GAMEOVERSTARTINDEX 20
#define HUDSTARTINDEX 40
#define TREASUREINDEX 60
#define CHESTTEXTURE 7777
#define AHNKTEXTURE 7778

using namespace DirectX::SimpleMath;

GUIRenderer::GUIRenderer() : Renderer(){
	this->mGraphicsData = new GraphicsData();

	// for testing
	navTest = nullptr;

	hasTreasures = false;
	ahnkStartIndex = 0;
}

GUIRenderer::~GUIRenderer() {
	delete this->mGraphicsData;
}

void GUIRenderer::setup(ID3D11Device *device, ShaderHandler &shaders) {
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIMENSIONS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shaders.setupVertexShader(device, SHADERS, L"GUIVS.hlsl", "main", desc, ARRAYSIZE(desc));
	shaders.setupPixelShader(device, SHADERS, L"GUIPS.hlsl", "main");
	shaders.setupGeometryShader(device, SHADERS, L"GUIGS.hlsl", "main");

	Vector2 dimension = { 0.4f, 0.2f };
	// Add new GUI elements here
	this->mMenuElements.push_back(GUI_ELEMENT{ Vector3(-0.2f, 0.2f, 0), dimension });
	this->mMenuElements.push_back(GUI_ELEMENT{ Vector3(-0.2f, -0.2f, 0), dimension });

	this->mGameOverElements.push_back(GUI_ELEMENT{ Vector3(-0.2f, -0.2f, 0), dimension });
	this->mGameOverElements.push_back(GUI_ELEMENT{ Vector3(-0.4f, 0.2f, 0), Vector2(0.8f, 0.2f) });

	this->mHudElements.push_back(GUI_ELEMENT{ Vector3(-0.85f, 0.6f, 0),  Vector2(0.15f, 0.3f) });

	// Add the texture here, texture ID = index of element in element arrays,
	//this class got own graphicsdata, so infinite ids is availabe (not inf)
	mGraphicsData->loadTexture(0, L"play.png", device);
	mGraphicsData->loadTexture(1, L"options.png", device);

	mGraphicsData->loadTexture(GAMEOVERSTARTINDEX, L"Confirm.png", device);
	mGraphicsData->loadTexture(GAMEOVERSTARTINDEX + 1, L"gameOver.png", device);

	mGraphicsData->loadTexture(CHESTTEXTURE, L"chest.png", device);
	mGraphicsData->loadTexture(AHNKTEXTURE, L"ahnk.png", device);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = &this->mMenuElements[0];
	mGraphicsData->createVertexBuffer(0, sizeof(GUI_ELEMENT) * this->mMenuElements.size(), &data, device);

	data.pSysMem = &this->mGameOverElements[0];
	this->mGraphicsData->createVertexBuffer(1, sizeof(GUI_ELEMENT) * this->mGameOverElements.size(), &data, device);
	
	data.pSysMem = &this->mHudElements[0];
	this->mGraphicsData->createVertexBuffer(2, sizeof(GUI_ELEMENT) * this->mHudElements.size(), &data, device);
}

void GUIRenderer::loadButtons(MenuHandler &menuHandler) {
	for (int i = 0; i < this->mMenuElements.size(); i++)
		menuHandler.addButton(i,
			Vector2(this->mMenuElements[i].pos), this->mMenuElements[i].dimensions);//i is pretty hardcoded, change later, change elements to use vector2

	for (int i = 0; i < this->mGameOverElements.size(); i++)
		menuHandler.addButton(i + this->mMenuElements.size(),
			Vector2(this->mGameOverElements[i].pos), this->mGameOverElements[i].dimensions);
}

void GUIRenderer::render(ID3D11DeviceContext *context, ShaderHandler &shaders, GAMESTATE const &state) {
	context->IASetInputLayout(shaders.getInputLayout(SHADERS));
	shaders.setShaders(context, SHADERS, SHADERS, SHADERS);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//if (state == GAMESTATE::PLAY)
		//renderHud(context, shaders);
	if (state == GAMESTATE::MAIN_MENU)
		renderMenu(context, shaders, 0, this->mMenuElements.size(), 0);
	else if (state == GAMESTATE::GAME_OVER)
	{
		renderMenu(context, shaders, 1, this->mGameOverElements.size(), GAMEOVERSTARTINDEX);
		if (hasTreasures) 
			renderTreasure(context, shaders);
	}
}

void GUIRenderer::renderMenu(ID3D11DeviceContext *context, ShaderHandler &shaders, int vertexBufferKey, int nrOfElements, int srvOffset) {
	UINT stride = sizeof(GUI_ELEMENT), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getVertexBuffer(vertexBufferKey);
	ID3D11ShaderResourceView *srv;

	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

	// Loop through and draw buttons, optimize plz
	for (int i = 0; i < nrOfElements; i++) {
		srv = this->mGraphicsData->getSRV(i + srvOffset);
		context->PSSetShaderResources(0, 1, &srv);
		context->Draw(1, i);
	}
}

void GUIRenderer::renderTreasure(ID3D11DeviceContext *context, ShaderHandler &shaders) {
	UINT stride = sizeof(GUI_ELEMENT), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getVertexBuffer(TREASUREINDEX);
	ID3D11ShaderResourceView *srv;

	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

	// Loop through and draw buttons, optimize plz
	srv = this->mGraphicsData->getSRV(CHESTTEXTURE);
	context->PSSetShaderResources(0, 1, &srv);
	for (int i = 0; i < ahnkStartIndex; i++) {
		context->Draw(1, i);
	}

	srv = this->mGraphicsData->getSRV(AHNKTEXTURE);
	context->PSSetShaderResources(0, 1, &srv);
	for (int i = ahnkStartIndex; i < mTreasures.size(); i++) {
		context->Draw(1, i);
	}
}

void GUIRenderer::renderHud(ID3D11DeviceContext *context, ShaderHandler &shaders) {
	UINT stride = sizeof(GUI_ELEMENT), offset = 0;
	ID3D11Buffer *buffer = this->mGraphicsData->getVertexBuffer(2);
	ID3D11ShaderResourceView *srv = this->mGraphicsData->getSRV(0);

	context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

	if (navTest)
		context->PSSetShaderResources(0, 1, &navTest);
	else
		context->PSSetShaderResources(0, 1, &srv);

	context->Draw(1, 0); // not used right now
}

void GUIRenderer::clearTreasures() {
	if (hasTreasures) {
		this->mTreasures.clear();
		this->mGraphicsData->removeData(TREASUREINDEX);
		hasTreasures = false;
	}
}

void GUIRenderer::createTreasures(ID3D11Device* device, int chests, int ahnks)
{
	Vector2 dimension = { 0.2f, 0.2f };
	// Add new GUI elements here

	for (int i = 0; i < chests; i++)
	{
		this->mTreasures.push_back(GUI_ELEMENT{Vector3(-0.8f + i * 0.35, 0.7f, 0), dimension });
	}

	ahnkStartIndex = mTreasures.size();

	for (int i = 0; i < ahnks; i++)
	{
		this->mTreasures.push_back(GUI_ELEMENT{Vector3(-0.8f + i * 0.35, 0.4f, 0), dimension });
	}

	if (mTreasures.size() > 0) {
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = &this->mTreasures[0];
		mGraphicsData->createVertexBuffer(TREASUREINDEX, sizeof(GUI_ELEMENT) * this->mTreasures.size(), &data, device);
		hasTreasures = true;
	}
}

void GUIRenderer::setNavigationTest(ID3D11Device *device, void* pixels, int w, int h) {
	mGraphicsData->loadTexture(HUDSTARTINDEX, L"NAVIGATION_TEST.bmp", device);
	navTest = mGraphicsData->getSRV(HUDSTARTINDEX);

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