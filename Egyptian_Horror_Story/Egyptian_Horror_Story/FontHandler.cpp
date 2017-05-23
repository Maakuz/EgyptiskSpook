#include "FontHandler.h"
#define TEXTURE_PATH L"../Resource/Textures/"
#define END L".spriteFont"

using namespace DirectX::SimpleMath;

FontHandler::FontHandler() {
	spriteBatch = nullptr;
	spriteFont = nullptr;
}

FontHandler::~FontHandler() {
	if (spriteBatch) delete spriteBatch;
	if (spriteFont) delete spriteFont;
}

void FontHandler::loadFont(ID3D11Device *device) {
	spriteFont = new DirectX::SpriteFont(device, TEXTURE_PATH L"impact" END);
}

void FontHandler::drawFont(ID3D11DeviceContext  *context, const wchar_t *str, Vector2 position) {
	if (!spriteBatch)
		spriteBatch = new DirectX::SpriteBatch(context);
	
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch, str, position);
	spriteBatch->End();
}