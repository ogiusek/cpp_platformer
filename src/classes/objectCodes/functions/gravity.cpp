#include <vector>
#include <map>

#include <iostream>
using namespace std;

void ObjectFunctions::Gravity(GameState *gameState, Object *object)
{
  const float gravity = (stringToFloat(object->objectMap["gravity"]) / 1000.0) * (float)gameState->frames.timeBetweenLastFrames;
  const float yVel = stringToFloat(object->objectMap["yVel"]);

  if (!object->objectMap.count("bottomCollision"))
  {
    object->objectMap["disableYFriction"] = "";
    object->objectMap["yVel"] = to_string(yVel + gravity);
  }
}