#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
    if (
        recA.x + recA.w >= recB.x &&    // Right edge of A >= Left edge of B
        recB.x + recB.w >= recA.x &&    // Right edge of B >= Left edge of A
        recA.y + recA.h >= recB.y &&    // Bottom edge of A >= Top edge of B
        recB.y + recB.h >= recA.y       // Bottom edge of B >= Top edge of A
        ) {
        return true;
    }
    return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
    if (AABB(colA.collider, colB.collider)) {
        //std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }
    else {
        return false;
    }
}