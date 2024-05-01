#pragma once
#include "Global.h"

class Image
{
    enum IMAGE_LOAD_KIND
    {
        LOAD_RESOURCE, 
        LOAD_FILE,    
        LOAD_EMPTY, 
        LOAD_END
    };

    typedef struct tagImage
    {
        tagImage()
        {
            resID = 0;
            hMemDC = nullptr;
            hBit = nullptr;
            hOBit = nullptr;
            x = 0;
            y = 0;
            width = 0;
            height = 0;
            currentFrameX = 0;
            currentFrameY = 0;
            maxFrameX = 0;
            maxFrameY = 0;
            frameWidth = 0;
            frameHeight = 0;
            loadType = LOAD_RESOURCE;
        }

        DWORD resID;        // 리소스 아이디
        HDC hMemDC;         // 메모리 DC
        HBITMAP hBit;       // 비트맵(새로운 비트맵 핸들)
        HBITMAP hOBit;      // 올드 비트맵(기존 비트맵 핸들)
        float x;            // x좌표
        float y;            // y좌표
        int width;          // 이미지 가로크기
        int height;         // 이미지 세로 크기
        int currentFrameX;  // 현재 프레임 x
        int currentFrameY;  // 현재 프레임 y
        int maxFrameX;      // 최대 프레임 x
        int maxFrameY;      // 최대 프레임 y 
        int frameWidth;
        int frameHeight;

        BYTE loadType;      // 타입
    } IMAGE_INFO, * LPIMAGE_INFO;

public:
    Image(HINSTANCE, HWND);
    ~Image();

    // 빈 비트맵 초기화
    HRESULT Init(int width, int height);
    // 이미지 리소스 초기화
    HRESULT Init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = MAGENTA);
    //const char* fileName
    // 이미지 파일 초기화
    HRESULT Init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = MAGENTA);
    // 프레임 이미지 파일로 초기화
    HRESULT Init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = MAGENTA);
    HRESULT Init(const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = MAGENTA);

    void setTransColor(bool isTrans, COLORREF transColor);
    void Release();

    void Render(HDC hdc);
    void Render(HDC hdc, int destX, int destY);
    void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
    void renderStretch(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);

    void alphaRender(HDC hdc, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    void frameRender(HDC hdc, int destX, int destY);
    void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

    inline HDC getMemDC() { return m_imageInfo->hMemDC; }

    inline float getX() { return m_imageInfo->x; }
    inline void setX(float x) { m_imageInfo->x = x; }

    inline float getY() { return m_imageInfo->y; }
    inline void setY(float y) { m_imageInfo->y = y; }

    inline void setCenter(float x, float y)
    {
        m_imageInfo->x = x - (m_imageInfo->width / 2);
        m_imageInfo->y = y - (m_imageInfo->height / 2);
    }

    inline float getCenterX()
    {
        return m_imageInfo->maxFrameX <= 0 ? m_imageInfo->x + (m_imageInfo->width / 2)
            : m_imageInfo->x + (m_imageInfo->frameWidth / 2);
    }

    inline float getCenterY()
    {
        return m_imageInfo->maxFrameY <= 0 ? m_imageInfo->y + (m_imageInfo->height / 2)
            : m_imageInfo->y + (m_imageInfo->frameHeight / 2);
    }

    inline int getWidth() { return m_imageInfo->width; }
    inline int getHeight() { return m_imageInfo->height; }

    inline RECT getBoundingBox()
    {
        RECT rc;
        if (m_imageInfo->frameWidth != 0 && m_imageInfo->frameHeight != 0)
        {
            rc = makeRect(m_imageInfo->x, m_imageInfo->y, m_imageInfo->frameWidth, m_imageInfo->frameHeight);
        }
        else
        {
            rc = makeRect(m_imageInfo->x, m_imageInfo->y, m_imageInfo->width, m_imageInfo->height);
        }
        return rc;
    }

    inline int getFrameX() { return m_imageInfo->currentFrameX; }
    inline void setFrameX(int frameX)
    {
        m_imageInfo->currentFrameX = frameX;
        if (frameX > m_imageInfo->maxFrameX)
        {
            m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
        }
    }

    inline int getFrameY() { return m_imageInfo->currentFrameY; }
    inline void setFrameY(int frameY)
    {
        m_imageInfo->currentFrameY = frameY;
        if (frameY > m_imageInfo->maxFrameY)
        {
            m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
        }
    }

    inline int getFrameWidth() { return m_imageInfo->frameWidth; }
    inline int getFrameHeight() { return m_imageInfo->frameHeight; }
    inline int getMaxFrameX() { return m_imageInfo->maxFrameX; }
    inline int getMaxFrameY() { return m_imageInfo->maxFrameY; }


private:
    LPIMAGE_INFO m_imageInfo; //이미지 정보
    char* m_fileName; //이미지 경로 이름
    bool m_isTrans;  //배경색을 없앨 건지 여부 (투명 배경이냐?)
    COLORREF m_transColor; //보이지 않게할 특정 색상

    BLENDFUNCTION m_blendFunc; //알파 블렌드를 위한 정보
    LPIMAGE_INFO m_blendImage; //알파 블렌드를 사용하기 위한 이미지 정보

    HINSTANCE m_hInstance;
    HWND m_hWnd;
public:
    void InitHandle(HINSTANCE instance, HWND wnd) { m_hInstance = instance; m_hWnd = wnd; }
};