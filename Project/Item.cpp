#include "Item.h"
#include "ImageManager.h"
#include "TimeManager.h"

Item::Item(MapSpace mapSpace, ItemTypeTag itemType)
	: GameObject(GameObjectTag::Item)
	, _mapSpace(mapSpace)
	, _itemType(itemType)
	, _SIZE(BOARD_RECTSIZE)
	, _ANIMATION_COOLTIME(1.f)
	, _isNewCoolDown(0.2f)
{
	POINT_FLOAT pt;
	pt = mapSpaceToLeftTop(_mapSpace.row, _mapSpace.col);
	_start = pt;
	_isNew = true;
	_center.x = _start.x + _SIZE / 2.f;
	_center.y = _start.y + _SIZE / 2.f;
}

Item::~Item()
{
}

void Item::Init()
{
	switch (_itemType)
	{
	case ItemTypeTag::Ballon:
		setAnimationInfo("itemBallon", _ANIMATION_COOLTIME);
		break;
	case ItemTypeTag::Potion:
		setAnimationInfo("itemPotion", _ANIMATION_COOLTIME);
		break;
	case ItemTypeTag::PotionMax:
		setAnimationInfo("itemPotionMax", _ANIMATION_COOLTIME);
		break;
	case ItemTypeTag::Skate:
		setAnimationInfo("itemSkate", _ANIMATION_COOLTIME);
		break;
	}
}

void Item::Update()
{
	animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());
	_isNewCoolDown -= TimeManager::getSingleton()->getElapsedTime();
	if (_isNewCoolDown <= 0.f)
	{
		_isNew = false;
	}
}

void Item::Render(HDC hdc)
{
	ImageManager::getSingleton()->findImage(getStrKey())->
		frameRender(hdc, static_cast<int>(_start.x - 2.f), static_cast<int>(_start.y - 18.f)
		, getFrame(), 0);
}

void Item::Release()
{
}

void Item::onCollisionEnter(GameObject* other, RECT area)
{
}
