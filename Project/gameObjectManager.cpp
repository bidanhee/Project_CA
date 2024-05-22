#include "GameObjectManager.h"
#include "Player.h"
#include "Item.h"
#include "Bomb.h"
#include "Block.h"
#include "Wave.h"
#include "WaveController.h"

GameObjectManager::GameObjectManager()
{
	_instance_id = 0;

	_layerOrders.push_back(GameObjectTag::WaveStartingPoint);
	_layerOrders.push_back(GameObjectTag::Wave);
	_layerOrders.push_back(GameObjectTag::Item);
	_layerOrders.push_back(GameObjectTag::Bomb);
	_layerOrders.push_back(GameObjectTag::Block);
	_layerOrders.push_back(GameObjectTag::Player);
	_layerOrders.push_back(GameObjectTag::DesignElement);
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::registerObj(GameObject* obj)
{
	obj->setId(_instance_id++);
	_gameObj.push_back(obj);
	obj->Init(); 
}

void GameObjectManager::removeObj(int id)
{
	for (size_t i = 0; i < _gameObj.size(); ++i)
	{
		if (_gameObj[i]->getId() == id)
			_gameObj.erase(_gameObj.begin() + i);
	}
}

void GameObjectManager::removeObjAll()
{
	_gameObj.resize(0);
}

void GameObjectManager::updateObj()
{
	for (size_t i = 0; i < _gameObj.size(); ++i)
	{
		GameObject* g = _gameObj[i];
		if (g != nullptr)
		{
			g->Update();
		}
	}

	checkCollision();
}

void GameObjectManager::renderObj(HDC hdc)
{
	map<GameObjectTag, vector<GameObject*>> m;
	for (auto go : _gameObj)
		m[go->getTag()].push_back(go);

	for (auto tag : _layerOrders)
	{
		for (auto go : m[tag])
			go->Render(hdc);
	}
}

void GameObjectManager::releaseObj()
{
	for (size_t i = 0; i < _gameObj.size(); ++i)
	{
		_gameObj[i]->Release();
	}
}

void GameObjectManager::checkCollision()
{
	map<GameObjectTag, vector<GameObject*>> m;
	RECT rcTemp;

	for (auto go : _gameObj)
	{
		m[go->getTag()].push_back(go);
	}

	for (auto player : m[GameObjectTag::Player])
	{
		for (auto item : m[GameObjectTag::Item])
		{
			Player* p = dynamic_cast<Player*>(player);
			Item* i = dynamic_cast<Item*>(item);
			RECT playerCollisionRect = makeRect(p->getCollisionStartX(), p->getCollisionStartY(), p->getCollisionWidth(), p->getCollisionHeight());
			RECT itemRect = makeRect(i->getStartX(), i->getStartY(), i->getSize(), i->getSize());
			if (IntersectRect(&rcTemp, &playerCollisionRect, &itemRect))
			{
				GameObjectManager::getSingleton()->removeObj(i->getId());
				player->onCollisionEnter(item, rcTemp);
			}
		}

		for (auto block : m[GameObjectTag::Block])
		{
			Player* p = dynamic_cast<Player*>(player);
			Block* b = dynamic_cast<Block*>(block);
			RECT playerCollisionRect = makeRect(p->getCollisionStartX(), p->getCollisionStartY(), p->getCollisionWidth(), p->getCollisionHeight());
			RECT blockRect = makeRect(b->getStartX(), b->getStartY(), b->getSize(), b->getSize());
			if (IntersectRect(&rcTemp, &playerCollisionRect, &blockRect))
			{
				player->onCollisionEnter(block, rcTemp);
			}
		}
	}

	for (auto item : m[GameObjectTag::Item])
	{
		for (auto wave : m[GameObjectTag::Wave])
		{
			Wave* w = dynamic_cast<Wave*>(wave);
			Item* i = dynamic_cast<Item*>(item);
			RECT waveRect = makeRect(w->getStartX(), w->getStartY(), w->getSize(), w->getSize());
			RECT itemRect = makeRect(i->getStartX(), i->getStartY(), i->getSize(), i->getSize());
			if (IntersectRect(&rcTemp, &waveRect, &itemRect))
			{
				GameObjectManager::getSingleton()->removeObj(i->getId());
			}
		}
		for (auto waveStartingPoint : m[GameObjectTag::WaveStartingPoint])
		{
			Item* i = dynamic_cast<Item*>(item);
			WaveController* wsp = dynamic_cast<WaveController*>(waveStartingPoint);
			RECT itemRect = makeRect(i->getStartX(), i->getStartY(), i->getSize(), i->getSize());
			RECT waveStartingPointRect = makeRect(wsp->getStartX(), wsp->getStartY(), wsp->getSize(), wsp->getSize());
			if (IntersectRect(&rcTemp, &itemRect, &waveStartingPointRect))
			{
				GameObjectManager::getSingleton()->removeObj(i->getId());
			}
		}
	}
}

string GameObjectManager::showTagForDebug(GameObjectTag tag)
{
	switch (tag)
	{
	case GameObjectTag::Not:
		return "Not";
	case GameObjectTag::Player:
		return "Player";
	case GameObjectTag::Bomb:
		return "Bomb";
	case GameObjectTag::DesignElement:
		return "Design Element";
	case GameObjectTag::Wave:
		return "Wave";
	case GameObjectTag::WaveStartingPoint:
		return "WaveStartingPoint";
	case GameObjectTag::Item:
		return "Item";
	case GameObjectTag::Block:
		return "Block";
	default:
		return "?";
	}
}

void GameObjectManager::debug(HDC hdc)
{
	Text(15, 30, 80, "GameObj size: " + to_string(getGameObjSize()))(hdc);
	for (size_t i = 0; i < _gameObj.size(); ++i)
	{
		Text(15, 30, 100 + (15 * i), "ID: " + to_string(_gameObj[i]->getId()) + ", TAG: " + showTagForDebug(_gameObj[i]->getTag()), BLACK)(hdc);
	}
}