#include <vector>
#include <map>

#include <iostream>
using namespace std;

void ObjectFunctions::Velocity(GameState *gameState, Object *object)
{
  float xVel = stringToFloat(object->objectMap["xVel"]);
  float yVel = stringToFloat(object->objectMap["yVel"]);

  const float min_speed = 0.01;
  const float friction = (1.0 - stringToFloat(object->objectMap["friction"]));

  xVel = min(min_speed, max(-min_speed, xVel)) == xVel ? 0 : xVel;
  yVel = min(min_speed, max(-min_speed, yVel)) == yVel ? 0 : yVel;

  object->setXPos(object->getXPos(0) + xVel * (float)gameState->frames.timeBetweenLastFrames, 0);
  object->setYPos(object->getYPos(0) + yVel * (float)gameState->frames.timeBetweenLastFrames, 0);
  if (!object->objectMap.count("disableXFriction"))
    object->objectMap["xVel"] = to_string(xVel * friction);
  if (!object->objectMap.count("disableYFriction"))
    object->objectMap["yVel"] = to_string(yVel * friction);

  object->objectMap.erase("disableXFriction");
  object->objectMap.erase("disableYFriction");
}