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
using std::string_view;
using std::tuple;

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

template <typename T> struct Name {
  Name(T first, T last) : First(first), Last(last) {}

  T First;
  T Last;
};

Name(const char *)->Name<string_view>;

template <auto v> struct Constant { static constexpr auto InitValue = v; };

using IntStruct = Constant<2048>;

template <typename T>
typename std::enable_if_t<std::is_integral_v<T>, T> SquareRoot(T t) {
  cout << "[integral] ";
  return sqrt(t);
}

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
  }

  cout << "=== fold expression ===\n";
  {
    int a = 1;
    int b = 1;
    double c = 1.1;
    cout << Sum(a, c, b, 1) << endl;
    cout << Sum() << endl;
  }
  cout << endl;

  cout << "=== class template deduction ===\n";
  {
    cout << "=== with tuple ===\n";
    {
      auto t = tuple(1, 1.1);
      cout << std::get<0>(t) << ", " << std::get<1>(t) << endl;
    }
    cout << endl;

    cout << "=== char const* to string_view ===\n";
    {
      Name n1("John", "Smith"); // string_view

      string first = n1.First;
      string last = n1.Last;

      Name n2(first, last); // string
    }
  }
  cout << endl;

  cout << "\n=== template auto ===\n";
  { cout << IntStruct::InitValue << endl; }
  cout << endl;

  cout << "\n=== variable templates for meta-functions ===\n";
  {
    int num1 = 4;
    cout << SquareRoot(num1) << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;
  return 0;
}
