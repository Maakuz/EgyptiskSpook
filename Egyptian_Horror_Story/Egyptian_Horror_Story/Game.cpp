#include "Game.h"
#include "ParticleRenderer.h"

Game::Game(GraphicsHandler* mGraphicsHandler, OptionsHandler* options) {
	this->mStateHandler = new StateHandler();
	this->mStateHandler->setState(GAMESTATE::PLAY);

	this->mGraphics = mGraphicsHandler;
	this->mOptionHandler = options;

	this->mOptionHandler->setup(this->mGraphics->getDevice());

	this->mEntityHandler = new EntityHandler();

	this->mCamera = new CameraClass(this->mGraphics->getDevice(),
		this->mEntityHandler->getEntityRenderer()->getGraphicsData(),
		this->mOptionHandler->getGraphicSettings()
	);
	
	this->mEntityHandler->setupAudioManager(&this->mAudioManager);
	this->mEntityHandler->setupPlayer(this->mGraphics->getDevice(), 
		this->mGraphics->getDeviceContext(),
		this->mCamera);

	this->mEntityHandler->setupEntities(this->mGraphics->getDevice());
	
	mGuiRenderer = new GUIRenderer();
	this->mGraphics->addRenderer(mGuiRenderer);

	this->mGraphics->addRenderer(new ParticleRenderer(this->mCamera, mStateHandler->getState()));
	this->mGraphics->addRenderer(this->mEntityHandler->getEntityRenderer());

	this->mGraphics->setupRenderers();
	this->mGraphics->setupLightViewport(mEntityHandler->getPlayer()->getLight());
	this->mGraphics->setupDSAndSRViews();

	this->mAIHandler = new AIHandler(mEntityHandler->getEnemy(), mEntityHandler->getPlayer());

	this->mEntityHandler->setupTraps(this->mAIHandler, this->mGraphics->getDevice(), this->mGraphics->getDeviceContext());
}

Game::~Game()
{
	delete this->mStateHandler;
	delete this->mCamera;
	delete this->mEntityHandler;
	delete this->mAIHandler;
}

void Game::updateGame(float dt)
{
	this->mEntityHandler->update(this->mGraphics->getDeviceContext(), dt);
	this->mCamera->update(this->mGraphics->getDeviceContext());

	this->mAIHandler->update();
	if (this->mAIHandler->getNavigationTexture() != nullptr)
		mGuiRenderer->setNavigationTest(mGraphics->getDevice(), this->mAIHandler->getNavigationTexture(),
			this->mAIHandler->getNavMeshWidth(), this->mAIHandler->getNavMeshHeight());

}

void Game::draw() {
	this->mGraphics->clear();
	this->mGraphics->renderRenderers(this->mCamera->getMatrixBuffer(),
									this->mEntityHandler->getEntityRenderer()->getGraphicsData()->getConstantBuffer(301),
									mStateHandler->getState());
	this->mGraphics->present();
}

void Game::update(float dt) {
	this->mStateHandler->update(this, dt);
}

bool Game::handleMouseKeyPress(SDL_KeyboardEvent const& key)
{
	bool res = this->mEntityHandler->getPlayer()->handleMouseKeyPress(key);

	if (res)
		this->mOptionHandler->handleButtonPress(key, this->mGraphics->getDeviceContext());
	else
		res = this->mOptionHandler->handleButtonPress(key, this->mGraphics->getDeviceContext());

	switch (key.keysym.scancode)
	{
	case FOVUPKEY:
	case FOVDOWNKEY:
		this->mCamera->updateProjection(
			this->mGraphics->getDeviceContext(), 
			this->mOptionHandler->getGraphicSettings());
		break;
	}

	return res;
}

bool Game::handleMouseKeyRelease(SDL_KeyboardEvent const& key)
{
	bool res = this->mEntityHandler->getPlayer()->handleMouseKeyRelease(key);

	if (res)
		this->mOptionHandler->handleButtonRelease(key, this->mGraphics->getDeviceContext());

	else
		res = this->mOptionHandler->handleButtonRelease(key, this->mGraphics->getDeviceContext());

	return res;
}

void Game::handleMouseMotion(SDL_MouseMotionEvent const &motion)
{
	this->mEntityHandler->getPlayer()->handleMouseMotion(motion);
	this->mCamera->updateRotation(this->mGraphics->getDeviceContext());
}

void Game::updateLua() {
	this->mAIHandler->setupAI();
}

GAMESTATE Game::StateHandler::getState() {
	return this->state;
}

void Game::StateHandler::setState(GAMESTATE state) {
	this->state = state;
}

void Game::StateHandler::update(Game* g, float dt) {
	switch (this->state) {
	case GAMESTATE::DEFAULT:
		break;
	case GAMESTATE::MAIN_MENU:
		break;
	case GAMESTATE::PLAY:
		g->updateGame(dt);
		break;
	}
}

void Game::setWindowSize(SDL_Window* window) {
	SDL_SetWindowSize(window, 
		this->mOptionHandler->getGraphicSettings().width, 
		this->mOptionHandler->getGraphicSettings().height);
}
