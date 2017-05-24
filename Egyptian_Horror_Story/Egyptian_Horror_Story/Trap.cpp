#include "Trap.h"
#include "SimpleMath.h"
#include <SDL.h>
using namespace DirectX::SimpleMath;

Trap::Trap(int graphicsKey, float x, float y, float z) : Entity(graphicsKey) {
	setPosition(Vector3(x, y, z));
	startPosition = getPosition();
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
	return startPosition;
}