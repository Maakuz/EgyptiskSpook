#ifndef TRAP_H
#define TRAP_H
#include "Entity.h"

class Trap : public Entity {
private:
	DirectX::SimpleMath::Vector3 startPosition;
public:
	Trap(int graphicsKey, float x, float y, float z);
	virtual ~Trap();

	void updateAABB();
	void resetTrap();

	DirectX::SimpleMath::Vector3 getStartPosition() const;
};

#endif