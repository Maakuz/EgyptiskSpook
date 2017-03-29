#ifndef PLAYER
#define PLAYER
#include "Entity.h"
#include "CameraClass.h"

class Player : public Entity
{
private:
	CameraClass* mCamera;

public:
	Player(CameraClass* camera);
	virtual ~Player();
};

#endif