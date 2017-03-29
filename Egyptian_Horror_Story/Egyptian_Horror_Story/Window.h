#pragma once
#include <SDL.h>
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
	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	Window* operator=(Window const &window) = delete;
};