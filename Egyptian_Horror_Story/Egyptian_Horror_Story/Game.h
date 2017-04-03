#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"
#include "Player.h"
#include "CameraClass.h"

class Game
{
private:
	GraphicsHandler* mGraphics;
	Player* mPlayer;
	CameraClass* mCamera;

public:
	Game(GraphicsHandler* graphicsHandler, float width, float height);
	virtual ~Game();

	void update();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
};


#endif