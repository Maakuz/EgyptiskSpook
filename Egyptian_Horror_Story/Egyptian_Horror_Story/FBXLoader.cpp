#include "FBXLoader.h"
#include <SDL.h>

FbxVector4 FBXLoader::getNormal(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementNormal* normalElem)
{
	int lNormalIndex = 0;
	FbxVector4 norm;

	if (normalElem->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
		if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
			lNormalIndex = ctrlPointIndex;

		//reference mode is index-to-direct, get normals by the index-to-direct
		if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			lNormalIndex = normalElem->GetIndexArray().GetAt(ctrlPointIndex);

		norm = normalElem->GetDirectArray().GetAt(lNormalIndex);

		//SDL_Log("normals for vertex[%d]: %f %f %f %f \n",
			//ctrlPointIndex, norm[0], norm[1], norm[2], norm[3]);
	}

	else if (normalElem->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
		if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
			lNormalIndex = polygonVertexIndex;

		//reference mode is index-to-direct, get normals by the index-to-direct
		if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			lNormalIndex = normalElem->GetIndexArray().GetAt(polygonVertexIndex);

		norm = normalElem->GetDirectArray().GetAt(lNormalIndex);

		//SDL_Log("normals for vertex[%d]: %f %f %f %f \n",
			//polygonVertexIndex, norm[0], norm[1], norm[2], norm[3]);
	}
	

	return norm;

}

FbxVector2 FBXLoader::getUV(int ctrlPointIndex, int polygonVertexIndex, FbxGeometryElementUV * uvElem)
{
	int uvIndex = 0;
	FbxVector2 uv;

	if (uvElem->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
		if (uvElem->GetReferenceMode() == FbxGeometryElement::eDirect)
			uvIndex = ctrlPointIndex;

		//reference mode is index-to-direct, get normals by the index-to-direct
		if (uvElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			uvIndex = uvElem->GetIndexArray().GetAt(ctrlPointIndex);

		uv = uvElem->GetDirectArray().GetAt(uvIndex);

		//SDL_Log("UV for vertex[%d]: %f %f %f %f \n",
			//ctrlPointIndex, uv[0], uv[1]);
	}

	else if (uvElem->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
		if (uvElem->GetReferenceMode() == FbxGeometryElement::eDirect)
			uvIndex = polygonVertexIndex;

		//reference mode is index-to-direct, get normals by the index-to-direct
		if (uvElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			uvIndex = uvElem->GetIndexArray().GetAt(polygonVertexIndex);

		uv = uvElem->GetDirectArray().GetAt(uvIndex);

		//SDL_Log("UV for vertex[%d]: %f %f %f %f \n",
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
	if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
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

bool FBXLoader::loadVertices(std::vector<EntityStruct::VertexStruct>& verticeArray, FbxMesh* mesh)
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

				EntityStruct::VertexStruct vertice;
				vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
				vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
				vertice.pos.z = (float)vertices[controlPointIndex].mData[2];
				
				

				//Got normals of each polygon-vertex.
				FbxVector4 norm = this->getNormal(controlPointIndex, indexByPolygonVertex, normalElem);

				vertice.normal.x = (float)norm.mData[0];
				vertice.normal.y = (float)norm.mData[1];
				vertice.normal.z = (float)norm.mData[2];



				//get the uv
				FbxVector2 uv = this->getUV(controlPointIndex, indexByPolygonVertex++, uvElem);

				vertice.uv.x = (float)uv.mData[0];
				vertice.uv.y = (float)uv.mData[1];

				verticeArray.push_back(vertice);
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


				FbxVector4 norm = this->getNormal(controlPointIndex ,indexByPolygonVertex + SPLIT_ARRAY[k], normalElem);

				vertice.normal.x = (float)norm.mData[0];
				vertice.normal.y = (float)norm.mData[1];
				vertice.normal.z = (float)norm.mData[2];


				//get the uv
				FbxVector2 uv = this->getUV(controlPointIndex, indexByPolygonVertex + SPLIT_ARRAY[k], uvElem);

				vertice.uv.x = (float)uv.mData[0];
				vertice.uv.y = (float)uv.mData[1];

				verticeArray.push_back(vertice);
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

	bool res = importer->Initialize("../Resource/Models/sam.fbx", -1, this->mIOSettings);

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
