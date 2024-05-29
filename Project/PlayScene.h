#pragma once
#include "Scene.h"
class PlayScene : public Scene
{

public:
    PlayScene();
    ~PlayScene();

    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
    virtual void handleArgs(vector<int> args) override;

    static BombOnTyleTag bombArr[BOARD_ROW][BOARD_COL];
    static void changeBombArr(int row, int col, BombOnTyleTag condition);

};
