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

auto Add = [](int a, int b) { return (a + b); };

constexpr int32_t gNum = Add(5, 6);

int32_t main(const int32_t argc, const char **argv) {
  cout << "\n=== constexpr lambda ===\n";
  { cout << gNum << endl; }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
