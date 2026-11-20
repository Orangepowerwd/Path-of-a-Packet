#include <iostream>
#include "raylib.h"
#include "drawtextbox.h"
#include "player.h"
#include <fstream>
#include <string>
using namespace std;

//global variables

struct Wall {
    Rectangle bounds; //An object Wall consist of a Rectangle bounds.
};

Player player = { 0 };

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







Rectangle MessageCenterProcessor(Rectangle canva, string message, int font_size, int x_shift, int y_shift, int width_shift, int height_shift) { //Returns the center of a rectangle as a Vector2 object, which is used to position text in the center of a rectangle.]
    float textWidth = MeasureTextEx(font, message.c_str(), font_size, 3).x + width_shift;
    float textHeight = MeasureTextEx(font, message.c_str(), font_size, 3).y + height_shift;
    float centerX = canva.x + (canva.width - textWidth) / 2 + x_shift; //Returns a Vector2 object with the x and y position of the center of the rectangle.
    float centerY = canva.y + (canva.height - textHeight) / 2 + y_shift;

    //Secure the shifting of text within drawing canvas.
    if (centerX < canva.x) {
        centerX = canva.x;
    }
    else if (centerX + textWidth > canva.x + canva.width) {
        centerX = canva.x + canva.width - textWidth;
    }

    // Check vertical boundaries.
    if (centerY < canva.y) {
        centerY = canva.y;
    }
    else if (centerY + textHeight > canva.y + canva.height) {
        centerY = canva.y + canva.height - textHeight;
    }
    return Rectangle({centerX, centerY, textWidth, textHeight}); //Returns a Vector2 object with the x and y position of the center of the rectangle.
}

//Reads the levelx.txt from texts to diaplay reading on the left side.
void ReadTextFile(string filename, Rectangle canva, Color textColor) { //Reads the message.txt file to display the message in the textbox
    ifstream file(filename); //Opens the message.txt file to read the message to be displayed in the textbox
        int lines;
        string message; //String to hold the message to be displayed in the textbox
        if (file.is_open()) { //It has to open, else repo is missing the file :(
            file >> lines; //Reads the first line of the file, which is the number of lines in the file
            file.ignore(); //Ignores the first line of the file, which is the number of lines in the file
            getline(file, message); //Reads the second line of the file, which is the message to be displayed in the textbox
            Rectangle messageBox = MessageCenterProcessor(canva, message, 20, 0, 0, 0, 400); //Calculates the center of the textbox rectangle to position the message in the center
            DrawTextBoxed(font, message, messageBox, 20, 3, true, textColor); //Draws the message in the textbox
            float height = MeasureTextEx(font, message.c_str(), 20, 3).y + 30; //Calculates the height of the message to be displayed in the textbox
            for (int i = 1; i < lines; i++) { //Loops through the number of lines in the file
                getline(file, message); //Reads the current line of the file
                messageBox = {canva.x + 10, height, canva.width - 10, messageBox.height}; //Calculates the position of the message to be displayed in the textbox
                DrawTextBoxed(font, message, messageBox, 20, 3, true, textColor); //Draws the message in the textbox
                height += MeasureTextEx(font, message.c_str(), 20, 3).y; //Calculates the height of the message to be displayed in the textbox
            }
            file.close();
        }
    }

void NextButton() {
    string text = "Next"; //Message to be displayed on the button
    Rectangle button = MessageCenterProcessor(textbox, text, 40, 0, 200, 0, 0); //Calculates the center of the textbox rectangle to position the button in the center
    DrawRectangleRec(button, GREEN); //Draws the button on the screen
    Rectangle buttonText = MessageCenterProcessor(textbox, text, 40, 10, 200, 0, 0); //Calculates the center of the textbox rectangle to position the button text in the center
    DrawTextBoxed(font, text, buttonText, 30, 3, true, WHITE); //Draws the button text on the screen
    Vector2 mousePosition = GetMousePosition(); //Gets the mouse position
    if (CheckCollisionPointRec(mousePosition, button)) { //Checks if the mouse is over the button
        DrawRectangleRec(button, DARKGREEN); //If the mouse is over the button, draw the button in a darker color
        DrawTextBoxed(font, text, buttonText, 30, 3, true, WHITE); //Draws the button text on the screen
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //If the mouse is clicked, change the scene to 2
            scene ++; //Increment the scene variable to move to the next scene
        }
    }
}
void InitPlayer(){
  player.rec.x =  300;
  player.rec.y = 50;
  player.rec.width = 20;
  player.rec.height = 20;
  // initializes the "rectangle" of player, including position
  player.speed.x = 5;
  player.speed.y = 5;
  // Initializes player speed based on x and y coordinates using RayLib's Vector2
  player.color = GREEN;
  if (IsKeyDown(KEY_RIGHT)) player.rec.x += player.speed.x;
  if (IsKeyDown(KEY_LEFT)) player.rec.x -= player.speed.x;
  if (IsKeyDown(KEY_UP)) player.rec.y -= player.speed.y;
  if (IsKeyDown(KEY_DOWN)) player.rec.y += player.speed.y;
}
void DrawScene() {
    BeginDrawing();
    ClearBackground(WHITE); //Clears the background to white for each frame
    if (scene == 0) { //Startig screen has a different format
        //Display Text
        message = "Welcome to the Path of a Packet"; //Message to be displayed on the start screen
        textColor = WHITE; //Text color is WHITE
        DrawRectangleRec(startScene, BLACK); //Start screen background is BLACK
        Rectangle messageBox = MessageCenterProcessor(startScene, message, 20, 0, -50, 0, 0); //Calculates the center of the start screen rectangle to position the message in the center
        DrawTextBoxed(font, message, messageBox, 20, 3, true, textColor); //Draws the message on the start screen

        //Display Button
        string buttonMessage = "Start Game"; //Message to be displayed on the button
        Rectangle button = MessageCenterProcessor(startScene, buttonMessage, 20, 0, 30, 20, 0);
        Rectangle buttonText = MessageCenterProcessor(startScene, buttonMessage, 20, 0, 30, 0, 0);
        DrawRectangleRec(button, DARKGRAY); //Draws the button on the start screen
        DrawTextBoxed(font, buttonMessage, buttonText, 20, 3, true, textColor); //Draws the button text on the start screen
        Vector2 mousePosition = GetMousePosition(); //Gets the mouse position
        if (CheckCollisionPointRec(mousePosition, button)) { //Checks if the mouse is over the button
            DrawRectangleRec(button, GRAY); //If the mouse is over the button, draw the button in a lighter color
            DrawTextBoxed(font, buttonMessage, buttonText, 20, 3, true, textColor); //Draws the button text on the start screen
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //If the mouse is clicked, change the scene to 1
                scene = 1;
                InitPlayer();
            }
        }


    }
    else {
        DrawRectangleRec(textbox, WHITE); //Textbox on the left background WHITE
        textColor = BLACK; //Text color is BLACK
        DrawRectangleRec(gameArea, BLACK); // everything must be offset by game area
    }

    switch (scene) { //Switch statement to determine which scene to draw
        case 0: {
            break;
        }
        case 1: {
            //Left side reading textbox
            ReadTextFile("./texts/level1.txt", textbox, BLACK); //Reads the message.txt file to display the message in the textbox

            //Right side game play area
            ifstream file("./levels/level1.txt"); //Opens the level1.txt file to read the walls to be displayed in the game area
            if (file.is_open()) { //It has to open, else repo is missing the file :(
                int lines; //Declares the variables to be used later
                file >> lines; //Reads the first line of the file, which is the number of walls in the file
                file.ignore(); //Ignores the first line of the file,
                string message;
                getline(file, message); //Reads the second line of the file, which is the message to be displayed in the textbox
                Rectangle messageBox = MessageCenterProcessor(gameArea, message, 20, 0, 0, 0, 0); //Calculates the center of the textbox rectangle to position the message in the center
                DrawTextBoxed(font, message, messageBox, 20, 3, true, WHITE); //Draws the message in the textbox

                //Next button
                NextButton(); //Draws the next button on the screen
            }
            break;
        }

        default: {
            //Sample textbox reading
            ReadTextFile("./texts/levelx.txt", textbox, BLACK); //Reads the message.txt file to display the message in the textbox
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

            //Sample game area text
            string gameText = "Level X";
            Rectangle gameTextBox = MessageCenterProcessor(gameArea, gameText, 20, 0, -250, 0, 0); //Calculates the center of the textbox rectangle to position the message in the center
            DrawTextBoxed(font, gameText, gameTextBox, 20, 3, true, WHITE); //Draws the message in the textbox
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
