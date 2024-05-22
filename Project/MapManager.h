#pragma once
#include "Global.h"
#include "Tile.h"

class MapManager
{
public:
	static vector<vector<Tile>> makeMap(int);
};