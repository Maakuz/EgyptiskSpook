#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"
#include "EntityHandler.h"
#include "GUIRenderer.h"

class Game
{
private:

	class StateHandler {
	private:
		GAMESTATE state;
	public:
		GAMESTATE getState();
		void setState(GAMESTATE state);
		void update(Game* g, float dt);
	}* mStateHandler;

	GraphicsHandler* mGraphics;
	CameraClass* mCamera;
	EntityHandler* mEntityHandler;
	AIHandler* mAIHandler;
	GUIRenderer *mGuiRenderer; //temp
	AudioManager mAudioManager;
	OptionsHandler* mOptionHandler;

	void setupRenderers();
	void setupEntityHandler();
public:
	Game(GraphicsHandler* graphicsHandler, OptionsHandler* options);
	virtual ~Game();

	void updateGame(float dt);
	void update(float dt);
	void draw();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	void updateLua();
	void setWindowSize(SDL_Window* window);
};


#endif