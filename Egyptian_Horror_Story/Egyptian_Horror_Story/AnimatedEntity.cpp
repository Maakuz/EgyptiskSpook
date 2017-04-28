#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(int graphicsKey, int cBufferKey)
	:Entity(graphicsKey)
{
	this->mCBufferKey = cBufferKey;
}

AnimatedEntity::~AnimatedEntity()
{
}

int AnimatedEntity::getCBufferKey() const
{
	return this->mCBufferKey;
}
