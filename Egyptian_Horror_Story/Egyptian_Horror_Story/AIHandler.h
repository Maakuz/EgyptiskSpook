#ifndef AI_HANDLER_H
#define AI_HANDLER_H

#include "Entity.h"
#include <lua.hpp>
#include "Enemy.h"
#include "Player.h"

class AIHandler {
	private:
		Enemy *mEnemy; //pointer to enemy that will use the AI
		Player *mPlayer;
		lua_State *mState;

		void testScript(); //For testing
		bool handleError(int error);
	public:
		AIHandler(Enemy *enemy, Player *player);
		~AIHandler();
		AIHandler(AIHandler const &aiHandler) = delete;

		void update();
		void setupAI();

		// lua functions
		static int setEnemySpeed(lua_State *state, int speed);

		AIHandler* operator=(AIHandler const &aiHandler) = delete;
};

#endif