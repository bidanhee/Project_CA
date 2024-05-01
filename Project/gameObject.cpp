#include "gameObject.h"
#include "TimeManager.h"
void GameObject::animation(int maxFrame)
{
    _coolDown -= TimeManager::getSingleton()->getElapsedTime();

    if (_coolDown <= 0.0f)
    {
        _coolDown = _coolTime;
        _frame++;
        _frame %= (maxFrame + 1);
    }
}

void GameObject::onCollisionEnter(GameObject* other, RECT area)
{
}