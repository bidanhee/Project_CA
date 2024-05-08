#pragma once
#include "Global.h"
#include "gameObject.h"
#include "Player.h"
class Bomb : public GameObject
{
private:
	POINT_FLOAT _center;
	POINT_FLOAT _start;

	Player* _bombOwner;
	MapSpace _mapSpace;

	BombStateTag _previousState;
	BombStateTag _currentState;

	float _startTime;

	const int _SIZE;
	const int _POWER;
	const float _BOMB_COOLTIME;
	const float _POP_COOLTIME;
	const float _POP_TIME;
	const float _DISAPPEAR_TIME;

public:
	Bomb(Player* player, POINT_FLOAT center, int power);
	~Bomb();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void onCollisionEnter(GameObject* other, RECT area);


};