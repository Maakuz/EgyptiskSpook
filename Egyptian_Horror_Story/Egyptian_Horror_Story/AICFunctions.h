#ifndef AICFUNCTIONS_H
#define AICFUNCTIONS_H

#include <lua.hpp>

#include "Enemy.h"
#include "Player.h"
#include "NavMesh.h"

class AICFunctions {
public:
	// Enemy & Player specifik functions
	static int setEnemySpeed(lua_State *state);
	static int damagePlayer(lua_State *state);

	// Generic Entity Functions
	static int setEntityPosition(lua_State *state);
	static int getEntityPosition(lua_State *state);
	static int setEntityRotation(lua_State *state);
	static int setEntityOffsetRotation(lua_State *state);
	static int slowEntity(lua_State *state);
	static int stunEntity(lua_State *state);
	static int pushbackEntity(lua_State *state);

	// Generate 2 Entity Functions
	static int getDistanceBetween(lua_State *state);

	// Path Finding
	static int loadPathToEntity(lua_State *state);
	static int loadPathToPoint(lua_State *state);

	// FOV
	static int entitySeesEntity(lua_State *state);

	// Debugging
	static int log(lua_State *state);

	// other
	static void loadPath(Enemy *enemy, Entity *entity, NavMesh *navMesh);
};

#endif