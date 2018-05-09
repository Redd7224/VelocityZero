#pragma once
#include <vector>
#include <DirectXMath.h>
#include "spriteInfo.h"

class Game
{
public:
	Game();
	~Game();
	void Update(float deltaTime);
	std::vector<SpriteInfo> m_spritesToDraw;
private:
	void GenerateDummyLevel();
	
};
