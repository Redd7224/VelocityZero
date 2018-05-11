#pragma once
#include "spriteInfo.h"
#include "inputData.h"
#include "pch.h" //maybe too much stuff for this class
class Player
{
public:
	Player();
	~Player();
	void Move(InputData* inputData, float deltaTime);
	DirectX::XMFLOAT2 m_position;
	SpriteInfo m_SpriteInfo;

private:
	float moveSpeed = 100.0f;
	void UpdateSpriteIdxByDirection(int direction);
};