// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 8/7/21.
//
//*****************************************************************

#include <bits/stdc++.h>
#include <execution>

using std::cout;
using std::endl;
using std::vector;

int32_t main(const int32_t argc, const char **argv) {
  cout << "\n=== parallel sort ===\n";
  {
    vector<int32_t> vec = {1, 5, 2, 4, 3};
    std::sort(std::execution::par, vec.begin(), vec.end());

    for (auto elm : vec)
      cout << elm << ", ";
    cout << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
