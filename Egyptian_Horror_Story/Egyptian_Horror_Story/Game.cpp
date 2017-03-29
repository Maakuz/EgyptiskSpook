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
	this->graphics->render(this->camera->getMatrixBuffer());
	this->graphics->present();
}
