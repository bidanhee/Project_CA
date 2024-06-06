#include "playScene.h"
BombOnTyleTag PlayScene::bombArr[BOARD_ROW][BOARD_COL] = {};

#include "gameObjectManager.h"
#include "Player.h"
#include "Bomb.h"
#include "Item.h"
#include "MapManager.h"
#include "Block.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "SoundManager.h"

vector<vector<Tile>> _vvTile;

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
{

}

void PlayScene::Init()
{
    _vvTile = MapManager::makeMap(1);
    MapManager::makeBlocks(1);

    Player* player1 = new Player(PlayerTypeTag::Player1, 50, 100);
    GameObjectManager::getSingleton()->registerObj(player1);
    Player* player2 = new Player(PlayerTypeTag::Player2, 500, 400);
    GameObjectManager::getSingleton()->registerObj(player2);
}

void PlayScene::Release()
{
}

void PlayScene::Update()
{
    SoundManager::getSingleton()->repeatPlay(static_cast<int>(SoundTypeTag::PlayScene), SoundTypeTag::PlayScene);
}

void PlayScene::Render(HDC hdc)
{
    ImageManager::getSingleton()->Render("playBg", hdc);

    for (int i = 0; i < BOARD_ROW; ++i)
    {
        for (int j = 0; j < BOARD_COL; ++j)
        {
            ImageManager::getSingleton()->findImage(_vvTile[i][j].getStrKey())->
                Render(hdc, BOARD_STARTX + (BOARD_RECTSIZE * j), BOARD_STARTY + (BOARD_RECTSIZE * i));
        }
    }

    GameObjectManager::getSingleton()->renderObj(hdc);
    TimeManager::getSingleton()->Render(hdc);
    GameObjectManager::getSingleton()->debug(hdc);
}

void PlayScene::handleArgs(vector<int> args)
{
}

void PlayScene::changeBombArr(int row, int col, BombOnTyleTag condition)
{
	bombArr[row][col] = condition;
}