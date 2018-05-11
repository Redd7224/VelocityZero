#pragma once
#include <string>
#include "pch.h"

//TODO Actually figure out all the things we need to draw and add it to this struct
struct SpriteInfo {
	std::string textureName;
	DirectX::XMFLOAT2 position;
	RECT* sourceRect;
	float scale;
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
