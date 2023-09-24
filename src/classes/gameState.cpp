#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <chrono>
#include <thread>
#include <time.h>

#include <vector>
#include <map>

#include <iostream>
using namespace std;

class GameState;
#include "object.cpp"

class GameState
{
private:
  class Window
  {
  public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width = 1280;
    int height = 720;
  };

  class Input
  {
  public:
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    SDL_Event event;

    map<int, bool> keysMap;

    bool keysMapContains(vector<int> keys);
  };

  class Frames
  {
  public:
    bool running = 1;
    int lastFrame = SDL_GetTicks();
    int timeBetweenLastFrames = 0;

    int FPS_Limit = 600;
    int fps = 0;

    Frames() { lastFrame = SDL_GetTicks(); }
  };

  class Textures
  {
  private:
    map<string, SDL_Texture *> textures;

  public:
    SDL_Texture *GetTexture(SDL_Renderer *renderer, string path);

    Textures(SDL_Renderer *renderer, vector<string> preload = {})
    {
      for (int i = 0; i < preload.size(); i++)
        GetTexture(renderer, preload[i]);
    }
  };

  class Camera
  {
  public:
    float xPos = 0;
    float yPos = 0;
  };

public:
  int scene = 0;
  vector<Object> scenes;

  Window window = Window();

  Input input = Input();

  Frames frames = Frames();

  Textures textures = Textures(window.renderer, {});

  Camera camera;

  Object *getScene(int _scene = -1) { return &scenes[_scene == -1 ? scene : _scene]; }
  void addScene(Object _scene)
  {
    _scene.parent = nullptr;
    scenes.push_back(_scene);
  };
  void setScene(int _scene) { scene = _scene; };

  GameState() {}
  const bool coutTime = false;
};

#include "include.h"