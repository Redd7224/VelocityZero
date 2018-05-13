#include "levelGenerator.h"

LevelGenerator::LevelGenerator() {}
LevelGenerator::~LevelGenerator() {}
std::vector<int> LevelGenerator::Generate(int seed) {
	std::vector<int> result(maxSize * maxSize);
	for (size_t i = 0; i < maxSize; i++)
	{
		for (size_t j = 0; j < maxSize; j++)
		{
			result[i * maxSize + j] = 0;
		}
	}
	return result;
}
