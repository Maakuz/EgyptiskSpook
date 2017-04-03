#include "Game.h"
#include "ShadowRenderer.h"

Game::Game(GraphicsHandler* mGraphicsHandler, float width, float height)
{
	this->mGraphics = mGraphicsHandler;
	this->mCamera = new CameraClass(this->mGraphics->getDevice(), width, height);
	this->mPlayer = new Player(this->mCamera, this->mGraphics->getDevice());

	this->mGraphics->addRenderer(new ShadowRenderer(mPlayer->getLight()));
	this->mGraphics->setupRenderers();
	
	this->mGraphics->setupTestData();
	this->mGraphics->setupFloor();
}

Game::~Game()
{
	delete this->mCamera;
	delete this->mPlayer;
}

void Game::update()
{
	this->mCamera->update(this->mGraphics->getDeviceContext());
	this->mPlayer->updatePosition();

	this->mGraphics->renderRenderers();
	this->mGraphics->render(this->mCamera->getMatrixBuffer());
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
