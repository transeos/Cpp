// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Updated by Hiranmoy on 06/07/21.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;

class Foo {
public:
  Foo(int32_t s = 0) {
    cout << "Foo constructor called\n";

    arrptr_ = NULL;
    size_ = s;
    if (size_ > 0)
      arrptr_ = new int32_t[size_];
  }

  Foo(const Foo &foo) {
    cout << "copy constructor called\n";
    size_ = foo.size_;

    arrptr_ = new int32_t[size_];
    for (int32_t i = 0; i < size_; i++)
      arrptr_[i] = foo.arrptr_[i];
  }

  Foo(Foo &&foo) {
    cout << "Move constructor called\n";
    size_ = foo.size_;
    foo.size_ = 0;

    arrptr_ = foo.arrptr_;
    foo.arrptr_ = NULL;
  }

  ~Foo() {
    cout << "Foo destructor called\n";
    if (arrptr_)
      delete arrptr_;
  }

private:
  int32_t *arrptr_;
  int32_t size_;

public:
  Foo &operator=(const Foo &foo) {
    cout << "= called\n";

    if (arrptr_)
      delete arrptr_;

    size_ = foo.size_;

    if (arrptr_) {
      arrptr_ = new int32_t[size_];
      for (int32_t i = 0; i < size_; i++)
        arrptr_[i] = foo.arrptr_[i];
    }

    return *this;
  }

  Foo &operator+=(const Foo &right) {
    cout << "+= called\n";

    int32_t *newarr = new int32_t[size_ + right.size_];
    for (int32_t i = 0; i < size_; i++)
      newarr[i] = arrptr_[i];
    for (int32_t j = 0; j < right.size_; j++)
      newarr[j] = right.arrptr_[j];

    if (arrptr_)
      delete arrptr_;
    arrptr_ = newarr;

    size_ += right.size_;

    return *this;
  }

  template <typename T> friend T operator+(T &&left, T &&right) {
    T res = std::forward<T>(left);
    res += right;
    return res;
  }
};

int32_t main(const int32_t argc, const char **argv) {
  cout << endl << "=== rvalue and lvalue ===" << endl;
  {
    Foo a(10);
    Foo b(15);
    Foo c(20);
    Foo p = a + b + c;

    cout << " ###### " << endl;

    Foo q = std::move(a) + std::move(b) + Foo(30);
    cout << endl;
  }

  cout << endl << "=== Finish ===" << endl << endl;
  return 0;
}
