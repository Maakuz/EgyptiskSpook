#include "OptionsHandler.h"
#define SETTINGPATH "../UserSettings/settings.ini"

void OptionsHandler::updateBuffer(ID3D11DeviceContext* context)
{
	D3D11_MAPPED_SUBRESOURCE data;
	ZeroMemory(&data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	struct Padding
	{
		float brightness;
		float glory, will, prevail;
	};

	Padding pad{0};

	pad.brightness = this->mGraphics.brightness;

	context->Map(this->mBrightnessBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, &pad, sizeof(Padding));

	context->Unmap(this->mBrightnessBuffer, 0);

}

OptionsHandler::OptionsHandler()
{
	std::ifstream in(SETTINGPATH);

	if (in.is_open())
	{
		in >> this->mGraphics.width;
		in >> this->mGraphics.height;
		in >> this->mGraphics.fov;
		in >> this->mGraphics.farPlane;
		in >> this->mGraphics.brightness;

		in.close();
	}

	else
	{
		this->mGraphics.brightness = 0.f;
		this->mGraphics.height = DEFAULTHEIGHT;
		this->mGraphics.width = DEFAULTWIDTH;
		this->mGraphics.farPlane = DEFAULTFARPLANE;
		this->mGraphics.fov = DEFAULTFOV;
	}

}

OptionsHandler::~OptionsHandler()
{
	std::ofstream out(SETTINGPATH);

	if (out.is_open())
	{
		out << this->mGraphics.width << "\n";
		out << this->mGraphics.height << "\n";
		out << this->mGraphics.fov << "\n";
		out << this->mGraphics.farPlane << "\n";
		out << this->mGraphics.brightness << "\n";


		out.close();
	}

	this->mBrightnessBuffer->Release();
}

void OptionsHandler::setup(ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = 16;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = &this->mGraphics.brightness;

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->mBrightnessBuffer);
	if (FAILED(hr))
	{
		exit(-44);
	}
}

bool OptionsHandler::handleButtonPress(SDL_KeyboardEvent const& key, ID3D11DeviceContext* context)
{
	switch (key.keysym.scancode) {
	case SDL_SCANCODE_UP:
		this->mGraphics.brightness += 0.01f;
		this->updateBuffer(context);
		break;

	case SDL_SCANCODE_DOWN:
		this->mGraphics.brightness -= 0.01f;
		this->updateBuffer(context);
		break;
	}

	return true;
}

bool OptionsHandler::handleButtonRelease(SDL_KeyboardEvent const& key, ID3D11DeviceContext* context)
{
	
	return true;
}

settings::GraphicSettings& OptionsHandler::getGraphicSettings()
{
	return this->mGraphics;
}

ID3D11Buffer* OptionsHandler::getBrightnessBuffer()
{
	return this->mBrightnessBuffer;
}


