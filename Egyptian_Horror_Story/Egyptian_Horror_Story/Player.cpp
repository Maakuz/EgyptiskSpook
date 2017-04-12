#include "Player.h"
#define GROUND_Y 0.f //change later ok
#define GRAVITY 0.025f //change later ok
#define JUMP_START_VELOCITY 1.1f //change later ok FOR TESTING PURPOSES JUMPING BY LW

#define MAX_STAMINA 15.f // temp change later ok
#define SPRINT_MULTIPLIER 2.f // temp change later ok
#define TIRED_MULTIPLIER 0.6f // temp change later ok
#define START_STAMINA 3.f // temp change later ok

using namespace DirectX::SimpleMath;

Player::Player(CameraClass* camera, ID3D11Device* device, ID3D11DeviceContext* context, int key, GraphicsData* gData)
	:Entity(key)
{
	this->mCamera = camera;
	this->mSpeed = 0.05f;

	// sprinting
	this->mMaxStamina = 15.f;
	this->mStamina = this->mMaxStamina;

	// jumping stuff
	this->mJumping = false;
	this->mJumpingVelocity = 0;

	this->mLight = new Light(this->getPosition(), this->mCamera->getForward(), device, context, gData);
}

Player::~Player()
{
	if (this->mLight)
	delete this->mLight;
}

void Player::updatePosition()
{
	computeVelocity();
	handleJumping();
	handleSprinting();

	float sprintMultiplier = (mSprinting ? SPRINT_MULTIPLIER :
							  mStamina < START_STAMINA ? TIRED_MULTIPLIER : 1.f);

	DirectX::SimpleMath::Vector3 newPos
		= this->getPosition() + this->mVelocity * mSpeed * sprintMultiplier;

	this->setPosition(newPos);
	this->mCamera->setPos(newPos);
	updateLightPosition();
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
			break;
		case SDL_SCANCODE_SPACE:
			if (!this->mJumping) {
				this->mJumping = true;
				this->mJumpingVelocity = JUMP_START_VELOCITY;
			}
			break;
		case SDL_SCANCODE_LSHIFT:
			if (!this->mSprinting && this->mStamina > START_STAMINA) {
				this->mSprinting = true;
				this->mStamina -= START_STAMINA;
			}
			break;
	}

	return true;
}

bool Player::handleMouseKeyRelease(SDL_KeyboardEvent const &key)
{
	switch (key.keysym.scancode) {
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

void Player::setPosition(DirectX::SimpleMath::Vector3 pos)
{
	Entity::setPosition(pos);
	this->mCamera->setPos(pos);
}

// private
void Player::updateLightPosition() {
	DirectX::SimpleMath::Vector3 lightPos = getPosition();

	lightPos += this->mCamera->getRight() * 0.7f;
	lightPos += this->mCamera->getUp() * -1.f;

	this->mLight->update(lightPos, this->mCamera->getForward());
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
	} else {
		this->mStamina += 0.003f; //change later
	}
}