#include <iostream>
#include <string>
#include "raylib.h"
using namespace std;
#ifndef SPAWN_H
#define SPAWN_H


class Spawn {
public:
    Rectangle bounds;
    bool disappear;
    Spawn(float x, float y, bool disappear); //  constructor
    bool CheckCollision(Rectangle player); // (checkcollisionrec) collision boolean function that takes a player value
    void Draw();
};



#endif // SPAWN_H