#include "Wave.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "gameObjectManager.h"

Wave::Wave(int row, int col, WaveStateTag state, int power)
	: GameObject(GameObjectTag::Wave)
    , _state(state)
	, _startTime(TimeManager::getSingleton()->getWorldTime())
	, _SIZE(BOARD_RECTSIZE)
	, _WAVE_COOLTIME(0.02f)
	, _POWER(power)
{
	_mapSpace.row = row;
	_mapSpace.col = col;
	_start = mapSpaceToLeftTop(_mapSpace.row, _mapSpace.col);
	
	Init();
}

Wave::~Wave()
{
}

void Wave::Init()
{
	switch (_state)
	{
	case WaveStateTag::Up:
	{
		if (_POWER == 1)
			setAnimationInfo("waveUp1", _WAVE_COOLTIME);
		else
			setAnimationInfo("waveUp2", _WAVE_COOLTIME);
		break;
	}
	case WaveStateTag::Down:
	{
		if (_POWER == 1)
			setAnimationInfo("waveDown1", _WAVE_COOLTIME);
		else
			setAnimationInfo("waveDown2", _WAVE_COOLTIME);
		break;
	}
	case WaveStateTag::Left:
	{
		if (_POWER == 1)
			setAnimationInfo("waveLeft1", _WAVE_COOLTIME);
		else
			setAnimationInfo("waveLeft2", _WAVE_COOLTIME);
		break;
	}
	case WaveStateTag::Right:
	{
		if (_POWER == 1)
			setAnimationInfo("waveRight1", _WAVE_COOLTIME);
		else
			setAnimationInfo("waveRight2", _WAVE_COOLTIME);
		break;
	}
	}
}

void Wave::Update()
{
	int maxFrame = ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX();
	animation(maxFrame);

	if (getFrame() >= maxFrame)
	{
		GameObjectManager::getSingleton()->removeObj(getId());
	}
}

void Wave::Render(HDC hdc)
{
	ImageManager::getSingleton()->findImage(getStrKey())->frameRender(hdc, static_cast<int>(_start.x), static_cast<int>(_start.y), getFrame(), 0);
}

void Wave::Release()
{
}
