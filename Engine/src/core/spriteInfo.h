#pragma once
#include <string>
#include "pch.h"

//TODO Actually figure out all the things we need to draw and add it to this struct
struct SpriteInfo {
	std::string textureName;
	//TODO move SystemPosition and IsoPosition into a different struct/class. These are not part of the sprite but part of the system
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 isoPosition;
	DirectX::XMFLOAT2 systemPosition;
	RECT* sourceRect;
	float scale = 1;
	float rotation;
	bool isHoizontalSheet;
	DirectX::XMFLOAT2 spriteSize;
	DirectX::XMFLOAT2 spriteIdx;
	void CalcSourceRECT() {
		RECT* rt = new RECT();
		if (isHoizontalSheet) {
			rt->top = 0;
			rt->bottom = spriteSize.y;
			rt->left = spriteIdx.x * spriteSize.x;
			rt->right = (spriteIdx.x + 1) * spriteSize.x;
		}
		sourceRect = rt;
	}
};
