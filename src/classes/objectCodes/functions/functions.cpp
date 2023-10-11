#include <vector>
#include <map>

#include <iostream>
using namespace std;

class ObjectFunctions
{
public:
  static void Velocity(GameState *gameState, Object *object);
  static void Collision(GameState *gameState, Object *object);
  static void Gravity(GameState *gameState, Object *object);
  static void CameraFollow(GameState *gameState, Object *object);
  static void CameraFollowSmooth(GameState *gameState, Object *object);

  static void Test(GameState *gameState, Object *object);
};

void ObjectFunctions::Test(GameState *gameState, Object *object)
{
  cout << object->objectMap["yVel"] << endl;
  // cout << object->getXPos(1) << " xPos:yXpos " << object->getYPos(1) << endl;
}
