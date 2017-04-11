#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"
#include "EntityHandler.h"
#include "CameraClass.h"
#include "AIHandler.h"

class Game
{
private:
	GraphicsHandler* mGraphics;
	CameraClass* mCamera;
	EntityHandler* mEntityHandler;
	AIHandler* mAIHandler;
public:
	Game(GraphicsHandler* graphicsHandler, float width, float height);
	virtual ~Game();

	void update();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	void updateLua();
};


#endif