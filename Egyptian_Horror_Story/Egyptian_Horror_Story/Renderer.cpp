#include "Renderer.h"

Renderer::Renderer(int i) {
	this->mIdentifier = i;
}

Renderer::~Renderer()
{
}

void Renderer::setState(int i) {
	this->mIdentifier = i;
}
