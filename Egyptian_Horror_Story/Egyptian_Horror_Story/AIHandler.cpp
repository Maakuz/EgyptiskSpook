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

	addLuaFunctions(mState);

	lua_getglobal(mState, "enemySpeed");
	float speed = 0;

	if (lua_isnumber(mState, -1)) {
		speed = lua_tonumber(mState, -1);
		mEnemy->setSpeed(speed);
	} else {
		mEnemy->setSpeed(0);
	}

	lua_pop(mState, 1);
}

void AIHandler::addLuaFunctions(lua_State *state) {
	// ENEMY SPEED & POSITION
	void *userData[] = { mEnemy };
	addLuaFunction(state, "SetEnemySpeed", setEnemySpeed, userData, ARRAYSIZE(userData));
	addLuaFunction(state, "GetEnemyPosition", getEntityPosition, userData, ARRAYSIZE(userData));
	
	// PLAYER POSITION
	void *userData2[] = { mPlayer };
	addLuaFunction(state, "GetPlayerPosition", getEntityPosition, userData2, ARRAYSIZE(userData2));
	
	// GET DISTANCE BEETWEN
	void *userData3[] = { mEnemy, mPlayer };
	addLuaFunction(state, "GetDistanceBetween", getDistanceBetween, userData3, ARRAYSIZE(userData3));
}

void AIHandler::addLuaFunction(lua_State *state, const char *name,
	lua_CFunction func, void *userData[], int size) {
	for (int i = 0; i < size; i++) {
		lua_pushlightuserdata(state, userData[i]);
	}

	if(size > 0) lua_pushcclosure(state, func, size);
	else lua_pushcfunction(state, func);

	lua_setglobal(state, name);
}

void AIHandler::update() {
	Vector3 enemyToPlayer = mPlayer->getPosition() - mEnemy->getPosition();
	
	lua_getglobal(mState, "update");
	lua_pcall(mState, 0, 0, 0);

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

int AIHandler::getEntityPosition(lua_State *state) {
	Entity *entity = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	Vector3 position = entity->getPosition();
	lua_pushnumber(state, position.x);
	lua_pushnumber(state, position.y);
	lua_pushnumber(state, position.z);
	return 3;
}

int AIHandler::getDistanceBetween(lua_State *state) {
	Entity *entity1 = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	Entity *entity2 = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(2)));

	Vector3 eToE2 = entity1->getPosition() - entity2->getPosition();

	lua_pushnumber(state, eToE2.Length());

	return 1;
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