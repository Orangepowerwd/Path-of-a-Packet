#include "raylib.h"
#include "spawn.h"



Spawn::Spawn(float x, float y, bool disappear) {
    bounds.x = x;
    bounds.y = y;
    if (disappear) {
        bounds.width = 0;
        bounds.height = 0;
    } else {
        bounds.width = 20;
        bounds.height = 20;
    }
    this->disappear = disappear;
}

bool Spawn::CheckCollision(Rectangle player) {
    return CheckCollisionRecs(bounds, player);
}

void Spawn::Draw() {
    DrawRectangleRec(bounds, YELLOW);
}

