#ifndef TREASURE_H
#define TREASURE_H
#include "Entity.h"

class Treasure : public Entity 
{
private:
	int mValue;
	float mPickupTime;
	float mPickupCounter;
	bool mPickedUp;
public:
	Treasure(int key, float pickupTime = 5, int value = 100);
	virtual ~Treasure();

	void resetCounter();
	void increaseCounter(float val);

	float getPickupTime() const;
	float getPickupCounter() const;
	int getValue() const;
	bool getPickedUp() const;
	void setPickedUp(bool value);
};

#endif