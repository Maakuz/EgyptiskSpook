#include "Enemy.h"
#include "Player.h"
#include <SDL.h>
#define HALF_PATH_SIZE 2.5f
using namespace DirectX::SimpleMath;

Enemy::Enemy(int graphicsKey) : Entity(graphicsKey) {
	mHuntingPlayer = false;
	mCapsule = new Capsule(getPosition(), 2, 1);
}

Enemy::~Enemy() {

}

void Enemy::setVelocity(DirectX::SimpleMath::Vector3 velocity) {
	mVelocity = velocity;
}

void Enemy::setHuntingPlayer(bool huntingPlayer) {
	mHuntingPlayer = huntingPlayer;
}

int Enemy::setHuntingPlayerLua(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	if (lua_isboolean(state, -1))
		enemy->setHuntingPlayer(lua_toboolean(state, -1) == 1);
	return 0;
}

int Enemy::isHuntingPlayerLua(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	lua_pushboolean(state, enemy->isHuntingPlayer());
	return 1;
}

int Enemy::updateWaypoint(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	if (lua_istable(state, -1)) {
		lua_pushstring(state, "x");
		lua_gettable(state, -2);
		lua_pushstring(state, "y");
		lua_gettable(state, -3);
		lua_pushstring(state, "z");
		lua_gettable(state, -4);
		 
		if (lua_isnumber(state, -1) && lua_isnumber(state, -2) && lua_isnumber(state, -3)) {
			Vector3 waypoint(static_cast<float> (lua_tonumber(state, -3)),
				static_cast<float> (lua_tonumber(state, -2)),
				static_cast<float> (lua_tonumber(state, -1)));
			enemy->mVelocity = waypoint - enemy->getPosition();
			enemy->mVelocity.Normalize();
			enemy->mWaypoint = waypoint;
		}

		lua_pop(state, 4);
	}

	return 0;
}

Vector3 Enemy::getVelocity() const {
	return mVelocity;
}

Vector3 Enemy::getWaypoint() const {
	return mWaypoint;
}

bool Enemy::isHuntingPlayer() const {
	return mHuntingPlayer;
}

void Enemy::setSpeed(float speed) {
	mSpeed = speed;
}

int Enemy::update() {
	move(mVelocity * mSpeed);
	mCapsule->mPoint = getPosition();
	if ((mWaypoint - getPosition()).Length() <= mSpeed) {
		setPosition(mWaypoint);
		return 1; //On waypoint
	}

	return 0; //nothing
}

int Enemy::seesPlayer(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));
	Player *player = static_cast<Player*>
		(lua_touserdata(state, lua_upvalueindex(2)));

	Vector3 toPlayer = player->getPosition() - enemy->getPosition();
	toPlayer.Normalize();
	float dot = toPlayer.Dot(enemy->mVelocity);

	if (dot < 0) lua_pushboolean(state, false); //Behind enemy
	else if (player->getPosition().Length() * (1 - dot)
		< HALF_PATH_SIZE) lua_pushboolean(state, true);
						/* calculates if player is inside path monster
						 facing, ONLY FOR PATHS NOT ROOMES YET */
	else lua_pushboolean(state, false);

	return 1;
}