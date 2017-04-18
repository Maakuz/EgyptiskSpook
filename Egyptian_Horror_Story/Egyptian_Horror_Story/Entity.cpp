#include "Entity.h"

Entity::Entity(int graphicsKey)
{
	this->mPos = DirectX::SimpleMath::Vector3(0, 0, 0);
	this->mAABB = nullptr;

	this->mGraphicsKey = graphicsKey;
}

Entity::~Entity()
{
	if (this->mAABB)
		delete this->mAABB;
}

void Entity::move(DirectX::SimpleMath::Vector3 offset)
{
	this->mPos += offset;
}

void Entity::createAABB(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W)
{
	if (this->mAABB != nullptr)
		delete this->mAABB;

	this->mAABB = new AABB(pos, U, V, W);
}

void Entity::setPosition(DirectX::SimpleMath::Vector3 mPos)
{
	this->mPos = mPos;
}

DirectX::SimpleMath::Vector3 Entity::getPosition() const
{
	return this->mPos;
}

AABB Entity::getAABB()
{
	if (this->mAABB)
		return *this->mAABB;
}

int Entity::getKey() const
{
	return this->mGraphicsKey;
}
