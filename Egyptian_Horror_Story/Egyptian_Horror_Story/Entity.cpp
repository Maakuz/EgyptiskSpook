#include "Entity.h"

Entity::Entity()
{
	this->mPos = DirectX::SimpleMath::Vector3(0, 0, 0);
	this->mObb = nullptr;
	this->mRenderer = new EntityRenderer();
}

Entity::~Entity()
{
	if (this->mObb)
		delete this->mObb;
}

void Entity::move(DirectX::SimpleMath::Vector3 offset)
{
	this->mPos += offset;
}

void Entity::createOBB(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W)
{
	if (this->mObb != nullptr)
		delete this->mObb;

	this->mObb = new OBB(pos, U, V, W);
}

void Entity::setPosition(DirectX::SimpleMath::Vector3 mPos)
{
	this->mPos = mPos;
}

DirectX::SimpleMath::Vector3 Entity::getPosition() const
{
	return this->mPos;
}

OBB Entity::getOBB() const
{
	if (this->mObb)
		return *this->mObb;
}

EntityRenderer*& Entity::getRenderer()
{
	return this->mRenderer;
}
