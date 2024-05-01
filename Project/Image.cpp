#include "Image.h"
#pragma comment(lib, "msimg32.lib")

Image::Image(HINSTANCE instance, HWND wnd)
    : m_imageInfo(nullptr)
    , m_fileName(nullptr)
    , m_isTrans(NULL)
    , m_transColor(BLACK)
    , m_blendImage(nullptr)
{
    InitHandle(instance, wnd);
}

Image::~Image()
{
}

HRESULT Image::Init(int width, int height)
{
    if (m_imageInfo != nullptr) Release();

    HDC hdc = GetDC(m_hWnd);

    m_imageInfo = new IMAGE_INFO;
    m_imageInfo->loadType = LOAD_EMPTY;
    m_imageInfo->resID = 0;
    m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
    m_imageInfo->width = width;
    m_imageInfo->height = height;


    m_fileName = nullptr;

    m_blendFunc.BlendFlags = 0;
    m_blendFunc.AlphaFormat = 0;
    m_blendFunc.BlendOp = AC_SRC_OVER;

    m_blendImage = new IMAGE_INFO;
    m_blendImage->loadType = LOAD_EMPTY;
    m_blendImage->resID = 0;
    m_blendImage->hMemDC = CreateCompatibleDC(hdc);
    m_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
    m_blendImage->width = WINSIZEX;
    m_blendImage->height = WINSIZEY;

    m_isTrans = false;
    m_transColor = BLACK;

    ReleaseDC(m_hWnd, hdc);

    if (m_imageInfo->hBit == 0)
    {
        Release();
        return E_FAIL;
    }
    return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
    if (m_imageInfo != nullptr) Release();

    HDC hdc = GetDC(m_hWnd);

    m_imageInfo = new IMAGE_INFO;
    m_imageInfo->loadType = LOAD_RESOURCE;
    m_imageInfo->resID = resID;
    m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_imageInfo->hBit = (HBITMAP)LoadBitmap(m_hInstance, MAKEINTRESOURCE(m_imageInfo->resID)); 
    m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
    m_imageInfo->width = width;
    m_imageInfo->height = height;

    m_fileName = nullptr;

    m_blendFunc.BlendFlags = 0;
    m_blendFunc.AlphaFormat = 0;
    m_blendFunc.BlendOp = AC_SRC_OVER;

    m_blendImage = new IMAGE_INFO;
    m_blendImage->loadType = LOAD_EMPTY;
    m_blendImage->resID = 0;
    m_blendImage->hMemDC = CreateCompatibleDC(hdc);
    m_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
    m_blendImage->width = WINSIZEX;
    m_blendImage->height = WINSIZEY;

    m_isTrans = isTrans;
    m_transColor = transColor;

    ReleaseDC(m_hWnd, hdc);

    if (m_imageInfo->hBit == 0)
    {
        Release();
        return E_FAIL;
    }
    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{

    if (fileName == nullptr) return E_FAIL;

    if (m_imageInfo != nullptr) Release();

    HDC hdc = GetDC(m_hWnd);

    LPCWSTR fileStr = CharToLPCWSTR(fileName);

    m_imageInfo = new IMAGE_INFO;
    m_imageInfo->loadType = LOAD_FILE;
    m_imageInfo->resID = 0;
    m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileStr, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
    m_imageInfo->width = width;
    m_imageInfo->height = height;

    size_t len = strlen(fileName);
    m_fileName = new char[len + 1];
    strcpy_s(m_fileName, len + 1, fileName);

    m_blendFunc.BlendFlags = 0;
    m_blendFunc.AlphaFormat = 0;
    m_blendFunc.BlendOp = AC_SRC_OVER;

    m_blendImage = new IMAGE_INFO;
    m_blendImage->loadType = LOAD_EMPTY;
    m_blendImage->resID = 0;
    m_blendImage->hMemDC = CreateCompatibleDC(hdc);
    m_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
    m_blendImage->width = WINSIZEX;
    m_blendImage->height = WINSIZEY;

    m_isTrans = isTrans;
    m_transColor = transColor;

    ReleaseDC(m_hWnd, hdc); // DC해제

    if (m_imageInfo->hBit == 0)
    {

        Release();
        return E_FAIL;
    }
    return S_OK;
}

// 이미지 + 프레임 파일 초기화
HRESULT Image::Init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
    if (fileName == nullptr) return E_FAIL;

    if (m_imageInfo != nullptr) Release();

    HDC hdc = GetDC(m_hWnd);
    LPCWSTR fileStr = CharToLPCWSTR(fileName);

    m_imageInfo = new IMAGE_INFO;
    m_imageInfo->loadType = LOAD_FILE;
    m_imageInfo->resID = 0;
    m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileStr, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
    m_imageInfo->width = width;
    m_imageInfo->height = height;
    m_imageInfo->maxFrameX = frameX - 1;
    m_imageInfo->maxFrameY = frameY - 1;
    m_imageInfo->frameWidth = width / frameX;
    m_imageInfo->frameHeight = height / frameY;

    // 파일 이름
    size_t len = strlen(fileName);
    m_fileName = new char[len + 1];
    strcpy_s(m_fileName, len + 1, fileName);

    //알파 블렌드 옵션 설정
    m_blendFunc.BlendFlags = 0;
    m_blendFunc.AlphaFormat = 0;
    m_blendFunc.BlendOp = AC_SRC_OVER;

    //알파 블렌드 사용을 위한 이미지 설정
    m_blendImage = new IMAGE_INFO;
    m_blendImage->loadType = LOAD_EMPTY;
    m_blendImage->resID = 0;
    m_blendImage->hMemDC = CreateCompatibleDC(hdc);
    m_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
    m_blendImage->width = WINSIZEX;
    m_blendImage->height = WINSIZEY;

    // 투명키 컬러 세팅
    m_isTrans = isTrans;
    m_transColor = transColor;

    ReleaseDC(m_hWnd, hdc); // DC해제

    // 리소스를 얻어오는 데 실패했을 경우
    if (m_imageInfo->hBit == 0)
    {
        Release();
        return E_FAIL;
    }
    return S_OK;
}

HRESULT Image::Init(const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
    if (fileName == nullptr) return E_FAIL;

    if (m_imageInfo != nullptr) Release();

    HDC hdc = GetDC(m_hWnd);
    LPCWSTR fileStr = CharToLPCWSTR(fileName);

    m_imageInfo = new IMAGE_INFO;
    m_imageInfo->loadType = LOAD_FILE;
    m_imageInfo->resID = 0;
    m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
    m_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileStr, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
    m_imageInfo->x = static_cast<float>(x) - (width / frameX / 2.f);
    m_imageInfo->y = static_cast<float>(y) - (height / frameY / 2.f);
    m_imageInfo->width = width;
    m_imageInfo->height = height;
    m_imageInfo->maxFrameX = frameX - 1;
    m_imageInfo->maxFrameY = frameY - 1;
    m_imageInfo->frameWidth = width / frameX;
    m_imageInfo->frameHeight = height / frameY;

    size_t len = strlen(fileName);
    m_fileName = new char[len + 1];
    strcpy_s(m_fileName, len + 1, fileName);

    m_blendFunc.BlendFlags = 0;
    m_blendFunc.AlphaFormat = 0;
    m_blendFunc.BlendOp = AC_SRC_OVER;

    m_blendImage = new IMAGE_INFO;
    m_blendImage->loadType = LOAD_EMPTY;
    m_blendImage->resID = 0;
    m_blendImage->hMemDC = CreateCompatibleDC(hdc);
    m_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
    m_blendImage->width = WINSIZEX;
    m_blendImage->height = WINSIZEY;

    m_isTrans = isTrans;
    m_transColor = transColor;

    ReleaseDC(m_hWnd, hdc);

    if (m_imageInfo->hBit == 0)
    {
        Release();
        return E_FAIL;
    }
    return S_OK;
}

void Image::setTransColor(bool isTrans, COLORREF transColor)
{
    m_isTrans = isTrans;
    m_transColor = transColor;
}

void Image::Release()
{
    if (m_imageInfo)
    {
        SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
        DeleteObject(m_imageInfo->hOBit);
        DeleteObject(m_imageInfo->hMemDC);

        SAFE_DELETE(m_imageInfo);
        SAFE_DELETE(m_fileName);

        m_isTrans = false;
        m_transColor = BLACK;
    }
}

void Image::Render(HDC hdc)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC,
            0, 0, m_imageInfo->width, m_imageInfo->height, m_transColor);
    }
    else
    {
        BitBlt(hdc, 0, 0, m_imageInfo->width,  m_imageInfo->height,  m_imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void Image::Render(HDC hdc, int destX, int destY)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX, destY, m_imageInfo->width,  m_imageInfo->height,  m_imageInfo->hMemDC,
            0, 0, m_imageInfo->width,  m_imageInfo->height, m_transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC, 0, 0, SRCCOPY);
    }
}

void Image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX, destY, sourWidth, sourHeight, m_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, m_transColor);
    }
}

void Image::renderStretch(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
    StretchBlt(hdc, destX, destY, destWidth, destHeight, m_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, SRCCOPY);
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
    m_blendFunc.SourceConstantAlpha = alpha;

    if (m_isTrans)
    {
        BitBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, hdc, 0, 0, SRCCOPY);

        GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height,
            m_imageInfo->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_transColor);

        AlphaBlend(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
            m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
    }
    else
    {
        AlphaBlend(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
            m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
    }
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    m_blendFunc.SourceConstantAlpha = alpha;
    if (m_isTrans)
    {
        BitBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, hdc, destX, destY, SRCCOPY);

        GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height,
            m_imageInfo->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_transColor);

        AlphaBlend(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height,
            m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height,
            m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
    }
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    m_blendFunc.SourceConstantAlpha = alpha;
    if (m_isTrans)
    {
        BitBlt(m_blendImage->hMemDC, destX, destY, m_imageInfo->width, m_imageInfo->height, hdc, sourX, sourY, SRCCOPY);

        GdiTransparentBlt(m_blendImage->hMemDC, destX, destY, sourWidth, sourHeight,
            m_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, m_transColor);

        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
            m_blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight, m_blendFunc);
    }
    else
    {
        AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
            m_blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight, m_blendFunc);
    }

}

void Image::frameRender(HDC hdc, int destX, int destY)
{
    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX, destY,
            m_imageInfo->frameWidth,
            m_imageInfo->frameHeight,
            m_imageInfo->hMemDC, 
            m_imageInfo->currentFrameX * m_imageInfo->frameWidth, 
            m_imageInfo->currentFrameY * m_imageInfo->frameHeight, 
            m_imageInfo->frameWidth, 
            m_imageInfo->frameHeight, 
            m_transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY, 
            m_imageInfo->frameWidth,
            m_imageInfo->frameHeight,
            m_imageInfo->hMemDC,
            m_imageInfo->currentFrameX * m_imageInfo->frameWidth,
            m_imageInfo->currentFrameY * m_imageInfo->frameHeight,
            SRCCOPY);
    }
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    m_imageInfo->currentFrameX = currentFrameX;
    m_imageInfo->currentFrameY = currentFrameY;

    if (currentFrameX > m_imageInfo->maxFrameX)
    {
        m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
    }
    if (currentFrameY > m_imageInfo->maxFrameY)
    {
        m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
    }

    if (m_isTrans)
    {
        GdiTransparentBlt(hdc, destX,  destY,
            m_imageInfo->frameWidth,
            m_imageInfo->frameHeight,
            m_imageInfo->hMemDC,	
            m_imageInfo->currentFrameX * m_imageInfo->frameWidth,
            m_imageInfo->currentFrameY * m_imageInfo->frameHeight, 
            m_imageInfo->frameWidth,
            m_imageInfo->frameHeight, 
            m_transColor);
    }
    else
    {
        BitBlt(hdc, destX, destY,
            m_imageInfo->frameWidth,
            m_imageInfo->frameHeight,
            m_imageInfo->hMemDC,
            m_imageInfo->currentFrameX * m_imageInfo->frameWidth,
            m_imageInfo->currentFrameY * m_imageInfo->frameHeight,
            SRCCOPY);
    }
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
    if (offsetX < 0) offsetX = m_imageInfo->width + (offsetX % m_imageInfo->width);
    if (offsetY < 0) offsetY = m_imageInfo->height + (offsetY % m_imageInfo->height);

    RECT rcSour;
    int sourWidth;
    int sourHeight;

    RECT rcDest;

    int drawAreaX = drawArea->left;
    int drawAreaY = drawArea->top;
    int drawAreaW = drawArea->right - drawArea->left;
    int drawAreaH = drawArea->bottom - drawArea->top;

    for (int y = 0; y < drawAreaH; y += sourHeight)
    {
        rcSour.top = (y + offsetY) % m_imageInfo->height;
        rcSour.bottom = m_imageInfo->height;
        sourHeight = rcSour.bottom - rcSour.top;

        if (y + sourHeight > drawAreaH)
        {
            rcSour.bottom -= (y + sourHeight) - drawAreaH;
            sourHeight = rcSour.bottom - rcSour.top;
        }

        rcDest.top = y + drawAreaY;
        rcDest.bottom = rcDest.top + sourHeight;

        for (int x = 0; x < drawAreaW; x += sourWidth)
        {
            rcSour.left = (x + offsetX % m_imageInfo->width);
            rcSour.right = m_imageInfo->width;
            sourWidth = rcSour.right - rcSour.left;

            if (x + sourWidth > drawAreaW)
            {
                rcSour.right -= (x + sourWidth) - drawAreaW;
                sourWidth = rcSour.right - rcSour.left;
            }

            rcDest.left = x + drawAreaX;
            rcDest.right = rcDest.left + sourWidth;

            Render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
        }

    }
}