#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
	_instance_id = 0;

	_layerOrders.push_back(GameObjectTag::WaveStartingPoint);
	_layerOrders.push_back(GameObjectTag::Wave);
	_layerOrders.push_back(GameObjectTag::Item);
	_layerOrders.push_back(GameObjectTag::Bomb);
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

	/*if (GAMESTATEMANAGER->getGameStart())
	{
		notifyCollisions();
	}*/
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