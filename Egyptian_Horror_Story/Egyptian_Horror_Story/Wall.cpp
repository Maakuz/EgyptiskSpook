#include "Wall.h"

Wall::Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W, int key)
: Entity(key)
{
	this->createOBB(pos, U, V, W);
	this->mNormal = -W;
	this->mNormal.Normalize();
}

Wall::~Wall()
{
}

DirectX::SimpleMath::Vector3 Wall::getNormal() const
{
	return this->mNormal;
}
