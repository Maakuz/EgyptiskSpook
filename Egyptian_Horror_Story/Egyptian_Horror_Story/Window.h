#ifndef WINDOW_H
#define WINDOW_H

#include "Game.h"

#define TITLE "Cool Egypt Game"

class Window {
private:
	SDL_Window *mWindow;
	bool mRunning;
	Game* mGame;
	SDL_bool mLockCursor;
public:
	Window();
	Window(Window const &window) = delete;
	~Window();

	// returns false for fail
	bool setupWindowAndSDL(int width, int height);
	void startWindowLoop(GraphicsHandler* graphicsHandler, OptionsHandler* options);
	// returns false for quit event
	bool handleEvent(SDL_Event const &event);
	bool handleKeyPress(SDL_KeyboardEvent const &key);
	bool handleKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	Window* operator=(Window const &window) = delete;
};

#endif