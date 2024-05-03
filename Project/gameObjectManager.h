#pragma once
#include "Singleton.h"
#include "GameObject.h"

class GameObjectManager : public Singleton<GameObjectManager>
{
private:
    vector<GameObject*> _gameObj;
    vector<GameObjectTag> _layerOrders;
    int _instance_id;

public:
    GameObjectManager();
    ~GameObjectManager();

    size_t getGameObjSize()
    {
        return _gameObj.size();
    }
    vector<GameObject*> getGameObject()
    {
        return _gameObj;
    }

    void registerObj(GameObject* gameObj);
    void removeObj(int id);
    void removeObjAll();

    void updateObj();
    void renderObj(HDC hdc);
    void releaseObj();

    void checkCollision();

};