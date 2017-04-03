#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "CameraClass.h"
#include "Light.h"

#include <SDL.h>

class Player : public Entity
{
private:
	CameraClass* mCamera;
	DirectX::SimpleMath::Vector2 mDirection;

	float mSpeed;
	DirectX::SimpleMath::Vector3 mVelocity;

	Light* mLight;

public:
	Player(CameraClass* camera, ID3D11Device* device);
	virtual ~Player();

	void updatePosition();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	Light* getLight();

	
};

#endif