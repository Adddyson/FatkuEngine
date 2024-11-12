#pragma once
#include "../Src/Game.h"
#include "Ecs.h"
#include "Components.h"

class KeyboardController : public Component{
public:
	TransformComponent *transform;
    SpriteComponent* sprite;
	void init()override {
		transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
                // Vertical movement
            case SDLK_w:
            case SDLK_UP:
                transform->velocity.setY(-1);
                sprite->Play("Walk");
                break;
            case SDLK_s:
            case SDLK_DOWN:
                transform->velocity.setY(1);
                sprite->Play("Walk");
                break;

                // Horizontal movement
            case SDLK_a:
            case SDLK_LEFT:
                transform->velocity.setX(-1);
                sprite->Play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                transform->velocity.setX(1);
                sprite->Play("Walk");
                break;

            case SDLK_LSHIFT:
                transform->speed = 6;  // Sprint
                break;
            case SDLK_LCTRL:
                transform->speed = 1;  // Walk
                break;
            default:
                break;
			}

		}
        else if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
                if (transform->velocity.getY() < 0)
                    transform->velocity.setY(0);
                sprite->Play("Idle");
                break;

            case SDLK_s:
            case SDLK_DOWN:
                if (transform->velocity.getY() > 0)
                    transform->velocity.setY(0);
                sprite->Play("Idle");
                break;

            case SDLK_a:
            case SDLK_LEFT:
                if (transform->velocity.getX() < 0)
                    transform->velocity.setX(0);
                sprite->Play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                if (transform->velocity.getX() > 0)
                    transform->velocity.setX(0);
                sprite->Play("Idle");
                break;

            case SDLK_LSHIFT:
            case SDLK_LCTRL:
                transform->speed = 3;  // Reset to normal speed
                break;

            case SDLK_ESCAPE:
                Game::isRunning = false;
                break;
            default:
                break;
            }
        }
	}

};