#ifndef OPTIONHANDLER_H
#define OPTIONHANDLER_H

#include "Direct3DHeader.h"
#include <SDL.h>
#include <fstream>
#include "Structs.h"


class OptionsHandler
{
private:
	settings::GraphicSettings mGraphics;
	ID3D11Buffer* mBrightnessBuffer;


	void updateBuffer(ID3D11DeviceContext* context);
public:
	OptionsHandler();
	virtual ~OptionsHandler();

	void setup(ID3D11Device* device);

	bool handleButtonPress(SDL_KeyboardEvent const& key, ID3D11DeviceContext* context);
	bool handleButtonRelease(SDL_KeyboardEvent const& key, ID3D11DeviceContext* context);

	settings::GraphicSettings& getGraphicSettings();
	
	ID3D11Buffer* getBrightnessBuffer();
};


#endif
