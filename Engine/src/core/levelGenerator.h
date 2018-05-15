#pragma once
#include <vector>
#include <iostream> //This is just included for debug print
#include <random>
#include "LevelGeneratorRoom.h"
class LevelGenerator
{
public:
	LevelGenerator(int seed);
	~LevelGenerator();
	std::vector<int> Generate();
	void print();
	enum Tile
	{
		Unused = 0,
		Floor = 1,
		Wall = 2,
		InvisWall=3
	};

	enum Direction
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};

private:
	void setTile(int x, int y, int value);
	int getTile(int x, int y);

	void PlaceRoom(LevelGeneratorRoom room);
	LevelGeneratorRoom GenerateRoom();
	void SpreadRooms();
	int randomInt(int min, int max);
	void CreateSeeds();
	int m_origionalSeed =0;
	int m_seed = 0;
	int m_seedLength = 0;

	std::vector<int> m_seedDigets;
	


	int m_width, m_height;
	std::vector<int> m_CurrentDungeon;
	std::vector<LevelGeneratorRoom> m_rooms;
	const int MaxSeed = 999999;
	const int MaxWidth = 200;
	const int MaxHeight = 200;
	const int MinWidth = 80;
	const int MinHeight = 80;

	const int MaxRoomWidth = 15;
	const int MaxRoomHeight = 15;
	const int MinRoomWidth = 8;
	const int MinRoomHeight = 8;

	const int MinRoomCount = 20;
	const int MaxRoomCount = 40;

	const int BufferBetweenRooms = 2;
	std::mt19937 mt;

};