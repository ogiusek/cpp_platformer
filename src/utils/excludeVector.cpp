#include <vector>

using namespace std;

template <typename T>
vector<T> excludeVector(vector<T> vec1, vector<T> vec2)
{
  for (auto it1 = vec1.begin(); it1 != vec1.end();)
  {
    bool found = false;
    for (auto it2 = vec2.begin(); it2 != vec2.end(); ++it2)
    {
      if (*it1 == *it2)
      {
        found = true;
        break;
      }
    }

    if (found)
      it1 = vec1.erase(it1);
    else
      ++it1;
  }
  return vec1;
}