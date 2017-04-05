#ifndef GRAPHICSDATA_H
#define GRAPHICSDATA_H

#include "Direct3DHeader.h"
#include "WICTextureLoader.h"
#include <map>


class GraphicsData
{
private:
	
	std::map<char*, ID3D11Buffer*> mBuffers;
	std::map<char*, ID3D11ShaderResourceView*> mSrvs;

public:
	GraphicsData();
	virtual ~GraphicsData();

	bool loadTexture(char* key, wchar_t* path, ID3D11Device* device);

	HRESULT createConstantBuffer(char* key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);
	HRESULT createVertexBuffer(char* key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);

	ID3D11Buffer* getBuffer(char* key) const;
	ID3D11ShaderResourceView* getSRV(char* key);
};


#endif