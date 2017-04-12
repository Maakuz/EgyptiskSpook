#include "AIHandler.h"
#include <SDL.h> //for printing errors and stuff
#define TEST "scripts/test.lua"
#define AI "scripts/EnemyAI.lua"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

AIHandler::AIHandler(Enemy *enemy, Player *player) :
	mEnemy(enemy), mPlayer(player) {
	mState = luaL_newstate();

	setupAI();
}

AIHandler::~AIHandler() {
	lua_close(mState);
}

void AIHandler::setupAI() {
	int error = luaL_loadfile(mState, AI) || lua_pcall(mState, 0, 0, 0);
	handleError(error);

	lua_pushlightuserdata(mState, mEnemy);
	lua_pushcclosure(mState, setEnemySpeed, 1);
	lua_setglobal(mState, "SetEnemySpeed");
}

void AIHandler::update() {
	lua_getglobal(mState, "enemySpeed");
	float speed = 0;
	
	if (lua_isnumber(mState, -1))
		speed = lua_tonumber(mState, -1);

	lua_pop(mState, 1);

	Vector3 enemyToPlayer = mPlayer->getPosition() - mEnemy->getPosition();

	lua_getglobal(mState, "SeesPlayer");
	lua_pushnumber(mState, enemyToPlayer.Length());
	if (handleError(lua_pcall(mState, 1, 1, 0))) {
		/*
		if (lua_isboolean(mState, -1))
			if (!lua_toboolean(mState, -1)) //doesnt see player
				mEnemy->setSpeed(0);
			else
				mEnemy->setSpeed(speed);
		lua_pop(mState, 1);
		*/
	}

	enemyToPlayer.Normalize();
	mEnemy->setVelocity(enemyToPlayer);
	mEnemy->update();
}

// LUA
int AIHandler::setEnemySpeed(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	if (lua_isnumber(state, -1)) {
		enemy->setSpeed(lua_tonumber(state, -1));
		lua_pop(state, 1);
	}

	return 0;
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

// FOR TESTING -- REMOVE
void AIHandler::testScript() {
	lua_State *test = luaL_newstate();

	int error = luaL_loadfile(test, TEST) || lua_pcall(test, 0, 0, 0);
	if (handleError(error)) {
		luaL_openlibs(test);

		lua_getglobal(test, "hello");
		SDL_Log("Text1: %s", lua_tostring(test, -1));
		lua_pop(test, 1);

		lua_getglobal(test, "PrintWorld");
		error = lua_pcall(test, 0, 1, 0);
		if (handleError(error)) {
			SDL_Log("Text2: %s", lua_tostring(test, -1));
			lua_pop(test, 1);
		}
	}

	lua_close(test);
}