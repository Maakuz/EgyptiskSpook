#include "Game.h"
#include "ShadowRenderer.h"
#include "ParticleRenderer.h"

Game::Game(GraphicsHandler* mGraphicsHandler, float width, float height)
{
	this->mStateHandler = new StateHandler(GAMESTATE::MAIN_MENU);
	this->mGraphics = mGraphicsHandler;
	this->mCamera = new CameraClass(this->mGraphics->getDevice(), width, height);
	
	this->mEntityHandler = new EntityHandler(GAMESTATE::PLAY);

	this->mEntityHandler->setupPlayer(this->mGraphics->getDevice(), 
		this->mGraphics->getDeviceContext(),
		this->mCamera, 
		this->mEntityHandler->getRenderer()->getGraphicsData());

	this->mEntityHandler->setupEntities(this->mGraphics->getDevice());

	this->mGraphics->addRenderer(new ParticleRenderer(GAMESTATE::PLAY, this->mCamera));
	this->mGraphics->addRenderer(this->mEntityHandler->getRenderer());

	this->mGraphics->setupRenderers();


	//this->mGraphics->addRenderer(new ShadowRenderer(this->mEntityHandler->getPlayer()->getLight()));
}

Game::~Game()
{
	delete this->mStateHandler;
	delete this->mCamera;
	delete this->mEntityHandler;
}

void Game::updateGame() {
	this->mCamera->update(this->mGraphics->getDeviceContext());
	this->mEntityHandler->update();

	this->mGraphics->clear();
	this->mGraphics->renderRenderers(this->mCamera->getMatrixBuffer(), GAMESTATE::PLAY);
	this->mGraphics->present();
}

void Game::update() {
	this->mStateHandler->update(this->mStateHandler->state, this);
}

bool Game::handleMouseKeyPress(SDL_KeyboardEvent const& key)
{
	return this->mEntityHandler->getPlayer()->handleMouseKeyPress(key); //Skumt.
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

void Game::StateHandler::update(int i, Game* g) {
	switch(i) {
	case GAMESTATE::MAIN_MENU:
		break;
	case GAMESTATE::PLAY:
		g->updateGame();
		break;
	}
}

Game::StateHandler::StateHandler(int i) {
	this->state = i;
}
