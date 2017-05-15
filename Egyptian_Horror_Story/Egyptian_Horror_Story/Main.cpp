#include "Window.h"
#include "GraphicsHandler.h"
#include "OptionsHandler.h"

OptionsHandler gOptionsHandler;
GraphicsHandler gGraphicsHandler(&gOptionsHandler);
Window gWindow;

int main(int argc, char *args[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	gWindow.setupWindowAndSDL(
		gOptionsHandler.getGraphicSettings().width,
		gOptionsHandler.getGraphicSettings().height);

	gGraphicsHandler.setupSwapChain();
	gGraphicsHandler.setupViewport(
		gOptionsHandler.getGraphicSettings().width,
		gOptionsHandler.getGraphicSettings().height);
	gGraphicsHandler.setupSamplerState();

	gWindow.startWindowLoop(&gGraphicsHandler, &gOptionsHandler);

	return 0;
}