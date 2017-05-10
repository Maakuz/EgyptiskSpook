#include "AudioManager.h"

#define AUDIOPATH L"../Resource/Sfx/"

AudioManager::AudioManager()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif
	this->mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);

	this->mListener.SetPosition(DirectX::XMFLOAT3(0, 0, 0));
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

void AudioManager::createInstance(int instanceKey, int sfxKey)
{
	if (this->mSoundEffects[sfxKey])
		this->mInstances[instanceKey] = this->mSoundEffects[sfxKey].get()->CreateInstance();
}

void AudioManager::playInstance(int key, bool isLooped, float pitch, int emitterKey)
{
	if (this->mInstances[key])
	{
		this->mInstances[key] = this->mSoundEffects[key].get()->CreateInstance();

		if (emitterKey != -1 && this->mEmitters[key])
			this->mInstances[key].get()->Apply3D(this->mListener, *this->mEmitters[key]);
		
		this->mInstances[key].get()->SetPitch(pitch);
		this->mInstances[key].get()->Play(isLooped);
	}
}

void AudioManager::stopInstance(int key, bool immediately)
{
	if (this->mInstances[key] && 
		(this->mInstances[key].get()->GetState() == DirectX::PLAYING || 
			this->mInstances[key].get()->GetState() == DirectX::PAUSED))
	{
		this->mInstances[key].get()->Stop(immediately);
	}
	
}

int AudioManager::getInstanceState(int key)
{
	int ret = -1;
	if (this->mInstances[key])
		ret = this->mInstances[key].get()->GetState();

	return ret;
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

