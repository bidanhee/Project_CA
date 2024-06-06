#pragma once
#include "Scene.h"
class MainScene : public Scene
{
private:
    RECT _rect;

public:
    MainScene();
    ~MainScene();

    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
};