#ifndef AI_HANDLER_H
#define AI_HANDLER_H

#include <lua.hpp>
#include <vector>

#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Trap.h"
#include "NavMesh.h"

class AIHandler {
	private:
		struct TrapScript {
			Trap* trap;
			lua_State *state;
			char const *scriptPath; //for easy debugging
		};

		Enemy *mEnemy; //pointer to enemy that will use the AI
		Player *mPlayer;
		lua_State *mEnemyState;
		NavMesh navMesh;

		std::vector<TrapScript> mTraps;

		// helper
		void testScript(); //For testing

		void setupTraps();
		void setupTrapState(TrapScript &trap);

		void setupEnemy();
		bool handleError(lua_State *state, int error);

		// lua functions
		void addLuaFunctionsEnemy();
		void addLuaFunctionsTrap(lua_State *state, Trap *trap);

		void addLuaFunction(lua_State *state, const char *name,
			lua_CFunction func, void *userData[], int size);
	public:
		AIHandler(Enemy *enemy, Player *player);
		~AIHandler();
		AIHandler(AIHandler const &aiHandler) = delete;

		void update();
		void setupAI();

		void addTrap(char const *scriptPath, Trap *trap);

		AIHandler* operator=(AIHandler const &aiHandler) = delete;

		int getNavMeshWidth() const;
		int getNavMeshHeight() const;

		void* getNavigationTexture() const; //this is for debugging
};

#endif