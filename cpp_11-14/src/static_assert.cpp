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

template <typename T = int> class Base {
  static_assert(std::is_default_constructible<T>::value,
                "Base class template requires default-constructible elements");
  static_assert(!std::is_default_constructible<Base<T>>::value,
                "Base class should not have default-constructible");

protected:
  T _val;

public:
  Base(const T &val) : _val(val) {
    static_assert(
        ((sizeof(*this) + sizeof(this) - 1) / sizeof(this)) ==
            (((sizeof(T) + sizeof(this) - 1) / sizeof(this)) + 1),
        "this program requires that size of Base<T> is same as {T + pointer}");
  }
  virtual ~Base() {}

  // const T GetVal() const final { return _val; }  // (not allowed)
  virtual const T GetVal() const final { return _val; }

  // const T GetDVal() const { return T(); }  // (not allowed)
  virtual const T GetDVal() const { return T(); }
};

template <typename T = int> class Derived : public Base<T> {
private:
  T d_val;

public:
  Derived(const T &val1, const T &val2) : Base<T>(val1), d_val(val2) {}
  virtual ~Derived() {}

  // const T GetVal() const { return Base<T>::_val; }   // (not allowed)
  // const T GetDVal() const override { return d_val; } // (not allowed)
  // (only derived class definition not allowed )
  // virtual const T GetDVal() const override { return d_val; }
  virtual const T GetDVal() const override { return d_val; }
};

void Pr(int i) { cout << "[int] " << i << endl; }

void Pr(void *ptr) { cout << "[ptr] " << ptr << endl; }

int main(const int argc, const char **argv) {
  cout << "\n=== static assertions ===\n";
  {
    Base<> b(1.1);
    cout << "Size of b = " << sizeof(b) << endl;
    cout << b.GetVal() << ", " << b.GetDVal() << endl;

    Derived<> d(1.1, 2.2);
    cout << "Size of d = " << sizeof(d) << endl;
    cout << d.GetVal() << ", " << d.GetDVal() << endl;
  }

  cout << "\n=== nullptr ===\n";
  {
    // Pr(NULL); compile error
    Pr(nullptr);
  }

  cout << endl << "=== Finish ===" << endl << endl;
  return 0;
}
