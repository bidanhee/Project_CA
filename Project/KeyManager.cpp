#include "KeyManager.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

HRESULT KeyManager::Init()
{
    for (int i = 0; i < KEYMAX; ++i)
    {
        m_keyUp.set(i, false);
        m_keyDown.set(i, false);
    }
    return S_OK;
}

void KeyManager::Release()
{
}

bool KeyManager::isOnceKeyDown(int key)
{

    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (!m_keyDown[key])
        {
            m_keyDown.set(key, true);
            return true;
        }
    }
    else
    {
        m_keyDown.set(key, false);
    }

    return false;
}

bool KeyManager::isOnceKeyUp(int key)
{

    if (GetAsyncKeyState(key) & 0x8000)
    {
        m_keyUp.set(key, true);
    }
    else
    {
        if (m_keyUp[key])
        {
            m_keyUp.set(key, false);
            return false;
        }
    }
    return false;
}

bool KeyManager::isStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)return true;
    return false;
}

bool KeyManager::isToggleKey(int key)
{
    if (GetKeyState(key) & 0x0001)return true;
    return false;
}