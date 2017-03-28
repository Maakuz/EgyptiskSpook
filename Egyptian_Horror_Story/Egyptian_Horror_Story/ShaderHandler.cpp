#include "ShaderHandler.h"
using namespace std;

ShaderHandler::ShaderHandler() {

}

ShaderHandler::~ShaderHandler() {
	for (auto const &key : mVertexShaders) {
		if (key.second)
			key.second->Release();
	}

	for (auto const &key : mGeometryShaders) {
		if (key.second)
			key.second->Release();
	}

	for (auto const &key : mPixelShaders) {
		if(key.second)
			key.second->Release();
	}
}

HRESULT ShaderHandler::setupVertexShader(ID3D11Device *dev, int key, wchar_t *name, char *entryPoint) {
	ID3DBlob* blob = nullptr;
	HRESULT hr;
	hr = D3DCompileFromFile(name, nullptr, nullptr, entryPoint, "vs_5_0", 0, 0, &blob, nullptr);

	if (SUCCEEDED(hr)) {
		hr = dev->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mVertexShaders[key]);
		blob->Release();
	}
		
	return hr;
}

HRESULT ShaderHandler::setupPixelShader(ID3D11Device *dev, int key, wchar_t *name, char *entryPoint) {
	ID3DBlob* blob = nullptr;
	HRESULT hr = D3DCompileFromFile(name, nullptr, nullptr, entryPoint, "ps_5_0", 0, 0, &blob, nullptr);

	if (SUCCEEDED(hr)) {
		hr = dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mPixelShaders[key]);
		blob->Release();
	}
		
	return hr;
}

HRESULT ShaderHandler::setupGeometryShader(ID3D11Device *dev, int key, wchar_t *name, char *entryPoint) {
	ID3DBlob* blob = nullptr;
	HRESULT hr = D3DCompileFromFile(name, nullptr, nullptr, entryPoint, "gs_5_0", 0, 0, &blob, nullptr);

	if (SUCCEEDED(hr)) {
		hr = dev->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mGeometryShaders[key]);
		blob->Release();
	}
		
	return hr;
}

ID3D11VertexShader* ShaderHandler::getVertexShader(int key) {
	return mVertexShaders[key];
}

ID3D11GeometryShader* ShaderHandler::getGeometryShader(int key) {
	return mGeometryShaders[key];

}

ID3D11PixelShader* ShaderHandler::getPixelShader(int key) {
	return mPixelShaders[key];
}