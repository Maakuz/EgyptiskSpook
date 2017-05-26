#include "Enemy.h"
#include "Player.h"
#include <SDL.h>
#define HALF_PATH_SIZE 2.5f
using namespace DirectX::SimpleMath;

Enemy::Enemy(int graphicsKey) : Entity(graphicsKey) {
	mCapsule = nullptr;

	// hi
	mCapsule = new Capsule(getPosition(), 2, 1);

	// simple pathing
	currentPathNode = 0;
	mFollowPath = false;
	mPaused = false;
}

Enemy::~Enemy() {
	if (mCapsule)
		delete mCapsule;
}

void Enemy::setSpeed(float speed) {
	mSpeed = speed;
}

void Enemy::setVelocity(DirectX::SimpleMath::Vector3 velocity) {
	mVelocity = velocity;
}

void Enemy::setFollowPath(bool followPath) {
	mFollowPath = followPath;
}

void Enemy::setPathLoaded(bool loaded) {
	mLoaded = loaded;
}

bool Enemy::isPathLoaded() const {
	return mLoaded;
}

void Enemy::setWaypoint(Vector3 waypoint) {
	mVelocity = waypoint - getPosition();
	mVelocity.Normalize();
	mWaypoint = waypoint;
}

void Enemy::setPath(std::vector<Vector3> path) {
	mPath = path;
}

std::vector<Vector3> Enemy::getPath() const {
	return mPath;
}

void Enemy::updatePosition(GraphicsData* gData, ID3D11DeviceContext* context, DirectX::SimpleMath::Vector3 playerPos)
{
	DirectX::SimpleMath::Matrix posMat = DirectX::SimpleMath::Matrix::CreateTranslation(this->getPosition());
	posMat = posMat.Transpose();

	//Very simple solution, can be improved
	Matrix rot = Matrix::CreateRotationY(atan2(playerPos.x - this->getPosition().x, playerPos.z - this->getPosition().z));
	rot = rot.Transpose();

	posMat *= rot;

	D3D11_MAPPED_SUBRESOURCE data;
	ZeroMemory(&data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	context->Map(gData->getConstantBuffer(this->getKey()), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	
	memcpy(data.pData, &posMat, sizeof(DirectX::XMMATRIX));
	
	context->Unmap(gData->getConstantBuffer(this->getKey()), 0);

}

Vector3 Enemy::getVelocity() const {
	return mVelocity;
}

Vector3 Enemy::getWaypoint() const {
	return mWaypoint;
}

bool Enemy::onPath() const {
	return mFollowPath;
}

Enemy::UPDATE_RETURNS Enemy::update(float dt) {
	if (mPaused) return NOTHING;

	move(mVelocity * mSpeed * dt);
	mCapsule->mPoint = getPosition();
	if ((mWaypoint - getPosition()).Length() <= mSpeed * dt) {
		setPosition(mWaypoint);
		
		if (mFollowPath && ++currentPathNode < mPath.size()) {
			setWaypoint(mPath[currentPathNode]);
			return ON_PATH_WAYPOINT; // on path waypoint
		}
		else if (mFollowPath) {
			return ON_REACHED_PATH_DESTINATION; // on reached destination
		} 

		return ON_WAYPOINT; //On waypoint
	}

	return NOTHING; //nothing
}

/*
*  LUA FUNCTIONS
*  ONLY USED BY LUA
*/

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
			enemy->setWaypoint(waypoint);
		}

		lua_pop(state, 4);
	}

	return 0;
}


// !!! Deprecated !!!
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

int Enemy::getNextWaypoint(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	Vector3 waypoint;
	if (enemy->onPath())
		waypoint = enemy->mPath[enemy->currentPathNode];
	else
		waypoint = enemy->getWaypoint();

	lua_pushnumber(state, waypoint.x);
	lua_pushnumber(state, waypoint.y);
	lua_pushnumber(state, waypoint.z);

	return 3;
}

int Enemy::onPathLua(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	lua_pushboolean(state, enemy->onPath());

	return 1;
}

int Enemy::getPathSizeLua(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	lua_pushinteger(state, enemy->getPath().size());

	return 0;
}

int Enemy::setCurrentPathNodeLua(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	if (lua_isinteger(state, -1))
		enemy->currentPathNode = lua_tointeger(state, -1);

	return 0;
}

int Enemy::startPathing(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	enemy->mPath[enemy->currentPathNode];
	enemy->setFollowPath(true);
	enemy->setWaypoint(enemy->mPath[enemy->currentPathNode]);

	return 0;
}

int Enemy::stopPathing(lua_State *state) {
	Enemy *enemy = static_cast<Enemy*>
		(lua_touserdata(state, lua_upvalueindex(1)));

	enemy->setFollowPath(false);
	enemy->mVelocity = Vector3();

	return 0;
}