#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
  Entity(Vector2f p_pos, int width, int length, SDL_Texture *p_tex);
  Vector2f &getPos() { return pos; }
  float velocityX;
  float velocityY;
  int dirX = 0;
  int dirY = 0;
  int getWidth();
  int getLength();
  SDL_Texture *getTex();
  SDL_Rect getCurrentFrame();
  bool CollidesWith(Entity p);
  bool LeftCollidesWith(Entity p);
  bool RightCollidesWith(Entity p);
  bool TopCollidesWith(Entity p);
  bool BottomCollidesWith(Entity p);
  void setPos(float x, float y);
  // bool CollidesWith(Entity p, int XstartPos, int XendPos, int YstartPos, int
  // YendPos);
private:
  Vector2f pos;
  SDL_Rect currentFrame;
  SDL_Texture *tex;
};
