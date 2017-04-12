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
	DirectX::SimpleMath::Vector3 prevPos;

	float mSpeed, jumpingVelocity;
	bool mJumping;
	DirectX::SimpleMath::Vector3 mVelocity;

	Light* mLight;

public:
	//WTF
	Capsule* col;
	//WTF
	Player(CameraClass* camera, ID3D11Device* device, ID3D11DeviceContext* context, int grapchicsKey, GraphicsData* gData);
	virtual ~Player();

	void updatePosition();
	void handleJumping();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	Light* getLight();

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	DirectX::SimpleMath::Vector3 getPrevPos();
	void setPrevPos(DirectX::SimpleMath::Vector3 pos);
};

#endif