#include "Wall.h"

Wall::Wall(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W)
{
	this->createOBB(pos, U, V, W);
}

Wall::~Wall()
{
}
