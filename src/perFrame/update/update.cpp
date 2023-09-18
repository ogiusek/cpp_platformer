#include <SDL2/SDL.h>
#include <iostream>
#include <map>

using namespace std;

void PerFrame::Update(GameState *gameState)
{
  int start = SDL_GetTicks();
  // gameState->objects.Update(gameState);
  gameState->getScene()->Update(gameState);

  if (gameState->coutTime)
  {
    cout << "Update: " << SDL_GetTicks() - start << endl;
  }
}