#include <SDL2/SDL.h>
#include <iostream>
#include <map>

using namespace std;

void PerFrame::Input(GameState *gameState)
{
  // gameState->objects.Input(gameState);
  gameState->getScene()->Input(gameState);

  while (SDL_PollEvent(&gameState->input.event))
  {
    gameState->input.keystates = SDL_GetKeyboardState(NULL);

    if (gameState->input.keystates[SDL_SCANCODE_ESCAPE])
      gameState->frames.running = 0;

    if (gameState->input.event.type == SDL_QUIT)
      gameState->frames.running = 0;

    if (gameState->input.event.type == SDL_KEYDOWN)
    {
      // cout << "Pressed key code " << gameState->input.event.key.keysym.sym << "\n"; // -------------- get key number
      gameState->input.keysMap.insert(make_pair(gameState->input.event.key.keysym.sym, 1));
    }

    if (gameState->input.event.type == SDL_KEYUP)
    {
      gameState->input.keysMap.erase(gameState->input.event.key.keysym.sym);
    }
  }
}