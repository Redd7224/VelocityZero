#pragma once
#include "pch.h";
//Maybe this should be a class


enum ColliderType
{
	None,
	Sphere,
	Box
};

class Collider
{
public:
	ColliderType type;
	DirectX::BoundingBox boxCollider;
	DirectX::BoundingSphere sphereCollider;
	bool Intersects(Collider other);
	bool Intersects(DirectX::BoundingBox other);
	bool Intersects(DirectX::BoundingSphere other);
	Collider(DirectX::BoundingBox collider);
	Collider(DirectX::BoundingSphere collider);
	Collider();
	~Collider();

private:

};

