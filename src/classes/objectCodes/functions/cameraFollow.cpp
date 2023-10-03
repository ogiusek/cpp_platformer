#include <vector>
#include <map>

#include <iostream>
using namespace std;

void ObjectFunctions::CameraFollow(GameState *gameState, Object *object)
{
  gameState->camera.xPos = (object->getXPos(1) + (object->getWidth() / 2)) - gameState->window.width / 2;
  gameState->camera.yPos = (object->getYPos(1) + (object->getHeight() / 2)) - gameState->window.height / 2;
}

void ObjectFunctions::CameraFollowSmooth(GameState *gameState, Object *object)
{
  float cameraSpeed = max(0, (min(0.015 * (float)gameState->frames.timeBetweenLastFrames, 1))); // 0-1
  if (!object->objectMap.count("CameraFollowSmooth"))
  {
    cameraSpeed = 1;
    object->objectMap["CameraFollowSmooth"] = "";
  }

  gameState->camera.xPos = gameState->camera.xPos * (1 - cameraSpeed) + ((object->getXPos(1) + (object->getWidth() / 2)) - gameState->window.width / 2) * cameraSpeed;
  gameState->camera.yPos = gameState->camera.yPos * (1 - cameraSpeed) + ((object->getYPos(1) + (object->getHeight() / 2)) - gameState->window.height / 2) * cameraSpeed;
}
