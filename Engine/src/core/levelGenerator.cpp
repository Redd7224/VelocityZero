#include "LevelGenerator.h"



LevelGenerator::LevelGenerator(int seed)
{

	if (seed > MaxSeed) {
		seed = MaxSeed;
	}
	m_origionalSeed = seed;
	CreateSeeds();
	mt.seed(m_seed);
	int x = randomInt(MinWidth,MaxWidth);
	int y = randomInt(MinHeight,MaxHeight);
	if (x > MaxWidth) {
		m_width = MaxWidth;
	}
	else {
		m_width = x;
	}
	if ( y > MaxHeight){
		m_height = MaxHeight;
	}else{
		m_height = y;
	}
	
	m_CurrentDungeon.resize(m_width*m_height, Unused);

}


LevelGenerator::~LevelGenerator()
{

}

void LevelGenerator::CreateSeeds() {

	int modifiableSeed = m_origionalSeed;
	//If we have less then 3 digits. lets get bigger?
	while (modifiableSeed <= 999) {
		modifiableSeed = modifiableSeed * modifiableSeed;
	}
	m_seed = modifiableSeed;
	for (; modifiableSeed; modifiableSeed /= 10){
		m_seedLength++;
		m_seedDigets.push_back(modifiableSeed % 10);
	}

}

std::vector<int> LevelGenerator::Generate() {
	
	for (size_t i = 0; i < randomInt(MinRoomCount,MaxRoomCount); i++)
	{
		m_rooms.push_back(GenerateRoom());
	}
	SpreadRooms();
	for (size_t i = 0; i < m_rooms.size(); i++)
	{
		PlaceRoom(m_rooms[i]);

	}
	return m_CurrentDungeon;

}

void LevelGenerator::setTile(int x, int y, int value) {
	m_CurrentDungeon[x + y * m_width] = value;
}

int LevelGenerator::getTile(int x, int y) {
	return m_CurrentDungeon[x + y * m_width];
}

void LevelGenerator::SpreadRooms() {
	
	bool spread = false;
	while (!spread) {
		bool dirty = false;
		for (size_t i = 0; i < m_rooms.size(); i++)
		{
			int dir = randomInt(1, 8);
			LevelGeneratorRoom* currRoom = &m_rooms[i];
				for (size_t j = 0; j < m_rooms.size(); j++)
				{
					if (i == j) {
						continue;
					}
					if (currRoom->intersects(m_rooms[j], BufferBetweenRooms)) {
						dirty = true;
						switch (dir)
						{
						case 1:
							currRoom->x++;
							break;
						case 2:
							currRoom->x--;
							break;
						case 3:
							currRoom->y++;
							break;
						case 4:
							currRoom->y--;
							break;
						case 5:
							currRoom->y--;
							currRoom->x--;
							break;
						case 6:
							currRoom->y--;
							currRoom->x++;
							break;
						case 7:
							currRoom->y++;
							currRoom->x--;
							break;
						case 8:
							currRoom->y++;
							currRoom->x++;
							break;
						default:
							break;
						}
					}
				}
				if (currRoom->x + currRoom->width > m_width || currRoom->x < 0 || currRoom->y < 0 || currRoom->y + currRoom->height > m_height) {
					m_rooms.erase(m_rooms.begin() + i);
				}
			}

			if (!dirty) {
				spread = true;
			}
		}
	
}

void LevelGenerator::PlaceRoom(LevelGeneratorRoom room) {
	if (room.x < 1 || room.y < 1 || room.x + room.width > m_width - 1 || room.y + room.height > m_height - 1)
		return;

	for (int y = room.y; y < room.y + room.height; ++y)
		for (int x = room.x; x < room.x + room.width; ++x)
		{
			if (getTile(x, y) != Unused)
				return; // the area already used
		}

	for (int y = room.y - 1; y < room.y + room.height + 1; ++y)
		for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
		{
			if (x == room.x - 1 || y == room.y - 1 || x == room.x + room.width || y == room.y + room.height) {
				if (x+1 < room.x + room.width / 2 && (y != room.y + room.height || x == room.x-1)) {
					setTile(x, y, Wall);
				}
				else {
					setTile(x, y, InvisWall);
				}
				
			}
			else {
				setTile(x, y, Floor);
			}
		}
}
LevelGeneratorRoom LevelGenerator::GenerateRoom() {
	LevelGeneratorRoom result;
	result.x = m_width/2 - MaxRoomWidth;
	result.y = m_height/2 - MaxRoomHeight;
	result.width = randomInt(MinRoomWidth,MaxRoomWidth);
	result.height = randomInt(MinRoomHeight, MaxRoomHeight);
	return result;
}

void LevelGenerator::print()
{
	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
			std::cout << getTile(x, y);

		std::cout << std::endl;
	}
}




int LevelGenerator::randomInt(int min, int max) // inclusive min/max
{
	std::uniform_int_distribution<> dist(0, max - min);
	return dist(mt) + min;
}
