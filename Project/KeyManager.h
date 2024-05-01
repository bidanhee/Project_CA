#pragma once
#include "Global.h"
#include <bitset>
#include "Singleton.h"

#define KEYMAX 256

class KeyManager : public Singleton<KeyManager>
{
private:
    bitset<KEYMAX> m_keyUp;
    bitset<KEYMAX> m_keyDown;
public:
    KeyManager();
    ~KeyManager();

    HRESULT Init();
    void Release();

    bool isOnceKeyDown(int key);
    bool isOnceKeyUp(int key);
    bool isStayKeyDown(int key);
    bool isToggleKey(int key);
};