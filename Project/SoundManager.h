#pragma once
#include "Singleton.h"
#include "Global.h"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <unordered_map>
#pragma comment(lib, "fmodL_vc.lib")

class SoundManager : public Singleton<SoundManager>
{
private:
	FMOD::System* _system = nullptr;
	FMOD::Channel* _channels[15];
	unordered_map<SoundTypeTag, FMOD::Sound*> _sounds;
	float _volume;

	void ERRCHECK(FMOD_RESULT result);
public:
	void Init();	
	void Update();
	void Release();

	void registerSound(const SoundTypeTag& sound, string path);

	void play(int channelKey, const SoundTypeTag& sound);
	void repeatPlay(int channelKey, const SoundTypeTag& sound);
	void pause(int channelKey, bool paused);

	void stop(int channelKey);
	void setVolume(const float volume);

	float getVolume() const
	{
		return _volume;
	}
	void volumeUp(const float volume)
	{
		setVolume(_volume + volume);
	}
	void volumeDown(const float volume)
	{
		setVolume(_volume - volume);
	}
};