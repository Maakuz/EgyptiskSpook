#ifndef AI_HANDLER_H
#define AI_HANDLER_H

#include "Entity.h"
#include <lua.hpp>

class AIHandler {
	private:
		Entity *mEnemy; //pointer to enemy that will use the AI
		lua_State *mState;

		void testScript(); //For testing
	public:
		AIHandler();
		~AIHandler();
		AIHandler(AIHandler const &aiHandler) = delete;

		bool handleError(int error);

		AIHandler* operator=(AIHandler const &aiHandler) = delete;
};

#endif