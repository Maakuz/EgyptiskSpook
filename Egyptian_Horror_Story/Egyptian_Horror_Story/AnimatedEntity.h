#ifndef ANIMATEDENTITY_H
#define ANIMATEDENTITY_H

#include "Entity.h"

class AnimatedEntity : public Entity
{
private:
	int mCBufferKey;

public:
	AnimatedEntity(int graphicsKey, int cBufferKey);
	virtual ~AnimatedEntity();

	int getCBufferKey() const;

};


#endif
