#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <thread>
#include <time.h>

#include <map>
#include <vector>
#include <string>

#include <iostream>
using namespace std;

#include "utils/include.h"

#include "classes/gameState.cpp"
#include "loading_app/include.h"
#include "perFrame/include.h"

void count_fps(int *frames)
{
  *frames = *frames + 1;
  this_thread::sleep_for(chrono::seconds(1));
  *frames = *frames - 1;
}

int main()
{
  cout << "before All\n";
  GameState *gameState = new GameState();

  START_APP(gameState);

  gameState->addScene(Object({"scene0", 0, 0, 0, 0, false, false, {}, {}, {}}));

  gameState->getScene(0)->addChild(Object({"floor", -1000, 700, 1000, 50, true, true, {}, {}, {}}));
  // gameState->getScene(0)->addChild(Obj());
  gameState->getScene(0)->addChild(Object({"wall", -1000, 200, 100, 800, true, true, {}, {}, {}}));
  gameState->getScene(0)->addChild(Object({"platform", -500, 200, 500, 100, true, true, {}, {}, {}}));

  // for (int i = 0; i < 50000; i++)

  for (int i = 0; i < 50000; i++)
  {
    const int stepSize = 100;
    gameState->getScene(0)->addChild({"step", 0 + (float)(i * stepSize), 700 - (float)(i * stepSize), stepSize, 50 + i * stepSize, true, true, {}, {}, {}});
  }

  gameState->getScene(0)->addChild({"idle", 500, 500, 100, 100, true, true, {}, {}, {}});
  gameState->getScene(0)->addChild({"player",
                                    100,
                                    100,
                                    100,
                                    100,
                                    true,
                                    true,
                                    {{"gravity", "5.0"}, {"friction", "0.1"}, {"speed", "0.01"}, {"max_speed", "5.0"},

                                     {"jump_power", "10.0"},
                                     {"jump_length", "200"}},
                                    {&ObjectFunctions::Velocity, &ObjectFunctions::Gravity, &ObjectFunctions::Collision, &ObjectFunctions::CameraFollowSmooth},
                                    {&ObjectInputs::HorizontalMovement, &ObjectInputs::JumpingMovement}});
  // {&ObjectFunctions::Velocity, &ObjectFunctions::Collision, &ObjectFunctions::CameraFollowSmooth, &ObjectFunctions::Test},
  // {&ObjectInputs::HorizontalMovement, &ObjectInputs::VerticalMovement}});
  Object *player = gameState->getScene(0)->getChildrenByTag("player")[0];
  player->addChild({"head", 25, -50, 50, 50, true, true, {}, {}, {}});
  player->addChild({"lArm", -20, 10, 10, 150, true, true, {}, {}, {}});
  player->addChild({"rArm", 110, 10, 10, 150, true, true, {}, {}, {}});

  player->addChild({"rleg", 70, 100, 10, 150, true, true, {}, {}, {}});
  // player->addChild({"lleg", 20, 101, 10, 150, true, true, {}, {}, {}});

  cout << "\ninit\n";
  gameState->frames.lastFrame = SDL_GetTicks();

  while (gameState->frames.running)
  {
    if ((SDL_GetTicks() - gameState->frames.lastFrame) >= (1000.0 / (float)gameState->frames.FPS_Limit))
    {
      // count frame
      gameState->frames.timeBetweenLastFrames = SDL_GetTicks() - gameState->frames.lastFrame;
      gameState->frames.lastFrame = SDL_GetTicks();

      // fps counter
      thread count_fps_thread(count_fps, &gameState->frames.fps);
      count_fps_thread.detach();

      // per frame
      PerFrame::Draw(gameState);
      PerFrame::Input(gameState);
      PerFrame::Update(gameState);
    }
  }

  SHUT_DOWN(gameState);
  cout << "\nclose\n";
  return 0;
}