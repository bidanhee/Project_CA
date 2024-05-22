#pragma once
#include "gameObject.h"
#include "Wave.h"

enum {
    LEFT, RIGHT, UP, DOWN
};
class WaveController : public GameObject
{
    WaveControllerStateTag _state;
    MapSpace _mapSpace;
    POINT_FLOAT _start;

    int _currentWaveIndex;
    float _coolDown;

    const int _SIZE;
    const int _MAKE_COOLTIME;
    const int _POWER;

    bool _isClogged[4];
public:
    WaveController(MapSpace mapSpace, int power);
    ~WaveController();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

    bool checkBlockCollision(Wave*);

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