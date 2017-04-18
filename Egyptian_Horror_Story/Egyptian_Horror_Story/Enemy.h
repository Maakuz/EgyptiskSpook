#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <lua.hpp>

class Enemy : public Entity {
private:
	DirectX::SimpleMath::Vector3 mVelocity, mWaypoint;
	float mSpeed;
	bool mHuntingPlayer;
public:
	// temp ? 
	Capsule* mCapsule;

	Enemy(int graphicsKey);
	virtual ~Enemy();

	int update();

	void setSpeed(float speed);
	void setVelocity(DirectX::SimpleMath::Vector3 velocity);
	void setHuntingPlayer(bool huntingPlayer);

	DirectX::SimpleMath::Vector3 getVelocity() const;
	DirectX::SimpleMath::Vector3 getWaypoint() const;
	bool isHuntingPlayer() const;

	// lua
	static int setHuntingPlayerLua(lua_State *state);
	static int isHuntingPlayerLua(lua_State *state);
	static int updateWaypoint(lua_State *state);
	static int seesPlayer(lua_State *state);
};

#endif