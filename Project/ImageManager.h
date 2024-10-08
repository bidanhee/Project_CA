#pragma once
#include "Singleton.h"
#include "Image.h"

class ImageManager : public Singleton<ImageManager>
{
private:
    map<string, Image*> m_ImageList;
    HINSTANCE m_hInstance;
    HWND m_hWnd;
public :
    void InitHandle(HINSTANCE instance, HWND wnd) { m_hInstance = instance; m_hWnd = wnd; }
public:
    ImageManager();
    ~ImageManager();

    //셋업
    HRESULT Init();
    //해제
    void Release();

    //키 값으로 설정해서 초기화
    Image* addImage(string strKey, int width, int height);
    Image* addImage(string strKey, const DWORD resID, int width, int height, bool isTrans, COLORREF transColor);
    Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor);
    Image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = MAGENTA);

    Image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor);
    Image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor);


    // 이미지 찾기 함수
    Image* findImage(string strKey);

    // 이미지를 지운다
    BOOL deleteImage(string strKey);

    // 전체 이미지 지운다
    BOOL deleteAll();

    //렌더함수 추가
    void Render(string strKey, HDC hdc);
    void Render(string strKey, HDC hdc, int destX, int destY);
    void Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

    //알파블렌드
    void alphaRender(string strKey, HDC hdc, BYTE alpha);
    void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    //프레임 렌더
    void frameRender(string strKey, HDC hdc, int destX, int destY);
    void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    //루프 랜더
    void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

    //포레스트 맵용 이미지들 추가함수
    void addImageForForestMap();
};