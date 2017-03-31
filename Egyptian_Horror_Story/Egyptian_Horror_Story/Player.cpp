#include "Player.h"

Player::Player(CameraClass* camera)
{
	this->mCamera = camera;
	this->mSpeed = 0.03f;

}

Player::~Player()
{
}

void Player::updatePosition()
{
	this->mVelocity = this->mDirection.x * this->mCamera->getRight();
	this->mVelocity += this->mDirection.y * this->mCamera->getForward();

	DirectX::SimpleMath::Vector3 newPos = this->mCamera->getPos() + this->mVelocity * mSpeed;

	this->mCamera->setPos(newPos);
}

bool Player::handleMouseKeyPress(SDL_KeyboardEvent const &key)
{
	if (key.keysym.scancode == SDL_SCANCODE_A)
	{
		this->mDirection.x = -1;
	}

	if (key.keysym.scancode == SDL_SCANCODE_D)
	{
		this->mDirection.x = 1;
	}

	if (key.keysym.scancode == SDL_SCANCODE_W)
	{
		this->mDirection.y = 1;
	}

	if (key.keysym.scancode == SDL_SCANCODE_S)
	{
		this->mDirection.y = -1;
	}

	return true;
}

bool Player::handleMouseKeyRelease(SDL_KeyboardEvent const &key)
{
	if (key.keysym.scancode == SDL_SCANCODE_A)
	{
		this->mDirection.x = 0;
	}

	else if (key.keysym.scancode == SDL_SCANCODE_D)
	{
		this->mDirection.x = 0;
	}

	if (key.keysym.scancode == SDL_SCANCODE_W)
	{
		this->mDirection.y = 0;
	}

	else if (key.keysym.scancode == SDL_SCANCODE_S)
	{
		 this->mDirection.y = 0;
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
