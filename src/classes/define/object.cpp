#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <map>

#include <iostream>
using namespace std;

float Object::getXPos(bool absolute)
{
  if (absolute && parent != nullptr)
    return absXPos ? absXPos : parent->getXPos(1) + xPos;
  return xPos;
};
float Object::getYPos(bool absolute)
{
  if (absolute && parent != nullptr)
    return absYPos ? absYPos : parent->getYPos(1) + yPos;
  return yPos;
};

int Object::getWidth() { return width; };
int Object::getHeight() { return height; };

Object *Object::getScene() { return parent == nullptr ? this : parent->getScene(); }
vector<Object *> Object::getChildren(bool nested)
{
  if (children.size() == 0)
    return {};

  vector<Object *> childrenToReturn;

  if (nestedChildren.size() == 0 && nested)
  {
    nestedChildren = {};
    for (int i = 0; i < children.size(); i++)
    {
      Object *child = &children[i];
      nestedChildren.push_back(child);
      const vector<Object *> childChildren = child->getChildren(1);
      for (int j = 0; j < childChildren.size(); j++)
        nestedChildren.push_back(childChildren[j]);
    }
  }

  return nested ? nestedChildren : to_pointer_vector(&children);
};
vector<Object *> Object::getChildrenByTag(string tag, bool withNested)
{
  vector<Object *> allChildren = getChildren(withNested);
  vector<Object *> childrenWithTag;
  for (int i = 0; i < allChildren.size(); i++)
  {
    Object *child = allChildren[i];
    if (child->tag == tag)
      childrenWithTag.push_back(child);
  }
  return childrenWithTag;
}

// --------------------------------------------------------------------------

void Object::setWidth(int w) { width = w; }
void Object::setHeight(int h) { height = h; }

void Object::setXPos(float pos, float absolute)
{
  if (absolute && parent != nullptr)
  {
    xPos = pos - parent->getXPos(1);
  }
  else
    xPos = pos;
  refreshAbsolutePos();
}
void Object::setYPos(float pos, float absolute)
{
  if (absolute && parent != nullptr)
  {
    yPos = pos - parent->getXPos(1);
  }
  else
    yPos = pos;
  refreshAbsolutePos();
}
void Object::refreshAbsolutePos()
{
  absXPos = 0;
  absYPos = 0;
  for (int i = 0; i < children.size(); i++)
    children[i].refreshAbsolutePos();
}

void Object::refreshNestedChildren()
{
  nestedChildren = {};
  if (parent != nullptr)
    parent->refreshNestedChildren();
}
void Object::addChild(Object child)
{
  child.parent = this;
  children.push_back(child);
  refreshNestedChildren();
}

// --------------------------------------------------------------------------

void Object::Draw(GameState *gameState)
{
  for (int i = 0; i < children.size(); i++)
    children[i].Draw(gameState);

  if (!draw)
    return;

  const int objXPos = getXPos(1) - gameState->camera.xPos, objYPos = getYPos(1) - gameState->camera.yPos,
            objWidth = getWidth(), objHeight = getHeight();

  drawn = objXPos + objWidth > 0 && objXPos < gameState->window.width &&
          objYPos + objHeight > 0 && objYPos < gameState->window.height;

  if (!drawn) // if element is outside screen
    return;

  SDL_SetRenderDrawColor(gameState->window.renderer, 0, 0, 0, 200);
  SDL_Rect rect = {objXPos, objYPos, objWidth, objHeight};
  SDL_RenderFillRect(gameState->window.renderer, &rect); // TODO implement texture
}

void Object::Update(GameState *gameState)
{
  for (int i = 0; i < codes.size(); i++) // run user codes
    codes[i](gameState, this);

  for (int i = 0; i < children.size(); i++) // update children
    children[i].Update(gameState);
}

void Object::Input(GameState *gameState)
{
  for (int i = 0; i < inputCodes.size(); i++)
    inputCodes[i](gameState, this);

  for (int i = 0; i < children.size(); i++)
    children[i].Input(gameState);
}
