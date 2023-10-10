#include <vector>
#include <map>

#include <iostream>
using namespace std;

class ObjectInputs
{
public:
  static void HorizontalMovement(GameState *gameState, Object *object);
  static void VerticalMovement(GameState *gameState, Object *object);
  static void JumpingMovement(GameState *gameState, Object *object);
  // static void Platformer(GameState *gameState, Objects::Object *object);
};
