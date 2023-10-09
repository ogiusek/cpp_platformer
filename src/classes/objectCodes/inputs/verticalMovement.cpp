#include <vector>
#include <map>

#include <iostream>
using namespace std;

void ObjectInputs::VerticalMovement(GameState *gameState, Object *object)
{
  const float max_speed = stringToFloat(object->objectMap["max_speed"]) / 10;
  const float speed = stringToFloat(object->objectMap["speed"]) * (float)gameState->frames.timeBetweenLastFrames;

  float yVel = stringToFloat(object->objectMap["yVel"]);
  yVel = min(max_speed, max(-max_speed, yVel));
  float defaultYVel = yVel;

  const bool pressedW = gameState->input.keysMapContains({119, 1073741906}) && !object->objectMap.count("topCollision");
  const bool pressedS = gameState->input.keysMapContains({115, 1073741905}) && !object->objectMap.count("bottomCollision");

  if (pressedW ^ pressedS)
    object->objectMap["disableYFriction"] = "";
  if (pressedW) // w
    yVel = yVel - speed;
  if (pressedS) // s
    yVel = yVel + speed;

  if (defaultYVel < yVel)
    object->objectMap["yVel"] = to_string(max(yVel, -max_speed));
  else if (defaultYVel > yVel)
    object->objectMap["yVel"] = to_string(min(yVel, max_speed));
}