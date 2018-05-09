#pragma once
#include <string>
#include <DirectXMath.h>

//TODO Actually figure out all the things we need to draw and add it to this struct
struct SpriteInfo {
	std::string textureName;
	DirectX::XMFLOAT2 position;
	float scale;
	float rotation;
};
