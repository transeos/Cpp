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

// typedef struct __attribute__((__packed__)) node_ {
// typedef struct __attribute__((__aligned__)) node_ {
typedef struct node_ {
  char c;
  double x;
  int32_t b;
} Node;

class Base {
private:
  int32_t _val;

public:
  Base(int32_t val) : _val(val) {
    printf("Base(%p, val = %d) created\n", this, _val);
  }
  ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

  int32_t GetVal() const { return _val; }
  void SetVal(int32_t val) { _val = val; }

  float FloatVal;
};

class Derived : public Base {
public:
  Derived(int32_t val) : Base(val) {}
  ~Derived() {}
  // Virtual destructor will create seg fault in this program.
  // virtual ~Derived() { }
};

int32_t main(const int32_t argc, const char **argv) {
  cout << "\n=== dynamic_cast ===\n";
  {
    Base *b = new Derived(10);
    // Error: as "Base" class is not polymorphic
    // Derived* d = dynamic_cast<Derived*>(b);
    delete b;
  }
  cout << endl;

  cout << "\n=== reference ===\n";
  {
    int32_t a = 1;
    int32_t b = 2;
    const int32_t *p1 = &a;
    p1 = &b;

    int32_t *const p2 = &b;
    // p2 = &a;
    cout << *p2 << endl;

    Base b1(20);
    Base &r1 = b1;

    Base b2(21);
    Base &r2 = b2;

    r1 = b2;
    b2.SetVal(b2.GetVal() + 1);

    r2 = b1;

    cout << r1.GetVal() << "," << r2.GetVal() << endl;

    // int32_t** arr = &((int32_t*) malloc(sizeof(int32_t) * 25);
  }
  cout << endl;

  cout << "\n=== string character position ===\n";
  {
    std::string str1 = "-100";
    cout << "=== " << str1[0] << " ===" << endl;
  }
  cout << endl;

  cout << "\n=== memory alignment ===\n";
  {
    // string a = "abc";
    // cout << sizeof(a) << endl;
    cout << sizeof(Node) << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
