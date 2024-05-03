#include "TimeManager.h"
TimeManager::TimeManager()
    : _timer(NULL)
{
}

TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init()
{
    _timer = new Timer;
    _timer->Init();
    return S_OK;
}

void TimeManager::Release()
{
    if (_timer != NULL)
    {
        SAFE_DELETE(_timer);
    }
}

void TimeManager::Update(float lock)
{
    if (_timer != NULL)
        _timer->tick(lock);
}

void TimeManager::Render(HDC hdc)
{
    string strFrame;

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, WHITE);

#ifdef _DEBUG
    {
        if (_timer != NULL)
        {

            Text(12, 30, 60, "FPS: " + to_string(_timer->getFrameRate()))(hdc);
            Text(12, 670, 690, "WorldTime: " + to_string(_timer->getWorldTime()))(hdc);
            Text(12, 670, 710, "ElapsedTime: " + to_string(_timer->getElapsedTime()))(hdc);

        }
    }
#else
    {
        if (_timer != NULL)
        {
            Text(12, 920, 10, "FramePerSec: " + to_string(_timer->getFrameRate()), WHITE)(hdc);
        }
    }
#endif
}