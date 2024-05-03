#pragma once
#include "Global.h"

class GameObject
{
private:
    int _instance_id;
    GameObjectTag _tag;

    //애니메이션
    string _strKey;
    int _frame;
    float _coolTime;
    float _coolDown;

public:
    GameObject(GameObjectTag tag)
        : _instance_id(-1)
        , _tag(tag)
        , _strKey(string())
        , _frame(0)
        , _coolTime(0.f)
    {
        _coolDown = _coolTime;
    }
    virtual ~GameObject()
    {
    }

    virtual void Init() { }
    virtual void Update() { }
    virtual void Render(HDC hdc) { }
    virtual void Release() { }

    virtual void animation(int maxFrame) final;
    virtual void onCollisionEnter(GameObject* other, RECT area);


    //get set
    //
    void setId(const int id)
    {
        _instance_id = id;
    }
    int getId() const
    {
        return _instance_id;
    }

    void setStrKey(const string strKey)
    {
        _strKey = strKey;
    }
    string getStrKey() const
    {
        return _strKey;
    }

    void setFrame(const int frame)
    {
        _frame = frame;
    }
    int getFrame() const
    {
        return _frame;
    }

    void setCoolTime(const float coolTime)
    {
        _coolTime = coolTime;
    }
    float getCoolTime() const
    {
        return _coolTime;
    }

    void setCoolDown(const float coolDown)
    {
        _coolDown = coolDown;
    }
    float getCoolDown() const
    {
        return _coolDown;
    }

    void setAnimationInfo(const string strKey, const float coolTime, const int frame = 0)
    {
        _strKey = strKey;
        _coolTime = coolTime;
        _coolDown = _coolTime;
        _frame = frame;
    }

    GameObjectTag getTag()
    {
        return _tag;
    }
};