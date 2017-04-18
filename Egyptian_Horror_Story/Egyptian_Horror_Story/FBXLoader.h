#ifndef FBXLOADER_H
#define FBXLOADER_H
#include "Direct3DHeader.h"

#include "Structs.h"

#include <assert.h>
#include <fbxsdk.h>
#include <vector>

#include <string>



class FBXLoader
{
private:
	
	struct Joint
	{
		int parent;
		std::string name;
	};

	std::vector<Joint> mSkeleton;

	FbxManager* mFbxManager;
	FbxIOSettings* mIOSettings;

	const int SPLIT_ARRAY[6] = {0, 1, 2, 2, 3, 0};

	FbxVector4 getNormal(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementNormal* normalElem);
	FbxVector2 getUV(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementUV* uvElem);

	void getSkeleton(FbxNode* root);
	void recGetSkeleton(FbxNode* node, int index, int parentIndex);

	bool loadVertices(std::vector<EntityStruct::VertexStruct>& verticeArray, FbxMesh* mesh);

public:
	FBXLoader();
	virtual ~FBXLoader();

	bool loadMesh(std::vector<EntityStruct::VertexStruct>& verticeArray);
	

};


#endif // !FBXLOADER_H
