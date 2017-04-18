#include "AIHandler.h"
#include <SDL.h> //for printing errors and stuff
#define TEST "scripts/test.lua"
#define AI "scripts/EnemyAI.lua"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

AIHandler::AIHandler(Enemy *enemy, Player *player) :
	mEnemy(enemy), mPlayer(player) {
	mEnemyState = luaL_newstate();

	// TESTING
	testTrap = new Trap(0, 17, 0, -74);
	addTrap("scripts/TrapStone.lua", testTrap);

	setupAI();
}

AIHandler::~AIHandler() {
	lua_close(mEnemyState);

	for (TrapScript &trap : mTraps) {
		lua_close(trap.state);
	}

	// TESTING
	delete testTrap;
}

void AIHandler::setupTraps() {
	for (TrapScript &trap : mTraps) {
		lua_State *state = trap.state;

		lua_getglobal(state, "onStart");
		handleError(state, lua_pcall(state, 0, 0, 0));

		lua_getglobal(state, "getSize");
		handleError(state, lua_pcall(state, 0, 3, 0));

		if (lua_isnumber(state, -1) && lua_isnumber(state, -2) &&
			lua_isnumber(state, -3)) {
			trap.trap->createAABB(trap.trap->getPosition(), Vector3(lua_tonumber(state, -3), 0, 0),
								  Vector3(0, lua_tonumber(state, -2), 0), Vector3(0, 0, lua_tonumber(state, -1)));
			lua_pop(state, 3);
		}
	}
}

void AIHandler::addTrap(char const *scriptPath, Trap *trap) {
	lua_State *state = luaL_newstate();
	int error = luaL_loadfile(state, scriptPath) || lua_pcall(state, 0, 0, 0);
	handleError(state, error);
	luaL_openlibs(state);

	TrapScript script { trap, state };
	addLuaFunctionsTrap(state, trap);
	mTraps.push_back(script);
}

void AIHandler::setupEnemy() {
	int error = luaL_loadfile(mEnemyState, AI) || lua_pcall(mEnemyState, 0, 0, 0);
	handleError(mEnemyState, error);
	luaL_openlibs(mEnemyState);

	addLuaFunctionsEnemy();
	lua_getglobal(mEnemyState, "onStart");
	handleError(mEnemyState, lua_pcall(mEnemyState, 0, 0, 0));
}


void AIHandler::setupAI() {
	setupEnemy();
	setupTraps();
}

void AIHandler::addLuaFunctionsEnemy() {
	// For testing
	addLuaFunction(mEnemyState, "Log", log, nullptr, 0);

	// ENEMY SPEED & POSITION
	void *userData[] = { mEnemy };
	addLuaFunction(mEnemyState, "SetEnemySpeed", setEnemySpeed, userData, ARRAYSIZE(userData));
	addLuaFunction(mEnemyState, "GetEnemyPosition", getEntityPosition, userData, ARRAYSIZE(userData));
	addLuaFunction(mEnemyState, "SetEnemyWaypoint", Enemy::updateWaypoint, userData, ARRAYSIZE(userData));
	addLuaFunction(mEnemyState, "IsEnemyHuntingPlayer", Enemy::isHuntingPlayerLua, userData, ARRAYSIZE(userData));
	addLuaFunction(mEnemyState, "SetEnemyHuntingPlayer", Enemy::setHuntingPlayerLua, userData, ARRAYSIZE(userData));
	
	// PLAYER POSITION
	void *userData2[] = { mPlayer };
	addLuaFunction(mEnemyState, "GetPlayerPosition", getEntityPosition, userData2, ARRAYSIZE(userData2));
	
	// GET DISTANCE BEETWEN
	void *userData3[] = { mEnemy, mPlayer };
	addLuaFunction(mEnemyState, "GetDistanceBetween", getDistanceBetween, userData3, ARRAYSIZE(userData3));
	addLuaFunction(mEnemyState, "SeesPlayer", Enemy::seesPlayer, userData3, ARRAYSIZE(userData3));
}

void AIHandler::addLuaFunctionsTrap(lua_State *state, Trap *trap) {
	// For testing
	addLuaFunction(state, "Log", log, nullptr, 0);

	// TRAP FUNCTIONS
	void *userData[] = { trap };
	addLuaFunction(state, "GetPosition", getEntityPosition, userData, ARRAYSIZE(userData));

	// PLAYER FUNCTIONS
	void *userData2[] = { mPlayer };
	addLuaFunction(state, "GetPlayerPosition", getEntityPosition, userData2, ARRAYSIZE(userData2));

	// Enemy FUNCTIONS
	void *userData3[] = { mEnemy };
	addLuaFunction(state, "GetEnemyPosition", getEntityPosition, userData3, ARRAYSIZE(userData3));
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
	lua_getglobal(mEnemyState, "update");
	lua_pcall(mEnemyState, 0, 0, 0);

	if (mEnemy->update() == 1) {
		lua_getglobal(mEnemyState, "onReachingWaypoint");
		handleError(mEnemyState, lua_pcall(mEnemyState, 0, 0, 0));
	}// on waypoint 

	for (TrapScript &script : mTraps) {
		lua_State *state = script.state;
		lua_getglobal(state, "update");
		handleError(state, lua_pcall(state, 0, 0, 0));

		// should not be checked every frame, change later
		if (script.trap->getAABB().aabbVSCapsule(*mPlayer->col)) {
			lua_getglobal(state, "onPlayerCollision");
			handleError(state, lua_pcall(state, 0, 0, 0));
		}

		if (script.trap->getAABB().aabbVSCapsule(*mEnemy->mCapsule)) {
			lua_getglobal(state, "onEnemyCollision");
			handleError(state, lua_pcall(state, 0, 0, 0));
		}
	}
}

// LUA
int AIHandler::setEnemySpeed(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	if (lua_isnumber(state, -1)) {
		enemy->setSpeed(static_cast<float> (lua_tonumber(state, -1)));
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

int AIHandler::log(lua_State *state) {
	if (lua_isstring(state, -1)) {
		SDL_Log(lua_tostring(state, -1));
	}

	return 0;
}

// private
bool inline AIHandler::handleError(lua_State *state, int error) {
	if (error) {
			SDL_Log("Error: %s", lua_tostring(state, -1));
			lua_pop(state, 1);
			return false;
	}
	
	return true;
}

// FOR TESTING -- REMOVE
void AIHandler::testScript() {
	lua_State *test = luaL_newstate();

	int error = luaL_loadfile(test, TEST) || lua_pcall(test, 0, 0, 0);
	if (handleError(test, error)) {
		luaL_openlibs(test);

		lua_getglobal(test, "hello");
		SDL_Log("Text1: %s", lua_tostring(test, -1));
		lua_pop(test, 1);

		lua_getglobal(test, "PrintWorld");
		error = lua_pcall(test, 0, 1, 0);
		if (handleError(test, error)) {
			SDL_Log("Text2: %s", lua_tostring(test, -1));
			lua_pop(test, 1);
		}
	}

	lua_close(test);
}