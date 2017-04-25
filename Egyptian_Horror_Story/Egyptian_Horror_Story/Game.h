#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"
#include "EntityHandler.h"
#include "CameraClass.h"


class Game {
private:
	class StateHandler{
	public:
		int state;
		void update(int i, Game* g);
		StateHandler(int i);

	}* mStateHandler;

	GraphicsHandler* mGraphics;
	CameraClass* mCamera;
	EntityHandler* mEntityHandler;


public:
	Game(GraphicsHandler* graphicsHandler, float width, float height);
	virtual ~Game();
	void updateGame();
	void update();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
};


#endif