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

using std::array;
using std::cout;
using std::endl;
using std::optional;
using std::string;
using std::variant;

optional<bool> IsEven(int32_t num) {
  optional<bool> retVal;
  // optional<bool> retVal = std::nullopt works as well

  if (num >= 0)
    retVal = (num % 2 == 0);

  return retVal;
}

int32_t GetDiff(optional<int32_t> a, std::optional<int32_t> b) {
  return (a.value_or(0) - b.value_or(0));
}

int32_t main(const int32_t argc, const char **argv) {
  cout << "\n=== std::optional ===\n";
  {
    if (optional<bool> val = IsEven(-1); val.has_value() == false)
      cout << "negative" << endl;
    if (optional<bool> val = IsEven(2);
        ((val.has_value() == true) && (val.value() == true)))
      cout << "even" << endl;
    if (optional<bool> val = IsEven(3);
        ((val.has_value() == true) && (val.value() == false)))
      cout << "odd" << endl;
    cout << endl;

    cout << GetDiff(4, optional<int32_t>()) << endl;
  }
  cout << endl;

  cout << "\n=== variant ===\n";
  {
    variant<string, int32_t, array<int32_t, 100>> v;
    cout << sizeof(v) << endl;

    v = "variant string";
    cout << std::get<string>(v) << endl;

    v = 1.1;
    cout << std::get<int32_t>(v) << endl;

    v = array<int32_t, 100>();
    std::get<array<int32_t, 100>>(v)[0] = 2;
    std::get<array<int32_t, 100>>(v)[1] = 3;
    for (size_t idx = 0; idx < 2; ++idx) {
      cout << std::get<array<int32_t, 100>>(v)[idx] << ", ";
    }
    cout << endl;
  }

  cout << "\n=== std::any ===\n";
  {
    std::any var = 1;

    if (var.type() == typeid(int))
      cout << var.type().name() << " : " << std::any_cast<int>(var) << endl;

    var.reset();
    if (!var.has_value())
      cout << "no value found in var" << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
