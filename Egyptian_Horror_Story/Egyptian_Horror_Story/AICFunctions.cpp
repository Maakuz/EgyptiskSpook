#include "AICFunctions.h"

#include <vector>
#include <SDL.h>

#include "Trap.h"
#include "Enemy.h"
#include "Player.h"
#include "NavMesh.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

int AICFunctions::setEnemySpeed(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	if (lua_isnumber(state, -1)) {
		enemy->setSpeed(static_cast<float> (lua_tonumber(state, -1)));
		lua_pop(state, 1);
	}

	return 0;
}

int AICFunctions::getEntityPosition(lua_State *state) {
	Entity *entity = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	Vector3 position = entity->getPosition();
	lua_pushnumber(state, position.x);
	lua_pushnumber(state, position.y);
	lua_pushnumber(state, position.z);
	return 3;
}

int AICFunctions::getDistanceBetween(lua_State *state) {
	Entity *entity1 = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	Entity *entity2 = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(2)));

	Vector3 eToE2 = entity1->getPosition() - entity2->getPosition();

	lua_pushnumber(state, eToE2.Length());

	return 1;
}

int AICFunctions::entitySeesEntity(lua_State *state) {
	Enemy *entity1 = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	Entity *entity2 = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(2)));
	NavMesh *navMesh = static_cast<NavMesh*>
		(lua_touserdata(state, lua_upvalueindex(3)));

	Vector3 e1Pos = entity1->getPosition();
	Vector3 e2Pos = entity2->getPosition();

	lua_pushboolean(state, navMesh->canSeeFrom(e1Pos.x, e1Pos.z, e2Pos.x, e2Pos.z));

	return 1;
}

int AICFunctions::loadPathToEntity(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	Entity *entity = static_cast<Entity*>
		(lua_touserdata(state, lua_upvalueindex(2)));
	NavMesh *navMesh = static_cast<NavMesh*>
		(lua_touserdata(state, lua_upvalueindex(3)));

	Vector3 enemyPos = enemy->getPosition();
	Vector3 entityPos = entity->getPosition();

	enemy->setPath(navMesh->getPathToCoord(
		enemyPos.x,
		enemyPos.z,
		entityPos.x,
		entityPos.z
	));

	return 0;
}

int AICFunctions::loadPathToPoint(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	NavMesh *navMesh = static_cast<NavMesh*>
		(lua_touserdata(state, lua_upvalueindex(2)));

	Vector3 enemyPos = enemy->getPosition();

	if (lua_isinteger(state, -1) && lua_isinteger(state, -2)) {
		int x = lua_tonumber(state, -2), z = lua_tonumber(state, -1);
		enemy->setPath(navMesh->getPathToCoord(
			enemyPos.x, enemyPos.z,
			x, z
		));
	}

	return 0;
}


int AICFunctions::log(lua_State *state) {
	if (lua_isstring(state, -1)) {
		SDL_Log(lua_tostring(state, -1));
	}

	return 0;
}