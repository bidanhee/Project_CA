#include "SoundManager.h"

void SoundManager::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		char str[256];
		sprintf_s(str, "FMOD ERROR! (%d) %s\n", result, FMOD_ErrorString(result));
		MessageBox(NULL, CharToLPCWSTR(str), L"TEST", MB_OK);
	}
}

void SoundManager::Init()
{
	ERRCHECK(FMOD::System_Create(&_system));
	ERRCHECK(_system->init(15, FMOD_INIT_NORMAL, 0));

	registerSound(SoundTypeTag::Logo, "assets/sound/logo.mp3");
	registerSound(SoundTypeTag::MainScene, "assets/sound/login_scene.mp3");
	registerSound(SoundTypeTag::PlayScene, "assets/sound/play_scene.mp3");

	registerSound(SoundTypeTag::GameStart, "assets/sound/game_start.mp3");
	registerSound(SoundTypeTag::EatItem, "assets/sound/eat_item.mp3");
	registerSound(SoundTypeTag::Wave, "assets/sound/wave.mp3");

	registerSound(SoundTypeTag::Win, "assets/sound/win.mp3");
	registerSound(SoundTypeTag::Lose, "assets/sound/lose.mp3");

	registerSound(SoundTypeTag::PtInRect, "assets/sound/pt_in_rect.mp3");
	registerSound(SoundTypeTag::Click, "assets/sound/click.mp3");

	registerSound(SoundTypeTag::BombPop, "assets/sound/bomb_pop.mp3");
	registerSound(SoundTypeTag::BombSet, "assets/sound/bomb_set.mp3");
	registerSound(SoundTypeTag::GameOver, "assets/sound/game_over.mp3");
	registerSound(SoundTypeTag::PlayerDie, "assets/sound/player_die.mp3");
}

void SoundManager::Release()
{
	for (auto sound : _sounds)
		if (sound.second)
			sound.second->release();

	if (_system)
		_system->release();
}

void SoundManager::registerSound(const SoundTypeTag& sound, string path)
{
	auto key = sound;
	auto find = _sounds.find(key);
	if (find == _sounds.end())
		ERRCHECK(_system->createSound(path.c_str(), FMOD_DEFAULT, 0, &_sounds[key]));
	else
		assert(false && "SoundManager::registerSound()");
}

void SoundManager::play(int channelKey, const SoundTypeTag& sound)
{
	auto find = _sounds.find(sound);
	if (find != _sounds.end())
		ERRCHECK(_system->playSound(find->second, NULL, false, &_channels[channelKey]));
	else
		assert(false && "Sound::play()");
}

void SoundManager::repeatPlay(int channelKey, const SoundTypeTag& sound)
{
	bool isPlay;
	_channels[channelKey]->isPlaying(&isPlay);
	if (!isPlay)
	{
		play(channelKey, sound);
	}
}

void SoundManager::pause(int channelKey, bool paused)
{
	_channels[channelKey]->setPaused(paused);
}

void SoundManager::Update()
{
	_system->update();
}

void SoundManager::stop(int channelKey)
{
	_channels[channelKey]->stop();
}

void SoundManager::setVolume(const float volume)
{
	if (volume < 0.0f)
		_volume = 0.0f;
	else if (volume > 1.0f)
		_volume = 1.0f;
	else
		_volume = volume;

	for (auto channel : _channels)
		channel->setVolume(_volume);
}
