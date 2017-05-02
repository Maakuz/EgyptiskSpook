#include "Game.h"
#include "ShadowRenderer.h"
#include "ParticleRenderer.h"

Game::Game(GraphicsHandler* mGraphicsHandler, float width, float height)
{
	this->mGraphics = mGraphicsHandler;

	this->mEntityHandler = new EntityHandler();

	this->mCamera = new CameraClass(this->mGraphics->getDevice(),
		this->mEntityHandler->getEntityRenderer()->getGraphicsData(),
		this->mEntityHandler->getRiggedEntityRenderer()->getGraphicsData(),
		width, height);
	

	this->mEntityHandler->setupPlayer(this->mGraphics->getDevice(), 
		this->mGraphics->getDeviceContext(),
		this->mCamera);

	this->mEntityHandler->setupEntities(this->mGraphics->getDevice());

	mGuiRenderer = new GUIRenderer();
	this->mGraphics->addRenderer(mGuiRenderer);

	this->mGraphics->addRenderer(new ParticleRenderer(this->mCamera));
	this->mGraphics->addRenderer(this->mEntityHandler->getEntityRenderer());
	this->mGraphics->addRenderer(this->mEntityHandler->getRiggedEntityRenderer());

	this->mGraphics->setupRenderers();
	this->mGraphics->setupLightViewport(mEntityHandler->getPlayer()->getLight());
	this->mGraphics->setupDSAndSRViews();

	this->mAIHandler = new AIHandler(mEntityHandler->getEnemy(), mEntityHandler->getPlayer());

	//this->mGraphics->addRenderer(new ShadowRenderer(this->mEntityHandler->getPlayer()->getLight()));

	this->mAudioManager.playSfx();
}

Game::~Game()
{
	delete this->mCamera;
	delete this->mEntityHandler;
	delete this->mAIHandler;
}

void Game::update()
{
	this->mEntityHandler->update(this->mGraphics->getDeviceContext());
	this->mCamera->update(this->mGraphics->getDeviceContext());

	this->mGraphics->clear();
	this->mGraphics->renderRenderers(this->mCamera->getMatrixBuffer(), this->mEntityHandler->getEntityRenderer()->getGraphicsData()->getConstantBuffer(301));
	this->mGraphics->present();

	this->mAIHandler->update();
	if (this->mAIHandler->getNavigationTexture() != nullptr)
		mGuiRenderer->setNavigationTest(mGraphics->getDevice(), this->mAIHandler->getNavigationTexture(),
			this->mAIHandler->getNavMeshWidth(), this->mAIHandler->getNavMeshHeight());
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

void Game::updateLua() {
	this->mAIHandler->setupAI();
}