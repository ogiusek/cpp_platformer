SDL_Texture *GameState::Textures::GetTexture(SDL_Renderer *renderer, string path)
{
  if (textures.count(path))
    return textures[path];

  SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
  textures.insert(make_pair(path, texture));

  return texture;
}