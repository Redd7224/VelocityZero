#pragma once
#include "spriteInfo.h"
#include "inputData.h"
#include "gameObject.h"
#include "pch.h" //maybe too much stuff for this class
class Player: public GameObject
{
public:
	Player();
	~Player();
	void Move(InputData* inputData, float deltaTime);

private:
	float moveSpeed = 100.0f;
	void UpdateSpriteIdxByDirection(int direction);
};