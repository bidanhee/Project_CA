#pragma once
#include "gameObject.h"

class Wave : public GameObject
{
private:
    WaveStateTag _state;
    MapSpace _mapSpace;
    POINT_FLOAT _start;

    float _startTime;

    const int _SIZE;
    const float _WAVE_COOLTIME;
    const int _POWER;

public:
    Wave(int row, int col, WaveStateTag state, int power);
    ~Wave();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

};