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

// preprocessor predicate for header testing
#if __has_include(<invalid_header.h>)
#elif __has_include("common.h")
#include <common.h>
#else
int32_t gExternFlag = -1;
#endif

using std::cout;
using std::endl;

void Miscellaneous2() {
  cout << "\n=== global ===\n";
  { cout << "Global flag: " << gExternFlag; }
  cout << endl;
}
