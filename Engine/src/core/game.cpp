#include "game.h"

Game::Game(DirectX::XMFLOAT2 targetResolution) {
	m_pCamera = new Camera(targetResolution);
	m_pPlayer = new Player();
	GenerateDummyLevel();
}
Game::~Game() {}

void Game::Update(float deltaTime, InputData* inputData) {
	
	//Previous position and colission here is just a test
	prevPos = m_pPlayer->systemPosition;
	playerTile.x = (int)m_pPlayer->systemPosition.x / 32;
	playerTile.y = (int)m_pPlayer->systemPosition.y / 32;
	m_pPlayer->Move(inputData, deltaTime);
	playerCollision();



	//m_pCamera->FollowCentered(m_pPlayer->m_SpriteInfo.position);
	m_pCamera->FollowCentered(m_pPlayer->spriteInfo.position);


	//DRAW THINGS. Reset draw count before hand.
	for (size_t i = 0; i < SPRITELAYERSCOUNT; i++)
	{
		spritesToDrawLayers[i].drawCount = 0;
	}

	DrawSurroundingLevelData();

}

void Game::playerCollision() {

	//Tiles are 64x64 so they are 32 apart from each other. 32 to the left + 32 to the right = 64
	//Figure out where the player is in tile position
	int startx = playerTile.x - 2;
	int endx = playerTile.x + 2;
	if (startx < 0) {
		startx = 0;
	}
	if (endx > currLevelData.width) {
		endx = currLevelData.width;
	}
	int starty = playerTile.y - 2;
	int endy = playerTile.y + 2;
	if (starty < 0) {
		starty = 0;
	}
	if (endy > currLevelData.height) {
		endy = currLevelData.height;
	}
	
	//TODO getsize call was slow. This needs to be a const var
	for (size_t y = starty; y < endy; y++)
	{
		for (size_t x = startx; x < endx; x++)
		{
			TileInfo *ti = &currLevelData.tiles[x + y * currLevelData.width];
			if (m_pPlayer->collider.Intersects(ti->tileGameObjectsByLayer[1].collider)) {
				m_pPlayer->systemPosition = prevPos;
			}
		}
	}

	//somthing somethin playerChunk.y

}

void Game::DrawSurroundingLevelData() {
	//Tiles are 64x64 so they are 32 apart from each other. 32 to the left + 32 to the right = 64
	//Do better math here figure out how many tiles are shown based on screen resolution or have the camera figure that out
	//Need to make a clamp function	
	int startx = playerTile.x - 20;
	int endx = playerTile.x + 20;
	if (startx < 0) {
		startx = 0;
	}
	if (endx > currLevelData.width) {
		endx = currLevelData.width;
	}
	int starty = playerTile.y - 20;
	int endy = playerTile.y + 20;
	if (starty < 0) {
		starty = 0;
	}
	if (endy > currLevelData.height) {
		endy = currLevelData.height;
	}
	bool playerDrawn = false;
	//We are drawing Y first to add depth  allow player to get behind things easier This may just be logical and not needed
	for (size_t y = starty; y < endy; y++)
	{
		for (size_t x = startx; x < endx; x++)
		{
			if (y == playerTile.y && x == playerTile.x) {
				m_pCamera->FilterSpriteForView(m_pPlayer->spriteInfo, spritesToDrawLayers[1].spritesToDraw, spritesToDrawLayers[1].drawCount);
				playerDrawn = true;
			}
			TileInfo *ti = &currLevelData.tiles[x + y * currLevelData.width];
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
void Game::GenerateDummyLevel() {
	LevelGenerator lg(12764183);
	currLevelData.rawTiles = lg.Generate();
	m_pPlayer->systemPosition = DirectX::XMFLOAT2(lg.startx * 32, lg.starty * 32);
	currLevelData.width = lg.m_width;
	currLevelData.height = lg.m_height;
	currLevelData.tiles.resize(currLevelData.width * currLevelData.height);
	for (size_t x = 0; x < currLevelData.width; x++)
	{
		for (size_t y = 0; y < currLevelData.height; y++)
		{
			TileInfo ti;
			ti.x = x * 32;
			ti.y = y * 32;
			float isox = ti.x - ti.y;
			float isoy = (ti.x + ti.y) / 2;
			int tileType = currLevelData.rawTiles[x + y * currLevelData.width];
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
				si.origion = DirectX::XMFLOAT2(0, 64 + 32);
				si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
				si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
				si.position = DirectX::XMFLOAT2(isox, isoy);
				ti.tileGameObjectsByLayer[1] = GameObject(si, Collider(DirectX::BoundingBox(DirectX::XMFLOAT3(ti.x + 32, ti.y + 32, 0), DirectX::XMFLOAT3(16.0f, 16.0f, 0))));
			}
			currLevelData.tiles[x + y * currLevelData.width] = ti;
		}
	}
}



