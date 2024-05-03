#include "Player.h"

#include "TimeManager.h"
#include "ImageManager.h"
#include "KeyManager.h"

#define BOARD_STARTX   26
#define BOARD_STARTY   53
#define BOARD_RECTSIZE 52
#define BOARD_ROW      13
#define BOARD_COL      15
#define BOARD_WIDTH    (BOARD_RECTSIZE * BOARD_COL)  //780
#define BOARD_HEIGHT   (BOARD_RECTSIZE * BOARD_ROW ) //676

Player::Player(PlayerTypeTag playerType, float startX, float startY)
	: GameObject(GameObjectTag::Player)
	, _playerType(playerType)
	, _WIDTH(BOARD_RECTSIZE)
	, _HEIGHT(BOARD_RECTSIZE)
	, _speed(5.f)
	, _usedBombs(0)
	, _usableBombs(1)       
	, _power(1)               
	, _previousState(PlayerStateTag::Not)
	, _currentState(PlayerStateTag::Ready)
	, _startTime(static_cast<int>(TimeManager::getSingleton()->getWorldTime()))
	, _COLLISION_WIDTH(20)
	, _COLLISION_HEIGHT(26)
	, _BODY_WIDTH(42)
	, _BODY_HEIGHT(24)
	, _TRAP_SPEED(0.2f)
	, _setLive(false)
	, _MOVE_COOLTIME(0.1f)
	, _WAIT_COOLTIME(4.0f)
	, _READY_COOLTIME(0.1f)
	, _TRAP_COOLTIME(0.2f)
	, _TRAP_MOVE_COOLTIME(0.3f) 
	, _DIE_COOLTIME(0.2f)
	, _count(0)           
	, _check(false)
{
	_start.x = startX;
	_start.y = startY;

	setCenter();              
	setCollisionStart();       
	setBodyStart();           

	setAnimationInfo("playerBazziReady", _READY_COOLTIME);
}

Player::~Player()
{

}

void Player::Init()
{
}

void Player::Update()
{
	/*if (!GAMESTATEMANAGER->getGameStart())                             //게임이 시작하기 전에는 레디 애니메이션을 보여준다
	{
		int maxFrame = IMAGEMANAGER->findImage(getStrKey())->getMaxFrameX();
		animation(maxFrame);
		if (getFrame() >= maxFrame)                                    //번쩍번쩍 프레임 위함
			setFrame(15);
	}*/
	if (false) {}
	else
	{
		if (_currentState == PlayerStateTag::Ready)
		{
			setAnimationInfo("playerBazziWait", _WAIT_COOLTIME);
			_previousState = _currentState;
			_currentState = PlayerStateTag::Wait;
		}
		else if (_currentState == PlayerStateTag::Trap)
		{
			if (_currentState != _previousState)
			{
				_startTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime());
				setAnimationInfo("playerBazziTrap", _TRAP_COOLTIME);
				_speed = _TRAP_SPEED; //스피드 느려짐
				_previousState = _currentState;
			}
			int maxFrame = ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX();
			animation(maxFrame);
			if (getFrame() >= maxFrame)
				setFrame(8);

			//조금씩 아래로 내려온다
			_trapMoveCoolDown -= TimeManager::getSingleton()->getElapsedTime();
			if (_trapMoveCoolDown <= 0.f)
			{
				_trapMoveCoolDown = _TRAP_MOVE_COOLTIME;
				if (_start.y + 2.f <= BOARD_STARTY + BOARD_HEIGHT - _HEIGHT) //빠져나가지 않게 처리
					_start.y += 2.f;
			}

			int currentTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime());
			//cout << currentTime - _startTime << endl;
			if (currentTime - _startTime > 7) //7초가 지나면 죽은 상태로!!
			{
				_startTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime()); //죽고나서 몇초 시간 재기위함
				_previousState = _currentState;
				_currentState = PlayerStateTag::Die;
			}

			//갇혔을 때의 키보드 처리
			if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_UP)) ||
				(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_UP)) ||
				(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('R')))
			{
				if (_start.y - _speed >= BOARD_STARTY)
					_start.y -= _speed;
			}
			else if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_DOWN)) ||
				(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_DOWN)) ||
				(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('F')))
			{
				if (_start.y + _speed <= BOARD_STARTY + BOARD_HEIGHT - _HEIGHT)
					_start.y += _speed;
			}
			else if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_LEFT)) ||
				(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_LEFT)) ||
				(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('D')))
			{
				if (_start.x - _speed >= BOARD_STARTX)
					_start.x -= _speed;
			}
			else if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_RIGHT)) ||
				(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_RIGHT)) ||
				(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('G')))
			{
				if (_start.x + _speed <= BOARD_STARTX + BOARD_WIDTH - _WIDTH)
					_start.x += _speed;
			}
		}
		else if (_currentState == PlayerStateTag::Die)
		{
			/*GAMESTATEMANAGER->setGameOver(true);//게임오버 상태로 만든다
			if (_currentState != _previousState)
			{
				SOUNDMANAGER->play(static_cast<int>(SoundTypeTag::PlayerDie), SoundTypeTag::PlayerDie);
				SOUNDMANAGER->play(static_cast<int>(SoundTypeTag::GameOver), SoundTypeTag::GameOver);
				setAnimationInfo("playerBazziDie", _DIE_COOLTIME);
				_previousState = _currentState;
				//_flag = true;
			}
			int maxFrame = IMAGEMANAGER->findImage(getStrKey())->getMaxFrameX();
			animation(maxFrame);
			if (_count <= 3)
			{
				if (getFrame() >= maxFrame)
				{
					++_count;
					setFrame(7);
				}
			}
			else
				setFrame(maxFrame);

			//죽은지 5초 뒤에 게임오브젝트 매니저에서 삭제
			int currentTime = static_cast<int>(TIMEMANAGER->getWorldTime());
			if (currentTime - _startTime > 5)
				GAMEOBJMANGER->removeObj(getId());
				*/
		} //죽은 경우 끝
		else if (_currentState == PlayerStateTag::Live)
		{
			if (_currentState != _previousState)
			{
				//SOUNDMANAGER->play(static_cast<int>(SoundTypeTag::BombPop), SoundTypeTag::BombPop);
				setAnimationInfo("playerBazziLive", 0.3f);
				_previousState = _currentState;
			}
			int maxFrame = ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX();
			animation(maxFrame);
			if (getFrame() >= maxFrame)
			{
				_previousState = _currentState;
				_currentState = PlayerStateTag::Jump;
			}
		}
		else if (_currentState == PlayerStateTag::Jump)
		{
			if (_currentState != _previousState)
			{
				setAnimationInfo("playerBazziJump", 0.3f);
				_previousState = _currentState;
			}
			animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());
		}
		else
		{
			if (true/*!GAMESTATEMANAGER->getGameOver()*/)
			{
				if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_SPACE)) ||
					(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_RSHIFT)) ||
					(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown(VK_LSHIFT)))
				{
					if (!_check)
					{
						_check = true;
						//SOUNDMANAGER->play(static_cast<int>(SoundTypeTag::BombSet), SoundTypeTag::BombSet);
					}

					/*MapSpace m = centerToMapSpace(_center.x, _center.y);
					if (!PlayScene::mapArr[m.row][m.col].isBomb)
					{
						if (_usedBombs < _usableBombs)
						{
							Bomb* bomb = new Bomb(this, _center, _power);
							GAMEOBJMANGER->registerObj(bomb);
							_usedBombs++;
						}
					}*/
				}

				if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_UP)) ||
					(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_UP)) ||
					(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('R')))
				{
					_startTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime());

					_previousState = _currentState;
					_currentState = PlayerStateTag::Up;
					if (_previousState != _currentState)
					{
						setAnimationInfo("playerBazziUp", _MOVE_COOLTIME);
					}
					animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

					if (_start.y - _speed >= BOARD_STARTY)
					{
						_start.y -= _speed;
					}
				}
				else if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_DOWN)) ||
					(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_DOWN)) ||
					(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('F')))
				{
					_startTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime());

					_previousState = _currentState;
					_currentState = PlayerStateTag::Down;
					if (_previousState != _currentState)
					{
						setAnimationInfo("playerBazziDown", _MOVE_COOLTIME);
					}
					animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

					if (_start.y + _speed <= BOARD_STARTY + BOARD_HEIGHT - _HEIGHT)
					{
						_start.y += _speed;
					}
				}
				else if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_LEFT)) ||
					(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_LEFT)) ||
					(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('D')))
				{
					_startTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime());

					_previousState = _currentState;
					_currentState = PlayerStateTag::Left;
					if (_previousState != _currentState)
					{
						setAnimationInfo("playerBazziLeft", _MOVE_COOLTIME);
					}
					animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

					if (_start.x - _speed >= BOARD_STARTX)
					{
						_start.x -= _speed;
					}
				}
				else if ((_playerType == PlayerTypeTag::SoloPlayer && KeyManager::getSingleton()->isStayKeyDown(VK_RIGHT)) ||
					(_playerType == PlayerTypeTag::Player2 && KeyManager::getSingleton()->isStayKeyDown(VK_RIGHT)) ||
					(_playerType == PlayerTypeTag::Player1 && KeyManager::getSingleton()->isStayKeyDown('G')))
				{
					_startTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime());

					_previousState = _currentState;
					_currentState = PlayerStateTag::Right;
					if (_previousState != _currentState)
					{
						setAnimationInfo("playerBazziRight", _MOVE_COOLTIME);
					}
					animation(ImageManager::getSingleton()->findImage(getStrKey())->getMaxFrameX());

					if (_start.x + _speed <= BOARD_STARTX + BOARD_WIDTH - _WIDTH)
					{
						_start.x += _speed;
					}
				}
				else // 키 입력이 없는 경우
				{
					if (_currentState == PlayerStateTag::Left || _currentState == PlayerStateTag::Right ||
						_currentState == PlayerStateTag::Up || _currentState == PlayerStateTag::Down)
					{
						//캐릭터는 항상 0이나 4프레임으로 끝나야함
						int frameX = ImageManager::getSingleton()->findImage(getStrKey())->getFrameX();
						if (frameX != 0 || frameX != 4)
							setFrame(0);

						//키입력이 없고, 일정시간이 지나면 정면을 바라본다
						int currentTime = static_cast<int>(TimeManager::getSingleton()->getWorldTime());
						if (currentTime - _startTime > 3)
						{
							setAnimationInfo("playerBazziWait", _WAIT_COOLTIME);
							_previousState = _currentState;
							_currentState = PlayerStateTag::Wait;
						}

					}
				}//키 입력이 없는 경우
			}//게임오버상태가 아닌경우 끝
		} //레디도 트랩도 죽은상태도 아닌경우


		setCenter();
		setCollisionStart();
		setBodyStart();
	}
}


void Player::Render(HDC hdc)
{
	if (_currentState == PlayerStateTag::Ready)
		ImageManager::getSingleton()->findImage(getStrKey())->frameRender(hdc, static_cast<int>(_center.x - 32.f), static_cast<int>(_center.y - 65.f), getFrame(), 0);
	else if (_currentState == PlayerStateTag::Trap || _currentState == PlayerStateTag::Die) 
		ImageManager::getSingleton()->findImage(getStrKey())->frameRender(hdc, static_cast<int>(_center.x - 44.f), static_cast<int>(_center.y - 76.f), getFrame(), 0);
	else //기본
		ImageManager::getSingleton()->findImage(getStrKey())->frameRender(hdc, static_cast<int>(_center.x - 32.f), static_cast<int>(_center.y - 55.f), getFrame(), 0);


	if (_playerType == PlayerTypeTag::Player1)
		ImageManager::getSingleton()->findImage("player1")->Render(hdc, _center.x - 12.f, _center.y - 90.f);
	else if (_playerType == PlayerTypeTag::Player2)
		ImageManager::getSingleton()->findImage("player2")->Render(hdc, _center.x - 12.f, _center.y - 90.f);
	else if (_playerType == PlayerTypeTag::SoloPlayer)
		ImageManager::getSingleton()->findImage("soloPlayer")->Render(hdc, _center.x - 12.f, _center.y - 90.f);

}

void Player::Release()
{
}


void Player::onCollisionEnter(GameObject* other, RECT area)
{
	/*switch (other->getTag())
	{
	case GameObjectTag::Wave: 
	case GameObjectTag::WaveStartingPoint:
	{
		_previousState = _currentState;
		_currentState = PlayerStateTag::Trap;
	}
	break;
	case GameObjectTag::Item:
	{
		SOUNDMANAGER->play(static_cast<int>(SoundTypeTag::EatItem), SoundTypeTag::EatItem);
		Item* item = dynamic_cast<Item*>(other);

		switch (item->getItemType())
		{
		case ItemTypeTag::Ballon:
			if (_usableBombs < 6)
				_usableBombs++;
			break;
		case ItemTypeTag::Potion:
			if (_power < 7)
				_power++;
			break;
		case ItemTypeTag::PotionMakePowerMax:
			if (_power < 7)
				_power = 7;
			break;
		case ItemTypeTag::Skate:
			if (_speed < 5.f)
				_speed += 1.f;
			break;
		}

	}
	break;
	}
	*/
}

void Player::setCenter()
{
	_center.x = _start.x + (_WIDTH / 2) + 1;
	_center.y = _start.y + (_HEIGHT / 2);
}

void Player::setCollisionStart()
{
	_collisionStart.x = _center.x - 10;
	_collisionStart.y = _center.y - 8;
}

void Player::setBodyStart()
{
	_bodyStart.x = _center.x - 21;
	_bodyStart.y = _center.y - 8;
}

void Player::changeUsedBombs()
{
	_usedBombs--;
}
