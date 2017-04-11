#include "AIHandler.h"
#include <SDL.h> //for printing errors and stuff
#define TEST "scripts/test.lua"

AIHandler::AIHandler() {
	mState = luaL_newstate();
	luaL_loadfile(mState, TEST);
	luaL_openlibs(mState);
	int error = luaL_loadstring(mState, "printWorld()");
	
	if (error) {
		SDL_Log("Error: %s", lua_tostring(mState, -1));
		lua_pop(mState, -1);
	} else {
		lua_pcall(mState, 0, 1, 0);
		SDL_Log("Text: %s", lua_tostring(mState, -1));
		lua_pop(mState, -1);
	}
	lua_pop(mState, -1);
}

AIHandler::~AIHandler() {
	lua_close(mState);
}