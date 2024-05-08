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
    /*Player* player2 = new Player(PlayerTypeTag::SoloPlayer, 400, 400);
    Bomb* testBomb = new Bomb(player1, player1->getCenter(), 1);
    Bomb* testBomb2 = new Bomb(player2, player2->getCenter(), 1);
    Bomb* testBomb3 = new Bomb(player2, player2->getCenter(), 1);*/
    GameObjectManager::getSingleton()->registerObj(player1);
    /*GameObjectManager::getSingleton()->registerObj(player2);
    GameObjectManager::getSingleton()->registerObj(testBomb);
    GameObjectManager::getSingleton()->registerObj(testBomb2);
    GameObjectManager::getSingleton()->registerObj(testBomb3);*/
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
    GameObjectManager::getSingleton()->debug(getMemDC());

    this->getBackBuffer()->Render(getHDC());
}