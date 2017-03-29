#include "Entity.h"

Entity::Entity()
{
	this->pos = DirectX::SimpleMath::Vector3(0, 0, 0);
}

Entity::~Entity()
{
}

void Entity::move(DirectX::SimpleMath::Vector3 offset)
{
	this->pos += offset;
}

void Entity::setPosition(DirectX::SimpleMath::Vector3 pos)
{
	this->pos = pos;
}

DirectX::SimpleMath::Vector3 Entity::getPosition() const
{
	return this->pos;
}
