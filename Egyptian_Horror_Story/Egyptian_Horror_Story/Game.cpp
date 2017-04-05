#include "Game.h"
#include "ShadowRenderer.h"

Game::Game(GraphicsHandler* mGraphicsHandler, float width, float height)
{
	this->mGraphics = mGraphicsHandler;
	this->mCamera = new CameraClass(this->mGraphics->getDevice(), width, height);
	this->mPlayer = new Player(this->mCamera, this->mGraphics->getDevice());

	//test
	this->mWall = new Wall(
		DirectX::SimpleMath::Vector3(-1.f, -1.f, 0.f),
		DirectX::SimpleMath::Vector3(2.f, 0.f, 0.f),
		DirectX::SimpleMath::Vector3(0.f, 2.f, 0.f),
		DirectX::SimpleMath::Vector3(0.f, 0.f, 2.f));

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

	this->mWall->getRenderer()->loadObject(this->mGraphics->getDevice(), testData, 6,
		L"../Resource/Textures/normalMap.png");

	//another test
	this->mEntity = new Entity();

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

	this->mEntity->getRenderer()->loadObject(this->mGraphics->getDevice(), testData2, 6,
		L"../Resource/Textures/normalMap.png");

	//Borde inte objektet ha renderern och sedan skicka en 
	//pekare till graphicshandlern i stället?
	this->mGraphics->addRenderer(this->mWall->getRenderer());
	this->mGraphics->addRenderer(this->mEntity->getRenderer());
	this->mGraphics->addRenderer(new ShadowRenderer(mPlayer->getLight()));
	this->mGraphics->setupRenderers();

	this->mPlayer->setPosition(DirectX::SimpleMath::Vector3(0, 0, -5));


		
	
}

Game::~Game()
{
	delete this->mCamera;
	delete this->mPlayer;
	delete this->mWall;
	delete this->mEntity;
}

void Game::update()
{
	this->mCamera->update(this->mGraphics->getDeviceContext());

	DirectX::SimpleMath::Vector3 prevPos = this->mPlayer->getPosition();

	this->mPlayer->updatePosition();

	//test
	if (this->mWall->getOBB().obbVSPoint(this->mPlayer->getPosition()))
	{
		this->mPlayer->setPosition(this->mPlayer->getPosition() + mWall->getNormal() * 0.03f);
	}
	

	this->mGraphics->clear();
	this->mGraphics->renderRenderers(this->mCamera->getMatrixBuffer());
	this->mGraphics->present();
}

bool Game::handleMouseKeyPress(SDL_KeyboardEvent const& key)
{
	return this->mPlayer->handleMouseKeyPress(key);
}

bool Game::handleMouseKeyRelease(SDL_KeyboardEvent const& key)
{
	return this->mPlayer->handleMouseKeyRelease(key);
}

void Game::handleMouseMotion(SDL_MouseMotionEvent const &motion)
{
	this->mPlayer->handleMouseMotion(motion);
	this->mCamera->updateRotation(this->mGraphics->getDeviceContext());
}
