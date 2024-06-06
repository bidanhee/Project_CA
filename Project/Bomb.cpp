#include "Bomb.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "gameObjectManager.h"
#include "WaveController.h"
#include "PlayScene.h"

Bomb::Bomb(Player* player, POINT_FLOAT center, int power) 
	: GameObject(GameObjectTag::Bomb)
, _SIZE(BOARD_RECTSIZE)
, _POWER(power)
, _previousState(BombStateTag::Not)
, _currentState(BombStateTag::Set)
, _startTime(TimeManager::getSingleton()->getWorldTime())
, _BOMB_COOLTIME(0.2f)
, _POP_COOLTIME(0.1f)
, _POP_TIME(3.f)
, _DISAPPEAR_TIME(0.5f)
, _bombOwner(player)
, _isNewBomb(true)
{
	setAnimationInfo("bomb1", _BOMB_COOLTIME);
	
	_center.x = static_cast<float>(static_cast<int>((BOARD_STARTX + center.x) / BOARD_RECTSIZE) * BOARD_RECTSIZE);
	_center.y = static_cast<float>(static_cast<int>(center.y / BOARD_RECTSIZE) * BOARD_RECTSIZE + (BOARD_RECTSIZE / 2) + 1);

	_start.x = _center.x - BOARD_RECTSIZE / 2.f;
	_start.y = _center.y - BOARD_RECTSIZE / 2.f;

	_mapSpace = leftTopToMapSpace(_start.x, _start.y);

	PlayScene::changeBombArr(_mapSpace.row, _mapSpace.col, BombOnTyleTag::PlayerOnBomb);
}

Bomb::~Bomb()
{
}

void Bomb::Init()
{
}

void Bomb::Update()
{
	float currentTime;
	if (_currentState == BombStateTag::Set) 
	{
		currentTime = TimeManager::getSingleton()->getWorldTime();
		animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

		if (currentTime - _startTime > _POP_TIME)
		{
			_previousState = _currentState;
			_currentState = BombStateTag::MakeWave;
		}
	}
	else if (_currentState == BombStateTag::MakeWave)
	{
		WaveController* wave = new WaveController(_mapSpace, _POWER);
		GameObjectManager::getSingleton()->registerObj(wave);

		_previousState = _currentState;
		_currentState = BombStateTag::Pop;
	}
	else if (_currentState == BombStateTag::Pop)
	{
		if (_currentState != _previousState)
		{
			setAnimationInfo("bombPop", _POP_COOLTIME);
			_previousState = _currentState;
		}

		animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

		if (getFrame() == ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX())
		{
			_bombOwner->changeUsedBombs();
			PlayScene::changeBombArr(_mapSpace.row, _mapSpace.col, BombOnTyleTag::Not);
			GameObjectManager::getSingleton()->removeObj(getId());
		}
	}
}

void Bomb::Render(HDC hdc)
{
	ImageManager::getSingleton()->findImage(getStrKey())->
		frameRender(hdc, static_cast<int>(_center.x - (BOARD_RECTSIZE / 2)), static_cast<int>(_center.y - (BOARD_RECTSIZE / 2))
		, getFrame(), 0);
}

void Bomb::Release()
{
}

void Bomb::onCollisionEnter(GameObject* other, RECT area)
{
}
