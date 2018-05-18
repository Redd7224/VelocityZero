#include "game.h"

Game::Game(DirectX::XMFLOAT2 targetResolution) {
	m_pCamera = new Camera(targetResolution);
	m_pPlayer = new Player();
	GenerateDummyLevelChunks();

	chunkss.resize(chunksSize * chunksSize);
}
Game::~Game() {}
void Game::Update(float deltaTime, InputData* inputData) {
	
	//Previous position and colission here is just a test
	DirectX::XMFLOAT2 prevPos = m_pPlayer->m_position;
	m_pPlayer->Move(inputData, deltaTime);
	if (m_pPlayer->m_SpriteInfo.collider.Intersects(m_test.collider)) {
		m_pPlayer->m_position = prevPos;
	}

	//m_pCamera->Move(DirectX::XMFLOAT2(30 * inputData->xAxis, 30 * inputData->yAxis),deltaTime);
	m_pCamera->FollowCentered(m_pPlayer->m_SpriteInfo.position);

	drawCount = 0;
	

	//Get chunks to draw
	int x = (int) m_pPlayer->m_position.x / (16 * 32);
	int y = (int) m_pPlayer->m_position.y / (16 * 32);

	drawChunkData(x - 1, y - 1); // 1
	drawChunkData(x, y -1); // 2
	drawChunkData(x + 1, y-1); // 3
	drawChunkData(x -1, y); // 4
	
	//Maybe we should draw player in this chunk, splice it in to get depth right
	drawChunkDataWithPlayer(x, y); // 5 
	//m_pCamera->FilterSpriteForView(m_pPlayer->m_SpriteInfo, spritesToDraw, drawCount);
	
	drawChunkData(x+1, y); // 6
	drawChunkData(x - 1, y + 1); // 7
	drawChunkData(x, y+1); // 8
	drawChunkData(x + 1, y+1); // 9

	


	int foox = 1;
}
//TODO Draw this like the player one to get layers right?
void Game::drawChunkData(int x, int y) {
	//Break if  there is no way the chunk exists.
	if (x < 0 || y < 0) {
		return;
	}
	ChunkData* chunk = &chunkss[x * chunksSize + y];
	//TODO getsize call was slow. This needs to be a const var
	for (size_t i = 0; i < 256; i++)
	{
		m_pCamera->FilterSpriteForView(chunk->tiles[i].m_spriteInfo, spritesToDraw, drawCount);

	}
}
void Game::drawChunkDataWithPlayer(int x, int y) {
	//Break if  there is no way the chunk exists.
	if (x < 0 || y < 0) {
		return;
	}
	ChunkData* chunk = &chunkss[x * chunksSize + y];
	int fooy = (y * 32 * 16);
	int playerPosIdy = (m_pPlayer->m_position.y - fooy) /32 ;
	int foox = (x * 32 * 16);
	int playerPosIdx = (m_pPlayer->m_position.x - foox) / 32;
	bool playerDrawn = false;
	//TODO getsize call was slow. This needs to be a const var
	for (size_t i = 0; i < 16; i++)
	{

		for (size_t j = 0; j < 16; j++)
		{
			if (j - 1 == playerPosIdy && i - 1 == playerPosIdx) {
				m_pCamera->FilterSpriteForView(m_pPlayer->m_SpriteInfo, spritesToDraw, drawCount);
				playerDrawn = true;
			}
			m_pCamera->FilterSpriteForView(chunk->tiles[i * 16 + j].m_spriteInfo, spritesToDraw, drawCount);

		}

	}
	if (!playerDrawn) {
		m_pCamera->FilterSpriteForView(m_pPlayer->m_SpriteInfo, spritesToDraw, drawCount);
	}
}

void Game::GenerateDummyLevelChunks() {
	chunkss.resize(chunksSize * chunksSize);
	LevelGenerator lg(1276483);
	std::vector<int> generatedLevel = lg.Generate();
	m_pPlayer->m_position = DirectX::XMFLOAT2(lg.startx*32, lg.starty*32);
	int xChunks = lg.m_width / 16;
	int yChunks = lg.m_height / 16;
	for (size_t i = 0; i < xChunks; i++) {
		for (size_t j = 0; j < yChunks; j++) {
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

					int dungeonx = (i * 16) + k;
					int dungeony = (j * 16) + l;
					int tileType = generatedLevel[dungeonx + dungeony * lg.m_width];
					if (tileType == 1) {
						si.textureName = "PH_ground.png";
						si.sourceRect = new RECT();
						si.sourceRect->bottom = 64;
						si.sourceRect->right = 64;
						si.sourceRect->top = 0;
						si.sourceRect->left = 0;
						si.origion = DirectX::XMFLOAT2(0, 0);
						si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
						si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
						si.position = DirectX::XMFLOAT2(isox, isoy);
					}
					else {
						si.textureName = "PH_wall.png";
						si.sourceRect = new RECT();
						si.sourceRect->bottom = 128;
						si.sourceRect->right = 64;
						si.sourceRect->top = 0;
						si.sourceRect->left = 0;
						si.origion = DirectX::XMFLOAT2(0, 64+32);
						si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
						si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
						si.position = DirectX::XMFLOAT2(isox, isoy);
					}

					ti.m_spriteInfo = si;
					cd.tiles[k * 16 + l] = ti;
					//cd.tiles[l * 16 + k] = ti;
				}
			}
			chunkss[i * chunksSize + j] = cd;
		}
	}

	float x = 32 * 8;
	float y = 32 * 6;
	float isox = x - y;
	float isoy = (x + y) / 2;
	m_test.textureName = "PH_wall.png";
	m_test.sourceRect = new RECT();
	m_test.sourceRect->bottom = 128;
	m_test.sourceRect->right = 64;
	m_test.sourceRect->top = 0;
	m_test.sourceRect->left = 0;
	m_test.origion = DirectX::XMFLOAT2(0, 128);
	m_test.systemPosition = DirectX::XMFLOAT2(x, y);
	m_test.isoPosition = DirectX::XMFLOAT2(isox, isoy);
	m_test.position = DirectX::XMFLOAT2(isox, isoy);
	m_test.collider = DirectX::BoundingSphere(DirectX::XMFLOAT3(x, y, 0), 16);

}

