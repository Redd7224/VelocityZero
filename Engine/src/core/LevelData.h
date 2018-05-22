#pragma once
#include <vector>
#include "tileInfo.h"
struct LevelData {
	std::vector<int> rawTiles;
	std::vector<TileInfo> tiles;
	int height;
	int width;
};