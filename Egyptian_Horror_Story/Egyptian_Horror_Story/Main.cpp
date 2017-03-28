#include "Window.h"
#include "GraphicsHandler.h"

Window gWindow;
GraphicsHandler gGraphicsHandler;

int main(int argc, char *args[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	gWindow.setupWindowAndSDL();

	gGraphicsHandler.setupSwapChain();
	gGraphicsHandler.setupViewport(WIDTH, HEIGHT);
	gGraphicsHandler.setupBasicShaders();

	gWindow.startWindowLoop(gGraphicsHandler);

	return 0;
}