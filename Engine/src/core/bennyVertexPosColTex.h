#pragma once

#include <DirectXMath.h>

using namespace DirectX;
struct VertexPositionColorTexture
{
	XMFLOAT3 position;
	XMFLOAT4 color;
	XMFLOAT2 textureCoordinate;
};