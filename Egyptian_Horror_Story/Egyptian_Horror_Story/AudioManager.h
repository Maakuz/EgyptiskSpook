#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Direct3DHeader.h"
#include <Audio.h>
#include <map>
#include <string>
#include <fstream>
#include "lua.hpp"

class AudioManager
{
private:
	std::unique_ptr<DirectX::AudioEngine> mAudioEngine;

	std::map<int, std::unique_ptr<DirectX::SoundEffect>> mSoundEffects;


public:
	AudioManager();
	virtual ~AudioManager();

	void addSfx(int key, wchar_t* filename);

	void playSfx(int key);
	static int playSfx(lua_State* state);

};


#endif
