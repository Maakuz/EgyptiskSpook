#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include "MenuHandler.h"

#include <SimpleMath.h>
#include <vector>

class GUIRenderer : public Renderer {
private:
	struct GUI_ELEMENT {
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector2 dimensions;
	};
	GraphicsData *mGraphicsData;

	std::vector<GUI_ELEMENT> mElements;
	ID3D11ShaderResourceView *navTest, *menu;
public:
	GUIRenderer();
	GUIRenderer(GUIRenderer const &renderer) = delete;
	virtual ~GUIRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaders);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaders, GAMESTATE const &state);
	void loadButtons(MenuHandler &menuHandler);

	void renderStartMenu(ID3D11DeviceContext *context, ShaderHandler &shaders);
	void renderHud(ID3D11DeviceContext *context, ShaderHandler &shaders);

	void setNavigationTest(ID3D11Device *device, void* pixels, int w, int h); //for testing

	GUIRenderer* operator=(GUIRenderer const &renderer) = delete;
};

#endif