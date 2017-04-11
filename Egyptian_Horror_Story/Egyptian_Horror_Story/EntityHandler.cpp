#include "EntityHandler.h"

EntityHandler::EntityHandler()
{
	this->mEntityRenderer = new EntityRenderer();
}

EntityHandler::~EntityHandler()
{
	delete this->mPlayer;

	for (size_t i = 0; i < this->mEntities.size(); i++)
	{
		delete this->mEntities[i];
	}
}

void EntityHandler::setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera, GraphicsData* gData)
{
	this->mPlayer = new Player(camera, device, context, this->mNrOfKeys++, gData);
	this->mPlayer->setPosition(DirectX::SimpleMath::Vector3(0, 0, -5));
}

void EntityHandler::setupEntities(ID3D11Device* device)
{
	//test
	/*for (size_t j = 0; j < 3; j++)
	{
		for (size_t i = 0; i < 5; i++)
		{*/
			Wall* wall = new Wall(
				DirectX::SimpleMath::Vector3(-10.f, -2.f, 10.f),
				DirectX::SimpleMath::Vector3(7.f, 0.f, 0.f),
				DirectX::SimpleMath::Vector3(0.f, 6.f, 0.f),
				DirectX::SimpleMath::Vector3(0.f, 0.f, 2.f), this->mNrOfKeys++);

			EntityStruct::VertexStruct testData[] = {
				DirectX::SimpleMath::Vector3(-10.f , -2.f , 10.f),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(0.f, 1.f),

				DirectX::SimpleMath::Vector3(-10.f, 4.f , 10.f),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(0.f, 0.f),

				DirectX::SimpleMath::Vector3(-3 , -2.f , 10.f),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-3  , -2.f  , 10.f),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-3  , 4.f  , 10.f),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(1.f, 0.f),

				DirectX::SimpleMath::Vector3(-10.f , 4.f , 10.f),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(0.f, 0.f)
			};
			this->mEntityRenderer->loadObject(device, wall->getKey(), testData, 6, L"../Resource/Textures/pyramidStone.png");

			this->mEntities.push_back(wall);
	/*	}
	}*/

	/*for (size_t j = 0; j < 3; j++)
	{
		for (size_t i = 0; i < 25; i++)
		{*/
			 wall = new Wall(
				DirectX::SimpleMath::Vector3(-3, -2.f, 10.f),
				DirectX::SimpleMath::Vector3(2.f, 0.f, 0.f),
				DirectX::SimpleMath::Vector3(0.f, 6.f, 0.f),
				DirectX::SimpleMath::Vector3(0.f, 0.f, 53.f), this->mNrOfKeys++);


			EntityStruct::VertexStruct testData3[] = {
				DirectX::SimpleMath::Vector3(-3, -2.f , 10.f),
				DirectX::SimpleMath::Vector3(-1, 0, 0),
				DirectX::SimpleMath::Vector2(0.f, 1.f),

				DirectX::SimpleMath::Vector3(-3, 4.f , 10.f ),
				DirectX::SimpleMath::Vector3(-1, 0, 0),
				DirectX::SimpleMath::Vector2(0.f, 0.f),

				DirectX::SimpleMath::Vector3(-3, -2.f , -43 ),
				DirectX::SimpleMath::Vector3(-1, 0, 0),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-3, -2.f , -43 ),
				DirectX::SimpleMath::Vector3(-1, 0, 0),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-3, 4.f , -43),
				DirectX::SimpleMath::Vector3(-1, 0, 0),
				DirectX::SimpleMath::Vector2(1.f, 0.f),

				DirectX::SimpleMath::Vector3(-3, 4.f , 10.f ),
				DirectX::SimpleMath::Vector3(-1, 0, 0),
				DirectX::SimpleMath::Vector2(0.f, 0.f)
			};
			this->mEntityRenderer->loadObject(device, wall->getKey(), testData3, 6, L"../Resource/Textures/pyramidStone.png");

			this->mEntities.push_back(wall);
	/*	}
	}*/
	
	/*for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 3; j++) {*/
			 wall = new Wall(
				DirectX::SimpleMath::Vector3(-10, -2 , -50 ),
				DirectX::SimpleMath::Vector3(0.f, 0.f, 2.f),
				DirectX::SimpleMath::Vector3(0.f, 2.f, 0.f),
				DirectX::SimpleMath::Vector3(2.f, 0.f, 0.f), this->mNrOfKeys++);

			EntityStruct::VertexStruct testData4[] = {
				DirectX::SimpleMath::Vector3(-10, -2 , -50),
				DirectX::SimpleMath::Vector3(1, 0, 0),
				DirectX::SimpleMath::Vector2(0.f, 1.f),

				DirectX::SimpleMath::Vector3(-10, 4, -50 ),
				DirectX::SimpleMath::Vector3(1, 0, 0),
				DirectX::SimpleMath::Vector2(0.f, 0.f),

				DirectX::SimpleMath::Vector3(-10, -2 , 10 ),
				DirectX::SimpleMath::Vector3(1, 0, 0),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-10, -2 , 10 ),
				DirectX::SimpleMath::Vector3(1, 0, 0),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-10, 4 , 10 ),
				DirectX::SimpleMath::Vector3(1, 0, 0),
				DirectX::SimpleMath::Vector2(1.f, 0.f),

				DirectX::SimpleMath::Vector3(-10, 4 , -50 ),
				DirectX::SimpleMath::Vector3(1, 0, 0),
				DirectX::SimpleMath::Vector2(0.f, 0.f)
			};
			this->mEntityRenderer->loadObject(device, wall->getKey(), testData4, 6, L"../Resource/Textures/pyramidStone.png");
			this->mEntities.push_back(wall);
	/*	}
	}*/


	//for (int i = 0; i < 30; i++) {
	//	for (int j = 0; j < 3; j++) {
			 wall = new Wall(
				DirectX::SimpleMath::Vector3(-10, -2 , -50),
				DirectX::SimpleMath::Vector3(0.f, 0.f, 2.f),
				DirectX::SimpleMath::Vector3(0.f, 2.f, 0.f),
				DirectX::SimpleMath::Vector3(2.f, 0.f, 0.f), this->mNrOfKeys++);

			EntityStruct::VertexStruct testData5[] = {
				DirectX::SimpleMath::Vector3(70, -2 , -50),
				DirectX::SimpleMath::Vector3(0, 0, 1),
				DirectX::SimpleMath::Vector2(0.f, 1.f),

				DirectX::SimpleMath::Vector3(70 , 4 , -50 ),
				DirectX::SimpleMath::Vector3(0, 0, 1),
				DirectX::SimpleMath::Vector2(0.f, 0.f),

				DirectX::SimpleMath::Vector3(-10 , -2, -50 ),
				DirectX::SimpleMath::Vector3(0, 0, 1),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-10 , -2 , -50 ),
				DirectX::SimpleMath::Vector3(0, 0, 1),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(-10, 4, -50 ),
				DirectX::SimpleMath::Vector3(0, 0, 1),
				DirectX::SimpleMath::Vector2(1.f, 0.f),

				DirectX::SimpleMath::Vector3(70 , 4 , -50 ),
				DirectX::SimpleMath::Vector3(0, 0, 1),
				DirectX::SimpleMath::Vector2(0.f, 0.f)
			};
			this->mEntityRenderer->loadObject(device, wall->getKey(), testData5, 6, L"../Resource/Textures/pyramidStone.png");
			this->mEntities.push_back(wall);
	/*	}
	}*/

			wall = new Wall(
				DirectX::SimpleMath::Vector3(-10, -2, -50),
				DirectX::SimpleMath::Vector3(0.f, 0.f, 2.f),
				DirectX::SimpleMath::Vector3(0.f, 2.f, 0.f),
				DirectX::SimpleMath::Vector3(2.f, 0.f, 0.f), this->mNrOfKeys++);

			EntityStruct::VertexStruct testData6[] = {
				DirectX::SimpleMath::Vector3(-3, -2 , -43),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(0.f, 1.f),

				DirectX::SimpleMath::Vector3(-3 , 4 , -43),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(0.f, 0.f),

				DirectX::SimpleMath::Vector3(63 , -2, -43),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(63 , -2 , -43),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(1.f, 1.f),

				DirectX::SimpleMath::Vector3(63, 4, -43),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(1.f, 0.f),

				DirectX::SimpleMath::Vector3(-3 , 4 , -43),
				DirectX::SimpleMath::Vector3(0, 0, -1),
				DirectX::SimpleMath::Vector2(0.f, 0.f)
			};
			this->mEntityRenderer->loadObject(device, wall->getKey(), testData6, 6, L"../Resource/Textures/pyramidStone.png");
			this->mEntities.push_back(wall);



	//another test
	Entity* ent = new Entity(this->mNrOfKeys++);

	EntityStruct::VertexStruct testData2[] = {
		DirectX::SimpleMath::Vector3(-10.f, -2.f, -50.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(0.f, 1.f),

		DirectX::SimpleMath::Vector3(-10.f, -2.f, 10.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(0.f, 0.f),

		DirectX::SimpleMath::Vector3(-3, -2.f, 10.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(1.f, 0.f),

		DirectX::SimpleMath::Vector3(-10.f, -2.f, -50.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(0.f, 1.f),

		DirectX::SimpleMath::Vector3(-3, -2.f, -50.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(1.f, 1.f),

		DirectX::SimpleMath::Vector3(-3, -2.f, 10.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(1.f, 0.f)
	};
	this->mEntities.push_back(ent);
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData2, 6, L"../Resource/Textures/pyramidStone.png");

	ent = new Entity(this->mNrOfKeys++);
	EntityStruct::VertexStruct testData21[] = {
		DirectX::SimpleMath::Vector3(-3, -2.f, -50.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(0.f, 1.f),

		DirectX::SimpleMath::Vector3(-3, -2.f, -43),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(0.f, 0.f),

		DirectX::SimpleMath::Vector3(70, -2.f, -43),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(1.f, 0.f),

		DirectX::SimpleMath::Vector3(-3, -2.f, -50.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(0.f, 1.f),

		DirectX::SimpleMath::Vector3(70, -2.f, -50.f),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(1.f, 1.f),

		DirectX::SimpleMath::Vector3(70, -2.f, -43),
		DirectX::SimpleMath::Vector3(0, 1, 0),
		DirectX::SimpleMath::Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(ent);
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData21, 6, L"../Resource/Textures/pyramidStone.png");
}

void EntityHandler::update()
{
	DirectX::SimpleMath::Vector3 prevPos = this->mPlayer->getPosition();

	this->mPlayer->updatePosition();


	//Wall intersection test
	for (Entity *wall : this->mEntities) 
	{
		Wall* ptr = dynamic_cast<Wall*>(wall);
		if (ptr && ptr->getOBB().obbVSPoint(this->mPlayer->getPosition()))
		{
			this->mPlayer->setPosition(this->mPlayer->getPosition() + ptr->getNormal() * 0.03f);
		}
	}
	
}

EntityRenderer* EntityHandler::getRenderer()
{
	return this->mEntityRenderer;
}

Player* EntityHandler::getPlayer()
{
	return this->mPlayer;
}
