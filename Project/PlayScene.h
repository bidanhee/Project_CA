#pragma once
#include "Scene.h"

class PlayScene : public Scene
{
private:


public:
    PlayScene();
    ~PlayScene();

    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
    virtual void handleArgs(vector<int> args) override;

    static bool _isGameOver;
    static BombOnTyleTag bombArr[BOARD_ROW][BOARD_COL];
    static void changeBombArr(int row, int col, BombOnTyleTag condition);

    static bool getIsGameOver() { return _isGameOver; }
    static void setIsGameOver(bool state) { _isGameOver = state; }
};
