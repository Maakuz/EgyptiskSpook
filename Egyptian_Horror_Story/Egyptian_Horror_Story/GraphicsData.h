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
	std::map<int, ID3D11ShaderResourceView*> mSrvs;

	std::map<int, EntityStruct::VertexStruct*> mVertices;
	std::map<int, int> mNrOfVertices;

public:
	GraphicsData();
	GraphicsData(GraphicsData const &other) = delete;
	virtual ~GraphicsData();
	bool operator=(GraphicsData const &other) = delete;

	bool loadTexture(int key, wchar_t* path, ID3D11Device* device);

	HRESULT createConstantBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device, bool isDynamic = false);
	HRESULT createVertexBuffer(int key, UINT size, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device, bool isDynamic = false);
	void createVerticeArray(int key, EntityStruct::VertexStruct* vertices, int nrOfVertices);
	void setNrOfVertices(int key, int nrOfVertices);

	//Adds a cBuffer to that index
	void addConstantBuffer(int key, ID3D11Buffer* buffer);

	ID3D11Buffer* getBuffer(int key);
	ID3D11ShaderResourceView* getSRV(int key);
	EntityStruct::VertexStruct* getVertices(int key);
	int getNrOfVertices(int key);

	std::map<int, ID3D11Buffer*>* getBufferMap();
	std::map<int, ID3D11ShaderResourceView*>* getSrvMap();
	std::map<int, EntityStruct::VertexStruct*>* getVertexMap();
	std::map<int, int>* getNrOfVerticesMap();
};


#endif