#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, int width, int length, SDL_Texture* p_tex);
	Vector2f& getPos()
	{
		return pos;
	}
	int getWidth();
	int getLength();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	bool CollidesWith(Entity p);
	bool LeftCollidesWith(Entity p);
	bool RightCollidesWith(Entity p);
	// bool CollidesWith(Entity p, int XstartPos, int XendPos, int YstartPos, int YendPos);
private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};