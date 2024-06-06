#pragma once
#include "winFroc.h"
#include "gameObjectManager.h"

class cGame : 
    public WinFroc
{
public:
    cGame(HINSTANCE, HWND);
    virtual ~cGame();

    virtual HRESULT Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render() override;
};

