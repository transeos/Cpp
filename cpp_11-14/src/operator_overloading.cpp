// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 28/05/19.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;

class Base
{
  private:
    int32_t _val;

  public:
    explicit Base(int32_t val) : _val(val) { printf("Base(%p, val = %d) created\n", this, _val); }
    ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

    int32_t GetVal() const { return _val; }
    void SetVal(int32_t val) { _val = val; }

    void operator+=(const int32_t rhs) { _val += rhs; }
    void operator+=(const Base& rhs) { _val += rhs._val; }
    Base operator+(const Base& rhs) { return Base(_val + rhs._val); }
    void operator=(const int32_t rhs) { _val = rhs; }

    operator int32_t() const { return _val; }

    friend std::ostream& operator<<(std::ostream& os, const Base& b)
    {
      os << "Value : " << b._val << endl;
      return os;
    }
};

int32_t main(const int32_t argc, const char** argv)
{
  cout << "\n=== operator overloading ===\n";
  {
    Base b(1);
    b += 1;
    cout << b << endl;

    b += Base(2);
    cout << b << endl;

    b = b + Base(3);
    cout << b << endl;

    b = 10;
    cout << b << endl;

    int32_t a = b;
    cout << a << endl;
  }
  cout << endl << "=== Finish ===" << endl << endl;
  
  return 0;
}
