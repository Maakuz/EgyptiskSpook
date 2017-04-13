#include "Wall.h"

<<<<<<< HEAD
Wall::Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W, DirectX::SimpleMath::Vector3 n, int key)
: Entity(key)
{
	this->createOBB(pos, U, V, W);
	this->mNormal = n;
=======
Wall::Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 scale, int key)
: Entity(key)
{
	this->createOBB(pos, dir, up, scale);
	this->mNormal = dir;
>>>>>>> 7e58a1c3cdaf767f52eee7a2cec60f0d8d0d0c94
	this->mNormal.Normalize();
}

Wall::~Wall()
{
}

DirectX::SimpleMath::Vector3 Wall::getNormal() const
{
	return this->mNormal;
}
