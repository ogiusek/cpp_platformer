#include <map>
#include <vector>

using namespace std;

class Object
{
private:
  float xPos, yPos;
  float absXPos = 0, absYPos = 0;
  int width, height;

  vector<Object> children;

  vector<Object *> nestedChildren;
  vector<void (*)(GameState *, Object *)> inputCodes, codes;

protected:
  void refreshNestedChildren(), refreshAbsolutePos();

public:
  string tag;
  bool draw, drawn = 0, hitbox = 0;
  map<string, string> objectMap;
  Object *parent;

  float getXPos(bool absolute = 1), getYPos(bool absolute = 1);
  int getWidth(), getHeight();

  Object *getScene();
  vector<Object *> getChildren(bool nested = 1), getChildrenByTag(string tag, bool withNested = 0);

  void setXPos(float pos, float absolute = 0), setYPos(float pos, float absolute = 0),
      setWidth(int width), setHeight(int height),
      addChild(Object child), removeChild(Object *child);

  void Draw(GameState *gameState),
      Update(GameState *gameState),
      Input(GameState *gameState);

  Object(string _tag,
         float _xPos, float _yPos, int _width, int _height, bool _draw, bool _hitbox,
         map<string, string> _objectMap = {},
         vector<void (*)(GameState *, Object *)> _inputCodes = {},
         vector<void (*)(GameState *, Object *)> _codes = {})
      : tag(_tag), xPos(_xPos), yPos(_yPos), width(_width), height(_height), draw(_draw), hitbox(_hitbox),
        objectMap(_objectMap), inputCodes(_inputCodes), codes(_codes) {}
};
