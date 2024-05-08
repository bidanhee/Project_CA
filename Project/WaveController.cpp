#include "WaveController.h"
#include "TimeManager.h"
#include "gameObjectManager.h"
#include "Wave.h"

WaveControllor::WaveControllor(MapSpace mapSpace, int power)
	: GameObject(GameObjectTag::WaveStartingPoint)
	, _state(WaveControllerStateTag::Making)
	, _mapSpace(mapSpace)
	, _currentWaveIndex(1)
	, _SIZE(BOARD_RECTSIZE)
	, _MAKE_COOLTIME(0.05f)
	, _POWER(power)
{
	_coolDown = _MAKE_COOLTIME;
	_start = mapSpaceToLeftTop(mapSpace.row, mapSpace.col);
}

WaveControllor::~WaveControllor()
{
}

void WaveControllor::Init()
{
}

void WaveControllor::Update()
{
	if (_state == WaveControllerStateTag::Making)
	{
		_coolDown -= TimeManager::getSingleton()->getElapsedTime();
		if (_coolDown <= 0.f) 
		{
			_coolDown = _MAKE_COOLTIME;
			if (_currentWaveIndex <= _POWER)
			{

				if (_mapSpace.row - _currentWaveIndex >= 0)
				{
					Wave* upWave = new Wave(_mapSpace.row - _currentWaveIndex, _mapSpace.col, WaveStateTag::Up, _POWER);
					GameObjectManager::getSingleton()->registerObj(upWave);
				}
				if (_mapSpace.row + _currentWaveIndex <= BOARD_ROW - 1)
				{
					Wave* downWave = new Wave(_mapSpace.row + _currentWaveIndex, _mapSpace.col, WaveStateTag::Down, _POWER);
					GameObjectManager::getSingleton()->registerObj(downWave);
				}
				if (_mapSpace.col - _currentWaveIndex >= 0)
				{
					Wave* leftWave = new Wave(_mapSpace.row, _mapSpace.col - _currentWaveIndex, WaveStateTag::Left, _POWER);
					GameObjectManager::getSingleton()->registerObj(leftWave);
				}
				if (_mapSpace.col + _currentWaveIndex <= BOARD_COL - 1)
				{
					Wave* rightWave = new Wave(_mapSpace.row, _mapSpace.col + _currentWaveIndex, WaveStateTag::Right, _POWER);
					GameObjectManager::getSingleton()->registerObj(rightWave);
				}

				++_currentWaveIndex;
			}

			if (_currentWaveIndex - 1 == _POWER)
			{
				_state = WaveControllerStateTag::Complete;
			}
		}
	}
	else if (_state == WaveControllerStateTag::Complete)
	{
		GameObjectManager::getSingleton()->removeObj(getId());
	}

}

void WaveControllor::Render(HDC hdc)
{
}

void WaveControllor::Release()
{
}
