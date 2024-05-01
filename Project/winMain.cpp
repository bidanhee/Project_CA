#include "Global.h"
#include "cGame.h"
#include "TimeManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height, HWND _hWnd);
cGame* game;

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmParam, int cmdShow)
{
    MSG message; //윈도우 메세지
    WNDCLASS wndClass; //윈도우 클래스(정보)
    HINSTANCE hInstance;
    HWND hWnd;
    hInstance = _hInstance;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = WndProc;
    wndClass.lpszClassName = WINNAME;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);
    hWnd = CreateWindow
    (WINNAME, WINNAME, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        WINSTARTX, WINSTARTY,
        WINSIZEX, WINSIZEY,
        NULL, (HMENU)NULL, hInstance, NULL);

    //윈도우 창 크기 설정
    setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY, hWnd);
    //윈도우 창 띄어라
    ShowWindow(hWnd, cmdShow);

    testInstance = hInstance;
    game = new cGame(hInstance, hWnd);

    if (FAILED(game->Init()))
    {
        return 0;
    }

    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) break;
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            TimeManager::getSingleton()->Update(100.f);
            game->Update();
            game->Render();
        }
    }
    game->Release();

    UnregisterClass(WINNAME, hInstance);
    return message.wParam;
}

LRESULT CALLBACK WndProc(HWND _hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return game->MainProc(_hwnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height, HWND _hWnd)
{
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = width;
    rc.bottom = height;

    AdjustWindowRect(&rc, WINSTYLE, false);
    SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}