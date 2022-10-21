#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <ctime>
#include <unistd.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

double hireTimeInSeconds()
{
	double t = SDL_GetTicks();
	t *= 0.001f;
	return t;
}

void isCollidingLeft(Entity p, Entity c);

int velocityX = 0;
int velocityY = 0;

int main(int argv, char* args[])
{
	if(SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "FUCK FUCK FUCK IT'S NOT WORKING ABORT ABORT FUCK. SDL_ERROR: " << SDL_GetError() << std::endl;

	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "FUCK SHIT BALLS FUCK THE IMAGING QUANTUM MECHANIC SYSTEM DOENS'T WORK WE'RE GONNA DIE. ERROR: " << SDL_GetError() << std::endl;

	// Dt is deltaTime. This is the amount of times we update our game per second
	static const double dt = 0.01f; // 100 updates per second

	// The accumulater allows us to have smooth rendering.
	// Since our game runs at a set amout of updates per seconds,
	// we want to be able to render between updates
	static double accumulator = 0.0f;
	static double currentTime = hireTimeInSeconds();

	static double oneSecond = 0;
	static int framesRenderedInOneSecond = 0;

	RenderWindow window("c++ong", 256, 256);

	SDL_Texture* pixel = window.loadTexture("res/gfx/Pixel.png");
	SDL_Texture* placeholder = window.loadTexture("res/gfx/Mea.png");
	SDL_Texture* nothing = window.loadTexture("res/gfx/Nothing.png");

	// Entity entities[] = {Entity(0, 0, meTex), 
	// 					 	Entity(100, 0, ambrTex),
	// 					 	Entity(200, 0, meTex)};
	int ballx = 0;
	int bally = 0;
	int placeholdersIN = 0;
	std::vector<Entity> entities = {Entity(Vector2f(ballx, bally), 10, 10, pixel),
									Entity(Vector2f(ballx+10, bally), 5, 10, nothing),
									Entity(Vector2f(ballx, bally), 5, 10, nothing),
									Entity(Vector2f(ballx, bally+10), 10, 5, nothing),
									Entity(Vector2f(ballx, bally), 10, 5, nothing)};

	std::vector<Entity> placeholders = {Entity(Vector2f(100, 100), 50, 50, pixel)};
	std::vector<int> phX;
	std::vector<int> phY;
	// int phX[] = {0};
	// int phY[] = {0};
	bool gameRunning = true;

	SDL_Event event;

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	while(gameRunning)
	{
		double newTime = hireTimeInSeconds();
		double frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
			frameTime = 0.f;

		currentTime = newTime;

		accumulator += frameTime;
		oneSecond += frameTime;
		// std::future<void> asyncFunc = std::async(std::launch::async,isCollidingLeft,entities[0],entities[1]);

		while(accumulator >= dt)
		{
			ballx += velocityX;
			bally += velocityY;
			entities[0] = Entity(Vector2f(ballx, bally), 10, 10, pixel);
			entities[1] = Entity(Vector2f(ballx+10, bally+1), 5, 9, nothing);
			entities[2] = Entity(Vector2f(ballx-5, bally+1), 5, 9, nothing);
			entities[3] = Entity(Vector2f(ballx+1, bally+10), 9, 5, nothing);
			entities[4] = Entity(Vector2f(ballx+1, bally-5), 9, 5, nothing);
			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					gameRunning = false;
				if(SDL_KEYDOWN == event.type)
				{
					// if(SDLK_RETURN == event.key.keysym.sym)
					// {
					// 	{
					// 		int curPosX = ballx;
					// 		int curPosY = bally;

					// 		phX.push_back(curPosX);
					// 		phY.push_back(curPosY);

					// 		Entity placholdr(Vector2f(phX[placeholdersIN], phY[placeholdersIN]), 32, 32, placeholder);

					// 		placeholders.push_back(placholdr);
					// 		placeholdersIN++;
					// 	}
					// sleep(0.50);
					// }
				}
				if(SDL_KEYUP == event.type)
				{
					if(SDLK_w || SDLK_s == event.key.keysym.sym)
						velocityY = 0;
					if(SDLK_a || SDLK_d == event.key.keysym.sym)
						velocityX = 0;
				}
			}
			if(entities[4].CollidesWith(placeholders[0]) == false)
			{
				if(keystates[SDL_SCANCODE_W])
				{
					velocityY = -1;
				}
			}
			else
			{
				if(velocityY < 0)
				{
					velocityY = 0;
				}
			}
			if(entities[3].CollidesWith(placeholders[0]) == false)
			{
				if(keystates[SDL_SCANCODE_S])
				{
					velocityY = 1;
				}
			}
			else
			{
				if(velocityY > 0)
				{
					velocityY = 0;
				}
			}
			if(entities[2].CollidesWith(placeholders[0]) == false)
			{
				if(keystates[SDL_SCANCODE_A])
				{
					velocityX = -1;
				}
			}
			else
			{
				if(velocityX < 0)
				{
					velocityX = 0;
				}
			}
			if(entities[1].CollidesWith(placeholders[0]) == false)
			{
				if(keystates[SDL_SCANCODE_D])
				{
					velocityX = 1;
				}
			}
			else
			{
				if(velocityX > 0)
				{
					velocityX = 0;
				}
			}

			entities[0] = Entity(Vector2f(ballx, bally), 10, 10, pixel);
			accumulator -= dt;
		}

		const double alpha = accumulator / dt;

		window.clear();
		for (Entity& placehold : placeholders)
		{
			window.render(placehold);
		}
		for (Entity& entity : entities)
		{
			window.render(entity);
		}

		window.display();

		framesRenderedInOneSecond++;
		}

	window.cleanUp();
	SDL_Quit();

	return 0;
}

//bool runnn = true;

// void isCollidingLeft(Entity p, Entity c)
// {
// 	while(p.LeftCollidesWith(c))
// 	{
// 		if(velocityX == 1)
// 		{
// 			velocityX = 0;
// 			std::cout << "collission left\n";
// 		}
// 	}
// }
