#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "GraphicsData.h"
#include <lua.hpp>
#include <SimpleMath.h>
#include <vector>

class Enemy : public Entity {
public:
	enum UPDATE_RETURNS {
		NOTHING, ON_WAYPOINT, ON_PATH_WAYPOINT, ON_REACHED_PATH_DESTINATION
	};
private:
	DirectX::SimpleMath::Vector3 mVelocity, mWaypoint;
	float mSpeed;
	bool mFollowPath;

	int currentPathNode;
	std::vector<DirectX::SimpleMath::Vector3> mPath;
public:
	// temp ? 
	Capsule* mCapsule;

	Enemy(int graphicsKey);
	virtual ~Enemy();

	UPDATE_RETURNS update();

	void setSpeed(float speed);
	void setVelocity(DirectX::SimpleMath::Vector3 velocity);
	void setFollowPath(bool followPath);
	void setWaypoint(DirectX::SimpleMath::Vector3 waypoint);

	DirectX::SimpleMath::Vector3 getVelocity() const;
	DirectX::SimpleMath::Vector3 getWaypoint() const;
	bool onPath() const;

	void setPath(std::vector<DirectX::SimpleMath::Vector3> path);
	std::vector<DirectX::SimpleMath::Vector3> getPath() const;

	void updatePosition(GraphicsData* gData, ID3D11DeviceContext* context, DirectX::SimpleMath::Vector3 playerPos);

	// lua
	static int setHuntingPlayerLua(lua_State *state);
	static int updateWaypoint(lua_State *state);
	static int seesPlayer(lua_State *state);
	static int getNextWaypoint(lua_State *state);
	static int onPathLua(lua_State *state);
	static int getPathSizeLua(lua_State *state);
	static int setCurrentPathNodeLua(lua_State *state);

	static int stopPathing(lua_State *state);
	static int startPathing(lua_State *state);
};

#endif