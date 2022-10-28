#include "Entity.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"

Entity::Entity(Vector2f p_pos, int width, int length, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = width;
	currentFrame.h = length;
}

int Entity::getWidth()
{
	return currentFrame.w;
}

int Entity::getLength()
{
	return currentFrame.h;
}

// float Entity::getX()
// {
// 	return x;
// }
// float Entity::getY()
// {
// 	return y;
// }

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

bool Entity::CollidesWith(Entity p)
{
	if(getPos().x >= p.getPos().x && 
	   getPos().x <= (p.getPos().x+p.getWidth()) && 
	   (getPos().x+getWidth()) >= p.getPos().x && 
	   (getPos().x+getWidth()) <= (p.getPos().x+p.getWidth()) && 
	   getPos().y >= p.getPos().y && 
	   getPos().y <= (p.getPos().y+p.getLength()) && 
	   (getPos().y+getLength()) >= p.getPos().y && 
	   (getPos().y+getLength()) <= p.getPos().y+p.getLength()){
		return true;
	}
	else{
		return false;
	}
}
bool Entity::LeftCollidesWith(Entity p)
{
	if((getPos().x+getWidth()) == p.getPos().x &&
	   getPos().y >= p.getPos().y && 
	   getPos().y <= (p.getPos().y+p.getLength()) &&
	   (getPos().y+getLength()) >= p.getPos().y &&
	   (getPos().y+getLength()) <= (p.getPos().y+p.getLength())){
		return true;
	}
	else{
		return false;
	}
}
bool Entity::RightCollidesWith(Entity p)
{
	if((getPos().x == (p.getPos().x+p.getWidth()) && getPos().y >= p.getPos().y && getPos().y <= (p.getPos().y+p.getLength()) && (getPos().y+getLength()) >= p.getPos().y && (getPos().y+getLength()) <= (p.getPos().y+p.getLength()))){
		return true;
	}
	else{
		return false;
	}
}

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}