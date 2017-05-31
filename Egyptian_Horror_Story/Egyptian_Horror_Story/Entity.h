#ifndef ENTITY_H
#define ENTITY_H

#include "Colliders.h"
#include "GraphicsData.h"

class Entity
{
private:
	DirectX::SimpleMath::Vector3 mPos, mWorldPos, mRot, mOffsetRot, mScale; // RoT ftw
	AABB* mAABB;
	int mGraphicsKey;

public:
	Entity(int graphicsKey);
	virtual ~Entity();

	void move(DirectX::SimpleMath::Vector3 offset);
	void createAABB(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 U, DirectX::SimpleMath::Vector3 V, DirectX::SimpleMath::Vector3 W);

	virtual void setPosition(DirectX::SimpleMath::Vector3 pos); //Idk why these are virtual
	virtual void setPosition(float x, float y, float z);
	virtual void setScale(DirectX::SimpleMath::Vector3 scale);
	virtual void setRotation(DirectX::SimpleMath::Vector3 rot);
	DirectX::SimpleMath::Vector3 getRotation() const;
	virtual void setOffsetRotation(DirectX::SimpleMath::Vector3 offRot); // Used to transform before rotation
	DirectX::SimpleMath::Vector3 getPosition() const;
	DirectX::SimpleMath::Vector3 getWorldPosition() const;

	//Sets the transform to the position of the object
	void updateTransformBuffer(ID3D11DeviceContext* context, GraphicsData* gData);

	int getKey() const;

	AABB* getAABB();
};


#endif