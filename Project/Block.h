#pragma once
#include "Global.h"
#include "gameObject.h"
class Block : public GameObject
{
private:
	POINT_FLOAT _center;
	POINT_FLOAT _start;

	MapSpace _mapSpace;

	BlockStateTag _previousState;
	BlockStateTag _currentState;

	const BlockTypeTag _blockType;
	const int _SIZE;
	const float _ANIMATION_COOLTIME;
	const float _POP_COOLTIME;
	const float _POP_TIME;
	const float _DISAPPEAR_TIME;

public:
	Block(MapSpace, BlockTypeTag);
	~Block();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void onCollisionEnter(GameObject* other, RECT area);

	void setState(BlockStateTag);

	float getStartX() { return _start.x; }
	float getStartY() { return _start.y; }
	float getCenterX() { return _center.x; }
	float getCenterY() { return _center.y; }
	int getSize() { return _SIZE; }
	BlockStateTag getState() { return _currentState; }
};