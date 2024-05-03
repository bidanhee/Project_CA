#pragma once
#include "Global.h"

class Scene
{
private:

public:
    Scene() {}
    virtual ~Scene() {}

    virtual void Init() {}
    virtual void Release() {}
    virtual void Update() {}
    virtual void Render(HDC hdc) {}

    virtual void handleArgs(vector<int> args) {}
};