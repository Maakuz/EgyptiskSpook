#include "FBXLoader.h"
#include <SDL.h>

FbxVector4 FBXLoader::getNormal(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementNormal* normalElem)
{
	int lNormalIndex = 0;
	FbxVector4 norm;

	if (normalElem->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
			lNormalIndex = ctrlPointIndex;

		if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			lNormalIndex = normalElem->GetIndexArray().GetAt(ctrlPointIndex);

		norm = normalElem->GetDirectArray().GetAt(lNormalIndex);

		//SDL_Log("normals for vertex[%d]: %f %f %f %f \n",
			//ctrlPointIndex, norm[0], norm[1], norm[2], norm[3]);
	}

	else if (normalElem->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
			lNormalIndex = polygonVertexIndex;

		if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			lNormalIndex = normalElem->GetIndexArray().GetAt(polygonVertexIndex);

		norm = normalElem->GetDirectArray().GetAt(lNormalIndex);

		//SDL_Log("normals for vertex[%d]: %f %f %f %f \n",
			//polygonVertexIndex, norm[0], norm[1], norm[2], norm[3]);
	}
	

	return norm;

}

FbxVector2 FBXLoader::getUV(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementUV* uvElem)
{
	int uvIndex = 0;
	FbxVector2 uv;

	if (uvElem->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (uvElem->GetReferenceMode() == FbxGeometryElement::eDirect)
			uvIndex = ctrlPointIndex;

		if (uvElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			uvIndex = uvElem->GetIndexArray().GetAt(ctrlPointIndex);

		uv = uvElem->GetDirectArray().GetAt(uvIndex);

		//SDL_Log("UV for vertex[%d]: %f %f \n",
			//ctrlPointIndex, uv[0], uv[1]);
	}

	else if (uvElem->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		uv = uvElem->GetDirectArray().GetAt(polygonVertexIndex);

		//SDL_Log("UV for vertex[%d]: %f %f \n",
		//polygonVertexIndex, uv[0], uv[1]);
	}

	return uv;
}

void FBXLoader::getSkeleton(FbxNode* root)
{
	for (int i = 0; i < root->GetChildCount(); i++)
	{
		FbxNode* currentNode = root->GetChild(i);
		this->recGetSkeleton(currentNode, 0, -1);
	}
}

void FBXLoader::recGetSkeleton(FbxNode* node, int index, int parentIndex)
{
	if (node->GetNodeAttribute() && node->GetNodeAttribute()->GetAttributeType() && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		Joint temp;
		temp.parent = parentIndex;
		temp.name = node->GetName();
		this->mSkeleton.push_back(temp);
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		recGetSkeleton(node->GetChild(i), this->mSkeleton.size(), index);
	}
}

void FBXLoader::setupJoints(FbxNode* root)
{
	FbxMesh* mesh = root->GetMesh();

	int nrOfDeformations = mesh->GetDeformerCount();

	//Probably maybe not needed
	const FbxVector4 lT = root->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 lR = root->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 lS = root->GetGeometricScaling(FbxNode::eSourcePivot);

	FbxAMatrix geometryTransform = FbxAMatrix(lT, lR, lS);
	//end

	for (int i = 0; i < nrOfDeformations; i++)
	{
		FbxSkin* skin = reinterpret_cast<FbxSkin*>(mesh->GetDeformer(i, FbxDeformer::eSkin));

		if (skin)
		{
			int nrOfClusters = skin->GetClusterCount();
			for (int j = 0; j < nrOfClusters; j++)
			{
				FbxCluster* cluster = skin->GetCluster(j);
				int index = this->findJoint(cluster->GetLink()->GetName());

				FbxAMatrix transform;
				FbxAMatrix transformLink;

				cluster->GetTransformMatrix(transform);
				cluster->GetTransformLinkMatrix(transformLink);
				this->mSkeleton[index].globalBindInverse = transformLink.Inverse() * transform * geometryTransform;
				this->mSkeleton[index].node = cluster->GetLink();
			}
		}
	}

}

int FBXLoader::findJoint(std::string name)
{
	int res = -1;
	
	for (int i = 0; i < this->mSkeleton.size() && res == -1; i++)
	{
		if (this->mSkeleton[i].name == name)
			res = i;
	}

	return res;
}

bool FBXLoader::loadVertices(std::vector<EntityStruct::VertexStruct>& vertexArray, FbxMesh* mesh)
{
	FbxVector4* vertices = mesh->GetControlPoints();
	FbxGeometryElementNormal* normalElem = mesh->GetElementNormal();
	FbxGeometryElementUV* uvElem = mesh->GetElementUV();


	int indexByPolygonVertex = 0;

	for (int j = 0; j < mesh->GetPolygonCount(); j++)
	{
		int nrOfVertices = mesh->GetPolygonSize(j);

		assert(nrOfVertices == 3 || nrOfVertices == 4);

		if (nrOfVertices == 3)
		{
			for (int k = 0; k < nrOfVertices; k++)
			{
				int controlPointIndex = mesh->GetPolygonVertex(j, k);

				EntityStruct::VertexStruct vertex;
				vertex.pos.x = (float)vertices[controlPointIndex].mData[0];
				vertex.pos.y = (float)vertices[controlPointIndex].mData[1];
				vertex.pos.z = (float)vertices[controlPointIndex].mData[2];
				
				

				//Got normals of each polygon-vertex.
				FbxVector4 norm = this->getNormal(controlPointIndex, indexByPolygonVertex, normalElem);

				vertex.normal.x = (float)norm.mData[0];
				vertex.normal.y = (float)norm.mData[1];
				vertex.normal.z = (float)norm.mData[2];



				//get the uv
				FbxVector2 uv = this->getUV(controlPointIndex, mesh->GetTextureUVIndex(j, k), uvElem);

				vertex.uv.x = (float)uv.mData[0];
				vertex.uv.y =1.f - (float)uv.mData[1];

				vertexArray.push_back(vertex);

				indexByPolygonVertex++;
			}

		}

		if (nrOfVertices == 4)
		{
			for (int k = 0; k < 6; k++)
			{
				int controlPointIndex = mesh->GetPolygonVertex(j, SPLIT_ARRAY[k]);

				EntityStruct::VertexStruct vertice;
				vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
				vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
				vertice.pos.z = (float)vertices[controlPointIndex].mData[2];


				FbxVector4 norm = this->getNormal(controlPointIndex, indexByPolygonVertex + SPLIT_ARRAY[k], normalElem);

				vertice.normal.x = (float)norm.mData[0];
				vertice.normal.y = (float)norm.mData[1];
				vertice.normal.z = (float)norm.mData[2];


				//get the uv THIS IS PROBABLY WRoNG
				FbxVector2 uv = this->getUV(controlPointIndex, indexByPolygonVertex + SPLIT_ARRAY[k], uvElem);

				vertice.uv.x = (float)uv.mData[0];
				vertice.uv.y =1.f - (float)uv.mData[1];

				vertexArray.push_back(vertice);
			}

			indexByPolygonVertex += nrOfVertices;
		}

	}

	return true;
}

bool FBXLoader::loadVertices(std::vector<EntityStruct::SkinnedVertexStruct>& vertexArray, FbxMesh* mesh)
{
	FbxVector4* vertices = mesh->GetControlPoints();
	FbxGeometryElementNormal* normalElem = mesh->GetElementNormal();
	FbxGeometryElementUV* uvElem = mesh->GetElementUV();


	int indexByPolygonVertex = 0;

	for (int j = 0; j < mesh->GetPolygonCount(); j++)
	{
		int nrOfVertices = mesh->GetPolygonSize(j);

		assert(nrOfVertices == 3 || nrOfVertices == 4);

		if (nrOfVertices == 3)
		{
			for (int k = 0; k < nrOfVertices; k++)
			{
				int controlPointIndex = mesh->GetPolygonVertex(j, k);

				EntityStruct::SkinnedVertexStruct vertex;
				vertex.pos.x = (float)vertices[controlPointIndex].mData[0];
				vertex.pos.y = (float)vertices[controlPointIndex].mData[1];
				vertex.pos.z = (float)vertices[controlPointIndex].mData[2];



				//Got normals of each polygon-vertex.
				FbxVector4 norm = this->getNormal(controlPointIndex, indexByPolygonVertex, normalElem);

				vertex.normal.x = (float)norm.mData[0];
				vertex.normal.y = (float)norm.mData[1];
				vertex.normal.z = (float)norm.mData[2];



				//get the uv
				FbxVector2 uv = this->getUV(controlPointIndex, mesh->GetTextureUVIndex(j, k), uvElem);

				vertex.uv.x = (float)uv.mData[0];
				vertex.uv.y = 1.f - (float)uv.mData[1];

				vertexArray.push_back(vertex);

				indexByPolygonVertex++;
			}

		}

		if (nrOfVertices == 4)
		{
			for (int k = 0; k < 6; k++)
			{
				int controlPointIndex = mesh->GetPolygonVertex(j, SPLIT_ARRAY[k]);

				EntityStruct::SkinnedVertexStruct vertice;
				vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
				vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
				vertice.pos.z = (float)vertices[controlPointIndex].mData[2];


				FbxVector4 norm = this->getNormal(controlPointIndex, indexByPolygonVertex + SPLIT_ARRAY[k], normalElem);

				vertice.normal.x = (float)norm.mData[0];
				vertice.normal.y = (float)norm.mData[1];
				vertice.normal.z = (float)norm.mData[2];


				//get the uv THIS IS PROBABLY WRoNG
				FbxVector2 uv = this->getUV(controlPointIndex, indexByPolygonVertex + SPLIT_ARRAY[k], uvElem);

				vertice.uv.x = (float)uv.mData[0];
				vertice.uv.y = 1.f - (float)uv.mData[1];

				vertexArray.push_back(vertice);
			}

			indexByPolygonVertex += nrOfVertices;
		}

	}

	return true;
}

FBXLoader::FBXLoader()
{
	this->mFbxManager = nullptr;
}

FBXLoader::~FBXLoader()
{

}

bool FBXLoader::loadMesh(std::vector<EntityStruct::VertexStruct>& verticeArray)
{

	if (this->mFbxManager == nullptr)
	{
		this->mFbxManager = FbxManager::Create();

		this->mIOSettings = FbxIOSettings::Create(this->mFbxManager, IOSROOT);
		this->mFbxManager->SetIOSettings(this->mIOSettings);
	}

	FbxImporter* importer = FbxImporter::Create(this->mFbxManager, "");
	FbxScene* scene = FbxScene::Create(this->mFbxManager, "");

	bool res = importer->Initialize("../Resource/Models/ModelTestTri.fbx", -1, this->mIOSettings);

	if (!res)
		exit(-88);

	res = importer->Import(scene);

	if (!res)
		exit(-89);

	importer->Destroy();

	FbxNode* RootNode = scene->GetRootNode();

	if (RootNode)
	{
		for (int i = 0; i < RootNode->GetChildCount(); i++)
		{
			FbxNode* childNode = RootNode->GetChild(i);

			
			if (childNode->GetNodeAttribute() != NULL)
			{
				FbxNodeAttribute::EType attributeType = childNode->GetNodeAttribute()->GetAttributeType();

				if (attributeType == FbxNodeAttribute::eMesh)
				{
					FbxMesh* mesh = (FbxMesh*)childNode->GetNodeAttribute();

					this->loadVertices(verticeArray, mesh);
				}
			}
		}
	}

	return false;
}

bool FBXLoader::loadSkinnedMesh(std::vector<EntityStruct::SkinnedVertexStruct>& verticeArray)
{
	if (this->mFbxManager == nullptr)
	{
		this->mFbxManager = FbxManager::Create();

		this->mIOSettings = FbxIOSettings::Create(this->mFbxManager, IOSROOT);
		this->mFbxManager->SetIOSettings(this->mIOSettings);
	}

	FbxImporter* importer = FbxImporter::Create(this->mFbxManager, "");
	FbxScene* scene = FbxScene::Create(this->mFbxManager, "");

	bool res = importer->Initialize("../Resource/Models/dargon.fbx", -1, this->mIOSettings);

	if (!res)
		exit(-88);

	res = importer->Import(scene);

	if (!res)
		exit(-89);

	importer->Destroy();

	FbxNode* RootNode = scene->GetRootNode();

	if (RootNode)
	{
		for (int i = 0; i < RootNode->GetChildCount(); i++)
		{
			FbxNode* childNode = RootNode->GetChild(i);


			if (childNode->GetNodeAttribute() != NULL)
			{
				FbxNodeAttribute::EType attributeType = childNode->GetNodeAttribute()->GetAttributeType();

				if (attributeType == FbxNodeAttribute::eMesh)
				{
					FbxMesh* mesh = (FbxMesh*)childNode->GetNodeAttribute();

					this->loadVertices(verticeArray, mesh);
				}
			}
		}
	}

	this->getSkeleton(RootNode);

	return false;
}
