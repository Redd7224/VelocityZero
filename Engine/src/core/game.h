#pragma once
#include <vector>
#include <array>
#include <DirectXMath.h>
#include <time.h>
#include "spriteInfo.h"
#include "camera.h"
#include "inputData.h"
#include "player.h"
#include "chunkData.h"
#include "tileInfo.h"
#include "levelGenerator.h"
#include "spritesToDraw.h"
#include "LevelData.h"
#define SPRITELAYERSCOUNT 5 

class Game
{
public:
	Game(DirectX::XMFLOAT2 targetResolution);
	~Game();
	void Update(float deltaTime,InputData* inputData);
	std::vector<SpriteInfo> m_spritesToDraw;

	SpritesToDraw spritesToDrawLayers[SPRITELAYERSCOUNT];

private:
	void GenerateDummyLevel();
	void CreateLobbyLevel();
	void CreateTileInfo();
	void DrawSurroundingLevelData();
	void playerCollision();
	void attackCollision(Collider*);

	Player* m_pPlayer;
	//used for player col, doesnt belong here
	DirectX::XMFLOAT2 prevPos;
	DirectX::XMFLOAT2 playerTile;
	std::vector<SpriteInfo> m_currentLevelSpriteInfo;
	std::vector<ChunkData> chunkss;
	SpriteInfo m_test;
	Camera* m_pCamera;
	LevelData currLevelData;
	const int chunksSize = 32;
	DirectX::XMFLOAT2 m_targetResolution;
	
	const int tileSize = 128;

};
