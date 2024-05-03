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
	for (auto g : _gameObj)
	{
		g->Update();
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