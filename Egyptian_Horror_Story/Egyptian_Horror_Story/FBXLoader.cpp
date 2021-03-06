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

bool FBXLoader::loadVertices(std::vector<VertexStruct>& vertexArray, FbxMesh* mesh)
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

				VertexStruct vertex;
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

				VertexStruct vertice;
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

FBXLoader::FBXLoader()
{
	this->mFbxManager = nullptr;
}

FBXLoader::~FBXLoader()
{
}

bool FBXLoader::loadMesh(std::vector<VertexStruct>& verticeArray, std::string filename)
{

	if (this->mFbxManager == nullptr)
	{
		this->mFbxManager = FbxManager::Create();

		this->mIOSettings = FbxIOSettings::Create(this->mFbxManager, IOSROOT);
		this->mFbxManager->SetIOSettings(this->mIOSettings);
	}

	FbxImporter* importer = FbxImporter::Create(this->mFbxManager, "");
	mScene = FbxScene::Create(this->mFbxManager, "");

	std::string temp = "../Resource/Models/" + filename;


	bool res = importer->Initialize(temp.c_str(), -1, this->mIOSettings);

	if (!res)
		exit(-88);

	res = importer->Import(mScene);

	if (!res)
		exit(-89);

	importer->Destroy();

	FbxNode* RootNode = mScene->GetRootNode();

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