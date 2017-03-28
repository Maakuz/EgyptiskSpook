#pragma once
#include "Direct3DHeader.h"
#include <map>

class ShaderHandler {
private:
	std::map<int, ID3D11VertexShader*> mVertexShaders;
	std::map<int, ID3D11GeometryShader*> mGeometryShaders;
	std::map<int, ID3D11PixelShader*> mPixelShaders;
public:
	ShaderHandler();
	ShaderHandler(ShaderHandler const &handler) = delete;
	~ShaderHandler();

	HRESULT setupVertexShader(ID3D11Device *dev, int key,
		wchar_t *name, char *entryPoint);
	HRESULT setupPixelShader(ID3D11Device *dev, int key,
		wchar_t *name, char *entryPoint);
	HRESULT setupGeometryShader(ID3D11Device *dev, int key,
		wchar_t *name, char *entryPoint);

	ID3D11VertexShader* getVertexShader(int key);
	ID3D11GeometryShader* getGeometryShader(int key);
	ID3D11PixelShader* getPixelShader(int key);

	ShaderHandler* operator=(ShaderHandler const &handler) = delete;
};