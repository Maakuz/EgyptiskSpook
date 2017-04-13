#include "Wall.h"

Wall::Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale, int key)
: Entity(key)
{
	this->createOBB(pos, dir, up, scale);
	this->mNormal = dir;
	this->mNormal.Normalize();
}

Wall::~Wall()
{
}

DirectX::SimpleMath::Vector3 Wall::getNormal() const
{
	return this->mNormal;
}
