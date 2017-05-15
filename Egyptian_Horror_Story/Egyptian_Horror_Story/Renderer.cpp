#include "Renderer.h"

Renderer::Renderer(GAMESTATE identifier) {
	this->mIdentifier = identifier;
}

Renderer::~Renderer()
{
}

void Renderer::setIdentifier(GAMESTATE state) {
	this->mIdentifier = state;
}

GAMESTATE Renderer::getIdentifier() {
	return this->mIdentifier;
}