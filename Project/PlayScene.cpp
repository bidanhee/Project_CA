#include "playScene.h"
BombOnTyleTag PlayScene::bombArr[BOARD_ROW][BOARD_COL] = {};

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
{

}

void PlayScene::Init()
{
}

void PlayScene::Release()
{
}

void PlayScene::Update()
{
}

void PlayScene::Render(HDC hdc)
{
}

void PlayScene::handleArgs(vector<int> args)
{
}

void PlayScene::changeBombArr(int row, int col, BombOnTyleTag condition)
{
	bombArr[row][col] = condition;
}