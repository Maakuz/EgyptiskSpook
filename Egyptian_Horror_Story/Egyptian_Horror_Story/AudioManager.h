#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H



#include "Direct3DHeader.h"
#include <Audio.h>

class AudioManager
{
private:
	std::unique_ptr<DirectX::AudioEngine> mAudioEngine;

	std::unique_ptr<DirectX::SoundEffect> mSoundEffect;

public:
	AudioManager();
	virtual ~AudioManager();

	void playSfx();

};


#endif
