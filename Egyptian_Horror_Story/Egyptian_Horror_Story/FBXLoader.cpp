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

	bool res = importer->Initialize("../Resource/Models/9v.fbx", -1, this->mIOSettings);

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

					

					for (int j = 0; j < mesh->GetPolygonCount(); j++)
					{
						int nrOfVertices = mesh->GetPolygonSize(j);

						if (nrOfVertices == 3)
						{
							for (int k = 0; k < nrOfVertices; k++)
							{
								int controlPointIndex = mesh->GetPolygonVertex(j, k);

								EntityStruct::VertexStruct vertice;
								vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
								vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
								vertice.pos.z = (float)vertices[controlPointIndex].mData[2];

								int lNormalIndex = 0;

								//reference mode is direct, the normal index is same as vertex index.
								//get normals by the index of control vertex
								if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
									lNormalIndex = i;

								//reference mode is index-to-direct, get normals by the index-to-direct
								if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
									lNormalIndex = normalElem->GetIndexArray().GetAt(i);

								//Got normals of each vertex.
								FbxVector4 lNormal = normalElem->GetDirectArray().GetAt(lNormalIndex);

								vertice.normal.x = lNormal.mData[0];
								vertice.normal.y = lNormal.mData[1];
								vertice.normal.z = lNormal.mData[2];

								verticeArray.push_back(vertice);
							}

						}

						if (nrOfVertices == 4)
						{
							int controlPointIndex = mesh->GetPolygonVertex(j, 0);

							//GÖR DETTA FINT
							if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
								lNormalIndex = i;

							//reference mode is index-to-direct, get normals by the index-to-direct
							if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
								lNormalIndex = normalElem->GetIndexArray().GetAt(i);


							EntityStruct::VertexStruct vertice;
							vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
							vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
							vertice.pos.z = (float)vertices[controlPointIndex].mData[2];


							FbxVector4 norm = normalElem->GetDirectArray().GetAt(controlPointIndex);
							vertice.normal.x = norm.mData[0];
							vertice.normal.y = norm.mData[1];
							vertice.normal.z = norm.mData[2];

							verticeArray.push_back(vertice);

							controlPointIndex = mesh->GetPolygonVertex(j, 1);

							vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
							vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
							vertice.pos.z = (float)vertices[controlPointIndex].mData[2];

							norm = normalElem->GetDirectArray().GetAt(controlPointIndex);
							vertice.normal.x = norm.mData[0];
							vertice.normal.y = norm.mData[1];
							vertice.normal.z = norm.mData[2];

							verticeArray.push_back(vertice);

							controlPointIndex = mesh->GetPolygonVertex(j, 2);

							vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
							vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
							vertice.pos.z = (float)vertices[controlPointIndex].mData[2];

							norm = normalElem->GetDirectArray().GetAt(controlPointIndex);
							vertice.normal.x = norm.mData[0];
							vertice.normal.y = norm.mData[1];
							vertice.normal.z = norm.mData[2];

							verticeArray.push_back(vertice);

							controlPointIndex = mesh->GetPolygonVertex(j, 2);

							vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
							vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
							vertice.pos.z = (float)vertices[controlPointIndex].mData[2];

							norm = normalElem->GetDirectArray().GetAt(controlPointIndex);
							vertice.normal.x = norm.mData[0];
							vertice.normal.y = norm.mData[1];
							vertice.normal.z = norm.mData[2];

							verticeArray.push_back(vertice);

							controlPointIndex = mesh->GetPolygonVertex(j, 3);

							vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
							vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
							vertice.pos.z = (float)vertices[controlPointIndex].mData[2];

							norm = normalElem->GetDirectArray().GetAt(controlPointIndex);
							vertice.normal.x = norm.mData[0];
							vertice.normal.y = norm.mData[1];
							vertice.normal.z = norm.mData[2];

							verticeArray.push_back(vertice);

							controlPointIndex = mesh->GetPolygonVertex(j, 0);

							vertice.pos.x = (float)vertices[controlPointIndex].mData[0];
							vertice.pos.y = (float)vertices[controlPointIndex].mData[1];
							vertice.pos.z = (float)vertices[controlPointIndex].mData[2];

							norm = normalElem->GetDirectArray().GetAt(controlPointIndex);
							vertice.normal.x = norm.mData[0];
							vertice.normal.y = norm.mData[1];
							vertice.normal.z = norm.mData[2];

							verticeArray.push_back(vertice);

							//int lNormalIndex = 0;

							////reference mode is direct, the normal index is same as vertex index.
							////get normals by the index of control vertex
							//if (normalElem->GetReferenceMode() == FbxGeometryElement::eDirect)
							//	lNormalIndex = i;

							////reference mode is index-to-direct, get normals by the index-to-direct
							//if (normalElem->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
							//	lNormalIndex = normalElem->GetIndexArray().GetAt(i);

							////Got normals of each vertex.
							//FbxVector4 lNormal = normalElem->GetDirectArray().GetAt(lNormalIndex);

							//vertice.normal.x = lNormal.mData[0];
							//vertice.normal.y = lNormal.mData[1];
							//vertice.normal.z = lNormal.mData[2];

							//verticeArray.push_back(vertice);
						}

					}
				
				
}
			}
		}
	}


	return false;
}
