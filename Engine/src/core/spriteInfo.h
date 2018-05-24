#pragma once
#include "pch.h"

//TODO Actually figure out all the things we need to draw and add it to this struct
struct SpriteInfo {
	int textureKey = -1;
	DirectX::BoundingSphere collider;
	//TODO move SystemPosition and IsoPosition into a different struct/class. These are not part of the sprite but part of the system
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 isoPosition;
	DirectX::XMFLOAT2 systemPosition;
	RECT sourceRect;
	float scale = 1;
	float rotation;
	bool isHoizontalSheet;
	DirectX::XMFLOAT2 spriteSize;
	DirectX::XMFLOAT2 spriteIdx = DirectX::XMFLOAT2(-1,-1);
	DirectX::XMFLOAT2 origion;
	void CalcSourceRECT() {
		if (isHoizontalSheet) {
			sourceRect.top = 0;
			sourceRect.bottom = spriteSize.y;
			sourceRect.left = spriteIdx.x * spriteSize.x;
			sourceRect.right = (spriteIdx.x + 1) * spriteSize.x;
		}
	}
};
