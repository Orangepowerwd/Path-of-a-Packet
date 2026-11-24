#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "wall.h"
#include <vector>

using namespace std;

class Player {
private:
    Rectangle rec;
    Vector2 speed;
    Color color;

public:
    Player();
    Rectangle GetRec();
    void Move(Rectangle gameArea); // takes walls and game area, moves character and checks collision

    void Draw(); // draw player
    void Reset();
};
// adapted from raylib asteroid game: https://github.com/raysan5/raylib-games/blob/master/classics/src/asteroids.c

#endif
