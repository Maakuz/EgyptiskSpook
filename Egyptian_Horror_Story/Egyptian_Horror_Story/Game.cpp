#include "Game.h"
#include "ParticleRenderer.h"

void Game::setupRenderers()
{
	mGuiRenderer = new GUIRenderer();
	this->mGraphics->addRenderer(mGuiRenderer);

	this->mGraphics->addRenderer(new ParticleRenderer(this->mCamera, mStateHandler->getState()));
	this->mGraphics->addRenderer(this->mEntityHandler->getEntityRenderer());

	this->mGraphics->setupRenderers();
	this->mGraphics->setupDSAndSRViews();

	mGuiRenderer->loadButtons(this->mMenuHandler); // Find better place to load buttons
}

void Game::setupEntityHandler()
{

	this->mEntityHandler->setupAudioManager(&this->mAudioManager);
	this->mEntityHandler->setupPlayer(this->mGraphics->getDevice(),
		this->mGraphics->getDeviceContext(),
		this->mCamera);

	this->mEntityHandler->setupEntities(this->mGraphics->getDevice());

	//this is neccessary for the traps
	this->mAIHandler = new AIHandler(mEntityHandler->getEnemy(), mEntityHandler->getPlayer());

	this->mEntityHandler->setupTraps(this->mAIHandler, this->mGraphics->getDevice(), this->mGraphics->getDeviceContext());

	this->mEntityHandler->initialize();
}

Game::Game(GraphicsHandler* mGraphicsHandler, OptionsHandler* options, SDL_Window* window) {
	this->mStateHandler = new StateHandler();
	this->mEntityHandler = new EntityHandler();

	this->mStateHandler->setState(GAMESTATE::MAIN_MENU);

	this->mGraphics = mGraphicsHandler;
	this->mOptionHandler = options;
	this->mWindow = window;

	this->mOptionHandler->setup(this->mGraphics->getDevice());
	
	this->mCamera = new CameraClass(this->mGraphics->getDevice(),
		this->mEntityHandler->getEntityRenderer()->getGraphicsData(),
		this->mOptionHandler->getGraphicSettings());

	this->setupEntityHandler();

	this->setupRenderers();
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

	this->mAIHandler->update(dt);
	if (this->mAIHandler->getNavigationTexture() != nullptr)
		mGuiRenderer->setNavigationTest(mGraphics->getDevice(), this->mAIHandler->getNavigationTexture(),
			this->mAIHandler->getNavMeshWidth(), this->mAIHandler->getNavMeshHeight());

	this->mCamera->updateRotation(this->mGraphics->getDeviceContext());

	if (this->mEntityHandler->getPlayer()->isDead())
	{
		this->mStateHandler->setState(GAMESTATE::GAME_OVER);
		SDL_SetRelativeMouseMode(SDL_bool::SDL_FALSE);
	}
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

bool Game::handleKeyboardPress(SDL_KeyboardEvent const& key)
{
	this->mEntityHandler->getPlayer()->handleKeyboardPress(key);
	this->mOptionHandler->handleButtonPress(key, this->mGraphics->getDeviceContext());

	switch (key.keysym.scancode)
	{
	case FOVUPKEY:
	case FOVDOWNKEY:
		this->mCamera->updateProjection(
			this->mGraphics->getDeviceContext(), 
			this->mOptionHandler->getGraphicSettings());
		break;
	}

	return true;
}

bool Game::handleKeyboardRelease(SDL_KeyboardEvent const& key)
{
	this->mEntityHandler->getPlayer()->handleKeyboardRelease(key);
	this->mOptionHandler->handleButtonRelease(key, this->mGraphics->getDeviceContext());

	return true;
}

void Game::handleMouseMotion(SDL_MouseMotionEvent const &motion)
{
	this->mEntityHandler->getPlayer()->handleMouseMotion(motion);
	this->mMenuHandler.mouseMotion(motion);
}

bool Game::handleMousePress(SDL_MouseButtonEvent const &button) {
	this->mStateHandler->setState(
		this->mMenuHandler.mousePress(button, this->mStateHandler->getState())
	);

	if (this->mStateHandler->getState() == PLAY)
	{
		SDL_SetRelativeMouseMode(SDL_bool::SDL_TRUE);
		this->mEntityHandler->initialize();
		this->mAIHandler->setupAI();
		this->mEntityHandler->getPlayer()->initializePlayer();
	}


	return true;
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
	int width = this->mOptionHandler->getGraphicSettings().width;
	int height = this->mOptionHandler->getGraphicSettings().height;
	SDL_SetWindowSize(window, width, height);
	this->mMenuHandler.setWindowResolution(width, height);
}
