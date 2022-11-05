#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <future>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

#include "Entity.hpp"
#include "RenderWindow.hpp"
#include "Utils.hpp"

double hireTimeInSeconds() {
  double t = SDL_GetTicks();
  t *= 0.001f;
  return t;
}

void isCollidingLeft(Entity p, Entity c);

int main(int argv, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "FUCK FUCK FUCK IT'S NOT WORKING ABORT ABORT FUCK. SDL_ERROR: "
              << SDL_GetError() << std::endl;

  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cout << "FUCK SHIT BALLS FUCK THE IMAGING QUANTUM MECHANIC SYSTEM "
                 "DOENS'T WORK WE'RE GONNA DIE. ERROR: "
              << SDL_GetError() << std::endl;

  static const double dt = 0.01f;

  static double accumulator = 0.0f;
  static double currentTime = hireTimeInSeconds();

  static double oneSecond = 0;
  static int framesRenderedInOneSecond = 0;

  RenderWindow window("game", 256, 256);

  SDL_Texture *pixel = window.loadTexture("res/gfx/Pixel.png");

  std::vector<Entity> entities = {Entity(Vector2f(0, 0), 10, 10, pixel),
                                  Entity(Vector2f(100, 206), 10, 10, pixel)};
  int EntityAmount = entities.size();

  std::vector<Entity> objects = {Entity(Vector2f(25, 25), 30, 30, pixel),
                                 Entity(Vector2f(206, 25), 30, 30, pixel),
                                 Entity(Vector2f(25, 206), 30, 30, pixel),
                                 Entity(Vector2f(206, 206), 30, 30, pixel),
                                 Entity(Vector2f(0, 0), 256, 1, pixel),
                                 Entity(Vector2f(0, 0), 1, 256, pixel),
                                 Entity(Vector2f(0, 256), 256, 1, pixel),
                                 Entity(Vector2f(256, 0), 1, 256, pixel)};
  bool gameRunning = true;

  SDL_Event event;

  const Uint8 *keystates = SDL_GetKeyboardState(NULL);

  entities[0].velocityX = 1;
  entities[0].velocityY = 1;

  entities[1].velocityX = 1;
  entities[1].velocityY = 1;
  entities[1].dirX = 1;

  while (gameRunning) {
    double newTime = hireTimeInSeconds();
    double frameTime = newTime - currentTime;

    if (frameTime > 0.25f)
      frameTime = 0.f;

    currentTime = newTime;

    accumulator += frameTime;
    oneSecond += frameTime;
    // std::future<void> asyncFunc =
    // std::async(std::launch::async,isCollidingLeft,entities[0],entities[1]);

    while (accumulator >= dt) {
      // entities[0].velocityX = 1;
      // entities[0].velocityY = 1;
      for (Entity &ent : entities) {
        ent.setPos(ent.getPos().x + (ent.velocityX * ent.dirX),
                   ent.getPos().y + (ent.velocityY * ent.dirY));
      }
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
          gameRunning = false;
        if (SDL_KEYDOWN == event.type) {
        }
        if (SDL_KEYUP == event.type) {
          if (SDLK_w || SDLK_s == event.key.keysym.sym)
            entities[0].dirX = 0;
          if (SDLK_a || SDLK_d == event.key.keysym.sym)
            entities[0].dirY = 0;
        }
      }
      if (keystates[SDL_SCANCODE_W]) {
        entities[0].dirY = -1;
      }
      if (keystates[SDL_SCANCODE_S]) {
        entities[0].dirY = 1;
      }

      if (keystates[SDL_SCANCODE_A]) {
        entities[0].dirX = -1;
      }
      if (keystates[SDL_SCANCODE_D]) {
        entities[0].dirX = 1;
      }
      for (Entity &obj : objects) {
        for (int i = 0; i < EntityAmount; i++) {
          if (entities[i].LeftCollidesWith(obj)) {
            if (entities[i].dirX > 0) {
              entities[i].dirX = 0;
            }
          }
          if (entities[i].RightCollidesWith(obj)) {
            if (entities[i].dirX < 0) {
              entities[i].dirX = 0;
            }
          }
          if (entities[i].BottomCollidesWith(obj)) {
            if (entities[i].dirY > 0) {
              entities[i].dirY = 0;
            }
          }
          if (entities[i].TopCollidesWith(obj)) {
            if (entities[i].dirY < 0) {
              entities[i].dirY = 0;
            }
          }
        }
      }
      accumulator -= dt;
    }

    const double alpha = accumulator / dt;

    window.clear();
    for (Entity &object : objects) {
      window.render(object);
    }
    for (Entity &entity : entities) {
      window.render(entity);
    }

    window.display();

    framesRenderedInOneSecond++;
  }

  window.cleanUp();
  SDL_Quit();

  return 0;
}
