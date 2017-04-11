#include "AIHandler.h"

AIHandler::AIHandler() {
	mState = luaL_newstate();
}

AIHandler::~AIHandler() {
	lua_close(mState);
}