#pragma once
struct LevelGeneratorRoom {
	int x, y;
	int width, height;
	bool intersects(LevelGeneratorRoom room,int IntersectBuffer) {
		bool xOverlap = valueInRange(x, room.x, room.x + room.width) ||
			valueInRange(room.x, x, x + width + IntersectBuffer);

		bool yOverlap = valueInRange(y, room.y, room.y + room.height) ||
			valueInRange(room.y, y, y + height+ IntersectBuffer);

		return xOverlap && yOverlap;
	}

	bool valueInRange(int value, int min, int max)
	{
		return (value >= min) && (value <= max);
	}
};