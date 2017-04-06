#ifndef ENTITY_H
#define ENTITY_H

#include "OBB.h"

class Entity
{
private:
	DirectX::SimpleMath::Vector3 mPos;
	OBB* mObb;
	int mGraphicsKey;

public:
	Entity(int graphicsKey);
	virtual ~Entity();

	void move(DirectX::SimpleMath::Vector3 offset);
	void createOBB(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W);

	virtual void setPosition(DirectX::SimpleMath::Vector3 pos);
	DirectX::SimpleMath::Vector3 getPosition() const;

	int getKey() const;

	OBB getOBB() const;
};


#endif