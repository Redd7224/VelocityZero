#pragma once
#include <DirectXMath.h>
#include <vector>
#include "spriteInfo.h"

class Camera
{
public:
	Camera(DirectX::XMFLOAT2 targetResolution);
	~Camera();
	void Move(DirectX::XMFLOAT2 vel, float delta);
	void FollowCentered(DirectX::XMFLOAT2 position);
	void FilterSpritesForView(std::vector<SpriteInfo> &spritesToDraw);
	void FilterSpritesForView(std::vector<SpriteInfo> &spritesToDraw, SpriteInfo *spritesOut[], int &drawCount);
	void FilterSpriteForView(SpriteInfo &sprite, SpriteInfo *spritesOut[], int &drawCount);
private:
	DirectX::XMFLOAT4 m_viewport;
	DirectX::XMFLOAT2 m_targetResolution;
	DirectX::XMFLOAT2 m_buffer;


	void TranslateSpriteToScreenPosition(SpriteInfo &spriteInfo);


};
