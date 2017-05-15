#ifndef TRAP_H
#define TRAP_H
#include "Entity.h"

class Trap : public Entity {
private:

public:
	Trap(int graphicsKey, float x, float y, float z);
	virtual ~Trap();
};

#endif