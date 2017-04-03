#ifndef ENTITY_H
#define ENTITY_H

#include "OBB.h"

class Entity
{
private:
	DirectX::SimpleMath::Vector3 mPos;
	OBB* mObb;

public:
	Entity();
	virtual ~Entity();

	void move(DirectX::SimpleMath::Vector3 offset);
	void createOBB(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W);

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	DirectX::SimpleMath::Vector3 getPosition() const;

	OBB getOBB() const;
};


#endif