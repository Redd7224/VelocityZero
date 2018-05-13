#pragma once
#include <vector>


class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();
	std::vector<int> Generate(int seed);
private:
	const int maxSize = 512;
};
