#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Draw
{
public:
  static void Text(GameState *gameState, int x, int y, string text, int fontSize, SDL_Color color);
};
