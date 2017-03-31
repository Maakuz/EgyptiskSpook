#ifndef PLAYER
#define PLAYER
#include "Entity.h"
#include "CameraClass.h"

#include <SDL.h>

class Player : public Entity
{
private:
	CameraClass* mCamera;
	DirectX::SimpleMath::Vector2 mDirection;

	float mSpeed;
	DirectX::SimpleMath::Vector3 mVelocity;

public:
	Player(CameraClass* camera);
	virtual ~Player();

	void updatePosition();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
};

#endif