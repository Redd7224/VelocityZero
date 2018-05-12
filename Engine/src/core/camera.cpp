#include "camera.h"

//TODO handle scaling. Have fixed resolutions per aspect ratio? and scale accordingly
Camera::Camera(DirectX::XMFLOAT2 targetResolution) {
	m_targetResolution = targetResolution;
	m_viewport = DirectX::XMFLOAT4(0, 0, targetResolution.x, targetResolution.y);
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
void Camera::FilterSpritesForView(std::vector<SpriteInfo> &spritesToDraw) {
	if (!spritesToDraw.empty()) {
		//Calculate a buffer so  likelyhood is low we stop drawing a sprite while part of it is visible. 
		float xBuffer = m_targetResolution.x * .2;
		float yBuffer = m_targetResolution.y * .2;
		for (int i = spritesToDraw.size() - 1; i >= 0; i--) {
			SpriteInfo currSpriteInfo = spritesToDraw.at(i);
			//check if sprite is in viewport
			bool isInViewport = false;
			//TODO factor in sprite size?

			//TODO refactor, this is structed this way to easily debug
			bool isXInViewPort = false;
			bool isYInViewPort = false;
			if ((currSpriteInfo.position.x + xBuffer >= m_viewport.x && currSpriteInfo.position.x - xBuffer <= m_viewport.z)) {
				isXInViewPort = true;
			}
			if ((currSpriteInfo.position.y + yBuffer >= m_viewport.y && currSpriteInfo.position.y <= m_viewport.w)) {
				isYInViewPort = true;
			}
			if (isXInViewPort && isYInViewPort) {
				isInViewport = true;
			}
			if (isInViewport) {
				TranslateSpriteToScreenPosition(spritesToDraw.at(i));
			}
			else {
				int foox = 1; 
				//Erase is too slow, we need to use a fixed array or pass back fixed array Instead of removing from a vector
				//spritesToDraw.erase(spritesToDraw.begin() + i);
			}

		}
	}
}

void Camera::FilterSpritesForView(std::vector<SpriteInfo> &spritesToDraw, SpriteInfo *spritesOut[], int &drawCount) {
	if (!spritesToDraw.empty()) {
		//Calculate a buffer so  likelyhood is low we stop drawing a sprite while part of it is visible. 
		float xBuffer = m_targetResolution.x * .2;
		float yBuffer = m_targetResolution.y * .2;
		/*
		for (auto it = spritesToDraw.begin(); it != spritesToDraw.end(); ++it)
		{
			SpriteInfo* currSpriteInfo = it._Ptr;
			*/
		for (int i = 0; i < spritesToDraw.size(); i++) 
		{
			SpriteInfo* currSpriteInfo = &spritesToDraw[i];


			//check if sprite is in viewport
			bool isInViewport = false;
			//TODO factor in sprite size?

			//TODO refactor, this is structed this way to easily debug
			bool isXInViewPort = false;
			bool isYInViewPort = false;
			if ((currSpriteInfo->isoPosition.x + xBuffer >= m_viewport.x && currSpriteInfo->isoPosition.x - xBuffer <= m_viewport.z)) {
				isXInViewPort = true;
			}
			if ((currSpriteInfo->isoPosition.y + yBuffer >= m_viewport.y && currSpriteInfo->isoPosition.y <= m_viewport.w)) {
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
}


void Camera::FilterSpriteForView(SpriteInfo &sprite, SpriteInfo *spritesOut[], int &drawCount) {
	SpriteInfo* currSpriteInfo = &sprite;
	currSpriteInfo->position.x = currSpriteInfo->isoPosition.x + (-1 * m_viewport.x);
	currSpriteInfo->position.y = currSpriteInfo->isoPosition.y + (-1 * m_viewport.y);
	spritesOut[drawCount] = currSpriteInfo;
	drawCount++;
}


void Camera::TranslateSpriteToScreenPosition(SpriteInfo &spriteInfo) {
	
	spriteInfo.position.x += -1 * m_viewport.x;
	spriteInfo.position.y += -1 * m_viewport.y;

}
