#include "Game.h"
#include "ShadowRenderer.h"
#include "ParticleRenderer.h"

Game::Game(GraphicsHandler* mGraphicsHandler, float width, float height)
{
	this->mGraphics = mGraphicsHandler;
	this->mCamera = new CameraClass(this->mGraphics->getDevice(), width, height);
	
	this->mEntityHandler = new EntityHandler();

	this->mEntityHandler->setupPlayer(this->mGraphics->getDevice(), 
		this->mGraphics->getDeviceContext(),
		this->mCamera, 
		this->mEntityHandler->getRenderer()->getGraphicsData());

	this->mEntityHandler->setupEntities(this->mGraphics->getDevice());

	this->mGraphics->addRenderer(new ParticleRenderer(this->mCamera)); // temp
	this->mGraphics->addRenderer(this->mEntityHandler->getRenderer());
	this->mGraphics->addRenderer(new ParticleRenderer(this->mCamera)); // temp

	this->mGraphics->setupRenderers();


	//this->mGraphics->addRenderer(new ShadowRenderer(this->mEntityHandler->getPlayer()->getLight()));
}

Game::~Game()
{
	delete this->mCamera;
	delete this->mEntityHandler;
}

void Game::update()
{
	this->mCamera->update(this->mGraphics->getDeviceContext());
	this->mEntityHandler->update();

	this->mGraphics->clear();
	this->mGraphics->renderRenderers(this->mCamera->getMatrixBuffer());
	this->mGraphics->present();
}

bool Game::handleMouseKeyPress(SDL_KeyboardEvent const& key)
{
	return this->mEntityHandler->getPlayer()->handleMouseKeyPress(key);
}

bool Game::handleMouseKeyRelease(SDL_KeyboardEvent const& key)
{
	return this->mEntityHandler->getPlayer()->handleMouseKeyRelease(key);
}

void Game::handleMouseMotion(SDL_MouseMotionEvent const &motion)
{
	this->mEntityHandler->getPlayer()->handleMouseMotion(motion);
	this->mCamera->updateRotation(this->mGraphics->getDeviceContext());
}
