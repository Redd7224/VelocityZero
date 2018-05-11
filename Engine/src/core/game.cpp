#include "game.h"

Game::Game(DirectX::XMFLOAT2 targetResolution) {
	m_pCamera = new Camera(targetResolution);
	GenerateDummyLevel2();
	m_pPlayer = new Player();
	m_pPlayer->m_position = DirectX::XMFLOAT2(400, 300);
}
Game::~Game() {}
void Game::Update(float deltaTime, InputData* inputData) {
	int x = 1;
	//we may not want to clear . but may be easest for now. 
	m_spritesToDraw.clear();
	m_spritesToDraw.insert(m_spritesToDraw.end(), m_currentLevelSpriteInfo.begin(), m_currentLevelSpriteInfo.end());

	m_pPlayer->Move(inputData, deltaTime);

	m_spritesToDraw.push_back(m_pPlayer->m_SpriteInfo);

	//m_pCamera->Move(DirectX::XMFLOAT2(30 * inputData->xAxis, 30 * inputData->yAxis),deltaTime);
	m_pCamera->FollowCentered(m_pPlayer->m_SpriteInfo.position);

	//Filter sprites that are in view. This also translates them to screen pos
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
			si.sourceRect = new RECT();
			si.sourceRect->bottom = 64;
			si.sourceRect->right = 64;
			si.sourceRect->top = 0;
			si.sourceRect->left= 0;
			si.position = DirectX::XMFLOAT2(x, y );
			m_currentLevelSpriteInfo.push_back(si);
		}
	}
}


void Game::GenerateDummyLevel2() {
	float startx = 400;
	float starty = 300;
	for (size_t j = 1; j < 10; j++)
	{
		for (size_t i = 1; i < 10; i++)
		{
			float x = startx + 32 * i;
			float y = starty+ 32 * j;
			float isox = x - y;
			float isoy = (x + y) / 2;
			SpriteInfo si;
			si.textureName = "PH_ground.png";
			si.sourceRect = new RECT();
			si.sourceRect->bottom = 64;
			si.sourceRect->right = 64;
			si.sourceRect->top = 0;
			si.sourceRect->left = 0;
			si.position = DirectX::XMFLOAT2(isox, isoy);
			m_currentLevelSpriteInfo.push_back(si);
		}
	}
}