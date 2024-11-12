#pragma once
#include "ECS.h" 
#include "../Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
    Vector2D velocity;
    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;


    float x() const { return position.getX(); }
    float y() const { return position.getY(); }


    void setPosition(float x, float y) {
        position.setX(x);
        position.setY(y);
    }

    TransformComponent() {
        position.Zero();
    }

    TransformComponent(int sc) {
        position.setX(400);
        position.setY(320);
        scale = sc;
    }

    TransformComponent(float x, float y, int sc) {
        position.setX(x);
        position.setY(y);
        scale = sc;
    }

    TransformComponent(float x, float y, int h, int w, int sc) {
        position.setX(x);
        position.setY(y);
        height = h;
        width = w;
        scale = sc;
    }

    void init() override {
        velocity.Zero();
    }
	void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;

	}


};