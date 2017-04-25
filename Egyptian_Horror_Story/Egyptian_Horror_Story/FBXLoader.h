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

	struct KeyFrame
	{
		int test;
	};
	
	struct Joint
	{
		int parent;
		std::string name;
		FbxAMatrix globalBindInverse;
		FbxNode* node;
	};



	std::vector<Joint> mSkeleton;
	std::vector<std::vector<EntityStruct::weightAndIndex>> mVertexWeights;

	FbxManager* mFbxManager;
	FbxIOSettings* mIOSettings;
	FbxScene* mScene;
	float mAnimLength;

	const int SPLIT_ARRAY[6] = {0, 1, 2, 2, 3, 0};

	FbxVector4 getNormal(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementNormal* normalElem);
	FbxVector2 getUV(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementUV* uvElem);

	void getSkeleton(FbxNode* root);
	void recGetSkeleton(FbxNode* node, int index, int parentIndex);
	void setupJoints(FbxNode* root);
	int findJoint(std::string name);


	bool loadVertices(std::vector<EntityStruct::VertexStruct>& verticeArray, FbxMesh* mesh);
	bool loadVertices(std::vector<EntityStruct::SkinnedVertexStruct>& verticeArray, FbxMesh* mesh);

public:
	FBXLoader();
	virtual ~FBXLoader();


	bool loadMesh(std::vector<EntityStruct::VertexStruct>& verticeArray, std::string filename);
	bool loadSkinnedMesh(std::vector<EntityStruct::SkinnedVertexStruct>& verticeArray, std::string filename);
	

};


#endif // !FBXLOADER_H
