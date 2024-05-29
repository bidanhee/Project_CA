#include "Block.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "Item.h"
#include "gameObjectManager.h"
Block::Block(MapSpace mapSpace, BlockImageTypeTag blockImageType)
	: GameObject(GameObjectTag::Block)
	, _mapSpace(mapSpace)
	, _SIZE(BOARD_RECTSIZE)
	, _previousState(BlockStateTag::Not)
	, _currentState(BlockStateTag::Set)
	, _ANIMATION_COOLTIME(1.f)
	, _POP_COOLTIME(0.05f)
	, _POP_TIME(3.f)
	, _DISAPPEAR_TIME(0.5f)
	, _blockImageType(blockImageType)
{
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
	switch (_blockImageType)
	{
	case BlockImageTypeTag::BasketBlock:
		setAnimationInfo("forestBlock1", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PasslessItem;
		break;
	case BlockImageTypeTag::GreenBlock:
		setAnimationInfo("forestBlock2", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PasslessItem;
		break;
	case BlockImageTypeTag::YGreenBlock:
		setAnimationInfo("forestBlock3", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PasslessItem;
		break;
	case BlockImageTypeTag::FlowerBlock:
		setAnimationInfo("forestBlock4", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PasslessNormal;
		break;
	case BlockImageTypeTag::GrassBlock1:
		setAnimationInfo("forestBlock5", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PassableNormal;
		break;
	case BlockImageTypeTag::GrassBlock2:
		setAnimationInfo("forestBlock6", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PassableNormal;
		break;
	case BlockImageTypeTag::GrassWithBerryBlock1:
		setAnimationInfo("forestBlock6", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PassableNormal;
		break;
	case BlockImageTypeTag::GrassWithBerryBlock2:
		setAnimationInfo("forestBlock6", _ANIMATION_COOLTIME);
		_blockType = BlockTypeTag::PassableNormal;
		break;
	case BlockImageTypeTag::Object1:
		_blockType = BlockTypeTag::Object;
		break;
	case BlockImageTypeTag::Object2:
		_blockType = BlockTypeTag::Object;
		break;
	case BlockImageTypeTag::Object3:
		_blockType = BlockTypeTag::Object;
		break;
	}
}

void Block::Update()
{
	if (_blockType != BlockTypeTag::Object)
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
				switch (_blockImageType)
				{
				case BlockImageTypeTag::BasketBlock:
					setAnimationInfo("block1Pop", _POP_COOLTIME);
					break;
				case BlockImageTypeTag::GreenBlock:
					setAnimationInfo("block2Pop", _POP_COOLTIME);
					break;
				case BlockImageTypeTag::YGreenBlock:
					setAnimationInfo("block3Pop", _POP_COOLTIME);
					break;
				case BlockImageTypeTag::FlowerBlock:
					setAnimationInfo("block4Pop", _POP_COOLTIME);
					break;
				case BlockImageTypeTag::GrassBlock1:
					setAnimationInfo("block5Pop", _POP_COOLTIME);
					break;
				case BlockImageTypeTag::GrassBlock2:
					setAnimationInfo("block6Pop", _POP_COOLTIME);
					break;
				default:
					break;
				}
				_previousState = _currentState;
			}

			animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

			if (getFrame() == ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX())
			{
				if (_blockType == BlockTypeTag::PasslessItem)
				{
					Item* item = new Item(_mapSpace, static_cast<ItemTypeTag>(getRand(1, 4)));
					GameObjectManager::getSingleton()->registerObj(item);
				}

				GameObjectManager::getSingleton()->removeObj(getId());
			}
		}
	}
}

void Block::Render(HDC hdc)
{
	if (_blockType == BlockTypeTag::Object)
	{
		switch (_blockImageType)
		{
		case BlockImageTypeTag::Object1:
			ImageManager::getSingleton()->Render("forestObject1", hdc, _start.x, _start.y - 8.0f);
			break;
		case BlockImageTypeTag::Object2:
			ImageManager::getSingleton()->Render("forestObject2", hdc, _start.x, _start.y - 8.0f);
			break;
		case BlockImageTypeTag::Object3:
			ImageManager::getSingleton()->Render("forestObject3", hdc, _start.x, _start.y - 8.0f);
			break;
		}
	}
	else
	{
		ImageManager::getSingleton()->findImage(getStrKey())->
			frameRender(hdc, static_cast<int>(_start.x - 6.f), static_cast<int>(_start.y - 12.f)
				, getFrame(), 0);
	}
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
