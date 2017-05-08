#ifndef AICFUNCTIONS_H
#define AICFUNCTIONS_H

#include <lua.hpp>

class AICFunctions {
public:
	static int setEnemySpeed(lua_State *state);
	static int setEntityPosition(lua_State *state);

	static int getEntityPosition(lua_State *state);
	static int getDistanceBetween(lua_State *state);

	static int loadPathToEntity(lua_State *state);
	static int loadPathToPoint(lua_State *state);

	static int entitySeesEntity(lua_State *state);
	static int log(lua_State *state);
};

#endif