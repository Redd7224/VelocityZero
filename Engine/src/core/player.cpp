#include "player.h"


Player::Player() {
	spriteInfo.textureKey=3;
	spriteInfo.spriteSize.x = 64;
	spriteInfo.spriteSize.y = 64;
	spriteInfo.scale = 1;
	spriteInfo.rotation = 0;
	spriteInfo.spriteIdx.x = 0;
	spriteInfo.origion = DirectX::XMFLOAT2(0, 64);
	spriteInfo.isHoizontalSheet = true;
	collider = Collider(DirectX::BoundingSphere(DirectX::XMFLOAT3(systemPosition.x, systemPosition.y, 0), 15));
	
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
		spriteInfo.spriteIdx.x = 4;
		break;
	case 2:
		
		isoX = -1;
		isoY = -1;
		spriteInfo.spriteIdx.x = 0;
		break;
	case 4:		
		yDiagMod = 2;
		isoX = 1;
		isoY = -1;
		spriteInfo.spriteIdx.x = 6;
		break;
	case 5:
		isoX = 1;
		isoY = 0;
		spriteInfo.spriteIdx.x = 5;
		break;
	case 6:
		isoX = 0;
		isoY = -1;
		spriteInfo.spriteIdx.x = 7;
		
		break;
	case 8:
		yDiagMod = 2;
		isoX = -1;
		isoY = 1;
		spriteInfo.spriteIdx.x = 2;
		break;
	case 9:
		isoX = 0;
		isoY = 1;
		spriteInfo.spriteIdx.x = 3;
		break;
	case 10:
		isoX = -1;
		isoY = 0;
		spriteInfo.spriteIdx.x = 1;

		break;
	default:
		spriteInfo.spriteIdx.x = 0;
		break;
	}

	spriteInfo.CalcSourceRECT();


		



	bool isometricDisplay = true;
	if (isometricDisplay) {
		systemPosition.x += -1 * (isoX * moveSpeed) / yDiagMod * deltaTime;
		systemPosition.y += -1 * (isoY * moveSpeed) / yDiagMod * deltaTime;

		spriteInfo.systemPosition.x = (systemPosition.x - systemPosition.y);
		spriteInfo.systemPosition.y = (systemPosition.x + systemPosition.y) / 2;

		spriteInfo.isoPosition.x = (systemPosition.x - systemPosition.y);
		spriteInfo.isoPosition.y = (systemPosition.x + systemPosition.y) / 2;



		spriteInfo.position.x = (systemPosition.x - systemPosition.y);
		spriteInfo.position.y = (systemPosition.x + systemPosition.y) / 2;
		/* PURE ISO METRIC*/
		/*
		m_position.x += -1 * (inputData->xAxis * moveSpeed) * deltaTime;
		m_position.y += -1 * (inputData->yAxis * moveSpeed)  * deltaTime;
		spriteInfo.position.x = (m_position.x - m_position.y);
		spriteInfo.position.y = (m_position.x + m_position.y) / 2;
		*/
	}
	else {
		systemPosition.x += -1 * (inputData->xAxis * moveSpeed) * deltaTime;
		systemPosition.y += -1 * (inputData->yAxis * moveSpeed) * deltaTime;
		spriteInfo.position.x = systemPosition.x;
		spriteInfo.position.y = systemPosition.y;
	}

	//Update Colider
	spriteInfo.collider.Center.x = systemPosition.x;
	spriteInfo.collider.Center.y = systemPosition.y;
	collider.sphereCollider.Center.x = systemPosition.x;
	collider.sphereCollider.Center.y = systemPosition.y;

}

void Player::UpdateSpriteIdxByDirection(int direction) {
	switch (direction)
	{
	case 1:
		spriteInfo.spriteIdx.x = 4;
		break;
	case 2:
		spriteInfo.spriteIdx.x = 0;
		break;
	case 4:
		spriteInfo.spriteIdx.x = 6;
		break;
	case 5:
		spriteInfo.spriteIdx.x = 7;
		break;
	case 6:
		spriteInfo.spriteIdx.x = 5;
		break;
	case 8:
		spriteInfo.spriteIdx.x = 2;
		break;
	case 9:
		spriteInfo.spriteIdx.x = 1;
		break;
	case 10:
		spriteInfo.spriteIdx.x = 3;
		break;
	default:
		spriteInfo.spriteIdx.x = 0;
		break;
	}

	spriteInfo.CalcSourceRECT();
}