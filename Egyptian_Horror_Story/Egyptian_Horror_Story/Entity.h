#ifndef ENTITY_H
#define ENTITY_H

#include "Direct3DHeader.h"

#include <math.h>
#include "SimpleMath.h"

class Entity
{
public:
	DirectX::SimpleMath::Vector3 mPos;
public:
	Entity();
	virtual ~Entity();

	void move(DirectX::SimpleMath::Vector3 offset);

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	DirectX::SimpleMath::Vector3 getPosition() const;
};


#endif