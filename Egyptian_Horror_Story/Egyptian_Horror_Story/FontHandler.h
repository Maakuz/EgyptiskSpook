#ifndef FONT_HANDLER_H
#define FONT_HANDLER_H

#include "Direct3DHeader.h"
#include "SimpleMath.h"
#include <SpriteFont.h>

class FontHandler {
private:
	DirectX::SpriteBatch *spriteBatch;
	DirectX::SpriteFont *spriteFont;
public:
	FontHandler();
	~FontHandler();

	void loadFont(ID3D11Device *device);
	void drawFont(ID3D11DeviceContext  *context, const wchar_t *str, DirectX::SimpleMath::Vector2 position);
};

#endif