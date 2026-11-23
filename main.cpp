#include <iostream>
#include "raylib.h"
#include "drawtextbox.h"
#include "player.h"
#include "wall.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//global variables

Player player;

vector<Wall> walls; // vector of walls -- hardcoded but will be adapted to levels later

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
            Rectangle messageBox = MessageCenterProcessor(canva, message, 15, 0, 0, 0, 400); //Calculates the center of the textbox rectangle to position the message in the center
            DrawTextBoxed(font, message, messageBox, 15, 3, true, textColor); //Draws the message in the textbox
            float height = MeasureTextEx(font, message.c_str(), 15, 3).y + 30; //Calculates the height of the message to be displayed in the textbox
            for (int i = 1; i < lines; i++) { //Loops through the number of lines in the file
                getline(file, message); //Reads the current line of the file
                messageBox = {canva.x + 10, height, canva.width - 10, messageBox.height}; //Calculates the position of the message to be displayed in the textbox
                DrawTextBoxed(font, message, messageBox, 12, 3, true, textColor); //Draws the message in the textbox
                height += MeasureTextEx(font, message.c_str(), 12, 3).y; //Calculates the height of the message to be displayed in the textbox
            }
            file.close();
        }
    }

  //Reads the levelx.txt from texts to diaplay reading on the left side. Also procedurally generates the walls
  void LoadWalls(string filename){
    ifstream file(filename); //Opens the message.txt file to read the message to be displayed in the textbox
        if (file.is_open()) { //It has to open, else repo is missing the file :(
          int numWalls;
            file >> numWalls;
            vector<Wall> wallsToAdd;
            for (int i = 0; i < numWalls; i++) {
                float x;
                float y;
                float width;
                float height; // all read walls
                if (!(file >> x >> y >> width >> height)) {
                    cout << "Error reading wall " << i << endl; // throws error if no wall
                }

                wallsToAdd.push_back(Wall(x, y, width, height)); // adds to wall
            }
            walls = wallsToAdd;

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
            cout << scene << endl; //Prints the current scene to the console for debugging purposes
        }
    }
}
void DrawScene() {
    BeginDrawing();
    ClearBackground(WHITE); //Clears the background to white for each frame
    if (scene == 0) { //Startig screen has a different format
        DrawRectangleRec(startScene, BLACK); //Start screen background is BLACK

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
            //Display text
            message = "Welcome to the Path of a Packet"; //Message to be displayed on the start screen
            textColor = WHITE; //Text color is WHITE
            Rectangle messageBox = MessageCenterProcessor(startScene, message, 20, 0, -50, 0, 0); //Calculates the center of the start screen rectangle to position the message in the center
            DrawTextBoxed(font, message, messageBox, 20, 3, true, textColor); //Draws the message on the start screen
            break;
        }
        case 1: { // TUTORIAL LEVEL
            //Left side reading textbox
            ReadTextFile("./texts/tutorial.txt", textbox, BLACK); //Reads the message.txt file to display the message in the textbox
            //Special command for the tutorial to have text where the gameplay should be
            ifstream file("./levels/tutorial.txt"); //Opens the level1.txt file to read the walls to be displayed in the game area
            if (file.is_open()) { //It has to open, else repo is missing the file :(
                int lines; //Declares the variables to be used later
                file >> lines; //Reads the first line of the file, which is the number of walls in the file
                file.ignore(); //Ignores the first line of the file,
                string message;
                getline(file, message); //Reads the second line of the file, which is the message to be displayed in the textbox
                Rectangle messageBox = MessageCenterProcessor(gameArea, message, 20, 0, 0, 0, 0); //Calculates the center of the textbox rectangle to position the message in the center
                DrawTextBoxed(font, message, messageBox, 20, 3, true, WHITE); //Draws the message in the textbox
            }
            NextButton();//Next button
            break;
        }
        case -1:{ // dedicated game over scene, needs to be before gameplay so that gameplay always runs default without crossing into game over
          DrawRectangleRec(startScene, BLACK); // resets screen
          message = "GAME OVER"; //Message to be displayed on the start screen
          textColor = WHITE; //Text color is WHITE
          Rectangle messageBox = MessageCenterProcessor(startScene, message, 20, 0, -50, 0, 0); //Calculates the center of the start screen rectangle to position the message in the center
          DrawTextBoxed(font, message, messageBox, 20, 3, true, textColor); //Draws the message on the start screen
          string buttonMessage = "RETRY?"; //Message to be displayed on the button
          Rectangle button = MessageCenterProcessor(startScene, buttonMessage, 20, 0, 30, 20, 0);
          Rectangle buttonText = MessageCenterProcessor(startScene, buttonMessage, 20, 0, 30, 0, 0);
          DrawRectangleRec(button, DARKGRAY); //Draws the button on the start screen
          DrawTextBoxed(font, buttonMessage, buttonText, 20, 3, true, textColor); //Draws the button text on the start screen
          Vector2 mousePosition = GetMousePosition(); //Gets the mouse position
          if (CheckCollisionPointRec(mousePosition, button)) { //Checks if the mouse is over the button
              DrawRectangleRec(button, GRAY); //If the mouse is over the button, draw the button in a lighter color
              DrawTextBoxed(font, buttonMessage, buttonText, 20, 3, true, textColor); //Draws the button text on the start screen
              if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //If the mouse is clicked, change the scene to 1
                  player.Reset();
                  scene = 1;
              }
          }
          break;
          }


        default: {
          // default includes general gameplay that isn't the tutorial or game over screen
          // Note here that "scene" is always one ahead because 0 occupies the beggining screen and 1 occupies the tutorial
            string textlevel = "./texts/level" + to_string(scene - 1) + ".txt"; // takes scene to create text file
            string wallFile = "./levels/level" + to_string(scene - 1) + ".txt"; // takes scene to create wall file
            ReadTextFile(textlevel, textbox, BLACK);
            LoadWalls(wallFile);
            BeginScissorMode( // scissor-mode cuts away elements from specific dimensions https://www.raylib.com/examples/core/loader.html?name=core_scissor_test
                gameArea.x, //In short the goal is to prevent rendering outside of the game area
                gameArea.y,
                gameArea.width,
                gameArea.height
            );
            EndScissorMode();
            for (int i = 0; i < walls.size(); i++) { // wall iteration for calling draw
                walls[i].Draw();
            }
            player.Move(gameArea);
            player.Draw();
            for (int i = 0 ;i < walls.size();i++) {
                if (walls[i].CheckCollision(player.GetRec())) {
                  scene = -1; //game over
                break;
              }
            }
            if (player.GetRec().x + player.GetRec().width >= gameArea.x + gameArea.width) { // if player's rectangle (entirely) touches the right wall of the screen, next level
              player.Reset();
              scene++;
            }

            //Sample game area text
            string gameText = "Path of a Packet";
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
