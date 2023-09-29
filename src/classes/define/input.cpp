bool GameState::Input::keysMapContains(vector<int> keys)
{
  for (int i = 0; i < keys.size(); i++)
  {
    if (keysMap.count(keys[i]))
      return 1;
  }
  return 0;
}