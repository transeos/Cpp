// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 7/7/2.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::forward;
using std::string;

template <typename T0, typename... Ts> void PrintT(T0 &&t0, Ts &&... ts) {
  cout << t0;

  if constexpr (sizeof...(ts)) {
    cout << ", ";
    PrintT(forward<Ts>(ts)...);
  }
}

template <typename... Ts> void PrintFold(Ts &&... ts) {
  (cout << "[fold] " << ... << std::forward<Ts>(ts)) << endl;
}

template <typename... Ns> auto Sum(Ns &&... ns) { return (ns + ... + 0); }

struct Person {
  Person(const uint32_t id, const string &name, uint16_t age)
      : _id(id), _name(name), _age(age) {}

  template <std::size_t I> auto &Get() {
    if constexpr (I == 0)
      return _id;
    else if constexpr (I == 1)
      return _name;
    else if constexpr (I == 2)
      return _age;
  }

private:
  uint32_t _id;
  string _name;
  uint16_t _age;
};

int32_t main(const int32_t argc, const char **argv) {
  cout << "\n=== complie time conditional statement ===\n";
  {
    cout << "=== variadic template function ===\n";
    {
      int32_t a = 1;
      double b = 2.1;
      char c = 'c';
      string d = "variadic";

      PrintT(a, b, c);
      cout << endl;
      PrintFold(a, b, c);

      PrintT(d);
      cout << endl;
      PrintFold(d);
    }
    cout << endl;

    cout << "=== get function like tuple ===\n";
    {
      Person p1(1, "nameless", 18);
      cout << p1.Get<0>() << ", " << p1.Get<1>() << ", " << p1.Get<2>() << endl;
    }
    cout << endl;

    cout << "=== fold expression ===\n";
    {
      int a = 1;
      int b = 1;
      double c = 1.1;
      cout << Sum(a, c, b, 1) << endl;
      cout << Sum() << endl;
    }
    cout << endl;
  }

  cout << "=== Finish ===" << endl << endl;
  return 0;
}
