#include "Enemy.h"

Enemy::Enemy(int graphicsKey) : Entity(graphicsKey) {
	
}

Enemy::~Enemy() {

}

void Enemy::setVelocity(DirectX::SimpleMath::Vector3 velocity) {
	mVelocity = velocity;
}

DirectX::SimpleMath::Vector3 Enemy::getVelocity() const {
	return mVelocity;
}

void Enemy::setSpeed(float speed) {
	mSpeed = speed;
}

void Enemy::update() {
	move(mVelocity * mSpeed);
}