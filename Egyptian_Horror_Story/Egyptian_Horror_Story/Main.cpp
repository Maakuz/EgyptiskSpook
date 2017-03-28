#include "Window.h"

Window gWindow;

int main(int argc, char *args[]) {
	gWindow.setupWindowAndSDL();
	gWindow.startWindowLoop();

	return 0;
}