#include "Window.h"

Window::Window() {
	mRunning = false;
	mWindow = nullptr;

	this->mGame = nullptr;
}

Window::~Window() {
	delete this->mGame;

	if (!mWindow)
		SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

bool Window::setupWindowAndSDL() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO); //to use SDL_Log

	mWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow == NULL) {
		SDL_Log("Window creation error ", SDL_GetError());
		return false;
	} else
		return true;
}

void Window::startWindowLoop(GraphicsHandler* graphicsHandler) {
	mRunning = true;
	SDL_Event event;

	this->mGame = new Game(graphicsHandler, WIDTH, HEIGHT);
	
	while (mRunning) {
		while (SDL_PollEvent(&event)) {
			if (!handleEvent(event))
				mRunning = false;
		}

		//do stuff
		this->mGame->update();

		SDL_Delay(5); // 5 ms delay per frame
	}
}

bool Window::handleEvent(SDL_Event const &event) {
	switch (event.type) {
	case SDL_QUIT:
		return false; //quit
	case SDL_KEYDOWN:
		return handleKeyPress(event.key);

	case SDL_KEYUP:
		return handleKeyRelease(event.key);

	case SDL_MOUSEMOTION:
		this->handleMouseMotion(event.motion);
	}



	return true;
}

bool Window::handleKeyPress(SDL_KeyboardEvent const &key) {
	switch (key.keysym.scancode) {
		case SDL_SCANCODE_ESCAPE:
			return false;
		case SDL_SCANCODE_RSHIFT:
			//change from fullscreen and back
			SDL_SetWindowFullscreen(mWindow, SDL_GetWindowFlags(mWindow) ^ SDL_WINDOW_FULLSCREEN);
		default:
			this->mGame->handleMouseKeyPress(key);
	}

	return true;
}

bool Window::handleKeyRelease(SDL_KeyboardEvent const &key)
{
	this->mGame->handleMouseKeyRelease(key);

	return true;
}

void Window::handleMouseMotion(SDL_MouseMotionEvent const &motion)
{
	this->mGame->handleMouseMotion(motion);
}