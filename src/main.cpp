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

int velocityX = 0;
int velocityY = 0;

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

  int ballx = 0;
  int bally = 0;
  std::vector<Entity> entities = {
      Entity(Vector2f(ballx, bally), 10, 10, pixel)};

  Entity CollBox[][4] = {Entity(Vector2f(-20, -20), 0, 0, pixel),
                         Entity(Vector2f(-20, -20), 0, 0, pixel),
                         Entity(Vector2f(-20, -20), 0, 0, pixel),
                         Entity(Vector2f(-20, -20), 0, 0, pixel)};

  int CollBoxRow = sizeof(CollBox) / sizeof(CollBox[0]);
  int CollBoxCollumn = sizeof(CollBox[0]) / sizeof(CollBox[0][0]);
  int EntityAmount = sizeof(entities) / sizeof(entities[0]);

  for (int i = 0; i < EntityAmount; i++) {
    Entity ent = entities[i];
    CollBox[i][0] =
        Entity(Vector2f(ent.getPos().x + ent.getWidth(), ent.getPos().y), 5,
               ent.getWidth(), pixel);
    CollBox[i][1] = Entity(Vector2f(ent.getPos().x, ent.getPos().y), 5,
                           ent.getWidth(), pixel);
    CollBox[i][2] =
        Entity(Vector2f(ent.getPos().x, ent.getPos().y + ent.getLength()),
               ent.getLength(), 5, pixel);
    CollBox[i][3] = Entity(Vector2f(ent.getPos().x + 5, ent.getPos().y),
                           ent.getLength(), 5, pixel);
  }

  std::vector<Entity> objects = {Entity(Vector2f(100, 100), 50, 50, pixel)};
  std::vector<int> phX;
  std::vector<int> phY;
  // int phX[] = {0};
  // int phY[] = {0};
  bool gameRunning = true;

  SDL_Event event;

  const Uint8 *keystates = SDL_GetKeyboardState(NULL);

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
      entities[0].setPos(entities[0].getPos().x + velocityX,
                         entities[0].getPos().y + velocityY);
      CollBoxRow = sizeof(CollBox) / sizeof(CollBox[0]);
      CollBoxCollumn = sizeof(CollBox[0]) / sizeof(CollBox[0][0]);
      for (int i = 0; i < CollBoxRow; i++) {
        for (int j = 0; j < CollBoxCollumn; j++) {
          if (j == 0) {
            CollBox[i][j].setPos(entities[i].getPos().x +
                                     entities[i].getWidth(),
                                 entities[i].getPos().y);
          }
          if (j == 1) {
            CollBox[i][j].setPos(entities[i].getPos().x - 1,
                                 entities[i].getPos().y);
          }
          if (j == 2) {
            CollBox[i][j].setPos(entities[i].getPos().x,
                                 entities[i].getPos().y +
                                     entities[i].getLength());
          }
          if (j == 3) {
            CollBox[i][j].setPos(entities[i].getPos().x,
                                 entities[i].getPos().y - 1);
          }
        }
      }
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
          gameRunning = false;
        if (SDL_KEYDOWN == event.type) {
        }
        if (SDL_KEYUP == event.type) {
          if (SDLK_w || SDLK_s == event.key.keysym.sym)
            velocityY = 0;
          if (SDLK_a || SDLK_d == event.key.keysym.sym)
            velocityX = 0;
        }
      }
      if (CollBox[0][3].CollidesWith(objects[0]) == false) {
        if (keystates[SDL_SCANCODE_W]) {
          velocityY = -1;
        }
      } else {
        if (velocityY < 0) {
          velocityY = 0;
        }
      }
      if (CollBox[0][2].CollidesWith(objects[0]) == false) {
        if (keystates[SDL_SCANCODE_S]) {
          velocityY = 1;
        }
      } else {
        if (velocityY > 0) {
          velocityY = 0;
        }
      }
      if (CollBox[0][1].CollidesWith(objects[0]) == false) {
        if (keystates[SDL_SCANCODE_A]) {
          velocityX = -1;
        }
      } else {
        if (velocityX < 0) {
          velocityX = 0;
        }
      }
      if (CollBox[0][0].CollidesWith(objects[0]) == false) {
        if (keystates[SDL_SCANCODE_D]) {
          velocityX = 1;
        }
      } else {
        if (velocityX > 0) {
          velocityX = 0;
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
