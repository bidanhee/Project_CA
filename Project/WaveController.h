#pragma once
#include "gameObject.h"

class WaveControllor : public GameObject
{
    WaveControllerStateTag _state;
    MapSpace _mapSpace;
    POINT_FLOAT _start;

    int _currentWaveIndex;
    float _coolDown;

    const int _SIZE;
    const int _MAKE_COOLTIME;
    const int _POWER;

public:
    WaveControllor(MapSpace mapSpace, int power);
    ~WaveControllor();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

    float getStartX() const
    {
        return _start.x;
    }
    float getStartY() const
    {
        return _start.y;
    }
    int getSize() const
    {
        return _SIZE;
    }
};