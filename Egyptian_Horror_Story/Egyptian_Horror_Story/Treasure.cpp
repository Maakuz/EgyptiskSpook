#include "Treasure.h"

Treasure::Treasure(int key, int pickupTime, int value)
	:Entity(key)
{
	this->mValue = value;
	this->mPickupTime = pickupTime;
}

Treasure::~Treasure()
{
}