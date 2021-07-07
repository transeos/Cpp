// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 27/05/19.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::set;
using std::string;
using std::unordered_set;
using std::vector;

#define TEST_M_VAL 10

class Base {
private:
  int _val;
  int _val3;

public:
  explicit Base(int val) : _val(val) {
    printf("Base(%p, val = %d) created\n", this, _val);
  }
  ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

  int GetVal() const { return _val; }
  void SetVal(int val) { _val = val; }

  bool operator==(const Base &rhs) { return (_val == rhs._val); }

  int _val2;
};

// Compute  hash values for Base as integer:
template <> struct std::hash<Base> {
  std::size_t operator()(const Base &k) const { return k.GetVal(); }
};

int main(const int argc, const char **argv) {
  cout << "\n=== lower bound ===\n";
  {
    vector<int> a = {1, 1, 3, 3, 5, 5, 7, 7, 9, 9};
    for (int num : a) {
      cout << num << " ";
    }
    cout << endl;

    auto low_iter = lower_bound(a.begin(), a.end(), 0);
    cout << "Lower bound of 0 : " << (low_iter - a.begin()) << endl;

    low_iter = lower_bound(a.begin(), a.end(), 10);
    cout << "Lower bound of 10 : " << (low_iter - a.begin()) << endl;

    low_iter = lower_bound(a.begin(), a.end(), 4);
    cout << "Lower bound of 4 : " << (low_iter - a.begin()) << endl;

    auto up_iter = upper_bound(a.begin(), a.end(), 4);
    cout << "Upper bound of 4 : " << (low_iter - a.begin()) << endl;

    low_iter = lower_bound(a.begin(), a.end(), 5);
    cout << "Lower bound of 5 : " << (low_iter - a.begin()) << endl;
  }
  cout << endl;

  cout << "\n=== unordered set ===\n";
  { unordered_set<Base> list; }
  cout << endl;

  cout << "\n=== macro ===\n";
  { cout << "TEST_M_VAL: " << TEST_M_VAL << endl; }
  cout << endl;

  cout << "\n=== string ===\n";
  {
    vector<string> v = {"test0", "test1", "test2"};
    cout << v[0] << endl;
  }
  cout << endl;

  cout << "\n=== syntax ===\n";
  {
    Base *b = new Base(10);
    cout << sizeof(Base) << "," << b << "," << &(b->_val2) << ","
         << ((Base *)(&(b->_val2)) + 1) << endl;
  }
  cout << endl;

  cout << "\n=== iterator increment/decrement ===\n";
  {
    set<int32_t> set1 = {0, 1, 2, 3, 4};

    set<int32_t>::iterator it = set1.begin();
    it++;
    auto it2 = it--;
    cout << *it2 << " " << *it << endl;
  }
  cout << endl;

  cout << endl << "=== Finish ===" << endl << endl;
  return 0;
}
