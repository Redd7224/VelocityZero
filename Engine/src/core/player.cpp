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
	float isoX = 0;
	float isoY = 0;
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
			direction += 4;
		}
		else {
			direction += 8;
		}
	}

	switch (direction)
	{
	case 1:
		isoX = 1;
		isoY = 1;
		m_SpriteInfo.spriteIdx.x = 4;
		break;
	case 2:
		
		isoX = -1;
		isoY = -1;
		m_SpriteInfo.spriteIdx.x = 0;
		break;
	case 4:		
		yDiagMod = 2;
		isoX = 1;
		isoY = -1;
		m_SpriteInfo.spriteIdx.x = 6;
		break;
	case 5:
		isoX = 1;
		isoY = 0;
		m_SpriteInfo.spriteIdx.x = 5;
		break;
	case 6:
		isoX = 0;
		isoY = -1;
		m_SpriteInfo.spriteIdx.x = 7;
		
		break;
	case 8:
		yDiagMod = 2;
		isoX = -1;
		isoY = 1;
		m_SpriteInfo.spriteIdx.x = 2;
		break;
	case 9:
		isoX = 0;
		isoY = 1;
		m_SpriteInfo.spriteIdx.x = 3;
		break;
	case 10:
		isoX = -1;
		isoY = 0;
		m_SpriteInfo.spriteIdx.x = 1;

		break;
	default:
		m_SpriteInfo.spriteIdx.x = 0;
		break;
	}

	m_SpriteInfo.CalcSourceRECT();


		



	bool isometricDisplay = true;
	if (isometricDisplay) {
		m_position.x += -1 * (isoX * moveSpeed) / yDiagMod * deltaTime;
		m_position.y += -1 * (isoY * moveSpeed) / yDiagMod * deltaTime;

		m_SpriteInfo.position.x = (m_position.x - m_position.y);
		m_SpriteInfo.position.y = (m_position.x + m_position.y) / 2;
		/* PURE ISO METRIC*/
		/*
		m_position.x += -1 * (inputData->xAxis * moveSpeed) * deltaTime;
		m_position.y += -1 * (inputData->yAxis * moveSpeed)  * deltaTime;
		m_SpriteInfo.position.x = (m_position.x - m_position.y);
		m_SpriteInfo.position.y = (m_position.x + m_position.y) / 2;
		*/
	}
	else {
		m_position.x += -1 * (inputData->xAxis * moveSpeed) * deltaTime;
		m_position.y += -1 * (inputData->yAxis * moveSpeed) * deltaTime;
		m_SpriteInfo.position.x = m_position.x;
		m_SpriteInfo.position.y = m_position.y;
	}

}

void Player::UpdateSpriteIdxByDirection(int direction) {
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
		m_SpriteInfo.spriteIdx.x = 7;
		break;
	case 6:
		m_SpriteInfo.spriteIdx.x = 5;
		break;
	case 8:
		m_SpriteInfo.spriteIdx.x = 2;
		break;
	case 9:
		m_SpriteInfo.spriteIdx.x = 1;
		break;
	case 10:
		m_SpriteInfo.spriteIdx.x = 3;
		break;
	default:
		m_SpriteInfo.spriteIdx.x = 0;
		break;
	}

	m_SpriteInfo.CalcSourceRECT();
}