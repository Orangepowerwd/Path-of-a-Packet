#include <iostream>
#include "raylib.h"
using namespace std;

int main() {

    InitWindow(800, 450, "Path-of-a-Packet");
    SetTargetFPS(60);
    string message = "PRESS ENTER TO CONTINUE";
    Color textColor = YELLOW;
    bool resizing = false;
    bool wordWrap = true; // Using this example to create text with rectangle bounds: https://www.raylib.com/examples/text/loader.html?name=text_rectangle_bounds
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);

        Rectangle textbox = { 0, 0, 270, 1080 };

        DrawRectangleRec(textbox, BLACK);
        DrawText(message.c_str(), 40, 40, 24, textColor);
        if (IsKeyDown(KEY_ENTER)) {
            message = "Welcome to the Path of a Packet";
            textColor = RED;
        }

        EndDrawing();
    }

    CloseWindow();
    cout << endl << endl << endl;
    cout << "more can happen in the terminal after the window is closed ..." << endl;

    return 0;
}
