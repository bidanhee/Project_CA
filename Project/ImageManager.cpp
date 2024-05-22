#include "ImageManager.h"

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

HRESULT ImageManager::Init()
{
    addImage("playBg", "assets/play_bg.bmp", WINSIZEX, WINSIZEY, true, MAGENTA);
    addImage("blackBg", "assets/black_bg.bmp", WINSIZEX, WINSIZEY);
    addImage("lobbySceneBg", "assets/lobby_scene_bg.bmp", WINSIZEX, WINSIZEY);
    addImage("loginSceneBg", "assets/login_scene_bg.bmp", WINSIZEX, WINSIZEY);
    addImage("modeSelectSceneBg", "assets/mode_select_scene_bg.bmp", WINSIZEX, WINSIZEY);

    addImage("START", "assets/game_start/START.bmp", 477, 77, true, MAGENTA);
    addImage("GAME", "assets/game_start/GAME.bmp", 244, 54, true, MAGENTA);

    addImage("GAME_GRAY", "assets/game_over/GAME.bmp", 351, 78, true, MAGENTA);
    addImage("OVER", "assets/game_over/OVER.bmp", 443, 81, true, MAGENTA);

    addFrameImage("playerBazziUp", "assets/player/bazzi/up.bmp", 512, 76, 8, 1, true, MAGENTA);
    addFrameImage("playerBazziDown", "assets/player/bazzi/down.bmp", 512, 76, 8, 1, true, MAGENTA);
    addFrameImage("playerBazziLeft", "assets/player/bazzi/left.bmp", 384, 76, 6, 1, true, MAGENTA);
    addFrameImage("playerBazziRight", "assets/player/bazzi/right.bmp", 384, 76, 6, 1, true, MAGENTA);
    addFrameImage("playerBazziWait", "assets/player/bazzi/wait.bmp", 192, 76, 3, 1, true, MAGENTA);
    addFrameImage("playerBazziReady", "assets/player/bazzi/ready.bmp", 1152, 86, 18, 1, true, MAGENTA);
    addFrameImage("playerBazziFlashLong", "assets/player/bazzi/flash_long.bmp", 256, 76, 4, 1, true, MAGENTA);
    addFrameImage("playerBazziTrap", "assets/player/bazzi/trap.bmp", 1144, 144, 13, 1, true, MAGENTA);
    addFrameImage("playerBazziDie", "assets/player/bazzi/die.bmp", 1144, 144, 13, 1, true, MAGENTA);
    addFrameImage("playerBazziLive", "assets/player/bazzi/live.bmp", 440, 144, 5, 1, true, MAGENTA);
    addFrameImage("playerBazziJump", "assets/player/bazzi/jump.bmp", 512, 80, 8, 1, true, MAGENTA);

    addImage("playerShadow", "assets/player/shadow.bmp", 42, 19, true, MAGENTA);

    addImage("player1", "assets/player/player1.bmp", 24, 28, true, MAGENTA);
    addImage("player2", "assets/player/player2.bmp", 24, 28, true, MAGENTA);
    addImage("soloPlayer", "assets/player/solo_player.bmp", 24, 28, true, MAGENTA);

    addImageForForestMap();

    addFrameImage("bomb1", "assets/bomb/1.bmp", 224, 54, 4, 1, true, MAGENTA);
    addFrameImage("bombPop", "assets/bomb/pop.bmp", 312, 52, 6, 1, true, MAGENTA);

    addFrameImage("waveLeft1", "assets/wave/left1.bmp", 572, 52, 11, 1, true, MAGENTA);
    addFrameImage("waveLeft2", "assets/wave/left2.bmp", 572, 52, 11, 1, true, MAGENTA);
    addFrameImage("waveRight1", "assets/wave/right1.bmp", 572, 52, 11, 1, true, MAGENTA);
    addFrameImage("waveRight2", "assets/wave/right2.bmp", 572, 52, 11, 1, true, MAGENTA);
    addFrameImage("waveUp1", "assets/wave/up1.bmp", 572, 52, 11, 1, true, MAGENTA);
    addFrameImage("waveUp2", "assets/wave/up2.bmp", 572, 52, 11, 1, true, MAGENTA);
    addFrameImage("waveDown1", "assets/wave/down1.bmp", 572, 52, 11, 1, true, MAGENTA);
    addFrameImage("waveDown2", "assets/wave/down2.bmp", 572, 52, 11, 1, true, MAGENTA);

    addFrameImage("itemBallon", "assets/item/ballon.bmp", 112, 70, 2, 1, true, MAGENTA);
    addFrameImage("itemPotion", "assets/item/potion.bmp", 112, 70, 2, 1, true, MAGENTA);
    addFrameImage("itemPotionMax", "assets/item/potion_make_power_max.bmp", 112, 70, 2, 1, true, MAGENTA);
    addFrameImage("itemSkate", "assets/item/skate.bmp", 112, 70, 2, 1, true, MAGENTA);
    
    addFrameImage("forestBlock1", "assets/map/forest/block/block_1.bmp", 68, 68, 1, 1, true, MAGENTA);
    addFrameImage("block1Pop", "assets/map/forest/block/block_1_pop.bmp", 340, 68, 5, 1, true, MAGENTA);
    addFrameImage("forestBlock2", "assets/map/forest/block/block_2.bmp", 172, 135, 3, 2, true, MAGENTA);
    addFrameImage("forestBlock3", "assets/map/forest/block/block_3.bmp", 172, 135, 3, 2, true, MAGENTA);
    addFrameImage("forestBlock4", "assets/map/forest/block/block_4.bmp", 172, 140, 3, 2, true, MAGENTA);
    addFrameImage("forestBlock5", "assets/map/forest/block/block_5.bmp", 172, 140, 3, 2, true, MAGENTA);
    addFrameImage("forestBlock6", "assets/map/forest/block/block_6.bmp", 195, 138, 3, 2, true, MAGENTA);
    addFrameImage("forestBlock7", "assets/map/forest/block/block_7.bmp", 195, 138, 3, 2, true, MAGENTA);
    addFrameImage("forestBlock8", "assets/map/forest/block/block_8.bmp", 325, 87, 5, 1, true, MAGENTA);
    addFrameImage("forestBlock9", "assets/map/forest/block/block_9.bmp", 325, 87, 5, 1, true, MAGENTA);

    addImage("forestObject1", "assets/map/forest/object/object_1.bmp", 55, 69, true, MAGENTA);
    addImage("forestObject2", "assets/map/forest/object/object_2.bmp", 55, 69, true, MAGENTA);
    addImage("forestObject3", "assets/map/forest/object/object_3.bmp", 55, 69, true, MAGENTA);
    addImage("forestObject4", "assets/map/forest/object/object_4.bmp", 61, 170, true, MAGENTA);
    addImage("forestObject5", "assets/map/forest/object/object_5.bmp", 57, 155, true, MAGENTA);
    addImage("forestObject6", "assets/map/forest/object/object_6.bmp", 213, 161, true, MAGENTA);

    addImage("forestTile1", "assets/map/forest/tile/tile_1.bmp", 52, 52);
    addImage("forestTile2", "assets/map/forest/tile/tile_2.bmp", 52, 52);
    addImage("forestTile3", "assets/map/forest/tile/tile_3.bmp", 52, 52);
    addImage("forestTile4", "assets/map/forest/tile/tile_4.bmp", 52, 52);
    addImage("forestTile5", "assets/map/forest/tile/tile_5.bmp", 52, 52);
    addImage("forestTile6", "assets/map/forest/tile/tile_6.bmp", 52, 52);
    addImage("forestTile7", "assets/map/forest/tile/tile_7.bmp", 52, 52);
    addImage("forestTile8", "assets/map/forest/tile/tile_8.bmp", 52, 52);
    addImage("forestTile9", "assets/map/forest/tile/tile_9.bmp", 52, 52);
    addImage("forestTile10", "assets/map/forest/tile/tile_10.bmp", 52, 52);

    return S_OK;
}

void ImageManager::Release()
{
    deleteAll();
}

Image* ImageManager::addImage(string strKey, int width, int height)
{
    Image* img = findImage(strKey);
    if (img) return img;

    img = new Image(m_hInstance, m_hWnd);

    if (FAILED(img->Init(width, height)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    m_ImageList.insert(make_pair(strKey, img));

    return img;
}

Image* ImageManager::addImage(string strKey, const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
    Image* img = findImage(strKey);
    if (img) return img; 

    img = new Image(m_hInstance, m_hWnd);
    if (FAILED(img->Init(resID, width, height, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    m_ImageList.insert(make_pair(strKey, img));

    return img;
}

Image* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
    Image* img = findImage(strKey);
    if (img) return img; 

    img = new Image(m_hInstance, m_hWnd);

    if (FAILED(img->Init(fileName, x, y, width, height, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }
    
    m_ImageList.insert(make_pair(strKey, img));

    return img;
}

Image* ImageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{

    Image* img = findImage(strKey);
    if (img) return img;

    img = new Image(m_hInstance, m_hWnd);

    if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }
    m_ImageList.insert(make_pair(strKey, img));

    return img;
}

Image* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
    Image* img = findImage(strKey);
    if (img) return img;

    img = new Image(m_hInstance, m_hWnd);

    if (FAILED(img->Init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }

    m_ImageList.insert(make_pair(strKey, img));

    return img;
}

Image* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
    Image* img = findImage(strKey);
    if (img) return img; 

    img = new Image(m_hInstance, m_hWnd);

    if (FAILED(img->Init(fileName, width, height, frameX, frameY, isTrans, transColor)))
    {
        SAFE_DELETE(img);
        return nullptr;
    }
    m_ImageList.insert(make_pair(strKey, img));

    return img;
}

Image* ImageManager::findImage(string strKey)
{
    auto key = m_ImageList.find(strKey);
    if (key != m_ImageList.end()) 
    {
        return key->second;
    }
    return nullptr;
}

BOOL ImageManager::deleteImage(string strKey)
{
    auto key = m_ImageList.find(strKey);
    if (key != m_ImageList.end())
    {
        key->second->Release();

        //메모리 해제
        SAFE_DELETE(key->second);
        m_ImageList.erase(key);
        return true;
    }
    return false;
}

BOOL ImageManager::deleteAll()
{
    auto it = m_ImageList.begin();
    for (; it != m_ImageList.end(); )
    {
        if (it->second != NULL)
        {
            SAFE_DELETE(it->second);
            it = m_ImageList.erase(it);
        }
        else
        {
            ++it;
        }
    }
    m_ImageList.clear();
    return true;
}

void ImageManager::Render(string strKey, HDC hdc)
{
    Image* img = findImage(strKey);
    if (img) img->Render(hdc);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
    Image* img = findImage(strKey);
    if (img) img->Render(hdc, destX, destY);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    Image* img = findImage(strKey);
    if (img) img->Render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
    Image* img = findImage(strKey);
    if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
    Image* img = findImage(strKey);
    if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    Image* img = findImage(strKey);
    if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
    Image* img = findImage(strKey);
    if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    Image* img = findImage(strKey);
    if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
    Image* img = findImage(strKey);
    if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void ImageManager::addImageForForestMap()
{
    /*
    //블럭
    //addFrameImage("forestBlock1", "assets/map/forest/block/block_1.bmp", 172, 135, 3, 2, true, MAGENTA);
    //addFrameImage("forestBlock2", "assets/map/forest/block/block_2.bmp", 172, 135, 3, 2, true, MAGENTA);
    //addFrameImage("forestBlock3", "assets/map/forest/block/block_3.bmp", 172, 135, 3, 2, true, MAGENTA);
    //addFrameImage("forestBlock4", "assets/map/forest/block/block_4.bmp", 172, 140, 3, 2, true, MAGENTA);
    //addFrameImage("forestBlock5", "assets/map/forest/block/block_5.bmp", 172, 140, 3, 2, true, MAGENTA);
    //addFrameImage("forestBlock6", "assets/map/forest/block/block_6.bmp", 195, 138, 3, 2, true, MAGENTA);
    //addFrameImage("forestBlock7", "assets/map/forest/block/block_7.bmp", 195, 138, 3, 2, true, MAGENTA);
    //addFrameImage("forestBlock8", "assets/map/forest/block/block_8.bmp", 325, 87, 5, 1, true, MAGENTA);
    //addFrameImage("forestBlock9", "assets/map/forest/block/block_9.bmp", 325, 87, 5, 1, true, MAGENTA);
    //오브젝트
    addImage("forestObject1", "assets/map/forest/object/object_1.bmp", 55, 69, true, MAGENTA);
    addImage("forestObject2", "assets/map/forest/object/object_2.bmp", 55, 69, true, MAGENTA);
    addImage("forestObject3", "assets/map/forest/object/object_3.bmp", 55, 69, true, MAGENTA);
    addImage("forestObject4", "assets/map/forest/object/object_4.bmp", 61, 170, true, MAGENTA);
    addImage("forestObject5", "assets/map/forest/object/object_5.bmp", 57, 155, true, MAGENTA);
    addImage("forestObject6", "assets/map/forest/object/object_6.bmp", 213, 161, true, MAGENTA);
    //타일
    addImage("forestTile1", "assets/map/forest/tile/tile_1.bmp", 52, 52);
    addImage("forestTile2", "assets/map/forest/tile/tile_2.bmp", 52, 52);
    addImage("forestTile3", "assets/map/forest/tile/tile_3.bmp", 52, 52);
    addImage("forestTile4", "assets/map/forest/tile/tile_4.bmp", 52, 52);
    addImage("forestTile5", "assets/map/forest/tile/tile_5.bmp", 52, 52);
    addImage("forestTile6", "assets/map/forest/tile/tile_6.bmp", 52, 52);
    addImage("forestTile7", "assets/map/forest/tile/tile_7.bmp", 52, 52);
    addImage("forestTile8", "assets/map/forest/tile/tile_8.bmp", 52, 52);
    addImage("forestTile9", "assets/map/forest/tile/tile_9.bmp", 52, 52);
    addImage("forestTile10", "assets/map/forest/tile/tile_10.bmp", 52, 52);
    */
}