#include "raylib.h"
#include "player.h"

Player::Player(){
  rec = { 300, 100, 20, 20 };
  speed = { 5, 5 };
  color = GREEN;
}

Rectangle Player::GetRec(){
  return rec;
}
void Player::Move(Rectangle gameArea){
  if (IsKeyDown(KEY_RIGHT)) {
      rec.x += speed.x;
  }
  if (IsKeyDown(KEY_LEFT)) {
      rec.x -= speed.x;
  }
  if (IsKeyDown(KEY_UP)) {
      rec.y -= speed.y;
  }
  if (IsKeyDown(KEY_DOWN)) {
      rec.y += speed.y;
  }

  if (rec.x < gameArea.x ) rec.x = gameArea.x; // restricts player to bounds x (the left)
  if (rec.y < gameArea.y ) rec.y = gameArea.y; // restricts player to bounds y (the bottom)
  if (rec.x + rec.width > gameArea.x + gameArea.width) rec.x = gameArea.x + gameArea.width - rec.width; // restricts player to otherside (right)
  if (rec.y + rec.height > gameArea.y + gameArea.height) rec.y = gameArea.y + gameArea.height - rec.height; // restricts player to  height (bottom)
  // Adapted from a ChatGPT prompt in order to keep player visible: the reason the last two add gameArea.{dimension} + gameArea.height - rec.height is so that the rectangle doesn't disappear and is instead stopped at the ends of its sprite

};

void Player::Draw(){
  DrawRectangleRec(rec, color);
}
