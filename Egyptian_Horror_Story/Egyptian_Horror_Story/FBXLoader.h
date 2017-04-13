#ifndef FBXLOADER_H
#define FBXLOADER_H
#include "Direct3DHeader.h"

#include "Structs.h"

#include <assert.h>
#include <fbxsdk.h>
#include <vector>

class FBXLoader
{
private:
	FbxManager* mFbxManager;
	FbxIOSettings* mIOSettings;

	const int SPLIT_ARRAY[6] = {0, 1, 2, 2, 3, 0};

	FbxVector4 getNormal(int index, FbxGeometryElementNormal* normalElem);

public:
	FBXLoader();
	virtual ~FBXLoader();

	bool loadMesh(std::vector<EntityStruct::VertexStruct>& verticeArray);
	

};


#endif // !FBXLOADER_H
