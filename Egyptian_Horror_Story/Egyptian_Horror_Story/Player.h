#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "CameraClass.h"
#include "Light.h"
#include "Treasure.h"

#include <SDL.h>

class Player : public Entity
{
private:
	CameraClass* mCamera;
	DirectX::SimpleMath::Vector2 mDirection;
	DirectX::SimpleMath::Vector3 mPrevPos;
	float mSneakTime;

	float mSpeed, mJumpingVelocity, mStamina, mMaxStamina;
	bool mJumping, mSprinting, mSneaking;
	DirectX::SimpleMath::Vector3 mVelocity;

	Treasure* mPickupableTres;
	bool mIsPickingTres;
	int mScore;

	Light* mLight;

	void updateLightPosition();
	void computeVelocity();
	void handleSprinting(float dt);
	float handleSneaking(float dt);
	void startSprint();
	void startSneaking();
	float getMovementMultiplier();

	void updateTreasureGrabbing(float dt);
public:
	//WTF
	Capsule* col;

	Player(CameraClass* camera, ID3D11Device* device, ID3D11DeviceContext* context, int grapchicsKey, GraphicsData* gData);
	virtual ~Player();

	void updatePosition(float dt);
	void handleJumping(float dt);

	bool handleKeyboardPress(SDL_KeyboardEvent const &key);
	bool handleKeyboardRelease(SDL_KeyboardEvent const &key);
	void handleMouseMotion(SDL_MouseMotionEvent const &motion);

	void setPickuppableTreasure(Treasure* tres);
	
	Light* getLight();
	CameraClass* getCamera();
	DirectX::SimpleMath::Vector3 getPrevPos() const;
	DirectX::SimpleMath::Vector3 getVelocity() const;

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	void setPrevPos(DirectX::SimpleMath::Vector3 pos);

	void damage();
};

#endif