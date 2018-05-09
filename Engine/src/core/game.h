#pragma once
#include <vector>
#include <DirectXMath.h>
#include "spriteInfo.h"
#include "camera.h"
class Game
{
public:
	Game(DirectX::XMFLOAT2 targetResolution);
	~Game();
	void Update(float deltaTime);
	std::vector<SpriteInfo> m_spritesToDraw;
private:
	void GenerateDummyLevel();
	
	std::vector<SpriteInfo> m_currentLevelSpriteInfo;
	Camera* m_pCamera;
};
