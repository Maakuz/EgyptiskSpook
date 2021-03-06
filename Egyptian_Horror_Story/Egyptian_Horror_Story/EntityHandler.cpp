#include "EntityHandler.h"
#define ENEMY_KEY 400
#define BASE_TRAP_KEY 1000
#define TREASURE_PICKUP_DIST 3.f
#define SCALE_X 1.f
#define SCALE_Z -1.f
#define OFFSET_X -9 * SCALE_X
#define OFFSET_Z -9 * SCALE_Z
#define TREASUREMAPPATH "../Resource/Textures/TreasureMesh.bmp"
#define MEGAWALLKEY 10000

DirectX::SimpleMath::Vector2 EntityHandler::toPixelCoord(int x, int z, int w, int h) const {
	x = abs(x) % w;
	z = abs(z) % h;
	
	float pX = floor(x * SCALE_X) + OFFSET_X;
	float pY = (floor(z * SCALE_Z) + OFFSET_Z);

	return DirectX::SimpleMath::Vector2(pX, pY);
}

void EntityHandler::addToMegarray(std::vector<VertexStruct>& megarray, VertexStruct arrayToadd[], int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		megarray.push_back(arrayToadd[i]);
	}
}

DirectX::SimpleMath::Vector2 EntityHandler::getPosition(float x, float y) const {
	DirectX::SimpleMath::Vector2 pixel(x, y);
	return DirectX::SimpleMath::Vector2(
		(pixel.x - OFFSET_X) / SCALE_X,
		(pixel.y - OFFSET_Z) / SCALE_Z
	);
}

void EntityHandler::hardcodedMap(ID3D11Device* device)
{
	using namespace DirectX::SimpleMath;

	std::vector<VertexStruct> megaArray;
	// v�gg one next to spawn
	Wall* wall;
	Entity* ent = nullptr;

	int tmpKey = 70000;
	wall = new Wall(
		Vector3(-10.f, -2.f, 10.f),
		Vector3(57.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 6; i++) {

		VertexStruct testData[] = {
			Vector3(-10.f + i*9.5f, -2.f , 10.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 1.f),

			Vector3(-10.f + i * 9.5f, 4.f , 10.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(-0.5f + i * 9.5f , -2.f , 10.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f),

			Vector3(-10.f + i * 9.5f , 4.f , 10.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(-0.5f + i * 9.5f  , 4.f  , 10.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 0.f),

			Vector3(-0.5f + i * 9.5f  , -2.f  , 10.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f)

		};
		this->addToMegarray(megaArray, testData);

	}


	wall = new Wall(
		Vector3(-3.f, -2.f, -43.f),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 46.f),
		Vector3(-1.f, 0.f, 0.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {

		VertexStruct testData3[] = {
			Vector3(-3.f, -2.f , -33.8f + i*9.2f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(-3.f, 4.f , -33.8f + i*9.2f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f, -2.f, -43.f + i*9.2f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(-3.f, 4.f , -33.8f + i*9.2f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f, 4.f , -43.f + i*9.2f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(-3.f, -2.f , -43.f + i*9.2f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};
		this->addToMegarray(megaArray, testData3);

	}



	// fet v�gg i z led	
	wall = new Wall(

		Vector3(-10.f, -2.f, -78.f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 88.f),
		Vector3(1.f, 0.f, 0.f), tmpKey++);
	this->mEntities.push_back(wall);

	for (int i = 0; i < 11; i++) {

		VertexStruct testData4[] = {
			Vector3(-10.f, -2.f, 2.f - i * 8.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(-10.f, 4.f, 2.f - i * 8.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(-10.f, -2.f, 10.f - i * 8.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(-10.f, 4.f, 2.f - i * 8.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(-10.f, 4.f, 10.f - i * 8.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(-10.f, -2.f, 10.f - i * 8.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData4);

	}



	//Ing�ng
	wall = new Wall(
		Vector3(20.f, -2.f, -50.f),
		Vector3(20.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 2; i++) {

		VertexStruct testData5[] = {
			Vector3(30.f + i * 10.f, -2.f , -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 1.f),

			Vector3(30.f + i * 10.f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(20.f + i * 10.f , -2.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f),

			Vector3(30.f + i * 10.f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(20.f + i * 10.f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 0.f),

			Vector3(20.f + i * 10.f, -2.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData5);

	}

	//Ing�ng
	wall = new Wall(
		Vector3(-4.f, -2.f, -50.f),
		Vector3(18.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(2.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 2; i++) {

		VertexStruct testData10[] = {
			Vector3(6.f + i * 9.f, -2.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 1.f),

			Vector3(6.f + i * 9.f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f + i * 9.f, -2.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f),

			Vector3(6.f + i * 9.f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f + i * 9.f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 0.f),

			Vector3(-3.f + i * 9.f, -2.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData10);

	}



	//rum
	wall = new Wall(
		Vector3(30.f, -2.f, -70.f),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 20.f),
		Vector3(-1.f, 0.f, 0.f), tmpKey++);

	this->mEntities.push_back(wall);
	for (int i = 0; i < 4; i++) {

		VertexStruct testData11[] = {
			Vector3(30.f, -2.f, -65.f + i * 5.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(30.f, 4.f, -65.f + i * 5.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(30.f, -2.f , -70.f + i * 5.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(30.f, 4.f, -65.f + i * 5.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(30.f, 4.f, -70.f + i * 5.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(30.f, -2.f, -70.f + i * 5.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData11);

	}
	wall = new Wall(
		Vector3(5.f, -2.f, -70.f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 20.f),
		Vector3(1.f, 0.f, 0.f), tmpKey++);
	this->mEntities.push_back(wall);

	for (int i = 0; i < 4; i++) {


		VertexStruct testData12[] = {
			Vector3(5.f, -2.f, -70.f + i * 5.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(5.f, 4.f, -70.f + i * 5.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(5.f, -2.f, -65.f + i * 5.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(5.f, 4.f, -70.f + i * 5.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(5.f, 4.f, -65.f + i * 5.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(5.f, -2.f, -65.f + i * 5.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData12);

	}

	wall = new Wall(
		Vector3(5.f, -2.f, -70.f),
		Vector3(25.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {


		VertexStruct testData13[] = {
			Vector3(10.f + i * 5.f, -2.f, -70.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 1.f),

			Vector3(10.f + i * 5.f, 4.f, -70.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(5.f + i * 5.f, -2.f, -70.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f),


			Vector3(10.f + i * 5.f, 4.f, -70.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(5.f + i * 5.f, 4.f, -70.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 0.f),

			Vector3(5.f + i * 5.f, -2.f, -70.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f),
		};
		this->addToMegarray(megaArray, testData13);

	}


	wall = new Wall(
		Vector3(5.f, -2.f, -50.f),
		Vector3(10.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 2; i++) {

		VertexStruct testData14[] = {
			Vector3(5.f + i * 5.f, -2.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 1.f),

			Vector3(5.f + i * 5.f, 4.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(10.f + i * 5.f, -2.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f),

			Vector3(5.f + i * 5.f, 4.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(10.f + i * 5.f, 4.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 0.f),

			Vector3(10.f + i * 5.f, -2.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f),
		};
		this->addToMegarray(megaArray, testData14);

	}
	wall = new Wall(
		Vector3(20.f, -2.f, -50.f),
		Vector3(10.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), tmpKey++);
	this->mEntities.push_back(wall);

	for (int i = 0; i < 2; i++) {


		VertexStruct testData15[] = {
			Vector3(20.f + i * 5.f, -2.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 1.f),

			Vector3(20.f + i * 5.f, 4.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(25.f + i * 5.f, -2.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f),

			Vector3(20.f + i * 5.f, 4.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(25.f + i * 5.f, 4.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 0.f),

			Vector3(25.f + i * 5.f, -2.f, -50.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData15);

	}


	//End rum

	wall = new Wall(
		Vector3(-3.f, -2.f, -43.f),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {

		VertexStruct testData6[] = {
			Vector3(-3.f + i*8.6f, -2.f , -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 1.f),

			Vector3(-3.f + i*8.6f , 4.f , -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(5.6f + i*8.6f , -2.f, -43.f),
			Vector3(0, 0, -1.f),
			Vector2(1.f, 1.f),

			Vector3(-3.f + i*8.6f , 4.f , -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(5.6f + i*8.6f, 4.f, -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 0.f),

			Vector3(5.6f + i*8.6f , -2.f , -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f)
		};
		this->addToMegarray(megaArray, testData6);

	}

	wall = new Wall(
		Vector3(40.f, -2.f, -43.f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 46.f),
		Vector3(1.f, 0.f, 0.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {


		VertexStruct testData7[] = {
			Vector3(40.f, -2.f , -43.f + i*9.2f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(40.f, 4.f , -43.f + i*9.2f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(40.f, -2.f, -33.8f + i*9.2f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(40.f, 4.f, -43.f + i*9.2f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(40.f, 4.f, -33.8f + i*9.2f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(40.f, -2.f , -33.8f + i*9.2f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData7);

	}

	wall = new Wall(
		Vector3(47.f, -2.f, -78.f),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 28.f),
		Vector3(-1.f, 0.f, 0.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 4; i++) {


		VertexStruct testData8[] = {
			Vector3(47.f, -2.f , -71.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(47.f, 4.f , -71.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(47.f, -2.f, -78.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(47.f, 4.f, -71.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(47.f, 4.f, -78.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(47.f, -2.f , -78.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};
		this->addToMegarray(megaArray, testData8);


	}
	wall = new Wall(
		Vector3(47.f, -2.f, -43.f),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 53.f),
		Vector3(-1.f, 0.f, 0.f), tmpKey++);

	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {

		VertexStruct testData16[] = {
			Vector3(47.f, -2.f , -32.4f + i*10.6f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(47.f, 4.f, -32.4f + i*10.6f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(47.f, -2.f, -43.f + i*10.6f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(47.f, 4.f, -32.4f + i*10.6f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(47.f, 4.f, -43.f + i*10.6f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(47.f, -2.f , -43.f + i*10.6f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData16);

	}

	wall = new Wall(
		Vector3(40.f, -2.f, -71.f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 21.f),
		Vector3(1.f, 0.f, 0.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 3; i++) {

		// andra sidan rumv�gg
		VertexStruct testData9[] = {
			Vector3(40.f, -2.f , -71.f + i * 7.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(40.f, 4.f, -71.f + i * 7.f),
			Vector3(1, 0, 0),
			Vector2(0.f, 0.f),

			Vector3(40.f, -2.f, -64.f + i * 7.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(40.f, 4.f, -71.f + i * 7.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(40.f, 4.f, -64.f + i * 7.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(40.f, -2.f , -64.f + i * 7.f),
			Vector3(1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData9);

	}


	wall = new Wall(
		Vector3(47.f, -2.f, -43.f),
		Vector3(33.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {


		VertexStruct testData17[] = {
			Vector3(47.f + i*6.6f, -2.f, -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 1.f),

			Vector3(47.f + i*6.6f , 4.f, -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(53.6f + i*6.6f, -2.f, -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f),

			Vector3(47.f + i*6.6f , 4.f , -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(53.6f + i*6.6f, 4.f, -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 0.f),

			Vector3(53.6f + i*6.6f , -2.f, -43.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f)
		};
		this->addToMegarray(megaArray, testData17);

	}
	wall = new Wall(
		Vector3(47.f, -2.f, -50.f),
		Vector3(33.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {

		VertexStruct testData18[] = {
			Vector3(53.6f + i*6.6f, -2.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 1.f),

			Vector3(53.6f + i*6.6f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(47.f + i*6.6f, -2.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f),

			Vector3(53.6f + i*6.6f , 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(47.f + i*6.6f, 4.f, -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 0.f),

			Vector3(47.f + i*6.6f , -2.f , -50.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f)
		};
		this->addToMegarray(megaArray, testData18);

	}



	//mittemot sidan vi vill ha
	wall = new Wall(
		Vector3(-3.f, -2.f, 3.f),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {

		VertexStruct testData19[] = {
			Vector3(5.6f + i*8.6f, -2.f, 3.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 1.f),

			Vector3(5.6f + i*8.6f , 4.f , 3.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f + i*8.6f , -2.f, 3.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f),

			Vector3(5.6f + i*8.6f , 4.f , 3.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f + i*8.6f, 4.f, 3.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 0.f),

			Vector3(-3.f + i*8.6f , -2.f , 3.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData19);

	}

	// mittemot den feta v�ggen i z led, kort
	wall = new Wall(
		Vector3(-3.f, -2.f, -71.f),
		Vector3(-1.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 21.f),
		Vector3(-1.f, 0.f, 0.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 3; i++) {

		VertexStruct testData41[] = {
			Vector3(-3.f, -2.f , -64.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 1.f),

			Vector3(-3.f, 4.f , -64.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f, -2.f , -71.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f),

			Vector3(-3.f, 4.f , -64.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(0.f, 0.f),

			Vector3(-3.f, 4.f , -71.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 0.f),

			Vector3(-3.f, -2.f , -71.f + i * 7.f),
			Vector3(-1.f, 0.f, 0.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData41);

	}

	//mittemot bakre v�ff
	wall = new Wall(
		Vector3(-3.f, -2.f, -71.f),
		Vector3(43.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, -1.f),
		Vector3(0.f, 0.f, -1.f), tmpKey++);
	this->mEntities.push_back(wall);
	for (int i = 0; i < 5; i++) {

		VertexStruct testData42[] = {
			Vector3(-3.f + i*8.6f, -2.f , -71.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 1.f),

			Vector3(-3.f + i*8.6f , 4.f , -71.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(5.6f + i*8.6f , -2.f, -71.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f),

			Vector3(-3.f + i*8.6f , 4.f , -71.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(0.f, 0.f),

			Vector3(5.6f + i*8.6f, 4.f, -71.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 0.f),

			Vector3(5.6f + i*8.6f , -2.f , -71.f),
			Vector3(0.f, 0.f, -1.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData42);

	}

	//bakre v�gg
	wall = new Wall(
		Vector3(-10.f, -2.f, -78.f),
		Vector3(57.f, 0.f, 0.f),
		Vector3(0.f, 6.f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 1.f), tmpKey++);
	this->mEntities.push_back(wall);


	for (int i = 0; i < 6; i++) {

		VertexStruct testData44[] = {
			Vector3(-0.5f + i*9.5f, -2.f , -78.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 1.f),

			Vector3(-0.5f + i*9.5f , 4.f , -78.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(-10.f + i*9.5f , -2.f, -78.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f),

			Vector3(-0.5f + i*9.5f , 4.f , -78.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(0.f, 0.f),

			Vector3(-10.f + i*9.5f, 4.f, -78.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 0.f),

			Vector3(-10.f + i*9.5f , -2.f , -78.f),
			Vector3(0.f, 0.f, 1.f),
			Vector2(1.f, 1.f)
		};

		this->addToMegarray(megaArray, testData44);

	}




	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
	
			VertexStruct testData31[] = {
				Vector3(-10.f + i * 7.f, -2.f, 10.f - j * 7.f),
				Vector3(0.f, 1.f, 0.f),
				Vector2(0.f, 1.f),

				Vector3(-3.f + i * 7.f, -2.f, 10.f - j * 7.f),
				Vector3(0.f, 1.f, 0.f),
				Vector2(0.f, 0.f),

				Vector3(-3.f + i * 7.f, -2.f, 3.f - j * 7.f),
				Vector3(0.f, 1.f, 0.f),
				Vector2(1.f, 0.f),

				Vector3(-10.f + i * 7.f, -2.f, 10.f - j * 7.f),
				Vector3(0.f, 1.f, 0.f),
				Vector2(0.f, 1.f),

				Vector3(-3.f + i * 7.f, -2.f, 3.f - j * 7.f),
				Vector3(0.f, 1.f, 0.f),
				Vector2(1.f, 0.f),

				Vector3(-10.f + i * 7.f, -2.f, 3.f - j * 7.f),
				Vector3(0.f, 1.f, 0.f),
				Vector2(1.f, 1.f)
			};

			this->addToMegarray(megaArray, testData31);

			VertexStruct testData34[] = {
				Vector3(-3.f + i * 7, 4.f, 10.f - j * 7.f),
				Vector3(0.f, -1.f, 0.f),
				Vector2(0.f, 0.f),

				Vector3(-10.f + i * 7.f, 4.f, 10.f - j * 7.f),
				Vector3(0.f, -1.f, 0.f),
				Vector2(0.f, 1.f),

				Vector3(-3.f + i * 7.f, 4.f, 3.f - j * 7.f),
				Vector3(0.f, -1.f, 0.f),
				Vector2(1.f, 0.f),

				Vector3(-3.f + i * 7.f, 4.f, 3.f - j * 7.f),
				Vector3(0.f, -1.f, 0.f),
				Vector2(1.f, 0.f),

				Vector3(-10.f + i * 7.f, 4.f, 10.f - j * 7.f),
				Vector3(0.f, -1.f, 0.f),
				Vector2(0.f, 1.f),

				Vector3(-10.f + i * 7.f, 4.f, 3.f - j * 7.f),
				Vector3(0.f, -1.f, 0.f),
				Vector2(1.f, 1.f)
			};

			this->addToMegarray(megaArray, testData34);
		}
	}


this->megaWall = new Entity(MEGAWALLKEY);

this->mEntityRenderer->loadObject(device, MEGAWALLKEY, megaArray.data(), megaArray.size(), sizeof(DirectX::XMFLOAT4X4), WALLTEXTURE);
}

void EntityHandler::loadEntityModel(std::string modelName, wchar_t* textureName, Entity* entity, ID3D11Device* device)
{
	std::vector<VertexStruct> temp;

	this->mLoader.loadMesh(temp, modelName);

	this->mEntityRenderer->loadObject(
		device,
		entity->getKey(),
		temp.data(),
		temp.size(),
		sizeof(DirectX::XMFLOAT4X4),
		textureName,
		entity->getPosition()
		);
}

void EntityHandler::updateAudio()
{
	//Updating emitters
	DirectX::SimpleMath::Vector3 feet = this->mPlayer->getPosition();
	feet.x -= 465.5f;

	//this->mAudioManager->updateEmitter(1, feet);
	this->mAudioManager->updateListener(this->mPlayer->getPosition(),
		this->mPlayer->getCamera()->getForward(),
		this->mPlayer->getCamera()->getUp());


	//Playing footsteps when player walks. could be moved into
	//player class. Right now more of a proof of concept
	if (abs(this->mPlayer->getVelocity().x) + abs(this->mPlayer->getVelocity().z) >= 0.3f
		&& !this->footstepsPlaying
		&& this->mPlayer->getVelocity().y == 0)
	{
		//Pitch should wary to make it less repetetive
		this->mAudioManager->playInstance(1, true, -0.5f);
		this->footstepsPlaying = true;
	}

	else if ((abs(this->mPlayer->getVelocity().x) + abs(this->mPlayer->getVelocity().z) < 0.3f
		|| this->mPlayer->getVelocity().y != 0)
		&& this->footstepsPlaying
		)
	{
		this->mAudioManager->stopInstance(1, false);
		this->footstepsPlaying = false;
	}
}

void EntityHandler::updateCollision()
{
	for (Entity *wall : this->mEntities)
	{
		Wall* ptr = dynamic_cast<Wall*>(wall);

		if (ptr && ptr->getAABB() && ptr->getAABB()->aabbVSCapsule(*this->getPlayer()->col)) {
			DirectX::SimpleMath::Vector3 ptop = this->mPlayer->getPrevPos() - this->mPlayer->getPosition();

			DirectX::SimpleMath::Vector3 norm = ptr->getNormal();

			ptop = ptop - (ptr->getNormal().Dot(ptop) * norm);

			ptop = -ptop;
			this->mPlayer->setPosition(this->mPlayer->getPrevPos() + ptop);
		}
	}
}

void EntityHandler::detectCloseTreasures()
{
	bool exit = false;

	for (size_t i = 0; i < this->mTreasures.size() && !exit; i++)
	{
		this->mPlayer->setPickuppableTreasure(nullptr);

		DirectX::SimpleMath::Vector3 playerToTres = this->mTreasures[i]->getPosition() - this->mPlayer->getPosition();

		if (this->mTreasures[i]->getPickedUp())
		{
			this->mEntityRenderer->getGraphicsData()->removeData(this->mTreasures[i]->getKey());
			
			delete this->mTreasures[i];
			this->mTreasures.erase(this->mTreasures.begin() + i);
			exit = true;
		}

		else if (playerToTres.Length() < TREASURE_PICKUP_DIST)
		{
			playerToTres.Normalize();
			if (playerToTres.Dot(this->mPlayer->getCamera()->getForward()) > 0.7)
			{
				this->mPlayer->setPickuppableTreasure(this->mTreasures[i]);
				exit = true;
			}
		}
	}
}

void EntityHandler::createAhnk(ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot)
{
	Treasure* tres = new Treasure(500 + this->mTreasures.size(), 20.f, 100);

	tres->setPosition(posRot.pos.x, posRot.pos.y -0.3f, posRot.pos.z);
	tres->setRotation(DirectX::SimpleMath::Vector3(0, posRot.rot * static_cast<float>(M_PI), 0));

	this->loadEntityModel("treasure1.fbx", L"ankhTexture.png", tres, device);
	tres->updateTransformBuffer(context, this->mEntityRenderer->getGraphicsData());

	this->mTreasures.push_back(tres);
}

void EntityHandler::createTreasureChest(ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot)
{
	Treasure* tres = new Treasure(500 + this->mTreasures.size(), 30.f, 300);

	tres->setPosition(posRot.pos.x, posRot.pos.y, posRot.pos.z);
	tres->setRotation(DirectX::SimpleMath::Vector3(0, posRot.rot * static_cast<float>(M_PI), 0));

	this->loadEntityModel("treasure2.fbx", L"chestTexture.png", tres, device);
	tres->updateTransformBuffer(context, this->mEntityRenderer->getGraphicsData());

	this->mTreasures.push_back(tres);
}

void EntityHandler::createBoulderTrap(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot, float yOffset)
{
	Trap* trap = new Trap(1000 + this->mTraps.size(), posRot.pos.x, posRot.pos.y + yOffset, posRot.pos.z);
	trap->setRotation(DirectX::SimpleMath::Vector3(0, posRot.rot * static_cast<float>(M_PI), 0));

	this->loadEntityModel("rock.fbx", L"sandstone.jpg", trap, device);
	trap->updateTransformBuffer(context, this->mEntityRenderer->getGraphicsData());

	ai->addTrap("scripts/TrapStone.lua", trap);
	this->mTraps.push_back(trap);
}

void EntityHandler::createGuillioutineTrap(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context, PosRot posRot)
{
	Trap* trap = new Trap(1000 + this->mTraps.size(), posRot.pos.x, posRot.pos.y + 1.2f, posRot.pos.z);
	trap->setRotation(DirectX::SimpleMath::Vector3(0, posRot.rot * static_cast<float>(M_PI), 0));

	this->loadEntityModel("Guilliotine.fbx", L"Giljotin.png", trap, device);
	trap->updateTransformBuffer(context, this->mEntityRenderer->getGraphicsData());

	ai->addTrap("scripts/TrapHanger.lua", trap);
	this->mTraps.push_back(trap);
}

void EntityHandler::setupPlayer(ID3D11Device* device, ID3D11DeviceContext* context, CameraClass* camera)
{
	this->mPlayer = new Player(camera, device, context, this->mNrOfKeys++, this->mEntityRenderer->getGraphicsData());

	this->mEnemy = new Enemy(ENEMY_KEY);

	this->loadEntityModel("monster.fbx", L"GhostTexture.png", this->mEnemy, device);
}

void EntityHandler::setupTreasureAndTraps(AIHandler* ai, ID3D11Device* device)
{
	using namespace DirectX::SimpleMath;

	std::ifstream file(TREASUREMAPPATH, std::ios::binary);
	if (file.is_open())
	{
		BITMAPFILEHEADER* fHeader = nullptr;
		BITMAPINFOHEADER* iHeader = nullptr;

		UINT8* headers[2] = { nullptr };
		UINT8* colors = nullptr;

		headers[0] = new UINT8[sizeof(BITMAPFILEHEADER)];
		headers[1] = new UINT8[sizeof(BITMAPINFOHEADER)];

		file.read((char*)headers[0], sizeof(BITMAPFILEHEADER));
		file.read((char*)headers[1], sizeof(BITMAPINFOHEADER));

		fHeader = (BITMAPFILEHEADER*)headers[0];
		iHeader = (BITMAPINFOHEADER*)headers[1];

		if (fHeader->bfType == 0x4D42)
		{
			int height = iHeader->biHeight;
			int width = iHeader->biWidth;

			int size = width * height * 3;

			colors = new UINT8[size];

			for (int i = 0; i < size; i++)
			{
				colors[i] = 0;
			}

			file.seekg(fHeader->bfOffBits);

			//Read all the bits into the color array
			file.read((char*)colors, size);

			file.close();

			//Create vectors from the color array
			int count = 0;
			int pos = 0;
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)
				{
					//TREASURE
					if (
						colors[count + 1] == 255 && 
						colors[count + 2] == 0)
					{
						Vector2 pos = toPixelCoord(i, height - j, width, height);
						PosRot temp;
						temp.pos = Vector3(pos.x, -1.4f, pos.y);
						temp.rot = colors[count] / 100.f;

						this->mTreasurePositions.push_back(temp);
					}

					//TRAPS
					else if (
						colors[count + 1] == 0 &&
						colors[count + 2] == 255)
					{
						Vector2 pos = toPixelCoord(i, height - j, width, height);
						PosRot temp;
						temp.pos = Vector3(pos.x, -1.6f, pos.y);
						temp.rot = colors[count] / 100.f;

						this->mTrapPositions.push_back(temp);
					}

					count += 3;
				}
			}

			delete headers[0];
			delete headers[1];
			delete colors;
		}
	}
}

EntityHandler::EntityHandler()
{
	this->mEntityRenderer = new EntityRenderer(GAMESTATE::PLAY);
	this->footstepsPlaying = false;
	srand(static_cast<unsigned int>(time(NULL)));
}

EntityHandler::~EntityHandler()
{
	delete this->mPlayer;
	delete this->mEnemy;
	delete this->mFlashlightModel;
	delete this->mLevel;
	delete this->megaWall;

	for (size_t i = 0; i < this->mEntities.size(); i++)
		delete this->mEntities[i];

	for (size_t i = 0; i < this->mTraps.size(); i++)
		delete this->mTraps[i];

	for (size_t i = 0; i < this->mTreasures.size(); i++)
	{
		if (this->mTreasures[i])
			delete this->mTreasures[i];
	}
}

void EntityHandler::loadMap(ID3D11Device* device)
{
	this->mLevel = new Entity(401);

	this->loadEntityModel("LevelDesignTest.fbx", WALLTEXTURE, this->mLevel, device);
}

void EntityHandler::setupEntities(AIHandler* ai, ID3D11Device* device)
{
	this->hardcodedMap(device);


	this->mFlashlightModel = new Entity(this->mPlayer->getLight()->getGraphicsKey());

	this->loadEntityModel("flashLight.fbx", L"dargon_bump.jpg", mFlashlightModel, device);


	this->setupTreasureAndTraps(ai, device);
}

void EntityHandler::setupAudioManager(AudioManager* manager)
{
	this->mAudioManager = manager;
	this->mAudioManager->addSfx(0, L"monster.wav");
	this->mAudioManager->addSfx(1, L"footStepLouder.wav");
	this->mAudioManager->createInstance(1, 1);
	this->mAudioManager->createEmitter(1);
	this->mAudioManager->apply3DToInstance(1, 1);
}

void EntityHandler::setupDifficulty(settings::DifficultySettings & diff)
{
	this->mTrapPercentage = diff.trapPercentage;
	this->mTreasurePercentage = diff.treasurePercentage;
}

void EntityHandler::initializeTreasureAndTraps(AIHandler* ai, ID3D11Device* device, ID3D11DeviceContext* context)
{
	using namespace DirectX::SimpleMath;

	for (size_t i = 0; i < this->mTraps.size(); i++)
	{
		this->mEntityRenderer->getGraphicsData()->removeData(this->mTraps[i]->getKey());
		delete this->mTraps[i];
	}

	for (size_t i = 0; i < this->mTreasures.size(); i++)
	{
		this->mEntityRenderer->getGraphicsData()->removeData(this->mTreasures[i]->getKey());
		delete this->mTreasures[i];
	}

	ai->resetTraps();

	this->mTraps.clear();
	this->mTreasures.clear();

	std::vector<PosRot> trapPosCopy = this->mTrapPositions;

	for (size_t i = 0; i < floor(this->mTrapPositions.size() * this->mTrapPercentage); i++)
	{
		int trapPos = rand() % trapPosCopy.size();

		PosRot temp = trapPosCopy[trapPos];
		trapPosCopy.erase(trapPosCopy.begin() + trapPos);



		if (rand() % 1000 < 500)
			this->createBoulderTrap(ai, device, context, temp, 12.f);

		else
			this->createGuillioutineTrap(ai, device, context, temp);
	}

	//***************************TREASURE*******************************
	std::vector<PosRot> treasurePosCopy = this->mTreasurePositions;

	for (size_t i = 0; i < floor(this->mTreasurePositions.size() * this->mTreasurePercentage); i++)
	{
		int treasurePos = rand() % treasurePosCopy.size();

		PosRot temp = treasurePosCopy[treasurePos];
		treasurePosCopy.erase(treasurePosCopy.begin() + treasurePos);



		if (rand() % 1000 < 500)
			this->createAhnk(device, context, temp);

		else
			this->createTreasureChest(device, context, temp);
	}

}

void EntityHandler::initialize()
{
	this->mPlayer->setPosition(DirectX::SimpleMath::Vector3(0, 0, 4));
	this->mEnemy->setPosition(DirectX::SimpleMath::Vector3(43, 0, -74));

	this->mPlayer->initialize();
}

void EntityHandler::update(ID3D11DeviceContext* context, float dt)
{
	DirectX::SimpleMath::Vector3 prevPos = this->mPlayer->getPosition();

	this->mPlayer->updatePosition(dt);
	this->mEnemy->updatePosition(this->mEntityRenderer->getGraphicsData(), context, this->mPlayer->getPosition());

	for (auto& trap : this->mTraps) {
		trap->updateAABB();
		trap->updateTransformBuffer(context, this->mEntityRenderer->getGraphicsData());
	}

	this->detectCloseTreasures();

	this->updateCollision();

	//this->updateAudio();
}

EntityRenderer* EntityHandler::getEntityRenderer()
{
	return this->mEntityRenderer;
}

Player* EntityHandler::getPlayer()
{
	return this->mPlayer;
}

Enemy* EntityHandler::getEnemy()
{
	return this->mEnemy;
}
