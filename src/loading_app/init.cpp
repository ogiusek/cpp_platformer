#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_hints.h>

#include <iostream>

using namespace std;

void START_APP(GameState *gameState)
{
  const bool fullscreen = 0;
  const string TITLE = "Platformer, Just Jump!";

  TTF_Init();
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    cout << "ERROR AT SDL INIT\n";

  if (SDL_CreateWindowAndRenderer(gameState->window.width, gameState->window.height, fullscreen, &(gameState->window.window), &(gameState->window.renderer)) < 0)
    cout
        << "ERROR AT SDL CREATE WINDOW AND RENDERER\n";

  SDL_SetWindowTitle(gameState->window.window, TITLE.c_str());
  SDL_ShowCursor(1);

  // SDL_Surface *icon = IMG_Load("Assets/Images/red-panda.png");
  // SDL_SetWindowIcon(window, icon);
  // SDL_SetWindowTitle(window, "Panda's fear");
  // SDL_FreeSurface(icon);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}