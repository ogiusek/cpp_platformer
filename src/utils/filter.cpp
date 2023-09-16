#include <vector>

template <typename T, typename Pred>
vector<T> filterVector(const vector<T> &vec, Pred p)
{
  vector<T> out;
  for (auto &&elem : vec)
  {
    if (p(elem))
    {
      out.push_back(elem);
    }
  }
  return out;
}