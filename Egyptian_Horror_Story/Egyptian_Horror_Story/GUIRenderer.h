#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "Renderer.h"
#include "GraphicsData.h"
#include <SimpleMath.h>

class GUIRenderer : public Renderer {
private:
	GraphicsData *mGraphicsData;

	UINT mSize;
	DirectX::SimpleMath::Vector3 *mParticles;
public:
	GUIRenderer();
	GUIRenderer(GUIRenderer const &renderer) = delete;
	virtual ~GUIRenderer();

	void setup(ID3D11Device *device, ShaderHandler &shaders);
	void render(ID3D11DeviceContext *context, ShaderHandler &shaders);

	GUIRenderer* operator=(GUIRenderer const &renderer) = delete;
};

#endif