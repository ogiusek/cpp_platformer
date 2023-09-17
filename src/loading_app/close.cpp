#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

using namespace std;

void SHUT_DOWN(GameState *gameState)
{
  TTF_Quit();
  SDL_DestroyRenderer(gameState->window.renderer);
  SDL_DestroyWindow(gameState->window.window);
  SDL_Quit();
}