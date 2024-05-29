#include "cGame.h"

cGame::cGame(HINSTANCE instance, HWND wnd)
{
    WinFroc::InitHandle(instance, wnd);
}

cGame::~cGame()
{
}
vector<vector<Tile>> _vvTile;
HRESULT cGame::Init()
{
    WinFroc::Init(true);

    _vvTile = MapManager::makeMap(1);


    Player* player1 = new Player(PlayerTypeTag::SoloPlayer, 50, 100);
    /*Player* player2 = new Player(PlayerTypeTag::SoloPlayer, 400, 400);
    Bomb* testBomb = new Bomb(player1, player1->getCenter(), 1);
    Bomb* testBomb2 = new Bomb(player2, player2->getCenter(), 1);
    Bomb* testBomb3 = new Bomb(player2, player2->getCenter(), 1);*/
    GameObjectManager::getSingleton()->registerObj(player1);
    /*GameObjectManager::getSingleton()->registerObj(player2);
    GameObjectManager::getSingleton()->registerObj(testBomb);
    GameObjectManager::getSingleton()->registerObj(testBomb2);
    GameObjectManager::getSingleton()->registerObj(testBomb3);*/

    MapManager::makeBlocks(1);

    return S_OK;
}

void cGame::Release()
{
    GameObjectManager::getSingleton()->releaseObj();
    WinFroc::Release();
}

float testCoolDown = 1.0f;
void cGame::Update()
{
    WinFroc::Update();
    GameObjectManager::getSingleton()->updateObj();

    /*testCoolDown -= TimeManager::getSingleton()->getElapsedTime();
    if (testCoolDown <= 0.f)
    {
        MapSpace mapSpace;
        mapSpace.row = getRand(1, 10);
        mapSpace.col = getRand(1, 10);
        Item* item = new Item(mapSpace, static_cast<ItemTypeTag>(getRand(1, 4)));
        GameObjectManager::getSingleton()->registerObj(item);
        testCoolDown += 3.f;
    }*/
}

void cGame::Render()
{
    PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

    for (int i = 0; i < BOARD_ROW; ++i)
    {
        for (int j = 0; j < BOARD_COL; ++j)
        {
            ImageManager::getSingleton()->findImage(_vvTile[i][j].getStrKey())->
                Render(getMemDC(), BOARD_STARTX + (BOARD_RECTSIZE * j), BOARD_STARTY + (BOARD_RECTSIZE * i));
        }
    }

    ImageManager::getSingleton()->Render("playBg", getMemDC());

    //ImageManager::getSingleton()->Render("OVER", getMemDC(), 200, 200);
    GameObjectManager::getSingleton()->renderObj(getMemDC());
    TimeManager::getSingleton()->Render(getMemDC());
    GameObjectManager::getSingleton()->debug(getMemDC());

    this->getBackBuffer()->Render(getHDC());
}