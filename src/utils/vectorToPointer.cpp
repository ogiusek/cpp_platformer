#include <vector>

using namespace std;

template <typename T>
vector<T *> to_pointer_vector(vector<T> *v)
{
  vector<T *> v_ptr;
  for (int i = 0; i < v->size(); i++)
    v_ptr.push_back(&v->at(i));

  return v_ptr;
}
