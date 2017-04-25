#include "Trap.h"
#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

Trap::Trap(int graphicsKey, float x, float y, float z) : Entity(graphicsKey) {
	setPosition(Vector3(x, y, z));
}

Trap::~Trap() {

}