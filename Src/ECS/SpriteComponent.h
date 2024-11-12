#pragma once
#include "SDL.h"
#include "../TextureManager.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "Animation.h"
#include <map>

class TransformComponent;
class Entity;

class SpriteComponent : public Component {
private:
    TransformComponent* transform{ nullptr };  // Initialize to nullptr
    SDL_Texture* texture{ nullptr };
    SDL_Rect srcRect;       // Initialize with values
    SDL_Rect destRect;

    // Optional: Store size for flexibility
    int srcW{ 32 };
    int srcH{ 32 };
    int destW{ 64 };
    int destH{ 64 };
    bool animated = false;
    int frames = 0;
    int speed = 100;//this is the delay between frames

public:

    int animIndex = 0;

    std::map<const char*, Animation> animations;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    // Constructor with path
    explicit SpriteComponent(const char* path) {  // Added explicit
        setTex(path);
    }

    explicit SpriteComponent(const char* path, bool isAnimated) {  // Added explicit
        animated = isAnimated;

        Animation idle = Animation(0, 4, 100);
        Animation walk = Animation(1, 8, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        Play("Idle");
        setTex(path);
    }

    virtual ~SpriteComponent() {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    // Separate texture loading for better error handling
    bool setTex(const char* path) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
        texture = TextureManager::LoadTexture(path);
        return texture != nullptr;
    }

    void setSize(int width, int height) {
        destRect.w = width;
        destRect.h = height;
    }

    void init() override {
        // Check if entity exists and has PositionComponent
        if (!entity) {
            throw std::runtime_error("Entity not set for SpriteComponent");
        }

        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;

    }

    void update() override {
        if (animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        srcRect.y = animIndex * transform->height;

        if (transform) {  // Safety check
            destRect.x = static_cast<int>(transform->position.getX()) - Game::camera.x;
            destRect.y = static_cast<int>(transform->position.getY()) - Game::camera.y;
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }
    }

    void draw() override {
        if (texture) {  // Safety check
            TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
        }
    }

    // Getters and setters for more control
    [[nodiscard]] SDL_Rect getDestRect() const { return destRect; }
    [[nodiscard]] SDL_Rect getSrcRect() const { return srcRect; }
    void setSrcRect(int x, int y, int w, int h) {
        srcRect = { x, y, w, h };
    }
    
    void Play(const char* animName) {

        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};