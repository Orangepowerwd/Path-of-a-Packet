#ifndef WALL_H
#define WALL_H

#include "raylib.h"

class Wall {
public:
    Rectangle bounds; // rectangle made up of wall
    Wall(float x, float y, float width, float height); //  constructor
    void Draw(); // draw function (DrawRectangleRec)
    bool CheckCollision(Rectangle player); // (checkcollisionrec) collision boolean function that takes a player value
};

#endif
