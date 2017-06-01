#include "AudioManager.h"
#include <SDL.h>

#define AUDIOPATH L"../Resource/Sfx/"

AudioManager::AudioManager()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_EnvironmentalReverb | DirectX::AudioEngine_ReverbUseFilters;

#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif

	this->mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	this->mAudioEngine->SetReverb(DirectX::Reverb_Alley);

	this->mListener.SetPosition(DirectX::XMFLOAT3(0, 0, 0));
}

AudioManager::~AudioManager()
{
}

void AudioManager::updateListener(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 forward, DirectX::SimpleMath::Vector3 up)
{
	this->mListener.SetPosition(position);
	this->mListener.SetOrientation(forward, up);
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
	{
		this->mInstances[instanceKey] = this->mSoundEffects[sfxKey].get()->CreateInstance(
			DirectX::SoundEffectInstance_Use3D | DirectX::SoundEffectInstance_ReverbUseFilters);
	
		if (this->mInstances[instanceKey] == nullptr)
			SDL_Log("DEN ÄR NULLPTR");
	}
}

void AudioManager::createEmitter(int key, DirectX::SimpleMath::Vector3 position)
{
	this->mEmitters[key] = std::unique_ptr<DirectX::AudioEmitter>(new DirectX::AudioEmitter());
	this->mEmitters[key].get()->SetPosition(position);
	this->mEmitters[key].get()->OrientFront.z *= -1;
}

void AudioManager::updateEmitter(int key, DirectX::SimpleMath::Vector3 position)
{
	if (this->mEmitters[key])
		this->mEmitters[key].get()->SetPosition(position);
}

void AudioManager::playInstance(int key, bool isLooped, float pitch)
{
	if (this->mInstances[key])
	{
		this->mInstances[key].get()->Stop();

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

void AudioManager::apply3DToInstance(int emitterKey, int instanceKey)
{
	if (emitterKey != -1 && this->mEmitters[emitterKey])
		this->mInstances[instanceKey].get()->Apply3D(this->mListener, *this->mEmitters[emitterKey], false);
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
		manager->playSfx(static_cast<int>(lua_tonumber(state, -1)));

	return 0;
}

