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
	prevPos = m_pPlayer->systemPosition;
	playerChunk.x = (int)m_pPlayer->systemPosition.x / (16 * 32);
	playerChunk.y = (int)m_pPlayer->systemPosition.y / (16 * 32);
	m_pPlayer->Move(inputData, deltaTime);
	playerCollision();

	//m_pCamera->Move(DirectX::XMFLOAT2(30 * inputData->xAxis, 30 * inputData->yAxis),deltaTime);
	//m_pCamera->FollowCentered(m_pPlayer->m_SpriteInfo.position);
	m_pCamera->FollowCentered(m_pPlayer->spriteInfo.position);
	//m_pCamera->FollowCentered(m_pPlayer->systemPosition);
	for (size_t i = 0; i < SPRITELAYERSCOUNT; i++)
	{
		spritesToDrawLayers[i].drawCount = 0;
	}

	//Get chunks to draw


	drawChunkData(playerChunk.x - 1, playerChunk.y - 1); // 1
	drawChunkData(playerChunk.x, playerChunk.y -1); // 2
	drawChunkData(playerChunk.x + 1, playerChunk.y -1); // 3
	drawChunkData(playerChunk.x -1, playerChunk.y); // 4
	
	//Maybe we should draw player in this chunk, splice it in to get depth right
	drawChunkDataWithPlayer(playerChunk.x, playerChunk.y); // 5 
	//m_pCamera->FilterSpriteForView(m_pPlayer->m_SpriteInfo, spritesToDraw, drawCount);
	
	drawChunkData(playerChunk.x +1, playerChunk.y); // 6
	drawChunkData(playerChunk.x - 1, playerChunk.y + 1); // 7
	drawChunkData(playerChunk.x, playerChunk.y +1); // 8
	drawChunkData(playerChunk.x + 1, playerChunk.y +1); // 9

	


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
		TileInfo *ti = &chunk->tiles[i];
		for (size_t p = 0; p < 5; p++)
		{
			m_pCamera->FilterSpriteForView(ti->tileGameObjectsByLayer[p].spriteInfo, spritesToDrawLayers[p].spritesToDraw, spritesToDrawLayers[p].drawCount);
		}

	}
}
void Game::drawChunkDataWithPlayer(int x, int y) {
	//Break if  there is no way the chunk exists.
	if (x < 0 || y < 0) {
		return;
	}
	ChunkData* chunk = &chunkss[x * chunksSize + y];
	int fooy = (y * 32 * 16);
	int playerPosIdy = (m_pPlayer->systemPosition.y - fooy) /32 ;
	int foox = (x * 32 * 16);
	int playerPosIdx = (m_pPlayer->systemPosition.x - foox) / 32;
	bool playerDrawn = false;
	//TODO getsize call was slow. This needs to be a const var
	for (size_t i = 0; i < 16; i++)
	{

		for (size_t j = 0; j < 16; j++)
		{
			if (j == playerPosIdy && i == playerPosIdx) {
				m_pCamera->FilterSpriteForView(m_pPlayer->spriteInfo, spritesToDrawLayers[1].spritesToDraw, spritesToDrawLayers[1].drawCount);
				playerDrawn = true;
			}
			TileInfo *ti = &chunk->tiles[i * 16 + j];
			for (size_t p = 0; p < 5; p++)
			{
				m_pCamera->FilterSpriteForView(ti->tileGameObjectsByLayer[p].spriteInfo, spritesToDrawLayers[p].spritesToDraw, spritesToDrawLayers[p].drawCount);
			}
		}

	}
	if (!playerDrawn) {
		m_pCamera->FilterSpriteForView(m_pPlayer->spriteInfo, spritesToDrawLayers[1].spritesToDraw, spritesToDrawLayers[1].drawCount);
	}
}

void Game::playerCollision() {
	ChunkData* chunk = &chunkss[playerChunk.x * chunksSize + playerChunk.y];
	//TODO getsize call was slow. This needs to be a const var
	for (size_t i = 0; i < 256; i++)
	{
		TileInfo *ti = &chunk->tiles[i];
		if (m_pPlayer->collider.Intersects(ti->tileGameObjectsByLayer[1].collider)) {
			m_pPlayer->systemPosition = prevPos;
		}
	}

	//somthing somethin playerChunk.y

}

void Game::GenerateDummyLevelChunks() {
	chunkss.resize(chunksSize * chunksSize);
	LevelGenerator lg(1276483);
	std::vector<int> generatedLevel = lg.Generate();
	m_pPlayer->systemPosition = DirectX::XMFLOAT2(lg.startx*32, lg.starty*32);
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

					int dungeonx = (i * 16) + k;
					int dungeony = (j * 16) + l;
					int tileType = generatedLevel[dungeonx + dungeony * lg.m_width];
					if (tileType == 1) {
						SpriteInfo si;

						si.textureKey = 1;
						si.sourceRect = new RECT();
						si.sourceRect->bottom = 64;
						si.sourceRect->right = 64;
						si.sourceRect->top = 0;
						si.sourceRect->left = 0;
						si.spriteIdx = DirectX::XMFLOAT2(0, 0);
						si.origion = DirectX::XMFLOAT2(0, 0);
						si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
						si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
						si.position = DirectX::XMFLOAT2(isox, isoy);
						ti.tileGameObjectsByLayer[0] = GameObject(si);
					}
					else {
						SpriteInfo si;
						si.textureKey = 2;
						si.sourceRect = new RECT();
						si.sourceRect->bottom = 128;
						si.sourceRect->right = 64;
						si.sourceRect->top = 0;
						si.sourceRect->left = 0;
						si.spriteIdx = DirectX::XMFLOAT2(0, 0);
						si.origion = DirectX::XMFLOAT2(0, 64+32);
						si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
						si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
						si.position = DirectX::XMFLOAT2(isox, isoy);
						ti.tileGameObjectsByLayer[1] = GameObject(si, Collider(DirectX::BoundingBox(DirectX::XMFLOAT3(ti.x + 32, ti.y + 32, 0), DirectX::XMFLOAT3(16.0f, 16.0f, 0))));
						
					}

					cd.tiles[k * 16 + l] = ti;
					//cd.tiles[l * 16 + k] = ti;
				}
			}
			chunkss[i * chunksSize + j] = cd;
		}
	}

}

