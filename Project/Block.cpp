#include "Block.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "gameObjectManager.h"
Block::Block(MapSpace mapSpace, BlockTypeTag blockType)
	: GameObject(GameObjectTag::Block)
	, _mapSpace(mapSpace)
	, _SIZE(BOARD_RECTSIZE)
	, _previousState(BlockStateTag::Not)
	, _currentState(BlockStateTag::Set)
	, _ANIMATION_COOLTIME(1.f)
	, _POP_COOLTIME(0.1f)
	, _POP_TIME(3.f)
	, _DISAPPEAR_TIME(0.5f)
	, _blockType(blockType)
{
	//TODO:: blocktype마다 다르게
	setAnimationInfo("forestBlock1", _ANIMATION_COOLTIME);

	POINT_FLOAT pt;
	pt = mapSpaceToLeftTop(_mapSpace.row, _mapSpace.col);
	_start = pt;

	_center.x = _start.x + _SIZE / 2.f;
	_center.y = _start.y + _SIZE / 2.f;
}

Block::~Block()
{
}

void Block::Init()
{
}

void Block::Update()
{
	float currentTime;
	if (_currentState == BlockStateTag::Set)
	{
		currentTime = TimeManager::getSingleton()->getWorldTime();
		animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());
	}
	else if (_currentState == BlockStateTag::Pop)
	{
		if (_currentState != _previousState)
		{
			//TODO: blocktype마다 다르게
			setAnimationInfo("block1Pop", _POP_COOLTIME);
			_previousState = _currentState;
		}

		animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

		if (getFrame() == ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX())
		{
			//TODO: 아이템생성, 시간조정
			GameObjectManager::getSingleton()->removeObj(getId());
		}
	}
}

void Block::Render(HDC hdc)
{
	ImageManager::getSingleton()->findImage(getStrKey())->
		frameRender(hdc, static_cast<int>(_start.x - 6.f), static_cast<int>(_start.y - 12.f)
			, getFrame(), 0);
}

void Block::Release()
{
}

void Block::onCollisionEnter(GameObject* other, RECT area)
{
}

void Block::setState(BlockStateTag state)
{
	_currentState = state;
}
