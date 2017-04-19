#ifndef AI_HANDLER_H
#define AI_HANDLER_H

#include "Entity.h"
#include <lua.hpp>
#include "Enemy.h"
#include "Player.h"
#include "Trap.h"
#include <vector>
#include "NavMesh.h"

class AIHandler {
	private:
		struct TrapScript {
			Trap* trap;
			lua_State *state;
		};

		Trap *testTrap;
		Enemy *mEnemy; //pointer to enemy that will use the AI
		Player *mPlayer;
		lua_State *mEnemyState;
		NavMesh navMesh;

		std::vector<TrapScript> mTraps;

		// helper
		void testScript(); //For testing
		void setupTraps();
		void setupEnemy();
		bool handleError(lua_State *state, int error);

		// lua functions
		void addLuaFunctionsEnemy();
		void addLuaFunctionsTrap(lua_State *state, Trap *trap);

		void addLuaFunction(lua_State *state, const char *name,
			lua_CFunction func, void *userData[], int size);

		static int setEnemySpeed(lua_State *state);
		static int setEntityPosition(lua_State *state);
		static int getEntityPosition(lua_State *state);
		static int getPlayerForward(lua_State *state);
		static int getDistanceBetween(lua_State *state);
		static int setPathToEntity(lua_State *state);
		static int log(lua_State *state);
	public:
		AIHandler(Enemy *enemy, Player *player);
		~AIHandler();
		AIHandler(AIHandler const &aiHandler) = delete;

		void update();
		void setupAI();

		void addTrap(char const *scriptPath, Trap *trap);

		AIHandler* operator=(AIHandler const &aiHandler) = delete;
};

#endif