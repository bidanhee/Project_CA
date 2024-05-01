#include "winFroc.h"

WinFroc::WinFroc()
{
}

WinFroc::~WinFroc()
{
}

HRESULT WinFroc::Init()
{
    _hdc = GetDC(m_hWnd);
    _managerInit = false;

    return S_OK;
}

HRESULT WinFroc::Init(bool managerInit)
{
    _hdc = GetDC(m_hWnd);
    _managerInit = managerInit;
    if (_managerInit)
    {
        ImageManager::getSingleton()->InitHandle(m_hInstance, m_hWnd);
        ImageManager::getSingleton()->Init();
        TimeManager::getSingleton()->Init();
        KeyManager::getSingleton()->Init();
    }
    return S_OK;
}

void WinFroc::Release()
{
    if (_managerInit)
    {
        ImageManager::getSingleton()->Release();
        TimeManager::getSingleton()->Release();
        KeyManager::getSingleton()->Release();
    }

    ReleaseDC(m_hWnd, _hdc);
}

void WinFroc::Update()
{
    InvalidateRect(m_hWnd, NULL, false);
}

void WinFroc::Render()
{
}

LRESULT WinFroc::MainProc(HWND _hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_MOUSEMOVE:
        ptMouse.x = LOWORD(lParam);
        ptMouse.y = HIWORD(lParam);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return (DefWindowProc(_hwnd, iMessage, wParam, lParam));
}