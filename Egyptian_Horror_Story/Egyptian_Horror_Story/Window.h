#pragma once
#include "Game.h"

#define WIDTH 1080
#define HEIGHT 720
#define TITLE "Cool Egypt Game"

class Window {
private:
	SDL_Window *mWindow;
	bool mRunning;

	Game* mGame;
public:
	Window();
	Window(Window const &window) = delete;
	~Window();

	// returns false for fail
	bool setupWindowAndSDL();
	void startWindowLoop(GraphicsHandler* graphicsHandler);
	// returns false for quit event
	bool handleEvent(SDL_Event const &event);
	bool handleKeyPress(SDL_KeyboardEvent const &key);
	bool handleKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	Window* operator=(Window const &window) = delete;
};