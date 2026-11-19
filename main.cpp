#include <iostream>
#include "raylib.h"
#include "drawtextbox.h"
#include <fstream>
using namespace std;

//global variables

struct Wall {
    Rectangle bounds; //An object Wall consist of a Rectangle bounds.
};


Wall walls[] = { //Arrays of walls, in format a wall object with Rectangle(x, y, width, height, bounds.)
    {{270, 0, 530, 80}}, //LATER SAVE THIS TO A FILE NAMED LEVELS
    {{270, 370, 530, 80}},
    {{470, 80, 50, 100}},
    {{620, 270, 50, 100}},
    {{770, 80, 30, 130}}
};
// ChatGPT advised use of drawing an array of bounds for the 'maze' portion
Rectangle gameArea = {270, 0, 530, 450}; //Game area is on right starting at x=270 y=0 to x=800 y=450, width 530, height 450. This is where the maze will be drawn.
Rectangle textbox = { 0, 0, 270, 450 }; //Textbox is on left starting at x=0 y=0 to x=270 y=450, width 270, height 450. This is where the text will be drawn.
Rectangle startScene = {0, 0, 800, 450}; //Start scene is the entire window, starting at x=0 y=0 to x=800 y=450, width 800, height 450. This is where the start screen will be drawn.
string message; //Declares the variables to be used later
Color textColor; 
Font font;

int scene = 0; //Scene variable, used to determine scene to draw

void DrawScene() {
    BeginDrawing();
    ClearBackground(WHITE); //Clears the background to white for each frame
    if (scene == 0) {
        message = "Press ENTER to start the game"; //Message to be displayed on the start screen
        textColor = WHITE; //Text color is WHITE
        DrawRectangleRec(startScene, BLACK); //Start screen background is BLACK
        DrawTextBoxed(font, message, startScene, 20, 3, true, textColor); //Draws the message on the start screen
        if (IsKeyDown(KEY_ENTER)) { //If the user presses ENTER, the scene variable is set to 1,
            scene = 1;
        }
    }
    else {
        DrawRectangleRec(textbox, WHITE); //Textbox on the left background WHITE
        textColor = BLACK; //Text color is BLACK
        DrawRectangleRec(gameArea, BLACK); // everything must be offset by game area
        for (Wall wall : walls) {
            DrawRectangleRec(wall.bounds, DARKGRAY);
        }
        BeginScissorMode( // scissor-mode cuts away elements from specific dimensions https://www.raylib.com/examples/core/loader.html?name=core_scissor_test
            gameArea.x, //In short the goal is to prevent rendering outside of the game area
            gameArea.y,
            gameArea.width,
            gameArea.height
        );
        EndScissorMode();
        DrawTextBoxed(font, message, textbox, 20, 3, true, textColor);
        if (IsKeyDown(KEY_ENTER)) {
            message = "Welcome to the Path of a Packet";
            textColor = RED;
        }
    }

    EndDrawing();
}


int main() {

    InitWindow(800, 450, "Path-of-a-Packet"); //Initialize the application windows size and title
    SetTargetFPS(60);
    font = GetFontDefault();
    // bool resizing = false; 
    // bool wordWrap = true; 
    while (!WindowShouldClose()) { //Exit method, quits program on ESC or window close. This is also the start of program loop
        DrawScene(); //DrawScene is a function that draws the scene, it is called every frame.
    }

    CloseWindow();
    return 0;
}
