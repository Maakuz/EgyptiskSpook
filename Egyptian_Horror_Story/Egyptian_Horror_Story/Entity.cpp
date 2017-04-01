#include "Entity.h"

Entity::Entity()
{
	this->mPos = DirectX::SimpleMath::Vector3(0, 0, 0);
}

Entity::~Entity()
{
}

void Entity::move(DirectX::SimpleMath::Vector3 offset)
{
	this->mPos += offset;
}

void Entity::setPosition(DirectX::SimpleMath::Vector3 mPos)
{
	this->mPos = mPos;
}

DirectX::SimpleMath::Vector3 Entity::getPosition() const
{
	return this->mPos;
}
