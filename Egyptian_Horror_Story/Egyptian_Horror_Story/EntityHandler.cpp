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

void EntityHandler::setupPlayer(ID3D11Device* device, CameraClass* camera)
{
	this->mPlayer = new Player(camera, device, this->mNrOfKeys++);
	this->mPlayer->setPosition(DirectX::SimpleMath::Vector3(0, 0, -5));
}

void EntityHandler::setupEntities(ID3D11Device * device)
{
	//test
	Wall* wall = new Wall(
		DirectX::SimpleMath::Vector3(-1.f, -1.f, 0.f),
		DirectX::SimpleMath::Vector3(2.f, 0.f, 0.f),
		DirectX::SimpleMath::Vector3(0.f, 2.f, 0.f),
		DirectX::SimpleMath::Vector3(0.f, 0.f, 2.f), 1);

	EntityStruct::VertexStruct testData[] = {
		DirectX::SimpleMath::Vector3(-1.f, -1.f, 0.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(0.f, 1.f),

		DirectX::SimpleMath::Vector3(-1.f, 1.f, 0.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(0.f, 0.f),

		DirectX::SimpleMath::Vector3(1.f, -1.f, 0.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(1.f, 1.f),

		DirectX::SimpleMath::Vector3(1.f, -1.f, 0.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(1.f, 1.f),

		DirectX::SimpleMath::Vector3(1.f, 1.f, 0.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(1.f, 0.f),

		DirectX::SimpleMath::Vector3(-1.f, 1.f, 0.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(0.f, 0.f)
	};

	//another test
	Entity* ent = new Entity(2);

	EntityStruct::VertexStruct testData2[] = {
		DirectX::SimpleMath::Vector3(-10.f, -2.f, -10.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(0.f, 1.f),

		DirectX::SimpleMath::Vector3(-10.f, -2.f, 10.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(0.f, 0.f),

		DirectX::SimpleMath::Vector3(10.f, -2.f, 10.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(1.f, 0.f),

		DirectX::SimpleMath::Vector3(-10.f, -2.f, -10.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(0.f, 1.f),

		DirectX::SimpleMath::Vector3(10.f, -2.f, -10.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(1.f, 1.f),

		DirectX::SimpleMath::Vector3(10.f, -2.f, 10.f),
		DirectX::SimpleMath::Vector3(),
		DirectX::SimpleMath::Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(wall);
	this->mEntities.push_back(ent);

	this->mEntityRenderer->loadObject(device, wall->getKey(), testData, 6, L"../Resource/Textures/normalMap.png");
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData2, 6, L"../Resource/Textures/normatgflMap.png");
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
