#include <iostream>
#include "raylib.h"
#include "drawtextbox.h"
#include <fstream>
#include <string>
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






Rectangle MessageCenterProcessor(Rectangle canva, string message, int x_shift, int y_shift, int width_shift, int height_shift) { //Returns the center of a rectangle as a Vector2 object, which is used to position text in the center of a rectangle.
    float textWidth = MeasureTextEx(font, message.c_str(), 20, 3).x + width_shift; 
    float textHeight = MeasureTextEx(font, message.c_str(), 20, 3).y + height_shift;
    float centerX = canva.x + (canva.width - textWidth) / 2 + x_shift; //Returns a Vector2 object with the x and y position of the center of the rectangle.
    float centerY = canva.y + (canva.height - textHeight) / 2 + y_shift;
    return Rectangle({centerX, centerY, textWidth, textHeight}); //Returns a Vector2 object with the x and y position of the center of the rectangle.
}

void DrawScene() {
    BeginDrawing();
    ClearBackground(WHITE); //Clears the background to white for each frame
    if (scene == 0) {
        //Display Text
        message = "Welcome to the Path of a Packet"; //Message to be displayed on the start screen
        textColor = WHITE; //Text color is WHITE
        DrawRectangleRec(startScene, BLACK); //Start screen background is BLACK
        Rectangle messageBox = MessageCenterProcessor(startScene, message, 0, -50, 0, 0); //Calculates the center of the start screen rectangle to position the message in the center
        DrawTextBoxed(font, message, messageBox, 20, 3, true, textColor); //Draws the message on the start screen

        //Display Button
        string buttonMessage = "Start Game"; //Message to be displayed on the button
        Rectangle button = MessageCenterProcessor(startScene, buttonMessage, 0, 30, 20, 0);
        Rectangle buttonText = MessageCenterProcessor(startScene, buttonMessage, 0, 30, 0, 0); 
        DrawRectangleRec(button, DARKGRAY); //Draws the button on the start screen
        DrawTextBoxed(font, buttonMessage, buttonText, 20, 3, true, textColor); //Draws the button text on the start screen
        Vector2 mousePosition = GetMousePosition(); //Gets the mouse position
        if (CheckCollisionPointRec(mousePosition, button)) { //Checks if the mouse is over the button
            DrawRectangleRec(button, GRAY); //If the mouse is over the button, draw the button in a lighter color
            DrawTextBoxed(font, buttonMessage, buttonText, 20, 3, true, textColor); //Draws the button text on the start screen
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //If the mouse is clicked, change the scene to 1
                scene = 1;
            } 
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
    }

    switch (scene) { //Switch statement to determine which scene to draw
        case 1: {
            ifstream file("./texts/readings.txt"); //Opens the message.txt file to read the message to be displayed in the textbox
            string message; //String to hold the message to be displayed in the textbox
            if (file.is_open()) {
                getline(file, message);
                file.close();
            }
            cout << "Message: " << message << endl; //Prints the message to the console for debugging purposes
            break;
        }

        default: {
            break;
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
