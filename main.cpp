#include <iostream>
#include "raylib.h"
#include "drawtextbox.h"
using namespace std;


int main() {

    InitWindow(800, 450, "Path-of-a-Packet");
    SetTargetFPS(60);
    string message = "PRESS ENTER TO CONTINUE";
    Color textColor = YELLOW;
    bool resizing = false;
    bool wordWrap = true;
    Font font = GetFontDefault();
    struct Wall {
        Rectangle bounds;
    };

    Wall walls[] = {
        {{270, 0, 530, 80}},
        {{270, 370, 530, 80}},
        {{470, 80, 50, 100}},
        {{620, 270, 50, 100}},
        {{770, 80, 30, 130}}
    };// ChatGPT advised use of drawing an array of bounds for the 'maze' portion
    Rectangle gameArea = {270, 0, 530, 450};
    Rectangle textbox = { 0, 0, 270, 450 };
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleRec(textbox, DARKBLUE);
        DrawRectangleRec(gameArea, BLACK); // everything must be offset by game area
        for (Wall wall : walls) {
            DrawRectangleRec(wall.bounds, DARKGRAY);
        }
        BeginScissorMode( // scissor-mode cuts away elements from specific dimensions https://www.raylib.com/examples/core/loader.html?name=core_scissor_test
          gameArea.x,
          gameArea.y,
          gameArea.width,
          gameArea.height
        );
        EndScissorMode();
        DrawTextBoxed(font, message, textbox, 20, 3, wordWrap, textColor);
        if (IsKeyDown(KEY_ENTER)) {
            message = "Welcome to the Path of a Packet";
            textColor = RED;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
