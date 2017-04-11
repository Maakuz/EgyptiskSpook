#include "AIHandler.h"
#include <SDL.h> //for printing errors and stuff
#define TEST "scripts/test.lua"
#define AI "scripts/EnemyAI.lua"

AIHandler::AIHandler(Enemy *enemy, Player *player) :
	mEnemy(enemy), mPlayer(player) {
	mState = luaL_newstate();

	setupAI();
}

AIHandler::~AIHandler() {
	lua_close(mState);
}

void AIHandler::setupAI() {

}

void AIHandler::update() {
	int error = luaL_loadfile(mState, TEST) || lua_pcall(mState, 0, 0, 0);
	handleError(error);
}

// private
bool inline AIHandler::handleError(int error) {
	if (error) {
			SDL_Log("Error: %s", lua_tostring(mState, -1));
			lua_pop(mState, 1);
			return false;
	}
	
	return true;
}

// FOR TESTING
void AIHandler::testScript() {
	lua_State *test = luaL_newstate();

	int error = luaL_loadfile(mState, TEST) || lua_pcall(mState, 0, 0, 0);
	if (handleError(error)) {
		luaL_openlibs(mState);

		lua_getglobal(mState, "hello");
		SDL_Log("Text1: %s", lua_tostring(mState, -1));
		lua_pop(mState, 1);

		lua_getglobal(mState, "PrintWorld");
		error = lua_pcall(mState, 0, 1, 0);
		if (handleError(error)) {
			SDL_Log("Text2: %s", lua_tostring(mState, -1));
			lua_pop(mState, 1);
		}
	}

	lua_close(test);
}