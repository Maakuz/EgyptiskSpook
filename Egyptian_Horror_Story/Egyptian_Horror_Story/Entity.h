#ifndef ENTITY_H
#define ENTITY_H

#include "Colliders.h"
#include "GraphicsData.h"

class Entity
{
private:
	DirectX::SimpleMath::Vector3 mPos;
	AABB* mAABB;
	int mGraphicsKey;

public:
	Entity(int graphicsKey);
	virtual ~Entity();

	void move(DirectX::SimpleMath::Vector3 offset);
	void createAABB(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W);

	virtual void setPosition(DirectX::SimpleMath::Vector3 pos);
	DirectX::SimpleMath::Vector3 getPosition() const;

	//Sets the transform to the position of the object
	void updateTransformBuffer(ID3D11DeviceContext* context, GraphicsData* gData);

	int getKey() const;

	AABB getAABB();
};


#endif