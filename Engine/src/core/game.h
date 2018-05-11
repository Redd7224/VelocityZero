#pragma once
#include <vector>
#include <DirectXMath.h>
#include "spriteInfo.h"
#include "camera.h"
#include "inputData.h"
#include "player.h"
class Game
{
public:
	Game(DirectX::XMFLOAT2 targetResolution);
	~Game();
	void Update(float deltaTime,InputData* inputData);
	std::vector<SpriteInfo> m_spritesToDraw;
private:
	void GenerateDummyLevel();
	void GenerateDummyLevel2();
	Player* m_pPlayer;
	std::vector<SpriteInfo> m_currentLevelSpriteInfo;
	Camera* m_pCamera;
};
