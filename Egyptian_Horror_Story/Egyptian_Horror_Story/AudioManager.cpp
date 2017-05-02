#include "AudioManager.h"

AudioManager::AudioManager()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif
	this->mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);

	this->mSoundEffect = std::make_unique<DirectX::SoundEffect>(this->mAudioEngine.get(), L"../Resource/Sfx/test.wav");
}

AudioManager::~AudioManager()
{
}

void AudioManager::playSfx()
{
	this->mSoundEffect->Play();
}
