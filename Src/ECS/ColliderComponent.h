#pragma once
#include "ECS.h"
#include <string>
#include "SDL.h"
#include "TransformComponent.h"
#include "../Game.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    std::string tag;
    SDL_Texture* tex;
    SDL_Rect srcR, destR;
    TransformComponent* transform;

    ColliderComponent() = default;

    // Changed to accept string by value instead of reference
    ColliderComponent(std::string t) : tag(std::move(t)) {
        collider = { 0, 0, 0, 0 };
    }

    // Changed to accept string by value instead of reference
    ColliderComponent(std::string t, int xpos, int ypos, int size) : tag(std::move(t)) {
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        tex = TextureManager::LoadTexture("assets/Collider.png");
        srcR = { 0,0,32,32 };
        destR = { collider.x,collider.y, collider.w, collider.h };
    }

    void update() override {
        if (tag != "terrain") {
            collider.x = static_cast<int>(transform->position.getX());
            collider.y = static_cast<int>(transform->position.getY());
            collider.w = static_cast<int>(transform->width * transform->scale);
            collider.h = static_cast<int>(transform->height * transform->scale);
        }
        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};