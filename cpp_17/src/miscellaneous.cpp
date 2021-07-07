// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 7/7/21.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::array;

class Base
{
  private:
    int32_t _val;

  public:
    Base(int32_t val) : _val(val) { printf("Base(%p, val = %d) created\n", this, _val); }
    virtual ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

    int32_t GetVal() const { return _val; }
    void SetVal(int32_t val) { _val = val; }

    float FloatVal;
};

class Derived : public Base
{
  public:
    Derived(int32_t val) : Base(val) { }
    virtual ~Derived() { }
};

int32_t main(const int32_t argc, const char** argv)
{
  cout << "\n=== structured bindings ===\n";
  {
    array<int32_t, 3> arr = {0, 1, 2};

    auto& [a, b, c] = arr;
    a++;
    b--;
    int32_t* p = &c;
    *p = 0;

    for (auto elm : arr)
      cout << elm << ", ";
  }
  cout << endl;

  cout << "\n=== initialise inside if ===\n";
  {
    if (time_t now = time(0); (now % 3) == 1)
      cout << "odd second1: " << now << endl;
    else if (struct tm* ptm = gmtime(&now); (now % 3) == 2)
      cout << "UTC time= " << ptm->tm_hour << ":" << ptm->tm_min << endl;
    else
      cout << "odd second2: " << now << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
