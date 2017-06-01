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

	for (auto const &key : mInputLayouts) {
		if (key.second)
			key.second->Release();
	}
}

HRESULT ShaderHandler::setupVertexShader(ID3D11Device *dev, int key,
	wchar_t *name, char *entryPoint,
	D3D11_INPUT_ELEMENT_DESC *desc, UINT nrOfElements) {

	ID3DBlob* blob = nullptr;
	HRESULT hr;
	hr = D3DCompileFromFile(name, nullptr, nullptr, entryPoint, "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, nullptr);

	if (SUCCEEDED(hr)) {
		hr = dev->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mVertexShaders[key]);
		
		if (SUCCEEDED(hr) && desc != nullptr) {
			hr = dev->CreateInputLayout(desc, nrOfElements, blob->GetBufferPointer(),
				blob->GetBufferSize(), &mInputLayouts[key]);
		}
		
		blob->Release();
	}
		
	return hr;
}

HRESULT ShaderHandler::setupPixelShader(ID3D11Device *dev, int key,
	wchar_t *name, char *entryPoint) {
	ID3DBlob* blob = nullptr;
	HRESULT hr = D3DCompileFromFile(name, nullptr, nullptr, entryPoint, "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, nullptr);

	if (SUCCEEDED(hr)) {
		hr = dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mPixelShaders[key]);
		blob->Release();
	}
		
	return hr;
}

HRESULT ShaderHandler::setupGeometryShader(ID3D11Device *dev, int key,
	wchar_t *name, char *entryPoint) {
	ID3DBlob* blob = nullptr;
	HRESULT hr = D3DCompileFromFile(name, nullptr, nullptr, entryPoint, "gs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, nullptr);

	if (SUCCEEDED(hr)) {
		hr = dev->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &mGeometryShaders[key]);
		blob->Release();
	}
		
	return hr;
}

// key = -1 unbinds the shader
void ShaderHandler::setVertexShader(ID3D11DeviceContext *context, int key) {
	context->VSSetShader(key == UNBIND_SHADER ? nullptr :
		mVertexShaders[key], nullptr, 0);
}

// key = -1 unbinds the shader
void ShaderHandler::setPixelShader(ID3D11DeviceContext *context, int key) {
	context->PSSetShader(key == UNBIND_SHADER ? nullptr :
		mPixelShaders[key], nullptr, 0);
}

// key = -1 unbinds the shader
void ShaderHandler::setGeometryShader(ID3D11DeviceContext *context, int key) {
	context->GSSetShader(key == UNBIND_SHADER ? nullptr :
		mGeometryShaders[key], nullptr, 0);
}

// key = -1 unbinds the shader
void ShaderHandler::setShaders(ID3D11DeviceContext *context, int vsKey, int psKey, int gsKey) {
	// This error message is just a warning, if you unbind the vertex shader things will not work out very well if another vertex shader is not bound
	if (mVertexShaders.find(vsKey) == mVertexShaders.end())
		MessageBox(0, L"Ye, that is (probably) not going to work (No working vertex shader key)", L"Warning!", 0);
	context->VSSetShader(vsKey == UNBIND_SHADER ? nullptr :
		mVertexShaders[vsKey], nullptr, 0);
	context->GSSetShader(gsKey == UNBIND_SHADER ? nullptr :
		mGeometryShaders[gsKey], nullptr, 0);
	context->PSSetShader(psKey == UNBIND_SHADER ? nullptr :
		mPixelShaders[psKey], nullptr, 0);
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

ID3D11InputLayout* ShaderHandler::getInputLayout(int key) {
	return mInputLayouts[key];
}