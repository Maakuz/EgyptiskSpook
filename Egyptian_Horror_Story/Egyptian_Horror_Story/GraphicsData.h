#ifndef GRAPHICSDATA_H
#define GRAPHICSDATA_H

#include "Direct3DHeader.h"
#include "WICTextureLoader.h"
#include <map>


class GraphicsData
{
private:
	
	std::map<int, ID3D11Buffer*> mBuffers;
	std::map<int, ID3D11ShaderResourceView*> mSrvs;

public:
	GraphicsData();
	GraphicsData(GraphicsData const &other) = delete;
	virtual ~GraphicsData();
	bool operator=(GraphicsData const &other) = delete;

	bool loadTexture(int key, wchar_t* path, ID3D11Device* device);

	HRESULT createConstantBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);
	HRESULT createVertexBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);

	ID3D11Buffer* getBuffer(int key) const;
	ID3D11ShaderResourceView* getSRV(int key);
};


#endif