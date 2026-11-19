

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player{
    Rectangle rec;
    Vector2 speed;
    Color color;
} Player;

// typedef renames a specific type, and struct is a class in which everything is public by default (which is fine in this instance)
// from raylib asteroid game: https://github.com/raysan5/raylib-games/blob/master/classics/src/asteroids.c

#endif
