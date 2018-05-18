#pragma once
#include <vector>
#include <array>
#include <DirectXMath.h>

#include "spriteInfo.h"
#include "camera.h"
#include "inputData.h"
#include "player.h"
#include "chunkData.h"
#include "tileInfo.h"
#include "levelGenerator.h"


class Game
{
public:
	Game(DirectX::XMFLOAT2 targetResolution);
	~Game();
	void Update(float deltaTime,InputData* inputData);
	std::vector<SpriteInfo> m_spritesToDraw;

	SpriteInfo *spritesToDraw[10000];
	int drawCount = 0;

private:
	void GenerateDummyLevelChunks();
	void drawChunkData(int x, int y);
	void drawChunkDataWithPlayer(int x, int y);

	Player* m_pPlayer;
	std::vector<SpriteInfo> m_currentLevelSpriteInfo;
	std::vector<ChunkData> chunkss;
	SpriteInfo m_test;
	Camera* m_pCamera;

	const int chunksSize = 32;
};
