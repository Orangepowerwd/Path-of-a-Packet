#include <iostream>
#include <string>
#include "raylib.h"
using namespace std;
#ifndef CheckPoint_H
#define CheckPoint_H


class CheckPoint {
public:
    Rectangle bounds;
    bool disappear;
    CheckPoint(float x, float y, bool disappear); //  constructor
    bool CheckCollision(Rectangle player); // (checkcollisionrec) collision boolean function that takes a player value
    void Draw();
};



#endif // CheckPoint_H