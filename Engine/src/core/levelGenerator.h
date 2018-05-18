#pragma once
#include <vector>
#include <iostream> //This is just included for debug print
#include <random>
#include "LevelGeneratorRoom.h"
#include "LevelGeneratorCorridor.h"
class LevelGenerator
{
public:
	LevelGenerator(int seed);
	~LevelGenerator();
	std::vector<int> Generate();
	void print();
	int m_width, m_height;
	int startx, starty;
	
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
	void PlaceCorr(LevelGeneratorRoom room);
	std::vector<int> GenerateDungeonSpread();
	std::vector<int> GenerateDungeonTouching();
	std::vector<int> GenerateDungeonRandomWalk();

	LevelGeneratorRoom GenerateRoom(int x, int y);
	LevelGeneratorRoom GenerateRoom();
	LevelGeneratorRoom GenerateCorr();
	bool GenerateTouchingRooms();
	void GenerateTouchingDoors();
	bool GenerateTouchingCheck(const Direction& dir, int width, int height);
	void SpreadRooms();
	int randomInt(int min, int max);
	void CreateSeeds();
	int m_origionalSeed =0;
	int m_seed = 0;
	int m_seedLength = 0;
	//hacks. 
	int curr_x = 0;
	int curr_y = 0;
	int m_roomNumberTarget = 0;
	int counter_ = 1;
	bool is_executed_ = false;

	//
	std::vector<int> m_seedDigets;
	


	std::vector<int> m_CurrentDungeon;
	std::vector<LevelGeneratorRoom> m_rooms;

	const int MaxSeed = 99999999999;
	const int MaxWidth = 400;
	const int MaxHeight = 400;
	const int MinWidth = 100;
	const int MinHeight = 100;

	const int MaxRoomWidth = 15;
	const int MaxRoomHeight = 15;
	const int MinRoomWidth = 5;
	const int MinRoomHeight = 5;

	const int MaxCorrWidth = 5;
	const int MaxCorrHeight = 10;
	const int MinCorrWidth = 3;
	const int MinCorrHeight = 5;

	const int MinRoomCount = 20;
	const int MaxRoomCount = 80;

	const int BufferBetweenRooms = 2;
	std::mt19937 mt;

};