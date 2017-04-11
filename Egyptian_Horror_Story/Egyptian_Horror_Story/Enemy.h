#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
private:
	DirectX::SimpleMath::Vector3 mVelocity;
	float mSpeed;
public:
	Enemy(int graphicsKey);
	virtual ~Enemy();

	void update();

	void setSpeed(float speed);
	void setVelocity(DirectX::SimpleMath::Vector3 velocity);
	DirectX::SimpleMath::Vector3 getVelocity() const;
};

#endif