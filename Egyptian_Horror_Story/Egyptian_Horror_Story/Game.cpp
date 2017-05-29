#include "Game.h"
#include "ParticleRenderer.h"

void Game::checkVictory()
{
	DirectX::SimpleMath::Vector3 pos = this->mEntityHandler->getPlayer()->getPosition();

	if (pos.x > 74 && pos.x < 80 && pos.z > -50 && pos.z < -43)
	{
		this->mVictory = true;
	}

	if (this->mVictory)
	{
		this->mEntityHandler->getEntityRenderer()->setFadeout(
			this->mEntityHandler->getEntityRenderer()->getFadeout() - 0.003f,
			this->mGraphics->getDeviceContext());

		if (this->mEntityHandler->getEntityRenderer()->getFadeout() < 0)
		{
			SDL_SetRelativeMouseMode(SDL_bool::SDL_FALSE);
			this->mStateHandler->setState(GAMESTATE::GAME_OVER);
		}
	}
}

void Game::setupRenderers()
{
	mGuiRenderer = new GUIRenderer();
	this->mSkyRenderer = new SkyRenderer();
	this->mGraphics->addRenderer(mGuiRenderer);

	this->mGraphics->addRenderer(new ParticleRenderer(this->mCamera, GAMESTATE::PLAY));
	this->mGraphics->addRenderer(this->mEntityHandler->getEntityRenderer());
	this->mGraphics->addRenderer(this->mSkyRenderer);

	this->mGraphics->setupRenderers();
	this->mGraphics->setupDSAndSRViews();

	mGuiRenderer->loadButtons(this->mMenuHandler);
}

void Game::setupEntityHandler()
{

	this->mEntityHandler->setupAudioManager(&this->mAudioManager);
	this->mEntityHandler->setupPlayer(this->mGraphics->getDevice(),
		this->mGraphics->getDeviceContext(),
		this->mCamera);

	//this is neccessary for the traps
	this->mAIHandler = new AIHandler(mEntityHandler->getEnemy(), mEntityHandler->getPlayer());
	
	this->mEntityHandler->setupEntities(this->mAIHandler, this->mGraphics->getDevice());

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
	this->mSkyRenderer->updateTransform(this->mCamera->getPos(), this->mGraphics->getDeviceContext());



	if (this->mEntityHandler->getPlayer()->isDead())
	{
		this->mStateHandler->setState(GAMESTATE::GAME_OVER);
		SDL_SetRelativeMouseMode(SDL_bool::SDL_FALSE);
	}

	this->checkVictory();
}

void Game::draw() {
	this->mGraphics->clear();
	this->mGraphics->renderRenderers(this->mCamera->getMatrixBuffer(),
									this->mEntityHandler->getEntityRenderer()->getGraphicsData()->getConstantBuffer(301),
									mStateHandler->getState());
	this->mGraphics->present();
}

void Game::initialize()
{
	this->mEntityHandler->getEntityRenderer()->setFadeout(1, this->mGraphics->getDeviceContext());
	this->mVictory = false;
	this->mEntityHandler->initialize();
	this->mEntityHandler->initializeTreasureAndTraps(this->mAIHandler, this->mGraphics->getDevice());
	this->mAIHandler->setupAI();
}

void Game::update(float dt) {
	this->mStateHandler->update(this, dt);
}

bool Game::handleKeyboardPress(SDL_KeyboardEvent const& key)
{
	DirectX::SimpleMath::Vector3 pos = this->mEntityHandler->getPlayer()->getPosition();
	this->mEntityHandler->getPlayer()->handleKeyboardPress(key);
	this->mOptionHandler->handleButtonPress(key, this->mGraphics->getDeviceContext());

	switch (key.keysym.scancode)
	{
	case SDL_SCANCODE_Q:
		SDL_Log("x = %f, y = %f, z = %f", pos.x, pos.y, pos.z); // TESTING METHOD
		break;
	case SDL_SCANCODE_R:
	{
		// CHANGE THIS IF IMG SIZE IS CHANGED
		DirectX::SimpleMath::Vector2 img = this->mEntityHandler->getPosition(pos.x, pos.z, 56, 86);
		SDL_Log("Px = %f, Py = %f", img.x, img.y); // TESTING METHOD
		break;
	}
	case FOVUPKEY:
		break;
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

	if (key.keysym.scancode == SDL_SCANCODE_2)
		this->mEntityHandler->initializeTreasureAndTraps(this->mAIHandler, this->mGraphics->getDevice());

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

	if (this->mStateHandler->needsInitialize)
	{
		this->mStateHandler->needsInitialize = false;

		SDL_SetRelativeMouseMode(SDL_bool::SDL_TRUE);
		this->initialize();
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

	//TODO: IF THERE EVER IS A STATE THAT DOES NOT RESTART THIS NEEDS TO BE CHANGED
	if (state == GAMESTATE::PLAY && this->state != GAMESTATE::PLAY)
		this->needsInitialize = true;

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
