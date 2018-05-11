#include "player.h"


Player::Player() {
	m_SpriteInfo.textureName="perspectiveTest1.png";
	m_SpriteInfo.spriteSize.x = 64;
	m_SpriteInfo.spriteSize.y = 64;
	m_SpriteInfo.scale = 0;
	m_SpriteInfo.rotation = 0;
	m_SpriteInfo.spriteIdx.x = 0;
	m_SpriteInfo.isHoizontalSheet = true;

}

Player::~Player() {}
void Player::Move(InputData* inputData, float deltaTime) {
	
	//If we move Diagionally we need to devide y movement by 2 to keep in perspective
	int yDiagMod = 1;

	//Total hack? Maybe should be done somewhere else 
	//Bitmask for 8 directions
	// 1 = up
	// 2 = down
	// 4 = left 
	// 8 = right
	int direction = 0;
	if (inputData->yAxis != 0) {
		if (inputData->yAxis > 0) {
			direction += 1;
		}
		else {
			direction += 2;
		}
	}

	if (inputData->xAxis != 0) {
		if (inputData->xAxis > 0) {
			direction += 8;
		}
		else {
			direction += 4;
		}
	}
	switch (direction)
	{
	case 1:
		m_SpriteInfo.spriteIdx.x = 4;
		break;
	case 2:
		m_SpriteInfo.spriteIdx.x = 0;
		break;
	case 4:
		m_SpriteInfo.spriteIdx.x = 6;
		break;
	case 5:
		yDiagMod = 2;
		m_SpriteInfo.spriteIdx.x = 7;
		break;
	case 6:
		yDiagMod = 2;
		m_SpriteInfo.spriteIdx.x = 5;
		break;
	case 8:
		m_SpriteInfo.spriteIdx.x = 2;
		break;
	case 9:
		yDiagMod = 2;
		m_SpriteInfo.spriteIdx.x = 1;
		break;
	case 10:
		yDiagMod = 2;
		m_SpriteInfo.spriteIdx.x = 3;
		break;
	default:
		m_SpriteInfo.spriteIdx.x = 0;
		break;
	}

	m_SpriteInfo.CalcSourceRECT();

	m_position.x += -1 * (inputData->xAxis * moveSpeed) * deltaTime;
	m_position.y +=  -1 * (inputData->yAxis * moveSpeed /yDiagMod) * deltaTime;
	m_SpriteInfo.position.x = m_position.x;
	m_SpriteInfo.position.y = m_position.y;

}

