#include "AudioManager.h"

#define AUDIOPATH L"../Resourrce/Sfx/"

AudioManager::AudioManager()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif
	this->mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
}

AudioManager::~AudioManager()
{
}

void AudioManager::addSfx(int key, wchar_t* filename)
{
	std::wstring temp(AUDIOPATH);
	temp += filename;

	std::ifstream ff(temp.c_str());

	if (ff.is_open())
	{
		this->mSoundEffects[key] = std::make_unique<DirectX::SoundEffect>(this->mAudioEngine.get(), temp.c_str());
		ff.close();
	}

	else
		this->mSoundEffects[key] = nullptr;

}

void AudioManager::playSfx(int key)
{
	if (this->mSoundEffects[key])
		this->mSoundEffects[key]->Play();
}

int AudioManager::playSfx(lua_State* state)
{
	AudioManager* manager = static_cast<AudioManager*>(lua_touserdata(state, lua_upvalueindex(1)));

	if (lua_isnumber(state, -1))
		manager->playSfx(lua_tonumber(state, -1));

	return 0;
}

