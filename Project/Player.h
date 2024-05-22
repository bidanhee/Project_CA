#pragma once
#include "gameObject.h"

class Player : public GameObject
{
private:
	PlayerTypeTag _playerType;
	POINT_FLOAT _start;
	POINT_FLOAT _center;
	POINT_FLOAT _collisionStart;
	POINT_FLOAT _bodyStart;
	POINT_FLOAT _previousStart;

	float _speed;     
	int _usableBombs; 
	int _usedBombs; 
	int _power;

	PlayerStateTag _previousState;
	PlayerStateTag _currentState;

	int _startTime;
	float _trapMoveCoolDown;
	int _count;
	bool _setLive; 
	bool _check;

	const int _WIDTH;
	const int _HEIGHT;
	const int _COLLISION_WIDTH;
	const int _COLLISION_HEIGHT;
	const int _BODY_WIDTH;
	const int _BODY_HEIGHT;

	const float _TRAP_SPEED;
	const float _MOVE_COOLTIME;
	const float _WAIT_COOLTIME;
	const float _READY_COOLTIME;
	const float _TRAP_COOLTIME;
	const float _TRAP_MOVE_COOLTIME;
	const float _DIE_COOLTIME;

	const float _BOMB_CREATE_COOLTIME;
	float _bombCreateTime;
public:
	Player(PlayerTypeTag playerType, float startX, float startY);
	~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void onCollisionEnter(GameObject* other, RECT area) override;

	void setCenter();
	void setCollisionStart();
	void setBodyStart();

	void changeUsedBombs();

	//get set
	POINT_FLOAT getCenter() const
	{
		return _center;
	}
	int getWidth() const
	{
		return _WIDTH;
	}
	int getHeight() const
	{
		return _HEIGHT;
	}

	float getStartX() const
	{
		return _start.x;
	}

	void setStartX(const float startX)
	{
		_start.x = startX;
	}

	float getStartY() const
	{
		return _start.y;
	}
	void setStartY(const float startY)
	{
		_start.y = startY;
	}

	int getCollisionWidth() const
	{
		return _COLLISION_WIDTH;
	}
	int getCollisionHeight() const
	{
		return _COLLISION_HEIGHT;
	}

	float getCollisionStartX()
	{
		return _collisionStart.x;
	}
	void setCollisionStartX(float collisionStartX)
	{
		_collisionStart.x = collisionStartX;
	}
	float getCollisionStartY()
	{
		return _collisionStart.y;
	}
	void setCollisionStartY(float collisionStartY)
	{
		_collisionStart.y = collisionStartY;
	}


	int getBodyWidth() const
	{
		return _BODY_WIDTH;
	}
	int getBodyHeight() const
	{
		return _BODY_HEIGHT;
	}

	float getBodyStartX()
	{
		return _bodyStart.x;
	}
	void setBodyStartX(float bodyStartX)
	{
		_bodyStart.x = bodyStartX;
	}
	float getBodyStartY()
	{
		return _bodyStart.y;
	}
	void setBodyStartY(float bodyStartY)
	{
		_bodyStart.y = bodyStartY;
	}

	PlayerTypeTag getPlayerType() const
	{
		return _playerType;
	}

	PlayerStateTag getPlayerState()
	{
		return _currentState;
	}
	void setPlayerState(PlayerStateTag state)
	{
		_previousState = _currentState;
		_currentState = state;
	}
	bool getLive()
	{
		return _setLive;
	}
	void setLive(bool live)
	{
		_setLive = live;
	}
};