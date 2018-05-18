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


	int x = randomInt(MinWidth, MaxWidth);
	int y = randomInt(MinHeight, MaxHeight);
	if (x > MaxWidth) {
		m_width = MaxWidth;
	}
	else {
		m_width = x;
	}
	if (y > MaxHeight) {
		m_height = MaxHeight;
	}
	else {
		m_height = y;
	}
	m_CurrentDungeon.resize(m_width*m_height, Unused);

	//GenerateDungeonTouching();
	GenerateDungeonRandomWalk();
	
	

	return m_CurrentDungeon;

}

std::vector<int> LevelGenerator::GenerateDungeonRandomWalk() {
	curr_x = randomInt(10, m_width);
	curr_y = randomInt(10, m_height);
	startx = curr_x;
	starty = curr_y;
	int maxFloorTileCount = randomInt((m_width * m_height * .3), (m_width * m_height * .7));
	int floorTileCount = 0;
	while (floorTileCount < maxFloorTileCount) {
		if (getTile(curr_x, curr_y) == Unused) {
			setTile(curr_x, curr_y, Floor);
			floorTileCount++;
		}
		int dir = randomInt(1, 4);
		switch (dir)
		{
		case 1:
			curr_y--;
			break;
		case 2:
			curr_y++;
			break;
		case 3:
			curr_x--;
			break;
		case 4:
			curr_x++;
			break;
		case 5:
			curr_y--;
			curr_x--;
			break;
		case 6:
			curr_y--;
			curr_x++;
			break;
		case 7:
			curr_y++;
			curr_x++;
			break;
		case 8:
			curr_y++;
			curr_x--;
			break;
		default:
			break;
		}
		if (curr_x <= 0) {
			curr_x++;
		}
		else if (curr_x >= m_width) {
			curr_x--;
		}
		if (curr_y <= 0) {
			curr_y++;
		}
		else if (curr_y >= m_height) {
			curr_y--;
		}

	}

	return m_CurrentDungeon;
}
std::vector<int> LevelGenerator::GenerateDungeonTouching() {
	curr_x = randomInt(10,m_width);
	curr_y = randomInt(10,m_height);
	m_roomNumberTarget = randomInt(MinRoomCount, MaxRoomCount);

	while (!GenerateTouchingRooms());
	//GenerateTouchingDoors();
	//GenerateTouchingRooms();
	//GenerateTouchingRooms();
	//GenerateTouchingRooms();

	return m_CurrentDungeon;
}

bool LevelGenerator::GenerateTouchingRooms() {
	bool result = false;
	//get random room size
	int width = randomInt(MinRoomWidth, MaxRoomWidth);
	int height = randomInt(MinRoomWidth, MaxRoomWidth);
	Direction n = Direction::North;
	Direction e = Direction::East;
	Direction s = Direction::South;
	Direction w = Direction::West;
	//Holds available directons to place room. Actually Quads not pure direction
	std::vector<Direction> availDirection;
	if((curr_x > 0 && curr_x < m_width) && (curr_y > 0 && curr_y < m_height)){
		if (GenerateTouchingCheck(Direction::North, width, height)) {
			availDirection.push_back(n);
		}
		if (GenerateTouchingCheck(Direction::East, width, height)) {
			availDirection.push_back(e);
		}
		if (GenerateTouchingCheck(Direction::South, width, height)) {
			availDirection.push_back(s);
		}
		if (GenerateTouchingCheck(Direction::West, width, height)) {
			availDirection.push_back(w);
		}
	}
	//Spawwn reset recusions... to get more then one path
	if (availDirection.empty() && m_rooms.size() < m_roomNumberTarget) {
		int foo = m_rooms.size() - counter_;
		if ( foo 
	> 0) {
			//May need var here to limit look ups
			curr_x = m_rooms[m_rooms.size() - counter_].x + m_rooms[m_rooms.size() - counter_].width-1;
			curr_y = m_rooms[m_rooms.size() - counter_].y + m_rooms[m_rooms.size() - counter_].height-1;
			counter_++;
			while (!GenerateTouchingRooms());
			while (!GenerateTouchingRooms());
		}
		else if (!is_executed_ && m_rooms.size() - counter_ == 0) {
			curr_x = m_rooms[0].x;
			curr_y = m_rooms[0].y;
			is_executed_ = true; //This condition should be executed only ONCE to start recurssion
			GenerateTouchingRooms();
		}
	}
	
	if (availDirection.size() <= 0) {
		result = true;
	}
	else {
		Direction rnd_dir = availDirection[randomInt(0,availDirection.size() - 1)];
		LevelGeneratorRoom room;
		room.x = curr_x;
		room.y = curr_y;
		room.width = width;
		room.height = height;
		//Set room direction and set current x and y to opposite corrnor

		//Make room in randomly selected direction
		switch (rnd_dir) {
		case Direction::East: {
			for (int y = curr_y; y < curr_y + height; y++) {
				for (int x = curr_x; x < curr_x + width; x++) {
					if (y == curr_y || y == curr_y + (height - 1)
						|| x == curr_x || x == curr_x + (width - 1)) {
						setTile(x, y, 2);
					}
					else {
						setTile(x, y, 1);
					}
				}
			}
			//Keep track of all rooms
			room.width = curr_x + (width - 1);
			room.height = curr_y + (height - 1);
			room.direction = Direction::East;
			//Set y&&x position to the opposite corner
			curr_y += (height - 1);
			curr_x += (width - 1);
		}
							  break;
		case Direction::South: {
			for (int y = curr_y; y < curr_y + height; y++) {
				for (int x = curr_x; x > curr_x - width; x--) {
					if (y == curr_y || y == curr_y + (height - 1)
						|| x == curr_x || x == curr_x - (width - 1)) {
						setTile(x, y, 2);
					}
					else {
						setTile(x, y, 1);
					}
				}
			}
			room.width = curr_x - (width - 1);
			room.height = curr_y + (height - 1);
			room.direction = Direction::South;
			curr_y += (height - 1);
			curr_x -= (width - 1);
		}
							   break;
		case Direction::North: {
			for (int y = curr_y; y > curr_y - height; y--) {
				for (int x = curr_x; x < curr_x + width; x++) {
					if (y == curr_y || y == curr_y - (height - 1)
						|| x == curr_x || x == curr_x + (width - 1)) {
						setTile(x, y, 2);
					}
					else {
						setTile(x, y, 1);
					}
				}
			}

			room.width = curr_x + (width - 1);
			room.height = curr_y - (height - 1);
			room.direction = Direction::North;
			curr_y -= (height - 1);
			curr_x += (width - 1);
		}
							   break;
		case Direction::West: {
			for (int y = curr_y; y > curr_y - height; y--) {
				for (int x = curr_x; x > curr_x - width; x--) {
					if (y == curr_y || y == curr_y - (height - 1)
						|| x == curr_x || x == curr_x - (width - 1)) {
						setTile(x, y, 2);
					}
					else {
						setTile(x, y, 1);
					}
				}
			}
			room.width = curr_x - (width - 1);
			room.height = curr_y - (height - 1);
			room.direction = Direction::West;
			curr_y -= (height - 1);
			curr_x -= (width - 1);
		}
		 break;
		}
		m_rooms.push_back(room);
	}

	//break
	return result;
}

void LevelGenerator::GenerateTouchingDoors() {

}

bool LevelGenerator::GenerateTouchingCheck(const Direction& dir, int width, int height) {
	bool result = true;
	switch (dir)
	{
	case Direction::North: //north east
		//check if we are not above or out to the right
		if (curr_y - height >= 0 && curr_x + width <= m_width) {
			//check if positions above contain a room
			for (int y = curr_y; y > curr_y- height; y--) {
				for (int x = curr_x; x < curr_x + width; x++) {
					if (y == curr_y || y == curr_y - (height - 1)
						|| x == curr_x || x == curr_x + (width - 1)) {
						continue;
					}
					if (getTile(x, y) != 0) {
						result = false;
						break;
					}
				}
				if (!result) {
					break;
				}
			}
		}
		break;
	case Direction::East: //sout east
						   //check if we are not below or out to the right
		if (curr_y + height <= m_height && curr_x + width <= m_width) {
			//check if positions above contain a room
			for (int y = curr_y; y < curr_y + height; y++) {
				for (int x = curr_x; x < curr_x + width; x++) {
					if (y == curr_y || y == curr_y + (height - 1)
						|| x == curr_x || x == curr_x + (width - 1)) {
						continue;
					}
					if (getTile(x, y) != 0) {
						result = false;
						break;
					}
				}
				if (!result) {
					break;
				}
			}
		}
		break;
	case Direction::South: //sout west
						  //check if we are not below or out to the left
		if (curr_y + height < m_height && curr_x - width > 0) {
			//check if positions above contain a room
			for (int y = curr_y; y < curr_y + height; y++) {
				for (int x = curr_x; x > curr_x - width; x--) {
					if (y == curr_y || y == curr_y + (height - 1)
						|| x == curr_x || x == curr_x - (width - 1)) {
						continue;
					}
					if (getTile(x, y) != 0) {
						result = false;
						break;
					}
				}
				if (!result) {
					break;
				}
			}
		}
		break;
	case Direction::West: //north west
						   //check if we are not above or out to the left
		if (curr_y - height >= 0 && curr_x - width >= 0) {
			//check if positions above contain a room
			for (int y = curr_y; y > curr_y - height; y--) {
				for (int x = curr_x; x > curr_x - width; x--) {
					if (y == curr_y || y == curr_y - (height - 1)
						|| x == curr_x || x == curr_x - (width - 1)) {
						continue;
					}
					if (getTile(x, y) != 0) {
						result = false;
						break;
					}
				}
				if (!result) {
					break;
				}
			}
		}
		break;
	default:
		result = false;
		break;
	}
	return result;
}


std::vector<int> LevelGenerator::GenerateDungeonSpread() {

	for (size_t i = 0; i < randomInt(MinRoomCount, MaxRoomCount); i++)
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
				setTile(x, y, Wall);
				
			}
			else {
				setTile(x, y, Floor);
			}
		}
}

void LevelGenerator::PlaceCorr(LevelGeneratorRoom room) {
	if (room.x < 1 || room.y < 1 || room.x + room.width > m_width - 1 || room.y + room.height > m_height - 1)
		return;

	for (int y = room.y - 1; y < room.y + room.height + 1; ++y)
		for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
		{
			if ( (y == room.y - 1 ||  y == room.y + room.height) && room.direction >= 2) {
				setTile(x, y, InvisWall);
			}
			else if ((x == room.x - 1 || x == room.x + room.width) && room.direction <= 1) {
				setTile(x, y, InvisWall);
			}
			else {
				setTile(x, y, Floor);
			}
		}
}

LevelGeneratorRoom LevelGenerator::GenerateRoom() {
	
	return GenerateRoom(m_width / 2 - MaxRoomWidth, m_height / 2 - MaxRoomHeight);
}

LevelGeneratorRoom LevelGenerator::GenerateRoom(int x, int y) {
	LevelGeneratorRoom result;
	result.x = x;
	result.y = y;
	result.width = randomInt(MinRoomWidth, MaxRoomWidth);
	result.height = randomInt(MinRoomHeight, MaxRoomHeight);
	return result;
}

LevelGeneratorRoom LevelGenerator::GenerateCorr() {
	LevelGeneratorRoom result;
	result.x = -1;
	result.y = -1;
	result.width = randomInt(MinCorrWidth, MaxCorrWidth);
	result.height = randomInt(MinCorrHeight, MaxCorrHeight);
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
