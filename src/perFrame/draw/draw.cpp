#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
using namespace std;

#include "include.h"

void PerFrame::Draw(GameState *gameState)
{
  int start = SDL_GetTicks();
  SDL_RenderClear(gameState->window.renderer);

  SDL_SetRenderDrawColor(gameState->window.renderer, 255, 255, 255, 255); // rgba

  SDL_Rect rect = {0, 0, gameState->window.width, gameState->window.height};
  SDL_RenderFillRect(gameState->window.renderer, &rect);

  // gameState->objects.Draw(gameState);
  gameState->getScene()->Draw(gameState);

  Draw::Text(gameState, 0, 0, (to_string(gameState->frames.fps) + "FPS"));

  SDL_RenderPresent(gameState->window.renderer);

  if (gameState->coutTime)
    cout << "Draw: " << SDL_GetTicks() - start << ", ";
}
