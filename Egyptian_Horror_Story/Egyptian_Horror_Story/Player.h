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
	DirectX::SimpleMath::Vector3 mPrevPos;

	float mSpeed, mJumpingVelocity, mStamina, mMaxStamina;
	bool mJumping, mSprinting, mSneaking;
	DirectX::SimpleMath::Vector3 mVelocity;

	Light* mLight;

	void updateLightPosition();
	void computeVelocity();
	void handleSprinting();
	void startSprint();
	void startSneaking();
	float getMovementMultiplier();
public:
	//WTF
	Capsule* col;

	Player(CameraClass* camera, ID3D11Device* device, ID3D11DeviceContext* context, int grapchicsKey, GraphicsData* gData, GraphicsData* gData2);
	virtual ~Player();

	void updatePosition();
	void handleJumping();

	bool handleMouseKeyPress(SDL_KeyboardEvent const &key);
	bool handleMouseKeyRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);
	
	Light* getLight();
	DirectX::SimpleMath::Vector3 getPrevPos() const;
	DirectX::SimpleMath::Vector3 getVelocity() const;

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	void setPrevPos(DirectX::SimpleMath::Vector3 pos);

	void damage();
};

#endif