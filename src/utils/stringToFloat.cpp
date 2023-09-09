#include <bits/stdc++.h>
using namespace std;

float stringToFloat(string str)
{
  try
  {
    return stof(str);
  }
  catch (const std::invalid_argument &e)
  {
    return 0;
  }
}