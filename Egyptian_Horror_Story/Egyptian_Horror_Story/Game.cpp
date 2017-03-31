#include "Game.h"

Game::Game(GraphicsHandler* graphicsHandler, float width, float height)
{
	this->graphics = graphicsHandler;
	this->camera = new CameraClass(this->graphics->getDevice(), width, height);
	this->player = new Player(this->camera);
}

Game::~Game()
{
	delete this->camera;
	delete this->player;
}

void Game::update()
{
	this->camera->update(this->graphics->getDeviceContext());
	this->player->updatePosition();

	this->graphics->render(this->camera->getMatrixBuffer());
	this->graphics->present();
}

bool Game::handleMouseKeyPress(SDL_KeyboardEvent const& key)
{
	return this->player->handleMouseKeyPress(key);
}

bool Game::handleMouseKeyRelease(SDL_KeyboardEvent const& key)
{
	return this->player->handleMouseKeyRelease(key);
}

void Game::handleMouseMotion(SDL_MouseMotionEvent const &motion)
{
	this->player->handleMouseMotion(motion);
}
