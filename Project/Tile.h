#pragma once
#include "Global.h"

class Tile
{
private:
    string _strKey;
public:
    Tile() : _strKey(string())
    {
    }
    Tile(string strKey) : _strKey(strKey)
    {
    }
    ~Tile(){}

    string getStrKey()
    {
        return _strKey;
    }
};