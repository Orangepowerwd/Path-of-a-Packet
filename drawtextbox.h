#ifndef DRAWTEXTBOX_H
#define DRAWTEXTBOX_H

#include "raylib.h"
#include "string"

// taken from Raylib Rectangle Bounds: https://www.raylib.com/examples/text/loader.html?name=text_rectangle_bounds

void DrawTextBoxed(Font font, const std::string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
// Draw text using font inside rectangle limits with support for text selection
void DrawTextBoxedSelectable(Font font, const std::string text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);
// no static since header file
#endif
