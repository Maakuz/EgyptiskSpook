#include "Treasure.h"

Treasure::Treasure(int key, float pickupTime, int value)
	:Entity(key)
{
	this->mValue = value;
	this->mPickupTime = pickupTime;
	this->mPickupCounter = 0;
	this->mPickedUp = false;
}

Treasure::~Treasure()
{
}

void Treasure::resetCounter()
{
	this->mPickupCounter = 0;
}

void Treasure::increaseCounter(float val)
{
	this->mPickupCounter += val;
}

float Treasure::getPickupTime() const
{
	return this->mPickupTime;
}

float Treasure::getPickupCounter() const
{
	return this->mPickupCounter;
}

int Treasure::getValue() const
{
	return this->mValue;
}

bool Treasure::getPickedUp() const
{
	return this->mPickedUp;
}

void Treasure::setPickedUp(bool value)
{
	this->mPickedUp = value;
}
