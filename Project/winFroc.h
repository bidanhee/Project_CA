#pragma once
#include "Image.h"
#include "Global.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

static Image* _backbuffer = ImageManager::getSingleton()->addImage("backBuffer", WINSIZEX, WINSIZEY);

class WinFroc
{
private:
    HDC _hdc;
    bool _managerInit;

    HINSTANCE m_hInstance;
    HWND m_hWnd;
public:
    void InitHandle(HINSTANCE instance, HWND wnd) { m_hInstance = instance; m_hWnd = wnd; }

public:

    WinFroc();
    virtual ~WinFroc();

    virtual HRESULT Init();
    virtual HRESULT Init(bool managerInit);
    virtual void Release();
    virtual void Update();
    virtual void Render();

    Image* getBackBuffer() { return _backbuffer; }

    HDC getMemDC() { return _backbuffer->getMemDC(); }
    HDC getHDC() { return _hdc; }

    LRESULT MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

