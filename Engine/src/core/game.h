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
	void GenerateDummyLevel();
	void GenerateDummyLevel2();
	void GenerateDummyLevelChunks();
	void drawChunkData(int x, int y);
	Player* m_pPlayer;
	std::vector<SpriteInfo> m_currentLevelSpriteInfo;
	std::vector<ChunkData> chunkss;

	Camera* m_pCamera;

	const int chunksSize = 32;
};
