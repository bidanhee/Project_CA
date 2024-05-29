#include "WaveController.h"
#include "TimeManager.h"
#include "gameObjectManager.h"
#include "Block.h"

WaveController::WaveController(MapSpace mapSpace, int power)
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
	for (int i = 0; i < 4; i++)
		_isClogged[i] = false;
}

WaveController::~WaveController()
{
}

void WaveController::Init()
{
}

void WaveController::Update()
{
	if (_state == WaveControllerStateTag::Making)
	{
		_coolDown -= TimeManager::getSingleton()->getElapsedTime();
		if (_coolDown <= 0.f) 
		{
			_coolDown = _MAKE_COOLTIME;
			if (_currentWaveIndex <= _POWER)
			{
				if (_mapSpace.row - _currentWaveIndex >= 0 && !_isClogged[UP])
				{
					Wave* upWave = new Wave(_mapSpace.row - _currentWaveIndex, _mapSpace.col, WaveStateTag::Up, _POWER);
					_isClogged[UP] = checkBlockCollision(upWave);

					GameObjectManager::getSingleton()->registerObj(upWave);
				}
				if (_mapSpace.row + _currentWaveIndex <= BOARD_ROW - 1 && !_isClogged[DOWN])
				{
					Wave* downWave = new Wave(_mapSpace.row + _currentWaveIndex, _mapSpace.col, WaveStateTag::Down, _POWER);
					_isClogged[DOWN] = checkBlockCollision(downWave);
					GameObjectManager::getSingleton()->registerObj(downWave);
				}
				if (_mapSpace.col - _currentWaveIndex >= 0 && !_isClogged[LEFT])
				{
					Wave* leftWave = new Wave(_mapSpace.row, _mapSpace.col - _currentWaveIndex, WaveStateTag::Left, _POWER);
					_isClogged[LEFT] = checkBlockCollision(leftWave);
					GameObjectManager::getSingleton()->registerObj(leftWave);
				}
				if (_mapSpace.col + _currentWaveIndex <= BOARD_COL - 1 && !_isClogged[RIGHT])
				{
					Wave* rightWave = new Wave(_mapSpace.row, _mapSpace.col + _currentWaveIndex, WaveStateTag::Right, _POWER);
					_isClogged[RIGHT] = checkBlockCollision(rightWave);
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

void WaveController::Render(HDC hdc)
{
}

void WaveController::Release()
{
}

bool WaveController::checkBlockCollision(Wave* w)
{
	map<GameObjectTag, vector<GameObject*>> m;
	RECT rcTemp;
	vector<GameObject*> _gameObj = GameObjectManager::getSingleton()->getGameObject();
	for (auto go : _gameObj)
	{
		m[go->getTag()].push_back(go);
	}
	for (auto block : m[GameObjectTag::Block])
	{
		Block* b = dynamic_cast<Block*>(block);
		RECT waveRect = makeRect(w->getStartX(), w->getStartY(), w->getSize(), w->getSize());
		RECT blockRect = makeRect(b->getStartX(), b->getStartY(), b->getSize(), b->getSize());
		if (IntersectRect(&rcTemp, &waveRect, &blockRect))
		{
			if ((b->getState() != BlockStateTag::Pop))
			{
				b->setState(BlockStateTag::Pop);
				return true;
			}
			return true;
		}
	}

	return false;
}
