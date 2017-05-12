#include "Player.h"
#include <SDL.h>
#define GRAVITY 0.025f //change later ok
#define GROUND_Y 0.f
#define JUMP_START_VELOCITY 1.1f //change later ok FOR TESTING PURPOSES JUMPING BY LW

#define MAX_STAMINA 15.f // temp change later ok
#define SPRINT_MULTIPLIER 2.f // temp change later ok
#define TIRED_MULTIPLIER 0.6f // temp change later ok
#define START_STAMINA 3.f // temp change later ok
#define SNEAK_MULTIPLIER 0.35f;
#define SNEAK_Y -0.5f; // Camera change while sneaking

using namespace DirectX::SimpleMath;

Player::Player(CameraClass* camera, ID3D11Device* device, ID3D11DeviceContext* context, int key, GraphicsData* gData)
	:Entity(key)
{
	this->mCamera = camera;

	// movement
	this->mSneaking = false;
	this->mSprinting = false;

	this->mMaxStamina = 15.f;
	this->mSpeed = 15.f; //magic numbers
	this->mStamina = this->mMaxStamina;

	//REMOVE
	this->col = new Capsule(this->mCamera->getPos(), 2, 1);

	// jumping stuff
	this->mJumping = false;
	this->mJumpingVelocity = 0;

	this->mLight = new Light(this->mCamera->getPos(), this->mCamera->getForward(), device, context, gData);
}

Player::~Player()
{
	if (this->mLight)
	delete this->mLight;

	delete this->col;
}

void Player::updatePosition(float dt)
{
	this->mPrevPos = this->getPosition();
	computeVelocity();
	handleJumping();
	handleSprinting();

	DirectX::SimpleMath::Vector3 newPos = this->getPosition() + this->mVelocity * mSpeed * getMovementMultiplier() * dt;

	this->setPosition(newPos);
	if (this->mSneaking) newPos.y += SNEAK_Y;
	this->mCamera->setPos(newPos);
	updateLightPosition();
	
	//ASDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	this->col->mPoint = this->mCamera->getPos();
}

void Player::handleJumping() {
	this->mVelocity.y = 0;
	this->mVelocity.Normalize(); // Norm to make speed forward speed same if you look up or down

	if (this->mJumping) {
		this->mJumpingVelocity -= GRAVITY; // delta time should be used
		this->mVelocity.y = mJumpingVelocity;

		if (getPosition().y + this->mVelocity.y * mSpeed <= GROUND_Y) {
			// set position to ground y
			DirectX::SimpleMath::Vector3 newPos = getPosition();
			newPos.y = GROUND_Y;
			setPosition(newPos);

			// reset velocity
			this->mVelocity.y = 0;
			this->mJumping = false;
			this->mVelocity.Normalize();
		}
	}
}

bool Player::handleMouseKeyPress(SDL_KeyboardEvent const &key)
{
	switch (key.keysym.scancode) {
		case SDL_SCANCODE_A:
			this->mDirection.x = -1;
			break;
		case SDL_SCANCODE_D:
			this->mDirection.x = 1;
			break;
		case SDL_SCANCODE_W:
			this->mDirection.y = 1;
			break;
		case SDL_SCANCODE_S:
			this->mDirection.y = -1;
			this->mSprinting = false;
			break;
		case SDL_SCANCODE_SPACE:
			if (!this->mJumping && getMovementMultiplier() == 1.f) {
				this->mJumping = true;
				this->mJumpingVelocity = JUMP_START_VELOCITY;
			}
			break;
		case SDL_SCANCODE_LSHIFT:
			startSprint();
			break;
		case SDL_SCANCODE_LCTRL:
			startSneaking();
			break;
	}

	return true;
}

bool Player::handleMouseKeyRelease(SDL_KeyboardEvent const &key)
{
	switch (key.keysym.scancode) {
		case SDL_SCANCODE_Q:
			SDL_Log("x = %f, y = %f, z = %f", getPosition().x, getPosition().y, getPosition().z); // TESTING METHOD
			break;
		case SDL_SCANCODE_A:
			if (this->mDirection.x == -1)
				this->mDirection.x = 0;
			break;
		case SDL_SCANCODE_D:
			if (this->mDirection.x == 1)
				this->mDirection.x = 0;
			break;
		case SDL_SCANCODE_W:
			if (this->mDirection.y == 1)
				this->mDirection.y = 0;
			break;
		case SDL_SCANCODE_S:
			if (this->mDirection.y == -1)
				this->mDirection.y = 0;
			break;
		case SDL_SCANCODE_LSHIFT:
			this->mSprinting = false;
			break;
		case SDL_SCANCODE_LCTRL:
			this->mSneaking = false;
			break;
	}

	return true;
}

void Player::handleMouseMotion(SDL_MouseMotionEvent const &motion)
{
	if (motion.xrel != 0)
	{
		this->mCamera->setYaw(this->mCamera->getYaw() + motion.xrel);
	}

	if (motion.yrel != 0)
	{
		this->mCamera->setPitch(this->mCamera->getPitch() - motion.yrel);
	}
}

Light* Player::getLight()
{
	return this->mLight;
}

CameraClass* Player::getCamera()
{
	return this->mCamera;
}

void Player::setPosition(DirectX::SimpleMath::Vector3 pos)
{
	Entity::setPosition(pos);
	this->mCamera->setPos(pos);
}

DirectX::SimpleMath::Vector3 Player::getPrevPos() const
{
	return this->mPrevPos;
}

DirectX::SimpleMath::Vector3 Player::getVelocity() const
{
	return this->mVelocity;
}

void Player::setPrevPos(DirectX::SimpleMath::Vector3 pos)
{
	this->mPrevPos = pos;
}

// private
void Player::updateLightPosition() {
	DirectX::SimpleMath::Vector3 offset;

	offset += this->mCamera->getRight() * 0.7f;
	offset += this->mCamera->getUp() * -1.f;

	this->mLight->update(this->mCamera->getPos(), offset, this->mCamera->getForward());
}

void Player::computeVelocity() {
	Vector3 normal = Vector3(0, 1, 0); //Normal of plane, shouldn't change
	Vector3 forward = this->mCamera->getForward();

	Vector3 proj = forward - normal * (forward.Dot(normal) / normal.LengthSquared()); // Project forward vector on plane
	proj.Normalize();

	this->mVelocity = this->mDirection.x * this->mCamera->getRight();
	this->mVelocity += this->mDirection.y * proj;
}

void Player::handleSprinting() {
	if (this->mSprinting) {
		this->mStamina -= 0.01f; //change later
		if (this->mStamina <= 0) {
			this->mStamina = 0;
			this->mSprinting = false;
		}
	}
	else {
		this->mStamina += 0.003f; //change later
	}
}

void Player::startSprint() {
	if (!this->mSprinting && this->mDirection.y != -1 && //no backsies
		this->mStamina > START_STAMINA && !this->mSneaking && !this->mJumping) {
		this->mSprinting = true;
		this->mStamina -= START_STAMINA;
	}
}

void inline Player::startSneaking() {
	if (!this->mSprinting)
		this->mSneaking = true;
}

float inline Player::getMovementMultiplier() {
	if (this->mSneaking) {
		return SNEAK_MULTIPLIER;
	} else if (this->mSprinting) {
		return SPRINT_MULTIPLIER;
	} else if (this->mStamina < START_STAMINA) {
		return TIRED_MULTIPLIER;
	}
	
	return 1.f;
}

void Player::damage() {
	// todo
}