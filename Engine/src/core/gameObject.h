#pragma once
#include "pch.h"
#include "spriteInfo.h"
#include "collider.h"
class GameObject
{
public:
	GameObject();
	GameObject(SpriteInfo si);
	GameObject(SpriteInfo si, Collider co);

	~GameObject();

	SpriteInfo spriteInfo;
	DirectX::XMFLOAT2 systemPosition;
	DirectX::XMFLOAT2 isoPosition;

	Collider collider;
private:

};