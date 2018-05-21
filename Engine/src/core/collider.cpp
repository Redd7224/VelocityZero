#include "collider.h"

Collider::Collider(DirectX::BoundingBox collider) {
	type = Box;
	boxCollider = collider;
}
Collider::Collider(DirectX::BoundingSphere collider) {
	type = Sphere;
	sphereCollider = collider;
}
Collider::Collider() {
	type = None;
}
Collider::~Collider() {}
bool Collider::Intersects(DirectX::BoundingBox other) {
	bool result = false;
	switch (type)
	{
	case None:
		break;
	case Sphere:
		result = sphereCollider.Intersects(other);
		break;
	case Box:
		result = boxCollider.Intersects(other);
		break;
	default:
		break;
	}
	return result;
}

bool Collider::Intersects(DirectX::BoundingSphere other) {
	bool result = false;
	switch (type)
	{
	case None:
		break;
	case Sphere:
		result = sphereCollider.Intersects(other);
		break;
	case Box:
		result = boxCollider.Intersects(other);
		break;
	default:
		break;
	}
	return result;
}
bool Collider::Intersects(Collider other) {
	bool result = false;
	switch (other.type)
	{
	case None:
		break;
	case Sphere:
		result = Intersects(other.sphereCollider);
		break;
	case Box:
		result = Intersects(other.boxCollider);
		break;
	default:
		break;
	}
	return result;
}
