#include <vector>
#include <map>

#include <iostream>
using namespace std;

void ObjectInputs::JumpingMovement(GameState *gameState, Object *object)
{
  // jump_power
  // jump_length

  const float yVel = stringToFloat(object->objectMap["yVel"]);
  const bool press = gameState->input.keysMapContains({32, 119, 1073741906}) && !object->objectMap.count("topCollision");

  if (press)
  {
    const int jumpRest = (int)stringToFloat(object->objectMap["jump_rest"]);

    if (jumpRest <= 0)
      return;

    const int jumpLength = (int)stringToFloat(object->objectMap["jump_length"]);
    const float jumpPower = stringToFloat(object->objectMap["jump_power"]) / 10;

    const int jumpEnergy = min(gameState->frames.timeBetweenLastFrames, jumpRest);

    object->objectMap["jump_rest"] = to_string(jumpRest - jumpEnergy);
    object->objectMap["yVel"] = to_string(-(jumpPower));
  }
  else if (yVel == 0)
    object->objectMap["jump_rest"] = object->objectMap["jump_length"];
  else
    object->objectMap["jump_rest"] = "0";

  // if (yVel == 0)
  //   object->objectMap["jump_val"];

  // if (&&yVel == 0) // w
  //   object->objectMap["yVel"] = to_string(-jumpPower);
}