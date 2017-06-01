#ifndef GRAPHICSDATA_H
#define GRAPHICSDATA_H

#include "Direct3DHeader.h"
#include "WICTextureLoader.h"
#include "Structs.h"
#include <map>
#include <string>

#define TEXTUREPATH L"../Resource/Textures/"


class GraphicsData
{
private:
	std::map<int, ID3D11Buffer*> mBuffers;
	std::map<int, ID3D11Buffer*> mCBuffers;
	std::map<int, ID3D11ShaderResourceView*> mSrvs;

	std::map<int, VertexStruct*> mVertices;
	std::map<int, int> mNrOfVertices;

public:
	GraphicsData();
	GraphicsData(GraphicsData const &other) = delete;
	virtual ~GraphicsData();
	bool operator=(GraphicsData const &other) = delete;

	bool loadTexture(int key, wchar_t* path, ID3D11Device* device);

	HRESULT createConstantBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device, bool isDynamic = false);
	HRESULT createVertexBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device, bool isDynamic = false);
	void createVerticeArray(int key, VertexStruct* vertices, int nrOfVertices);
	void setNrOfVertices(int key, int nrOfVertices);

	void removeData(int key);

	ID3D11Buffer* getVertexBuffer(int key);
	ID3D11Buffer* getConstantBuffer(int key);
	ID3D11ShaderResourceView* getSRV(int key);
	VertexStruct* getVertices(int key);
	int getNrOfVertices(int key);

	std::map<int, ID3D11Buffer*>* getVertexBufferMap();
	std::map<int, ID3D11Buffer*>* getConstantBufferMap();
	std::map<int, ID3D11ShaderResourceView*>* getSrvMap();
	std::map<int, VertexStruct*>* getVertexMap();
	std::map<int, int>* getNrOfVerticesMap();
};


#endif