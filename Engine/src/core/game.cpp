#include "game.h"

Game::Game(DirectX::XMFLOAT2 targetResolution) {
	m_targetResolution = targetResolution;
	m_pCamera = new Camera(targetResolution);
	m_pPlayer = new Player();
	CreateLobbyLevel();
	srand(time(NULL));
}
Game::~Game() {}

void Game::Update(float deltaTime, InputData* inputData) {
	//Rset values
	for (size_t i = 0; i < SPRITELAYERSCOUNT; i++)
	{
		spritesToDrawLayers[i].drawCount = 0;
	}

	//Check if we are chanign level. Instead of returning we should have a state machine
	if (inputData->button4 > 0) {
		m_test.textureKey = 4;
		m_test.sourceRect.bottom = 600;
		m_test.sourceRect.right = 800;
		m_test.sourceRect.top = 0;
		m_test.sourceRect.left = 0;
		m_test.spriteIdx = DirectX::XMFLOAT2(0, 0);
		m_test.origion = DirectX::XMFLOAT2(0, 0);
		m_test.position = DirectX::XMFLOAT2(0, 0);
		m_pCamera->DrawSpriteNoMod(m_test, spritesToDrawLayers[1].spritesToDraw, spritesToDrawLayers[1].drawCount);
		GenerateDummyLevel();
		return;
	}

	prevPos = m_pPlayer->systemPosition;
	playerTile.x = (int)m_pPlayer->systemPosition.x / 64;
	playerTile.y = (int)m_pPlayer->systemPosition.y / 64;

	if (inputData->button1 > 0) {
		
		Collider* collider = new Collider(DirectX::BoundingBox());
		DirectX::XMFLOAT2 playerCollider = m_pPlayer->systemPosition;
		collider->boxCollider.Extents = DirectX::XMFLOAT3(32, 32, 0);

		switch (m_pPlayer->direction)
		{
		case 1:
			playerCollider.x += 1;
			playerCollider.y += 1;
			break;
		case 2:
			playerCollider.x += -1;
			playerCollider.y += -1;
			break;
		case 4:
			playerCollider.x += 1;
			playerCollider.y += -1;
			break;
		case 5:
			playerCollider.x += 1;
			playerCollider.y += 0;
			break;
		case 6:
			playerCollider.x += 0;
			playerCollider.y += -1;
			break;
		case 8:
			playerCollider.x += -1;
			playerCollider.y += 1;
			break;
		case 9:
			playerCollider.x += 0;
			playerCollider.y += 1;
			break;
		case 10:
			playerCollider.x += -1;
			playerCollider.y += 0;
			break;
		default:
			break;
		}

		collider->boxCollider.Center = DirectX::XMFLOAT3(playerCollider.x, playerCollider.y, 0);

		attackCollision(collider);
	}

	//Previous position and colission here is just a test
	m_pPlayer->Move(inputData, deltaTime);
	playerCollision();

	//m_pCamera->FollowCentered(m_pPlayer->m_SpriteInfo.position);
	m_pCamera->FollowCentered(m_pPlayer->spriteInfo.position);

	//DRAW THINGS.
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

void Game::attackCollision(Collider* collider){

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
			if (collider->Intersects(ti->tileGameObjectsByLayer[1].collider)) {
				char a = 'a';
			}
		}
	}

	//somthing somethin playerChunk.y

}

void Game::DrawSurroundingLevelData() {
	//Tiles are 64x64 so they are 32 apart from each other. 32 to the left + 32 to the right = 64
	//Do better math here figure out how many tiles are shown based on screen resolution or have the camera figure that out
	//Need to make a clamp function	
	//need to do this once when resultio is set
	int tileRangex = m_targetResolution.y / (tileSize / 2) ;
	int tileRangey = m_targetResolution.x / (tileSize / 2) ;
	int startx = playerTile.x - tileRangex;
	int endx = playerTile.x + tileRangex;
	if (startx < 0) {
		startx = 0;
	}
	if (endx > currLevelData.width) {
		endx = currLevelData.width;
	}
	int starty = playerTile.y - tileRangey;
	int endy = playerTile.y + tileRangey;
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
	LevelGenerator lg(rand() % 99999999);
	currLevelData.rawTiles = lg.Generate();
	//currLevelData.rawTiles = lg.GenerateLobby();
	m_pPlayer->systemPosition = DirectX::XMFLOAT2(lg.startx * tileSize/2, lg.starty * tileSize/2);
	currLevelData.width = lg.m_width;
	currLevelData.height = lg.m_height;
	CreateTileInfo();
}
void Game::CreateLobbyLevel() {
	LevelGenerator lg(rand() % 99999999);
	currLevelData.rawTiles = lg.GenerateLobby();
	m_pPlayer->systemPosition = DirectX::XMFLOAT2(lg.startx * tileSize/2, lg.starty * tileSize/2);
	currLevelData.width = lg.m_width;
	currLevelData.height = lg.m_height;
	CreateTileInfo();

	//Hardcoded doodad to test
	int x = lg.startx * tileSize / 2;
	int y = (lg.starty - 4) * tileSize / 2;
	float isox = x - y;
	float isoy = (x + y) / 2;
	SpriteInfo si;
	si.textureKey = 6;
	si.sourceRect.bottom = 128;
	si.sourceRect.right = 256;
	si.sourceRect.top = 0;
	si.sourceRect.left = 0;
	si.spriteIdx = DirectX::XMFLOAT2(0, 0);
	si.origion = DirectX::XMFLOAT2(128, 64);
	si.systemPosition = DirectX::XMFLOAT2(x, y);
	si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
	si.position = DirectX::XMFLOAT2(isox, isoy);
	currLevelData.tiles[lg.startx + (lg.starty - 4) * currLevelData.width].tileGameObjectsByLayer[1] = GameObject(si, 
		Collider(DirectX::BoundingBox(DirectX::XMFLOAT3(x + 32, y + 64 , 0), DirectX::XMFLOAT3(64.0f, 16.0f, 0)))
	);


}
void Game::CreateTileInfo() {
	currLevelData.tiles.clear();
	currLevelData.tiles.resize(currLevelData.width * currLevelData.height);
	for (size_t x = 0; x < currLevelData.width; x++)
	{
		for (size_t y = 0; y < currLevelData.height; y++)
		{
			TileInfo ti;
			ti.x = x * tileSize/2;
			ti.y = y * tileSize/2;
			float isox = ti.x - ti.y;
			float isoy = (ti.x + ti.y) / 2;
			int tileType = currLevelData.rawTiles[x + y * currLevelData.width];
			if (tileType == 1) {
				SpriteInfo si;
				si.textureKey = 5;
				si.sourceRect.bottom = tileSize;
				si.sourceRect.right = tileSize;
				si.sourceRect.top = 0;
				si.sourceRect.left = 0;
				si.spriteIdx = DirectX::XMFLOAT2(0, 0);
				si.origion = DirectX::XMFLOAT2(0, 0);
				si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
				si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
				si.position = DirectX::XMFLOAT2(isox, isoy);
				ti.tileGameObjectsByLayer[0] = GameObject(si);
			}
			else if (tileType == 2) {
				SpriteInfo si;
				si.textureKey = 2;
				si.sourceRect.bottom = 128;
				si.sourceRect.right = 64;
				si.sourceRect.top = 0;
				si.sourceRect.left = 0;
				si.spriteIdx = DirectX::XMFLOAT2(0, 0);
				si.origion = DirectX::XMFLOAT2(0, 64 + 32);
				si.systemPosition = DirectX::XMFLOAT2(ti.x, ti.y);
				si.isoPosition = DirectX::XMFLOAT2(isox, isoy);
				si.position = DirectX::XMFLOAT2(isox, isoy);
				ti.tileGameObjectsByLayer[1] = GameObject(si, Collider(DirectX::BoundingBox(DirectX::XMFLOAT3(ti.x + 32, ti.y + 32, 0), DirectX::XMFLOAT3(16.0f, 16.0f, 0))));

			}
			else {
				SpriteInfo si;
				ti.tileGameObjectsByLayer[1] = GameObject(si, Collider(DirectX::BoundingBox(DirectX::XMFLOAT3(ti.x + 64, ti.y + 32, 0), DirectX::XMFLOAT3(32.0f, 32.0f, 0))));
			}
			currLevelData.tiles[x + y * currLevelData.width] = ti;
		}
	}
}



