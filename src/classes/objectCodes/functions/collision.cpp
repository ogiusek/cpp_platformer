#include <vector>
#include <map>

#include <iostream>
using namespace std;

class CollisionResponse
{
public:
  float xOffset, yOffset;

  CollisionResponse(float _xOffset, float _yOffset)
      : xOffset(_xOffset), yOffset(_yOffset) {}
};

CollisionResponse getCollisionOffset(GameState *gameState, vector<Object *> getCollisionWith, Object *object, Object *parent = nullptr)
{
  if (parent == nullptr)
    parent = object;

  parent->objectMap.erase("disableGravityCollision");
  parent->objectMap.erase("topCollision");
  parent->objectMap.erase("bottomCollision");
  parent->objectMap.erase("leftCollision");
  parent->objectMap.erase("rightCollision");

  const float parentXVel = stringToFloat(parent->objectMap["xVel"]);
  const float parentYVel = stringToFloat(parent->objectMap["yVel"]);

  float xOffset = 0, yOffset = 0;

  const float objXPos = object->getXPos(1),
              objYPos = object->getYPos(1);
  const int objW = object->getWidth(), objH = object->getHeight();

  const bool onScreen = objXPos - gameState->camera.xPos > 0 && objYPos - gameState->camera.yPos > 0 &&
                        objXPos - gameState->camera.xPos + objW < gameState->window.width &&
                        objYPos - gameState->camera.yPos + objH < gameState->window.height;

  int time = SDL_GetTicks();
  vector<Object *> elements = getCollisionWith;

  for (int i = 0; i < elements.size(); i++)
  {
    Object *element = elements[i];

    if (element == object || !element->hitbox || (onScreen && !(element->drawn)))
      continue;

    const float eleXPos = element->getXPos(1), eleYPos = element->getYPos(1);
    const int eleW = element->getWidth(), eleH = element->getHeight();

    if (objXPos <= eleXPos + eleW &&
        objXPos + objW >= eleXPos &&
        objYPos <= eleYPos + eleH &&
        objYPos + objH >= eleYPos)
    {
      const float rightX = (objXPos) - (eleXPos + (float)eleW);
      const float leftX = (objXPos + (float)objW) - (eleXPos);
      const float topY = (objYPos) - (eleYPos + (float)eleH);
      const float botY = (objYPos + (float)objH) - (eleYPos);

      if (min(mAbs(rightX), mAbs(leftX)) < min(mAbs(topY), mAbs(botY)))
      {
        const float xVel = stringToFloat(object->objectMap["xVel"]);
        if (mAbs(rightX) < mAbs(leftX)) // left collision
        {
          xOffset = -rightX;
          parent->objectMap["xVel"] = to_string(parentXVel * (parentXVel < 0));
          parent->objectMap["leftCollision"] = "";
        }
        else // right collition
        {
          xOffset = -leftX;
          parent->objectMap["xVel"] = to_string(parentXVel * (parentXVel > 0));
          parent->objectMap["rightCollision"] = "";
        }
      }
      else
      {
        const float yVel = stringToFloat(object->objectMap["yVel"]);
        if (mAbs(topY) < mAbs(botY)) // top collision
        {
          yOffset = -topY;
          parent->objectMap["yVel"] = to_string(parentYVel * (parentYVel > 0));
          parent->objectMap["topCollision"] = "";
        }
        else // bottom collision
        {
          yOffset = -botY;
          parent->objectMap["yVel"] = to_string(parentYVel * (parentYVel < 0));
          parent->objectMap["bottomCollision"] = "";
        }
      }
    }
  }

  vector<Object *> childrenCollision = object->getChildren(0);
  for (int i = 0; i < childrenCollision.size(); i++)
  {
    if (xOffset && yOffset)
      break;
    CollisionResponse childrenOffset = getCollisionOffset(gameState, getCollisionWith, childrenCollision[i], parent);

    if (!xOffset)
      xOffset += childrenOffset.xOffset;

    if (!yOffset)
      yOffset += childrenOffset.yOffset;
  }

  return {xOffset, yOffset};
}

void ObjectFunctions::Collision(GameState *gameState, Object *object)
{
  const float objXPos = object->getXPos(1),
              objYPos = object->getYPos(1);
  const int objW = object->getWidth(), objH = object->getHeight();

  const bool onScreen = objXPos - gameState->camera.xPos > 0 && objYPos - gameState->camera.yPos > 0 &&
                        objXPos - gameState->camera.xPos + objW < gameState->window.width &&
                        objYPos - gameState->camera.yPos + objH < gameState->window.height;

  // std::vector<int> v2 = filter(v1, [](int i) { return i % 3 == 0; });
  // vector<Object *> elements = filter(object->getScene()->getChildren(1), [](Object *obj) {});
  vector<Object *> elements = object->getScene()->getChildren(1);
  if (onScreen)
    elements = filterVector(elements, [](Object *obj)
                            { return obj->drawn; });

  vector<Object *> exceptions = object->getChildren(1);
  exceptions.push_back(object);
  elements = excludeVector(elements, exceptions);

  CollisionResponse collisionOffset = getCollisionOffset(gameState, elements, object);
  // cout << SDL_GetTicks() - aaa << " \n";
  // object->objectMap["xVel"] = to_string(stringToFloat(object->objectMap["xVel"]) * collisionOffset.xVelMultiplayer);
  object->setXPos(object->getXPos(1) + collisionOffset.xOffset, 1);

  // object->objectMap["yVel"] = to_string(stringToFloat(object->objectMap["yVel"]) * collisionOffset.yVelMultiplayer);
  object->setYPos(object->getYPos(1) + collisionOffset.yOffset, 1);

  return;
}