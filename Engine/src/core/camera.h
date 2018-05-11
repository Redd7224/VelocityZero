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
private:
	DirectX::XMFLOAT4 m_viewport;
	DirectX::XMFLOAT2 m_targetResolution;
	void TranslateSpriteToScreenPosition(SpriteInfo &spriteInfo);


};
