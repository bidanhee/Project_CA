#include "cGame.h"

cGame::cGame(HINSTANCE instance, HWND wnd)
{
    WinFroc::InitHandle(instance, wnd);
}

cGame::~cGame()
{
}

HRESULT cGame::Init()
{
    WinFroc::Init(true);

    return S_OK;
}

void cGame::Release()
{
    WinFroc::Release();
}

void cGame::Update()
{
    WinFroc::Update();
}

void cGame::Render()
{
    PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

    ImageManager::getSingleton()->render("playBg", getMemDC());
    ImageManager::getSingleton()->render("player1", getMemDC(), 100, 100);
    ImageManager::getSingleton()->render("playerBazziReady", getMemDC(), 100, 130);
    ImageManager::getSingleton()->render("OVER", getMemDC(), 200, 200);

    TimeManager::getSingleton()->render(getMemDC());

    this->getBackBuffer()->Render(getHDC());
}