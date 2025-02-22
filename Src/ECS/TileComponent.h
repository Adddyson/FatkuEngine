#pragma once

#include "ECS.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Vector2D.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
		}
	}
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path) {
		texture = TextureManager::LoadTexture(path);
		if (!texture) {
			std::cout << "Failed to load texture: " << path << std::endl;
			return;
		}

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = tsize*tscale;
	}
	void update() override {
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};