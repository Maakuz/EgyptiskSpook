#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Direct3DHeader.h"
#include "SimpleMath.h"
#include <Audio.h>
#include <map>
#include <string>
#include <fstream>
#include "lua.hpp"

class AudioManager
{
private:
	std::unique_ptr<DirectX::AudioEngine> mAudioEngine;
	DirectX::AudioListener mListener;

	std::map<int, std::unique_ptr<DirectX::SoundEffect>> mSoundEffects;
	
	std::map<int, std::unique_ptr<DirectX::SoundEffectInstance>> mInstances;

	std::map<int, std::unique_ptr<DirectX::AudioEmitter>> mEmitters;
public:
	AudioManager();
	virtual ~AudioManager();

	void updateListener(DirectX::SimpleMath::Vector3 position);

	void addSfx(int key, wchar_t* filename);

	//The instance key is the new key for the specific instance, sfxKey is the old key 
	//where the sound is stored
	void createInstance(int instanceKey, int sfxKey);

	void createEmitter(int key, DirectX::SimpleMath::Vector3 position);
	void updateEmitter(int key, DirectX::SimpleMath::Vector3 position);

	//Pitch ranges from -1 to 1
	void playInstance(int key, bool isLooped = false, float pitch = 0, int emitterKey = -1);
	void stopInstance(int key, bool immediately = true);

	//Will return -1 if sound not found
	int getInstanceState(int key);

	void playSfx(int key);
	static int playSfx(lua_State* state);

};


#endif
