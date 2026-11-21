#include "raylib.h"
#include "wall.h"

Wall::Wall(float x, float y, float width, float height){
  bounds = {x, y ,width, height};
}

void Wall::Draw(){
  DrawRectangleRec(bounds, DARKGRAY);
}

bool Wall::CheckCollision(Rectangle player){
  return CheckCollisionRecs(bounds, player);
}
