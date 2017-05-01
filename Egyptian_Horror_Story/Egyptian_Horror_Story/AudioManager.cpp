#include "AudioManager.h"

AudioManager::AudioManager()
{
	

	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif
	this->mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
}

AudioManager::~AudioManager()
{
}
