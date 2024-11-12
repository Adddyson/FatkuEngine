#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x,int y) {

	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
}
GameObject::~GameObject() {
	SDL_DestroyTexture(objTexture);  // Clean up the texture
}
void GameObject::Update() {

	xpos++;
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h*2;
	destRect.w = srcRect.w*2;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}