#include "FBXLoader.h"

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

	bool res = importer->Initialize("../Resource/Models/mon.FBX", -1, this->mIOSettings);

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

					for (int j = 0; j < mesh->GetPolygonCount(); j++)
					{
						int nrOfVertices = mesh->GetPolygonSize(j);
						assert(nrOfVertices == 3);

						for (int k = 0; k < nrOfVertices; k++)
						{
							int controlPointIndex = mesh->GetPolygonVertex(j, k);

							EntityStruct::VertexStruct vertice;
							vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
							vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
							vertice.pos.z = (float)vertices[controlPointIndex].mData[2];

							verticeArray.push_back(vertice);


						}
					}
				}
			}
		}
	}


	return false;
}
