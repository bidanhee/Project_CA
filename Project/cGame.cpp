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
    Player* player1 = new Player(PlayerTypeTag::SoloPlayer, 100, 100);
    GameObjectManager::getSingleton()->registerObj(player1);
    return S_OK;
}

void cGame::Release()
{
    GameObjectManager::getSingleton()->releaseObj();
    WinFroc::Release();
}

void cGame::Update()
{
    WinFroc::Update();
    GameObjectManager::getSingleton()->updateObj();
}

void cGame::Render()
{
    PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

    ImageManager::getSingleton()->Render("playBg", getMemDC());
    //ImageManager::getSingleton()->Render("player1", getMemDC(), 100, 100);
    //ImageManager::getSingleton()->Render("playerBazziReady", getMemDC(), 100, 130);
    //ImageManager::getSingleton()->Render("OVER", getMemDC(), 200, 200);
    GameObjectManager::getSingleton()->renderObj(getMemDC());
    TimeManager::getSingleton()->Render(getMemDC());

    this->getBackBuffer()->Render(getHDC());
}