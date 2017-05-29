#ifndef OPTIONHANDLER_H
#define OPTIONHANDLER_H

#include "Direct3DHeader.h"
#include <SDL.h>
#include <fstream>
#include <string>
#include "Structs.h"
//För att kunna använda M_PI
#define _USE_MATH_DEFINES
#include <math.h>


#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define DEFAULT_FOV 0.45
#define DEFAULT_FARPLANE 100
#define DEFAULT_BRIGHTNESS 0
#define DEFAULT_TRAP_PERCENTAGE 0.3f
#define DEFAULT_TREASURE_PERCENTAGE 0.3f

#define FOVUPKEY SDL_SCANCODE_RIGHT
#define FOVDOWNKEY SDL_SCANCODE_LEFT

class OptionsHandler
{
private:
	settings::GraphicSettings mGraphics;
	settings::DifficultySettings mDifficulty;
	ID3D11Buffer* mBrightnessBuffer;


	void updateBuffer(ID3D11DeviceContext* context);
public:
	OptionsHandler();
	virtual ~OptionsHandler();

	void setup(ID3D11Device* device);

	bool handleButtonPress(SDL_KeyboardEvent const& key, ID3D11DeviceContext* context);
	bool handleButtonRelease(SDL_KeyboardEvent const& key, ID3D11DeviceContext* context);

	settings::GraphicSettings& getGraphicSettings();
	settings::DifficultySettings& getDifficultySettings();
	
	ID3D11Buffer* getBrightnessBuffer();
};


#endif
