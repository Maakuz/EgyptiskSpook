#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include "Direct3DHeader.h"
#include <map>

class ShaderHandler {
public:
	static const int UNBIND_SHADER = -1;
private:
	std::map<int, ID3D11VertexShader*> mVertexShaders;
	std::map<int, ID3D11GeometryShader*> mGeometryShaders;
	std::map<int, ID3D11PixelShader*> mPixelShaders;
	std::map<int, ID3D11InputLayout*> mInputLayouts;
public:
	ShaderHandler();
	ShaderHandler(ShaderHandler const &handler) = delete;
	~ShaderHandler();

	// input layout & vertex shader have same key
	HRESULT setupVertexShader(ID3D11Device *dev, int key,
		wchar_t *name, char *entryPoint, D3D11_INPUT_ELEMENT_DESC *desc = nullptr, UINT nrOfElements = 0);
	HRESULT setupPixelShader(ID3D11Device *dev, int key,
		wchar_t *name, char *entryPoint);
	HRESULT setupGeometryShader(ID3D11Device *dev, int key,
		wchar_t *name, char *entryPoint);

	void setVertexShader(ID3D11DeviceContext *context, int key);
	void setPixelShader(ID3D11DeviceContext *context, int key);
	void setGeometryShader(ID3D11DeviceContext *context, int key);
	void setShaders(ID3D11DeviceContext *context, int vsKey, int psKey, int gsKey);

	ID3D11VertexShader* getVertexShader(int key);
	ID3D11GeometryShader* getGeometryShader(int key);
	ID3D11PixelShader* getPixelShader(int key);
	ID3D11InputLayout* getInputLayout(int key);

	ShaderHandler* operator=(ShaderHandler const &handler) = delete;
};

#endif