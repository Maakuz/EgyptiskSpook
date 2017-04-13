#include "FBXLoader.h"
#include <SDL.h>

FbxVector4 FBXLoader::getNormal(int index, FbxGeometryElementNormal* normalElem)
{
	int lNormalIndex = 0;
	//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
	if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
		lNormalIndex = index;

	//reference mode is index-to-direct, get normals by the index-to-direct
	if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
		lNormalIndex = normalElem->GetIndexArray().GetAt(index);

	FbxVector4 norm = normalElem->GetDirectArray().GetAt(lNormalIndex);

	SDL_Log("normals for vertex[%d]: %f %f %f %f \n",
		index, norm[0], norm[1], norm[2], norm[3]);

	return norm;

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

	bool res = importer->Initialize("../Resource/Models/mon.fbx", -1, this->mIOSettings);

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

					FbxVector4* vertices = mesh->GetControlPoints();
					FbxGeometryElementNormal* normalElem = mesh->GetElementNormal();

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
								FbxVector4 norm = this->getNormal(indexByPolygonVertex++, normalElem);

								vertice.normal.x = norm.mData[0];
								vertice.normal.y = norm.mData[1];
								vertice.normal.z = norm.mData[2];

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


								FbxVector4 norm = this->getNormal(indexByPolygonVertex + SPLIT_ARRAY[k], normalElem);

								vertice.normal.x = norm.mData[0];
								vertice.normal.y = norm.mData[1];
								vertice.normal.z = norm.mData[2];

								verticeArray.push_back(vertice);
							}

							indexByPolygonVertex += nrOfVertices;
						}

					}

					//This is working somewhat but not really.
					if (normalElem->GetMappingMode() == FbxGeometryElement::eByControlPoint)
					{
						for (int i = 0; i < mesh->GetControlPointsCount(); i++)
						{
							FbxVector4 norm = this->getNormal(i, normalElem);

							verticeArray[i].normal.x = norm.mData[0];
							verticeArray[i].normal.y = norm.mData[1];
							verticeArray[i].normal.z = norm.mData[2];
						}
					}
				}
			}
		}
	}


	return false;
}
