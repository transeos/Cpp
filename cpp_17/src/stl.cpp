// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 9/7/21.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::unordered_map;

class Base {
private:
  int32_t _val;

public:
  Base(int32_t val) : _val(val) {
    printf("Base(%p, val = %d) created\n", this, _val);
  }
  virtual ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

  int32_t GetVal() const { return _val; }
  void SetVal(int32_t val) { _val = val; }
};

int main(const int argc, const char **argv) {
  cout << "\n=== insertion in map ===\n";
  {
    unordered_map<int, Base> data;

    {
      Base b1(1);
      if (auto it = data.try_emplace(b1.GetVal(), b1); it.second == true)
        cout << "emplace successful at index " << it.first->first << endl;

      Base b2(2);
      if (auto it = data.try_emplace(b1.GetVal(), b2); it.second == false)
        cout << "emplace failed at index " << it.first->first << endl;

      Base b3(3);
      if (auto it = data.insert_or_assign(b1.GetVal(), b3); it.second == false)
        cout << "overwrite at index " << it.first->first << endl;
      cout << endl;
    }
    cout << endl;

    unordered_map<int, Base> data2;
    auto node = data.extract(1);
    node.key() = 2;
    data2.insert(std::move(node));
    for (auto it : data2)
      cout << it.first << " : " << it.second.GetVal() << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
