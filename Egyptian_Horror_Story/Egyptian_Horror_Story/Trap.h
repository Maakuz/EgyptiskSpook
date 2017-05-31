#ifndef TRAP_H
#define TRAP_H
#include "Entity.h"

class Trap : public Entity {
private:
	DirectX::SimpleMath::Vector3 mStartPosition;
	float mLength;
public:
	Trap(int graphicsKey, float x, float y, float z);
	virtual ~Trap();

	void updateAABB();
	void resetTrap();
	bool sphereVsPoint(DirectX::SimpleMath::Vector3 point) const;

	void setLength(float length);
	float getLength() const;

	DirectX::SimpleMath::Vector3 getStartPosition() const;
};

#endif