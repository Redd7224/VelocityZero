#pragma once
#include <array>
#include <vector>
#include "tileInfo.h"

struct ChunkData {
	//TODO maybe make this a Vector2, XMFLAOT2 position
	int x;
	int y;
	//TODO maybe this should [][]. So we can get specific tiles easily for a loaction? Example for collission
	//std::vector<std::vector<TileInfo>> tiles;
	//std::array<std::array<TileInfo, 32>, 32> levelTiles;
	//TileInfo levelTiles[32][32];
	std::vector<TileInfo> tiles;
	ChunkData() {
		tiles.resize(16 * 16);
	}
};