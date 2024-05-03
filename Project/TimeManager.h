#pragma once
#include "Singleton.h"
#include "Timer.h"

class TimeManager : public Singleton<TimeManager>
{
private:
    Timer* _timer;
    RECT rc;

public:
    TimeManager();
    ~TimeManager();

    HRESULT Init();
    void Release();
    void Update(float lock = 0.0f);
    void Render(HDC hdc);

    inline float getElapsedTime() const { return _timer->getElapsedTime(); }
    inline float getWorldTime() const { return _timer->getWorldTime(); }
};