#include "Wall.h"

Wall::Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W, DirectX::SimpleMath::Vector3 n, int key)
: Entity(key)
{
	this->createOBB(pos, U, V, W);
	this->mNormal = n;
	this->mNormal.Normalize();
}

Wall::~Wall()
{
}

DirectX::SimpleMath::Vector3 Wall::getNormal() const
{
	return this->mNormal;
}
