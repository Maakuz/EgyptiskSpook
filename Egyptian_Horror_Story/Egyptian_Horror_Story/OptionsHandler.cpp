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
	std::string str;

	if (in.is_open())
	{
		in >> str;
		in >> this->mGraphics.width;
		
		in >> str;
		in >> this->mGraphics.height;
		
		in >> str;
		in >> this->mGraphics.fov;
		
		in >> str;
		in >> this->mGraphics.farPlane;
		
		in >> str;
		in >> this->mGraphics.brightness;

		in.close();
	}

	else
	{
		this->mGraphics.brightness = DEFAULTBRIGHTNESS;
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
		out << "ScreenWidth " << this->mGraphics.width << "\n";
		out << "ScreenHeight " << this->mGraphics.height << "\n";
		out << "FieldOfView " << this->mGraphics.fov << "\n";
		out << "ViewDistance " << this->mGraphics.farPlane << "\n";
		out << "Brightness " << this->mGraphics.brightness << "\n";


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

	case FOVUPKEY:
		this->mGraphics.fov += 0.01;
		break;

	case FOVDOWNKEY:
		this->mGraphics.fov -= 0.01;
		break;
	}

	if (this->mGraphics.fov > 0.9f)
		this->mGraphics.fov = 0.9f;

	else if (this->mGraphics.fov < 0.3f)
		this->mGraphics.fov = 0.3f;

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


