#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"
#include "EntityHandler.h"
#include "CameraClass.h"
#include "AIHandler.h"
#include "GUIRenderer.h"
#include "AudioManager.h"

class Game
{
private:

	class StateHandler {
	private:
		int state;
	public:
		int getState();
		void setState(int i);
		void update(Game* g);
	}* mStateHandler;

	GraphicsHandler* mGraphics;
	CameraClass* mCamera;
	EntityHandler* mEntityHandler;
	AIHandler* mAIHandler;
	GUIRenderer *mGuiRenderer; //temp
	AudioManager mAudioManager;
public:
	Game(GraphicsHandler* graphicsHandler, float width, float height);
	virtual ~Game();

	void updateGame();
	void update();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	void updateLua();
};


#endif