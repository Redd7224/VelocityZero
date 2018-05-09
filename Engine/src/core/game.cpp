#include "game.h"

Game::Game(DirectX::XMFLOAT2 targetResolution) {
	m_pCamera = new Camera(targetResolution);
	GenerateDummyLevel();
}
Game::~Game() {}
void Game::Update(float deltaTime) {
	int x = 1;
	//we may not want to clear . but may be easest for now. 
	m_spritesToDraw.clear();
	m_spritesToDraw.insert(m_spritesToDraw.end(), m_currentLevelSpriteInfo.begin(), m_currentLevelSpriteInfo.end());
	
	m_pCamera->FilterSpritesForView(m_spritesToDraw);
}

void Game::GenerateDummyLevel() {
	for (size_t j = 1; j < 30; j++)
	{
		float y = 10 + (16 * j);
		int rowLength = 11;
		if (j % 2 == 0) {
			rowLength--;
		}
		
		for (size_t i = 1; i < rowLength; i++)
		{
			float x = 0;
			if (j % 2 == 0) {
				x = (64 * i) + 32;
			}
			else {
				x = 64 * i;
			}
			SpriteInfo si;
			si.textureName = "PH_ground.png";
			si.position = DirectX::XMFLOAT2(x, y );
			m_currentLevelSpriteInfo.push_back(si);
		}
	}
}