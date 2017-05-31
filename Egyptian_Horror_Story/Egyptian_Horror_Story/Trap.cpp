#include "Trap.h"
#include "SimpleMath.h"
#include <SDL.h>
using namespace DirectX::SimpleMath;

Trap::Trap(int graphicsKey, float x, float y, float z) : Entity(graphicsKey) {
	setPosition(Vector3(x, y, z));
	mStartPosition = getPosition();
	mLength = 0;
}

Trap::~Trap() {

}

void Trap::updateAABB() {
	if (getAABB()->mPoint != getPosition())
		getAABB()->mPoint = getPosition();
}

void Trap::resetTrap() {
	setPosition(getStartPosition());
}

DirectX::SimpleMath::Vector3 Trap::getStartPosition() const {
	return mStartPosition;
}

bool Trap::sphereVsPoint(DirectX::SimpleMath::Vector3 point) const {
	return (getWorldPosition() - point).Length() <= mLength;
}

void Trap::setLength(float length) {
	mLength = length;
}

float Trap::getLength() const {
	return mLength;
}