#pragma once
#include "gameObject.h"
class Item : public GameObject
{
private:
	POINT_FLOAT _center;
	POINT_FLOAT _start;

	MapSpace _mapSpace;

	ItemTypeTag _itemType;

	float _isNewCoolDown;
	bool _isNew;

	const int _SIZE;
	const int _ANIMATION_COOLTIME;
public:
	Item(MapSpace, ItemTypeTag);
	~Item();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void onCollisionEnter(GameObject* other, RECT area);

	ItemTypeTag getItemType() { return _itemType; }
	float getStartX() { return _start.x; }
	float getStartY() { return _start.y; }
	float getCenterX() { return _center.x; }
	float getCenterY() { return _center.y; }
	int getSize() { return _SIZE; }
	bool getIsNew() { return _isNew; }
};