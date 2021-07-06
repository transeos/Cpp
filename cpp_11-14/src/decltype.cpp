// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 17/03/19.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::vector;

// can only be used for constexpr
template <typename A, typename B> 
auto FindMin(const A& a, const B& b) -> decltype(a < b ? a : b) 
{
  return ((a < b) ? a : b);
}

class Base
{
  private:
    int32_t _val;

  public:
    Base(int32_t val) : _val(val) { printf("Base(%p, val = %d) created\n", this, _val); }
    ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

    int32_t GetVal() const { return _val; }
    void SetVal(int32_t val) { _val = val; }

    float FloatVal;
};

class Derived : public Base
{
  public:
    Derived(int32_t val) : Base(val) { }
    ~Derived() { }
};

int32_t main(const int32_t argc, const char** argv)
{
  cout << "\n=== decltype ===\n";
  {
    cout << FindMin(4, 3.44) << endl;
    cout << FindMin(5.4, 3) << endl;

    cout << endl;
    decltype(std::declval<Base>().GetVal()) a = 0;
    decltype(std::declval<Base>().FloatVal) b = 0;
    cout << typeid(a).name() << ", " << typeid(b).name() << endl;
  }

  cout << "\n=== auto ===\n";
  {
    cout << endl;
    {
      vector<Base> arr = { Base(1) };
      arr[0].SetVal(2);
      cout << endl;
    }
    cout << endl;
    {
      vector<Base> arr;
      arr.emplace_back(3);
      for (auto b : arr) {
        b.SetVal(4);
      }
      cout << endl;
    }
    cout << endl;
    {
      vector<Base> arr = { Base(5) };
      for (auto b : arr)
        b.SetVal(6);
      cout << endl;
    }
    cout << endl;
    {
      vector<Base> arr = { Base(7) };
      for (auto& b : arr)
        b.SetVal(8);
      cout << endl;
    }
    cout << endl;
    {
      vector<Base> arr = { Base(9) };
      for (const auto& b : arr) {
        // b.SetVal(10);  // compile error
      }
      cout << endl;
    }
    cout << endl;
  }
  cout << endl << "=== Finish ===" << endl << endl;

  return 0;
}
