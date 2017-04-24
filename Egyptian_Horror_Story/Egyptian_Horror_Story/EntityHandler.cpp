#include "EntityHandler.h"
#define ENEMY_KEY 400

void EntityHandler::hardcodedMap(ID3D11Device* device)
{
	using namespace DirectX::SimpleMath;
	Wall* wall = new Wall(
		Vector3(-10.f, -2.f, 10.f),
		Vector3(7.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData[] = {
		Vector3(-10.f , -2.f , 10.f),
		Vector3(0, 0, -1),
		Vector2(0.f, 1.f),

		Vector3(-10.f, 4.f , 10.f),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(-3 , -2.f , 10.f),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),

		Vector3(-10.f , 4.f , 10.f),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(-3  , 4.f  , 10.f),
		Vector3(0, 0, -1),
		Vector2(1.f, 0.f),

		Vector3(-3  , -2.f  , 10.f),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f)

	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);
	

	wall = new Wall(
		Vector3(-3, -2.f, -43.f),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 46.f),
		Vector3(-1.f, 0.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData3[] = {
		Vector3(-3, -2.f , 3),
		Vector3(-1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, 4.f , 3),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, -2.f , -43),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(-3, 4.f , 3),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, 4.f , -43),
		Vector3(-1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(-3, -2.f , -43),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData3, 6, WALLTEXTURE);

	this->mEntities.push_back(wall);
	

	wall = new Wall(

		Vector3(-10, -2, -78),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 88.f),
		Vector3(1.f, 0.f, 0.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData4[] = {
		Vector3(-10, -2 , -78),
		Vector3(1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(-10, 4, -78),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(-10, -2 , 10),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(-10, 4 , -78),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(-10, 4 , 10),
		Vector3(1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(-10, -2 , 10),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData4, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);
	

	//Ingång
	wall = new Wall(
		Vector3(20, -2, -50),
		Vector3(20.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData5[] = {
		Vector3(40, -2 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 1.f),

		Vector3(40 , 4 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(20 , -2, -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f),

		Vector3(40 , 4 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(20, 4, -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 0.f),

		Vector3(20 , -2 , -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData5, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	//Ingång
	wall = new Wall(
		Vector3(-4, -2, -50),
		Vector3(18.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(2.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData10[] = {
		Vector3(15, -2 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 1.f),

		Vector3(15 , 4 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(-3 , -2, -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f),

		Vector3(15 , 4 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(-3, 4, -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 0.f),

		Vector3(-3 , -2 , -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData10, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);
	

	//Rum
	wall = new Wall(
		Vector3(30, -2, -70),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 20.f),
		Vector3(-1.f, 0.f, 0.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData11[] = {
		Vector3(30, -2.f , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(30, 4.f , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(30, -2.f , -70),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(30, 4.f , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(30, 4.f , -70),
		Vector3(-1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(30, -2.f , -70),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData11, 6, WALLTEXTURE);//
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(5, -2, -70),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 20.f),
		Vector3(1.f, 0.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData12[] = {
		Vector3(5, -2 , -70),
		Vector3(1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(5, 4, -70),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(5, -2 , -50),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(5, 4 , -70),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(5, 4 , -50),
		Vector3(1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(5, -2 , -50),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData12, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(5, -2, -70),
		Vector3(25.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData13[] = {
		Vector3(30, -2 , -70),
		Vector3(0, 0, 1),
		Vector2(0.f, 1.f),

		Vector3(30 , 4 , -70),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(5 , -2, -70),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f),


		Vector3(30 , 4 , -70),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(5, 4, -70),
		Vector3(0, 0, 1),
		Vector2(1.f, 0.f),

		Vector3(5 , -2 , -70),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f),
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData13, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(5, -2, -50),
		Vector3(10.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData14[] = {
		Vector3(5, -2 , -50),
		Vector3(0, 0, -1),
		Vector2(0.f, 1.f),

		Vector3(5 , 4 , -50),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(15 , -2, -50),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),

		Vector3(5 , 4 , -50),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(15, 4, -50),
		Vector3(0, 0, -1),
		Vector2(1.f, 0.f),

		Vector3(15 , -2 , -50),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData14, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);
	
	wall = new Wall(
		Vector3(20, -2, -50),
		Vector3(10.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData15[] = {
		Vector3(20, -2 , -50),
		Vector3(0, 0, -1),
		Vector2(0.f, 1.f),

		Vector3(20 , 4 , -50),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(30 , -2, -50),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),

		Vector3(20 , 4 , -50),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(30, 4, -50),
		Vector3(0, 0, -1),
		Vector2(1.f, 0.f),

		Vector3(30 , -2 , -50),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData15, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);
	//End rum

	wall = new Wall(
		Vector3(-3, -2, -43),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData6[] = {
		Vector3(-3, -2 , -43),
		Vector3(0, 0, -1),
		Vector2(0.f, 1.f),

		Vector3(-3 , 4 , -43),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(40 , -2, -43),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),

		Vector3(-3 , 4 , -43),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(40, 4, -43),
		Vector3(0, 0, -1),
		Vector2(1.f, 0.f),

		Vector3(40 , -2 , -43),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData6, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(40, -2, -43),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 46.f),
		Vector3(1.f, 0.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData7[] = {
		Vector3(40, -2 , -43),
		Vector3(1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(40, 4 , -43),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(40, -2, 3),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(40, 4 , -43),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(40, 4, 3),
		Vector3(1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(40, -2 , 3),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData7, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(47, -2, -78),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 28.f),
		Vector3(-1.f, 0.f, 0.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData8[] = {
		Vector3(47, -2 , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(47, 4 , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(47, -2, -78),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(47, 4 , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(47, 4, -78),
		Vector3(-1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(47, -2 , -78),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData8, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(47, -2, -43),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 53.f),
		Vector3(-1.f, 0.f, 0.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData16[] = {
		Vector3(47, -2 , 10),
		Vector3(-1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(47, 4 , 10),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(47, -2, -43),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(47, 4 , 10),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(47, 4, -43),
		Vector3(-1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(47, -2 , -43),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData16, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(40, -2, -71),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 21.f),
		Vector3(1.f, 0.f, 0.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData9[] = {
		Vector3(40, -2 , -71),
		Vector3(1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(40, 4 , -71),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(40, -2, -50),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(40, 4 , -71),
		Vector3(1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(40, 4, -50),
		Vector3(1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(40, -2 , -50),
		Vector3(1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData9, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(47, -2, -43),
		Vector3(33.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData17[] = {
		Vector3(47, -2 , -43),
		Vector3(0, 0, -1),
		Vector2(0.f, 1.f),

		Vector3(47 , 4 , -43),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(80 , -2, -43),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),

		Vector3(47 , 4 , -43),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(80, 4, -43),
		Vector3(0, 0, -1),
		Vector2(1.f, 0.f),

		Vector3(80 , -2 , -43),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData17, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(47, -2, -50),
		Vector3(33.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData18[] = {
		Vector3(80, -2 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 1.f),

		Vector3(80 , 4 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(47 , -2, -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f),

		Vector3(80 , 4 , -50),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(47, 4, -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 0.f),

		Vector3(47 , -2 , -50),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData18, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(-3, -2, 3),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData19[] = {
		Vector3(40, -2 , 3),
		Vector3(0, 0, 1),
		Vector2(0.f, 1.f),

		Vector3(40 , 4 , 3),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(-3 , -2, 3),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f),

		Vector3(40 , 4 , 3),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(-3, 4, 3),
		Vector3(0, 0, 1),
		Vector2(1.f, 0.f),

		Vector3(-3 , -2 , 3),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData19, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(-3, -2, 10),
		Vector3(50.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData40[] = {
		Vector3(-3, -2 , 10),
		Vector3(0, 0, -1),
		Vector2(0.f, 1.f),

		Vector3(-3 , 4 , 10),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(47 , -2, 10),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),

		Vector3(-3 , 4 , 10),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(47, 4, 10),
		Vector3(0, 0, -1),
		Vector2(1.f, 0.f),

		Vector3(47 , -2 , 10),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData40, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(-3, -2.f, -71.f),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 21.f),
		Vector3(-1.f, 0.f, 0.f), this->mNrOfKeys++);



	EntityStruct::VertexStruct testData41[] = {
		Vector3(-3, -2.f , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, 4.f , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, -2.f , -71),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f),

		Vector3(-3, 4.f , -50),
		Vector3(-1, 0, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, 4.f , -71),
		Vector3(-1, 0, 0),
		Vector2(1.f, 0.f),

		Vector3(-3, -2.f , -71),
		Vector3(-1, 0, 0),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData41, 6, WALLTEXTURE);

	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(-3, -2, -71),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData42[] = {
		Vector3(-3, -2 , -71),
		Vector3(0, 0, -1),
		Vector2(0.f, 1.f),

		Vector3(-3 , 4 , -71),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(40 , -2, -71),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f),

		Vector3(-3 , 4 , -71),
		Vector3(0, 0, -1),
		Vector2(0.f, 0.f),

		Vector3(40, 4, -71),
		Vector3(0, 0, -1),
		Vector2(1.f, 0.f),

		Vector3(40 , -2 , -71),
		Vector3(0, 0, -1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData42, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	wall = new Wall(
		Vector3(-10, -2, -78),
		Vector3(57.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), this->mNrOfKeys++);


	EntityStruct::VertexStruct testData44[] = {
		Vector3(47, -2 , -78),
		Vector3(0, 0, 1),
		Vector2(0.f, 1.f),

		Vector3(47 , 4 , -78),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(-10 , -2, -78),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f),

		Vector3(47 , 4 , -78),
		Vector3(0, 0, 1),
		Vector2(0.f, 0.f),

		Vector3(-10, 4, -78),
		Vector3(0, 0, 1),
		Vector2(1.f, 0.f),

		Vector3(-10 , -2 , -78),
		Vector3(0, 0, 1),
		Vector2(1.f, 1.f)
	};
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData44, 6, WALLTEXTURE);
	this->mEntities.push_back(wall);

	//another test
	Entity* ent = new Entity(this->mNrOfKeys++);

	EntityStruct::VertexStruct testData2[] = {
		Vector3(-10.f, -2.f, -78.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(-10.f, -2.f, 10.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, -2.f, 10.f),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(-3, -2.f, 10.f),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(-3, -2.f, -78.f),
		Vector3(0, 1, 0),
		Vector2(1.f, 1.f),

		Vector3(-10.f, -2.f, -78.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f)
	};
	this->mEntities.push_back(ent);
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData2, 6, WALLTEXTURE);

	ent = new Entity(this->mNrOfKeys++);
	EntityStruct::VertexStruct testData21[] = {
		Vector3(-3, -2.f, -50.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, -2.f, -43),
		Vector3(0, 1, 0),
		Vector2(0.f, 0.f),

		Vector3(40, -2.f, -43),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(40, -2.f, -43),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(40, -2.f, -50.f),
		Vector3(0, 1, 0),
		Vector2(1.f, 1.f),

		Vector3(-3, -2.f, -50.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f)
	};

	this->mEntities.push_back(ent);
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData21, 6, WALLTEXTURE);

	ent = new Entity(this->mNrOfKeys++);
	EntityStruct::VertexStruct testData22[] = {
		Vector3(40, -2.f, -78),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(40, -2.f, 10),
		Vector3(0, 1, 0),
		Vector2(0.f, 0.f),

		Vector3(47, -2.f, 10),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(47, -2.f, 10),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(47, -2.f, -78.f),
		Vector3(0, 1, 0),
		Vector2(1.f, 1.f),

		Vector3(40, -2.f, -78.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f)
	};

	this->mEntities.push_back(ent);
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData22, 6, WALLTEXTURE);

	//Rum
	ent = new Entity(this->mNrOfKeys++);
	EntityStruct::VertexStruct testData23[] = {
		Vector3(30, -2.f, -70),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(5, -2.f, -70),
		Vector3(0, 1, 0),
		Vector2(0.f, 0.f),

		Vector3(5, -2.f, -50),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(5, -2.f, -50),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(30, -2.f, -50),
		Vector3(0, 1, 0),
		Vector2(1.f, 1.f),

		Vector3(30, -2.f, -70),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(ent);
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData23, 6, WALLTEXTURE);

	ent = new Entity(this->mNrOfKeys++);
	EntityStruct::VertexStruct testData29[] = {
		Vector3(47, -2.f, -50.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(47, -2.f, -43),
		Vector3(0, 1, 0),
		Vector2(0.f, 0.f),

		Vector3(80, -2.f, -43),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(80, -2.f, -43),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(80, -2.f, -50.f),
		Vector3(0, 1, 0),
		Vector2(1.f, 1.f),

		Vector3(47, -2.f, -50.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f)
	};

	this->mEntities.push_back(ent);
	this->mEntityRenderer->loadObject(device, ent->getKey(), testData29, 6, WALLTEXTURE);

	//Tak
	//Rumtak
	wall = new Wall(
		Vector3(5, 4, -70),
		Vector3(25.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 20.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData24[] = {
		Vector3(5, 4.f, -70),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(30, 4.f, -70),
		Vector3(0, -1, 0),
		Vector2(0.f, 0.f),

		Vector3(30, 4.f, -50),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(30, 4.f, -50),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(5, 4.f, -50),
		Vector3(0, -1, 0),
		Vector2(1.f, 1.f),

		Vector3(5, 4.f, -70),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData24, 6, WALLTEXTURE);

	wall = new Wall(
		Vector3(40, 4, -78),
		Vector3(7.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 88.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData25[] = {
		Vector3(47, 4.f, 10),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(40, 4.f, 10),
		Vector3(0, -1, 0),
		Vector2(0.f, 0.f),

		Vector3(40, 4.f, -78),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(40, 4.f, -78.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(47, 4.f, -78.f),
		Vector3(0, -1, 0),
		Vector2(1.f, 1.f),

		Vector3(47, 4.f, 10),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData25, 6, WALLTEXTURE);

	wall = new Wall(
		Vector3(-10, 4, -78),
		Vector3(7.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 88.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData27[] = {
		Vector3(-3, 4.f, 10.f),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(-10.f, 4.f, 10.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 0.f),

		Vector3(-10.f, 4.f, -78.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(-10.f, 4.f, -78.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, 4.f, -78.f),
		Vector3(0, -1, 0),
		Vector2(1.f, 1.f),

		Vector3(-3, 4.f, 10.f),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f)
	};
	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData27, 6, WALLTEXTURE);


	wall = new Wall(
		Vector3(-3, 4, -50),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 7.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData28[] = {
		Vector3(40, 4.f, -43),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(-3, 4.f, -43),
		Vector3(0, -1, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, 4.f, -50.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, 4.f, -50.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(40, 4.f, -50.f),
		Vector3(0, -1, 0),
		Vector2(1.f, 1.f),

		Vector3(40, 4.f, -43),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData28, 6, WALLTEXTURE);


	wall = new Wall(
		Vector3(47, 4, -50),
		Vector3(33.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 7.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData30[] = {
		Vector3(80, 4.f, -43),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(47, 4.f, -43),
		Vector3(0, -1, 0),
		Vector2(0.f, 0.f),

		Vector3(47, 4.f, -50.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(47, 4.f, -50.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(80, 4.f, -50.f),
		Vector3(0, -1, 0),
		Vector2(1.f, 1.f),

		Vector3(80, 4.f, -43),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f)
	};
	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData30, 6, WALLTEXTURE);


	//DETTA ÄR ETT GOLV
	wall = new Wall(
		Vector3(-3, 4, 3),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 7.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData31[] = {
		Vector3(-3, -2.f, 3),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, -2.f, 10),
		Vector3(0, 1, 0),
		Vector2(0.f, 0.f),

		Vector3(40, -2.f, 10),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(40, -2.f, 10),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(40, -2.f, 3.f),
		Vector3(0, 1, 0),
		Vector2(1.f, 1.f),

		Vector3(-3, -2.f, 3.f),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f)
	};

	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData31, 6, WALLTEXTURE);


	wall = new Wall(
		Vector3(-3, 4, 3),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 7.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData32[] = {
		Vector3(40, 4.f, 10),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(-3, 4.f, 10),
		Vector3(0, -1, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, 4.f, 3),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, 4.f, 3.f),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(40, 4.f, 3.f),
		Vector3(0, -1, 0),
		Vector2(1.f, 1.f),

		Vector3(40, 4.f, 10),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData32, 6, WALLTEXTURE);


	wall = new Wall(
		Vector3(-3, 4, -78),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 7.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData33[] = {
		Vector3(-3, 4.f, -71),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, 4.f, -78),
		Vector3(0, -1, 0),
		Vector2(0.f, 0.f),

		Vector3(40, 4.f, -78),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(40, 4.f, -78),
		Vector3(0, -1, 0),
		Vector2(1.f, 0.f),

		Vector3(40, 4.f, -71),
		Vector3(0, -1, 0),
		Vector2(1.f, 1.f),

		Vector3(-3, 4.f, -71),
		Vector3(0, -1, 0),
		Vector2(0.f, 1.f)
	};

	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData33, 6, WALLTEXTURE);

	wall = new Wall(
		Vector3(-3, 4, -78),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 7.f),
		Vector3(0.f, -1.f, 0.f), this->mNrOfKeys++);

	EntityStruct::VertexStruct testData34[] = {
		Vector3(40, -2, -78),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f),

		Vector3(-3, -2, -78),
		Vector3(0, 1, 0),
		Vector2(0.f, 0.f),

		Vector3(-3, -2, -71),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(-3, -2, -71),
		Vector3(0, 1, 0),
		Vector2(0.f, 1.f),

		Vector3(40, -2, -71),
		Vector3(0, 1, 0),
		Vector2(1.f, 1.f),

		Vector3(40, -2, -78),
		Vector3(0, 1, 0),
		Vector2(1.f, 0.f)
	};

	this->mEntities.push_back(wall);
	this->mEntityRenderer->loadObject(device, wall->getKey(), testData34, 6, WALLTEXTURE);

}

void EntityHandler::setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera)
{
	this->mPlayer = new Player(camera, device, context, this->mNrOfKeys++, this->mEntityRenderer->getGraphicsData(), this->mRiggedEntityRenderer->getGraphicsData());
	this->mPlayer->setPosition(DirectX::SimpleMath::Vector3(0, 0, 4));

	this->mEnemy = new Enemy(ENEMY_KEY);
	this->mEnemy->setPosition(DirectX::SimpleMath::Vector3(0, 0, 5));
}

EntityHandler::EntityHandler()
{
	this->mEntityRenderer = new EntityRenderer();
	this->mRiggedEntityRenderer = new RiggedEntityRenderer();
}

EntityHandler::~EntityHandler()
{
	delete this->mPlayer;
	delete this->mEnemy;

	for (size_t i = 0; i < this->mEntities.size(); i++)
	{
		delete this->mEntities[i];
	}
}

void EntityHandler::setupEntities(ID3D11Device* device)
{
	//this->hardcodedMap(device);

	std::vector<EntityStruct::SkinnedVertexStruct> test;

	this->mLoader.loadSkinnedMesh(test, "ModelTestAnimate.fbx");

	this->mRiggedTest = new Entity(0);

	this->mEntities.push_back(mRiggedTest);
	this->mRiggedEntityRenderer->loadObject(device, mRiggedTest->getKey(), test.data(), test.size(), L"mon.bmp");

	this->mRiggedEntityRenderer->loadObject(
		device, 
		mRiggedTest->getKey(),
		test.data(), 
		test.size(),
		L"dargon_bump.jpg");

}

void EntityHandler::update()
{
	DirectX::SimpleMath::Vector3 prevPos = this->mPlayer->getPosition();

	this->mPlayer->updatePosition();

	//Wall intersection test
	for (Entity *wall : this->mEntities) 
	{
		Wall* ptr = dynamic_cast<Wall*>(wall);

		if (ptr && ptr->getAABB().aabbVSCapsule(*this->getPlayer()->col)) {
			DirectX::SimpleMath::Vector3 ptop = this->mPlayer->getPrevPos() - this->mPlayer->getPosition();

			

			DirectX::SimpleMath::Vector3 norm = ptr->getNormal();
			//DirectX::SimpleMath::Vector3 norm = ptr->getAABB().calculateNormal(*this->mPlayer->col);

			//DirectX::SimpleMath::Vector3 norm = ptr->getAABB().getNormal(*this->getPlayer()->col);
			//DirectX::SimpleMath::Vector3 diff;
			//diff = mPlayer->getPosition() - ptr->getAABB().mPoint;
			//
			//DirectX::SimpleMath::Vector3 tmp1 = diff;
			//DirectX::SimpleMath::Vector3 tmp2 = norm;
			//
			//tmp1.Normalize();
			//tmp2.Normalize();
			//
			//diff = (tmp2.Dot(tmp1) * diff); //STÄMMER KAPPA
			//diff = norm - diff;
			//norm.Normalize();
			//this->mPlayer->setPosition(mPlayer->getPosition() + diff + norm * mPlayer->col->mRadius);



			//ptop = ptop - (norm.Dot(ptop) * norm);

			ptop = ptop - (ptr->getNormal().Dot(ptop) * norm);

			//this->mPlayer->setPrevPos(this->mPlayer->getPrevPos() + ptop);
			
			ptop = -ptop;
			this->mPlayer->setPosition(this->mPlayer->getPrevPos() + ptop);
			
			//this->mPlayer->setPosition(ptr->getOBB().mPoint);
			
					

		}
	}
}

EntityRenderer* EntityHandler::getEntityRenderer()
{
	return this->mEntityRenderer;
}

RiggedEntityRenderer* EntityHandler::getRiggedEntityRenderer()
{
	return mRiggedEntityRenderer;
}

Player* EntityHandler::getPlayer()
{
	return this->mPlayer;
}

Enemy* EntityHandler::getEnemy()
{
	return this->mEnemy;
}
