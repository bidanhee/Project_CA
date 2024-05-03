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

    //�¾�
    HRESULT Init();
    //����
    void Release();

    //Ű ������ �����ؼ� �ʱ�ȭ
    Image* addImage(string strKey, int width, int height);
    Image* addImage(string strKey, const DWORD resID, int width, int height, bool isTrans, COLORREF transColor);
    Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor);
    Image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = MAGENTA);

    Image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor);
    Image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor);


    // �̹��� ã�� �Լ�
    Image* findImage(string strKey);

    // �̹����� �����
    BOOL deleteImage(string strKey);

    // ��ü �̹��� �����
    BOOL deleteAll();

    //�����Լ� �߰�
    void Render(string strKey, HDC hdc);
    void Render(string strKey, HDC hdc, int destX, int destY);
    void Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

    //���ĺ���
    void alphaRender(string strKey, HDC hdc, BYTE alpha);
    void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
    void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

    //������ ����
    void frameRender(string strKey, HDC hdc, int destX, int destY);
    void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

    //���� ����
    void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

    //������Ʈ �ʿ� �̹����� �߰��Լ�
    void addImageForForestMap();
};