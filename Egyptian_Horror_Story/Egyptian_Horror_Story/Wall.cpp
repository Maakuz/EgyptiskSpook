#include "Wall.h"


Wall::Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 norm, int key)
: Entity(key)
{
	this->createAABB(pos, dir, up, scale);
	this->mNormal = norm;
	this->mNormal.Normalize();
}

Wall::~Wall()
{
}

DirectX::SimpleMath::Vector3 Wall::getNormal() const
{
	return this->mNormal;
}
