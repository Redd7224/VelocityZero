#include "gameObject.h"


GameObject::GameObject() {}
GameObject::~GameObject() {}
GameObject::GameObject(SpriteInfo si) {
	spriteInfo = si;
	systemPosition = si.systemPosition;
	isoPosition = si.isoPosition;
	collider = Collider();
}
GameObject::GameObject(SpriteInfo si, Collider co) {
	spriteInfo = si;
	systemPosition = si.systemPosition;
	isoPosition = si.isoPosition;
	collider = co;

}