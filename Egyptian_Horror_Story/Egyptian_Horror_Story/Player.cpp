#include "Player.h"
#define GROUND_Y 0.f //change later ok
#define GRAVITY 0.025f //change later ok
#define JUMP_START_VELOCITY 1.f //change later ok FOR TESTING PURPOSES JUMPING BY LW

Player::Player(CameraClass* camera, ID3D11Device* device, ID3D11DeviceContext* context, int key, GraphicsData* gData, GraphicsData* gData2)
	:Entity(key)
{
	this->mCamera = camera;
	this->mSpeed = 0.1f;


	// jumping stuff
	this->mJumping = false;
	this->jumpingVelocity = 0;

	this->mLight = new Light(this->getPosition(), this->mCamera->getForward(), device, context, gData, gData2);
}

Player::~Player()
{
	if (this->mLight)
	delete this->mLight;
}

void Player::updatePosition()
{
	using namespace DirectX::SimpleMath;
	Vector3 normal = Vector3(0, 1, 0); //Normal of plane, shouldn't change
	Vector3 forward = this->mCamera->getForward();

	Vector3 proj = forward - normal * (forward.Dot(normal) / normal.LengthSquared()); // Project forward vector on plane
	proj.Normalize();

	this->mVelocity = this->mDirection.x * this->mCamera->getRight();
	
	//Normal walk
	//this->mVelocity += this->mDirection.y * proj;
	//handleJumping();

	//Noclip
	this->mVelocity += this->mDirection.y * forward;

	DirectX::SimpleMath::Vector3 newPos = this->getPosition() + this->mVelocity * mSpeed;

	this->setPosition(newPos);
	this->mCamera->setPos(newPos);

	DirectX::SimpleMath::Vector3 lightPos = newPos;

	lightPos += this->mCamera->getRight() * 0.7f;
	lightPos += this->mCamera->getUp() * -1.f;

	this->mLight->update(lightPos, this->mCamera->getForward());
}

void Player::handleJumping() {
	this->mVelocity.y = 0;
	this->mVelocity.Normalize(); // Norm to make speed forward speed same if you look up or down

	if (this->mJumping) {
		this->jumpingVelocity -= GRAVITY; // delta time should be used
		this->mVelocity.y = jumpingVelocity;

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
				this->jumpingVelocity = JUMP_START_VELOCITY;
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
