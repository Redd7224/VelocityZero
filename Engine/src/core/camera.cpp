#include "camera.h"

//TODO handle scaling. Have fixed resolutions per aspect ratio? and scale accordingly
Camera::Camera(DirectX::XMFLOAT2 targetResolution) {
	m_targetResolution = targetResolution;
	m_viewport = DirectX::XMFLOAT4(0, 0, targetResolution.x, targetResolution.y);
	m_buffer = DirectX::XMFLOAT2(targetResolution.x * .1, targetResolution.y * .1);
}
Camera::~Camera() {}

//TODO handle Camera movement
void Camera::Move(DirectX::XMFLOAT2 vel, float delta) {
	m_viewport.x += vel.x * delta;
	m_viewport.z += vel.x * delta;
	m_viewport.y += vel.y * delta;
	m_viewport.w += vel.y * delta;
}

void Camera::FollowCentered(DirectX::XMFLOAT2 position) {
	m_viewport = DirectX::XMFLOAT4(position.x - (m_targetResolution.x /2), position.y - (m_targetResolution.y / 2), position.x + (m_targetResolution.x / 2), position.y + (m_targetResolution.y / 2));
}
void Camera::FilterSpriteForView(SpriteInfo &sprite, SpriteInfo *spritesOut[], int &drawCount) {
	SpriteInfo* currSpriteInfo = &sprite;
	if (currSpriteInfo->spriteIdx.x != -1) {
		//check if sprite is in viewport
		bool isInViewport = false;
		//TODO factor in sprite size?

		//TODO refactor, this is structed this way to easily debug
		bool isXInViewPort = false;
		bool isYInViewPort = false;
		if ((currSpriteInfo->isoPosition.x + m_buffer.x >= m_viewport.x && currSpriteInfo->isoPosition.x - m_buffer.x <= m_viewport.z)) {
			isXInViewPort = true;
		}
		if ((currSpriteInfo->isoPosition.y + m_buffer.y >= m_viewport.y && currSpriteInfo->isoPosition.y - m_buffer.y <= m_viewport.w)) {
			isYInViewPort = true;
		}
		if (isXInViewPort && isYInViewPort) {
			isInViewport = true;
		}
		if (isInViewport) {
			currSpriteInfo->position.x = currSpriteInfo->isoPosition.x + (-1 * m_viewport.x);
			currSpriteInfo->position.y = currSpriteInfo->isoPosition.y + (-1 * m_viewport.y);
			spritesOut[drawCount] = currSpriteInfo;
			drawCount++;
		}
	}
}

void Camera::DrawSpriteNoMod(SpriteInfo &sprite, SpriteInfo *spritesOut[], int &drawCount) {
	SpriteInfo* currSpriteInfo = &sprite;
	spritesOut[drawCount] = currSpriteInfo;
	drawCount++;
}

void Camera::TranslateSpriteToScreenPosition(SpriteInfo &spriteInfo) {
	
	spriteInfo.position.x += -1 * m_viewport.x;
	spriteInfo.position.y += -1 * m_viewport.y;

}
