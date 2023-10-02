#include <vector>
#include <map>

#include <iostream>
using namespace std;

void ObjectInputs::HorizontalMovement(GameState *gameState, Object *object)
{
  const float max_speed = stringToFloat(object->objectMap["max_speed"]) / 10;
  const float speed = stringToFloat(object->objectMap["speed"]) * (float)gameState->frames.timeBetweenLastFrames;

  float xVel = stringToFloat(object->objectMap["xVel"]);
  xVel = min(max_speed, max(-max_speed, xVel));
  float defaultXVel = xVel;

  const bool pressedA = gameState->input.keysMapContains({97, 1073741904}) && !object->objectMap.count("leftCollision");
  const bool pressedD = gameState->input.keysMapContains({100, 1073741903}) && !object->objectMap.count("rightCollision");

  if (pressedA ^ pressedD)
    object->objectMap["disableXFriction"] = "";
  if (pressedA) // a
    xVel = xVel - speed;
  if (pressedD) // d
    xVel = xVel + speed;

  if (defaultXVel < xVel)
    object->objectMap["xVel"] = to_string(max(xVel, -max_speed));
  else if (defaultXVel > xVel)
    object->objectMap["xVel"] = to_string(min(xVel, max_speed));
}