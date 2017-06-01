#include "OptionsHandler.h"
#define SETTINGPATH "../UserSettings/settings.ini"
#define OUT(a, b) out << a << " " << b << "\n"
#define IN(a) in >> str >> a

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
		IN(this->mGraphics.width);
		
		IN(this->mGraphics.height);
		
		IN(this->mGraphics.fov);
		
		IN(this->mGraphics.farPlane);
		
		IN(this->mGraphics.brightness);

		IN(this->mDifficulty.trapPercentage);
		
		IN(this->mDifficulty.treasurePercentage);


		in.close();
	}

	else
	{
		this->mGraphics.brightness = DEFAULT_BRIGHTNESS;
		this->mGraphics.height = DEFAULT_HEIGHT;
		this->mGraphics.width = DEFAULT_WIDTH;
		this->mGraphics.farPlane = DEFAULT_FARPLANE;
		this->mGraphics.fov = DEFAULT_FOV;
		
		this->mDifficulty.trapPercentage = DEFAULT_TRAP_PERCENTAGE;
		this->mDifficulty.treasurePercentage = DEFAULT_TREASURE_PERCENTAGE;
	}

}

OptionsHandler::~OptionsHandler()
{
	std::ofstream out(SETTINGPATH);

	if (out.is_open())
	{
		OUT("Screen_Width", this->mGraphics.width);
		OUT("Screen_Height", this->mGraphics.height);
		OUT("Field_Of_View", this->mGraphics.fov);
		OUT("View_Distance", this->mGraphics.farPlane);
		OUT("Brightness", this->mGraphics.brightness);
		OUT("Trap_Percentage", this->mDifficulty.trapPercentage);
		OUT("Treasure_Percentage", this->mDifficulty.treasurePercentage);

		out << "\nThis file will be overwritten with the current in game values on exit!\n";


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

settings::DifficultySettings & OptionsHandler::getDifficultySettings()
{
	return this->mDifficulty;
}

ID3D11Buffer* OptionsHandler::getBrightnessBuffer()
{
	return this->mBrightnessBuffer;
}


