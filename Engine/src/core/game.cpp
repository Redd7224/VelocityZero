#include "game.h"

Game::Game(DirectX::XMFLOAT2 targetResolution) {
	m_pCamera = new Camera(targetResolution);
	GenerateDummyLevel2();
	GenerateDummyLevelChunks();
	m_pPlayer = new Player();
	m_pPlayer->m_position = DirectX::XMFLOAT2(100, 100);

	chunkss.resize(chunksSize * chunksSize);
}
Game::~Game() {}
void Game::Update(float deltaTime, InputData* inputData) {
	
	//we may not want to clear . but may be easest for now. 

	m_pPlayer->Move(inputData, deltaTime);


	//m_pCamera->Move(DirectX::XMFLOAT2(30 * inputData->xAxis, 30 * inputData->yAxis),deltaTime);
	m_pCamera->FollowCentered(m_pPlayer->m_SpriteInfo.position);

	drawCount = 0;
	//m_pCamera->FilterSpritesForView(m_currentLevelSpriteInfo, spritesToDraw, drawCount);

	
	int x = (int) m_pPlayer->m_position.x / (16 * 32);
	int y = (int) m_pPlayer->m_position.y / (16 * 32);

	drawChunkData(x - 1, y - 1); // 1
	drawChunkData(x, y -1); // 2
	drawChunkData(x + 1, y-1); // 3
	drawChunkData(x -1, y); // 4
	drawChunkData(x, y); // 5 
	drawChunkData(x+1, y); // 6
	drawChunkData(x - 1, y + 1); // 7
	drawChunkData(x, y+1); // 8
	drawChunkData(x + 1, y+1); // 9



	m_pCamera->FilterSpriteForView(m_test, spritesToDraw, drawCount);

	m_pCamera->FilterSpriteForView(m_pPlayer->m_SpriteInfo, spritesToDraw, drawCount);


	int foox = 1;
}

void Game::drawChunkData(int x, int y) {
	if (x < 0 || y < 0) {
		return;
	}
	//Maybe getting chunk pointer is faster then getting it in the loopyloop.
	ChunkData* chunk = &chunkss[x * chunksSize + y];
	//TODO getsize call was slow. This needs to be a const var
	for (size_t i = 0; i < 256; i++)
	{
		m_pCamera->FilterSpriteForView(chunk->tiles[i].m_spriteInfo, spritesToDraw, drawCount);

	}

	
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

	for (size_t j = 1; j < 16; j++)
	{
		for (size_t i = 1; i < 16; i++)
		{
			float x = 32 * i;
			float y = 32 * j;
			float isox = x - y;
			float isoy = (x + y) / 2;
			SpriteInfo si;
			si.textureName = "PH_ground.png";
			si.sourceRect = new RECT();
			si.sourceRect->bottom = 64;
			si.sourceRect->right = 64;
			si.sourceRect->top = 0;
			si.sourceRect->left = 0;
			si.systemPosition = DirectX::XMFLOAT2(x, y);
			si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
			si.position = DirectX::XMFLOAT2(isox, isoy);
			m_currentLevelSpriteInfo.push_back(si);
		}
	}
}


void Game::GenerateDummyLevelChunks() {
	chunkss.resize(chunksSize * chunksSize);
	

	for (size_t i = 0; i < chunksSize; i++) {
		for (size_t j = 0; j < chunksSize; j++) {
			ChunkData cd;
			cd.tiles.resize(16 * 16);
			cd.x = i;
			cd.y = j;
			for (size_t k = 0; k < 16; k++)
			{
				for (size_t l = 0; l < 16; l++)
				{
					TileInfo ti;
					ti.x = (i * 32 * 16) + k * 32;
					ti.y = (j * 32 * 16) + l * 32;
					float isox = ti.x - ti.y;
					float isoy = (ti.x + ti.y) / 2;

					SpriteInfo si;
					si.textureName = "PH_ground.png";
					si.sourceRect = new RECT();
					si.sourceRect->bottom = 64;
					si.sourceRect->right = 64;
					si.sourceRect->top = 0;
					si.sourceRect->left = 0;
					si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
					si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
					si.position = DirectX::XMFLOAT2(isox, isoy);
					ti.m_spriteInfo = si;

					cd.tiles[k * 16 + l] = ti;
				}
			}
			chunkss[i * chunksSize + j] = cd;
		}
	}

	float x = 32 * 0;
	float y = 32 * 0;
	float isox = x - y;
	float isoy = (x + y) / 2;
	m_test.textureName = "PH_wall.png";
	m_test.sourceRect = new RECT();
	m_test.sourceRect->bottom = 128;
	m_test.sourceRect->right = 64;
	m_test.sourceRect->top = 0;
	m_test.sourceRect->left = 0;
	m_test.systemPosition = DirectX::XMFLOAT2(x, y);
	m_test.isoPosition = DirectX::XMFLOAT2(isox, isoy);
	m_test.position = DirectX::XMFLOAT2(isox, isoy);


}

