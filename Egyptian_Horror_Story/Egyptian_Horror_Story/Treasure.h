#ifndef TREASURE_H
#define TREASURE_H
#include "Entity.h"

class Treasure : public Entity 
{
private:
	int mValue;
	int mPickupTime;
public:
	Treasure(int key, int pickupTime = 5, int value = 100);
	virtual ~Treasure();
};

#endif