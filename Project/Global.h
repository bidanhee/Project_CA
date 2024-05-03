#pragma once

// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 추가 헤더
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cassert>
#include <map>
#include <string>
#include <functional>

using namespace std;

// 윈도우 설정
#define WINNAME (LPCWSTR)(TEXT("22311010_송은찬"))
#define WINSTARTX    200
#define WINSTARTY    30
#define WINSIZEX     1040 
#define WINSIZEY     780
#define WINSTYLE WS_CAPTION | WS_SYSMENU

// 색상
#define MAGENTA      RGB(255, 0, 255)
#define BLACK        RGB(0, 0, 0)
#define WHITE        RGB(255, 255, 255)

// SAFE DELETE
#define SAFE_DELETE(p)          {if(p)  {delete   (p);   (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)    {if(p)  {delete[] (p);   (p)=NULL;}}
#define SAFE_RELEASE(p)         {if(p)  {(p)->Release(); (p)=NULL;}}

static POINT ptMouse = { 0, 0 };

static HINSTANCE testInstance;

template < typename T1, typename T2, typename T3, typename T4>
inline RECT makeRect(T1 x, T2 y, T3 width, T4 height)
{
    RECT rc = { static_cast<int>(x), static_cast<int>(y),
        static_cast<int>(x + width), static_cast<int>(y + height) };
    return rc;
}

inline LPCWSTR CharToLPCWSTR(const char* text)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
    wchar_t* wideText = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, text, -1, wideText, size);
    return (LPCWSTR)wideText;
}


enum class GameObjectTag
{
    Not,
    Player,
    Bomb,
    DesignElement,
    Wave,
    WaveStartingPoint,
    Item
};


enum class PlayerTypeTag
{
    Player1,
    Player2,
    SoloPlayer
};

enum class PlayerStateTag
{
    Not,
    Ready,
    Wait,
    Up,
    Down,
    Left,
    Right,
    Trap,
    Die,
    Live,
    Jump
};

struct Text
{
    Text(int size, int x, int y, string str, COLORREF textColor = RGB(0, 0, 0), string font = "다음_Regular")
        : _size(size)
        , _x(x)
        , _y(y)
        , _str(str)
        , _font(font)
        , _textColor(textColor)
    {}

    void operator()(HDC hdc)
    {
        HFONT font, oldFont;
        font = CreateFont(_size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, CharToLPCWSTR(_font.c_str()));
        oldFont = (HFONT)SelectObject(hdc, font);
        SetBkMode(hdc, TRANSPARENT); 
        SetTextColor(hdc, _textColor);
        TextOut(hdc, _x, _y, CharToLPCWSTR(_str.c_str()), static_cast<int>(_str.size()));
        SelectObject(hdc, oldFont);
        DeleteObject(font);
    }

    int _size;
    int _x;
    int _y;
    string _str;
    string _font;
    COLORREF _textColor;
};

struct POINT_FLOAT
{
    POINT_FLOAT()
        : x(0.f)
        , y(0.f)
    {
    }
    POINT_FLOAT(float px, float py)
    {
        x = px;
        y = py;
    }
    float x;
    float y;
};