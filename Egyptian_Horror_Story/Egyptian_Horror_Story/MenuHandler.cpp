#include "MenuHandler.h"

using namespace DirectX::SimpleMath;

MenuHandler::MenuHandler()
{
}

MenuHandler::~MenuHandler()
{
}

void MenuHandler::setWindowResolution(int width, int height) {
	this->mWidth = static_cast<float> (width);
	this->mHeight = static_cast<float> (height);
}

void MenuHandler::clearButtons() {
	this->mButtons.clear();
}

void MenuHandler::addButton(int id, Vector2 position, Vector2 dimensions) {
	this->mButtons.push_back({ id, position, dimensions });
}

void MenuHandler::mouseMotion(SDL_MouseMotionEvent const &event) {
	Vector2 mousePos(event.x * 2 / this->mWidth - 1,
					 (event.y * 2 / this->mHeight - 1) * -1); //flip y
	// SDL_Log("Motion: %f,%f, Buttons: %d", mousePos.x, mousePos.y, this->mButtons.size());
	
	for (auto const &button : this->mButtons) {
		if (buttonVsMouse(button, mousePos)) {
			onHoverButton(button.buttonId);
		}
	}
}

GAMESTATE MenuHandler::mousePress(SDL_MouseButtonEvent const &event, GAMESTATE currentState) {
	Vector2 mousePos(event.x * 2 / this->mWidth - 1,
					(event.y * 2 / this->mHeight - 1) * -1);

	for (auto const &button : this->mButtons) {
		if (buttonVsMouse(button, mousePos)) {
			GAMESTATE state = onPressButton(button.buttonId, currentState);

			if (state != currentState)
				return state;
		}
	}

	return currentState;
}

bool MenuHandler::buttonVsMouse(Button const &button, Vector2 const &mousePos) {
	/* Simple Geometry
	                  - Hanzo */
	if (mousePos.x >= button.position.x &&
		mousePos.x <= button.dimensions.x + button.position.x) {
		if (mousePos.y >= button.position.y &&
			mousePos.y <= button.dimensions.y + button.position.y) {
			return true;
		}
	}

	return false;
}

void MenuHandler::onHoverButton(int id) {

}

GAMESTATE MenuHandler::onPressButton(int id, GAMESTATE currentState) {
	if (currentState == MAIN_MENU) {
		switch (id) { // The id of button is decided in GUIRenderer.cpp
			case 0: // "PLAY" button
				return PLAY;
			case 1: // "OPTIONS" button
				return MAIN_MENU;
		}
	}

	else if (currentState == GAME_OVER)
		switch (id)
		{
		case 2: //GO BACK TO MENU BUTTON
			return MAIN_MENU;
			break;
		}
	return currentState;
}