#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include "Direct3DHeader.h"
#include "Renderer.h"

#include <SDL.h>
#include <SimpleMath.h>
#include <vector>

class MenuHandler
{
private:
	struct Button {
		int buttonId;
		DirectX::SimpleMath::Vector2 position, dimensions;
	};
	std::vector<Button> mButtons;
	float mWidth, mHeight;

	inline bool buttonVsMouse(Button const &button, DirectX::SimpleMath::Vector2 const &mousePos);
	void onHoverButton(int id);
	GAMESTATE onPressButton(int id, GAMESTATE currentState);
public:
	MenuHandler();
	virtual ~MenuHandler();

	void clearButtons();
	void addButton(int id, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 dimensions);
	void setWindowResolution(int width, int height);

	void mouseMotion(SDL_MouseMotionEvent const &event);
	GAMESTATE mousePress(SDL_MouseButtonEvent const &event, GAMESTATE currentState);
};

#endif