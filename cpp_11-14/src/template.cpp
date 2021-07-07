// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 12/03/19.
//
//*****************************************************************

#include <bits/stdc++.h>

#include "template_variadic.h"

using std::array;
using std::cout;
using std::endl;
using std::tuple;
using std::vector;

constexpr int32_t TestGetNum(const int32_t n) { return (n * 2); }

// Due to reinterpret_cast, this function cannot be declared as 'constexpr'.
bool IsLittleEndian() {
  const uint16_t n = 0x0001;
  const uint8_t *m = reinterpret_cast<const uint8_t *>(&n);
  return (*m != 0);
}

template <typename T> void Basic::PrT(const T &val) { cout << val << endl; }

template <typename T, T v> struct Constant {
  static constexpr T InitValue = v;
};

using IntStruct = Constant<int, 2048>;

template <typename T = int32_t, size_t NUM = 1> class Base {
private:
  array<T, NUM> _vals;

protected:
  bool _printVal;

public:
  Base(const T &val) {
    _printVal = true;

    for (size_t idx = 0; idx < NUM; idx++)
      _vals[idx] = (val * (idx + 1));

    cout << "Base(" << this;
    if (_printVal) {
      cout << ", val = ";
      Pr(false);
    }
    cout << ") created\n";
  }
  ~Base() {
    cout << "Base(" << this;
    if (_printVal) {
      cout << ", val = ";
      Pr(false);
    }
    cout << ") destroyed\n";
  }

  const T &GetVal(const size_t idx = 0) const { return _vals[idx]; }

  constexpr int32_t Num() const { return NUM; }

  void Pr(const bool newLine = true) const {
    for (size_t idx = 0; idx < NUM; idx++)
      cout << GetVal(idx) << " ";

    if (newLine)
      cout << "(" << Num() << ")" << endl;
  }
};

template <typename T, typename U> bool CompareT(const T &a, const U &b) {
  return a == b;
}

template <typename T, typename U, typename... Args>
bool CompareT(const T &a, const U &b, Args... args) {
  return ((a == b) && CompareT(args...));
}

template <typename T = char> void PrintCharT(const T *a) { cout << a; }

template <typename T = char, typename... Args>
void PrintCharT(const T *a, Args... args) {
  PrintCharT(a);
  cout << " ";
  PrintCharT(args...);
}

template <size_t, class> struct VarStructT;

template <size_t k, class... Ts>
typename std::enable_if<k == 0,
                        typename VarStructT<0, tuple<Ts...>>::type &>::type
std::get(tuple<Ts...> &t) {
  return t.tail;
}

template <size_t k, class T, class... Ts>
typename std::enable_if<k != 0,
                        typename VarStructT<k, tuple<T, Ts...>>::type &>::type
std::get(tuple<T, Ts...> &t) {
  tuple<Ts...> &base = t;
  return std::get<k - 1>(base);
}

template <typename T, typename... Args> class VarT {
private:
  T _commonVal;
  tuple<Args...> _vars;

  template <size_t k> typename std::enable_if<k == 0, void>::type Pr() {
    cout << "start -> " << GetVal<k>() << endl;
  }

  template <size_t k> typename std::enable_if<k != 0, void>::type Pr() {
    Pr<k - 1>();
    cout << GetVal<k>() << endl;
  }

public:
  VarT(const T &val, const Args &... args)
      : _vars{std::move(args)...}, _commonVal(val) {}
  ~VarT() {}

  void SetCommonVal(const T &val) { _commonVal = val; }
  T &GetCommonVal() { return _commonVal; }

  template <size_t k> auto GetVal() -> decltype(std::get<k>(_vars)) & {
    return std::get<k>(_vars);
  }

  void printAll() {
    Pr<sizeof...(Args) - 1>();
    cout << "-> end" << endl;
  }
};

template <typename... Args> class VarArrT {
private:
  tuple<vector<Args>...> _vars;

public:
  VarArrT(const vector<Args> &... args) : _vars(args...) {}
  ~VarArrT() {}

  template <size_t k> auto getArr() -> decltype(std::get<k>(_vars)) & {
    return std::get<k>(_vars);
  }
};

template <typename T, typename... Args> class Var2T {
private:
  tuple<T, Args...> _vars;

  // CheckType() is an empty function to pointer restriction on first argument
  typename std::enable_if<std::is_pointer<T>::value, void>::type checkType() {}

  template <size_t k> void printVar();

  template <size_t k> typename std::enable_if<k == 0, void>::type Pr() {
    printVar<k>();
  }

  template <size_t k> typename std::enable_if<k != 0, void>::type Pr() {
    Pr<k - 1>();
    printVar<k>();
  }

public:
  Var2T(const T &val, const Args &... args) : _vars{val, std::move(args)...} {}
  ~Var2T() {}

  template <size_t k> auto GetVal() -> decltype(std::get<k>(_vars)) & {
    return std::get<k>(_vars);
  }

  void printAll() { Pr<sizeof...(Args)>(); }
};

template <typename T, typename... Args>
template <size_t k>
void Var2T<T, Args...>::printVar() {
  cout << "[" << k << "] " << std::get<k>(_vars) << endl;
}

int32_t main(const int32_t argc, const char **argv) {
  cout << "\n=== template with default type and constant value ===\n";
  {
    Base<> b1(1.1);
    b1.Pr();
    Base<float> b2(1.1);
    b2.Pr();
    Base<int32_t, 2> b3(1.1);
    b3.Pr();

    constexpr int32_t c = TestGetNum(2);
    Base<float, c> b4(1.1);
    b4.Pr();
  }

  cout << "\n=== Variadic function templates ===\n";
  {
    {
      auto sp = std::make_shared<Base<>>(2);
      auto sp2 = sp;

      const bool output = CompareT(1, 1, sp2, sp);
      cout << output << endl;
    }
    cout << endl;
    {
      PrintCharT<>("Pass any", "number of arguments", "to print");
      cout << endl;
    }
  }

  cout << "\n=== Variadic template structures ===\n";
  {
    tuple<double, uint64_t, const char *> t(12.2, 42, "big");

    cout << "0th item = " << std::get<0>(t) << endl;
    cout << "1st item = " << std::get<1>(t) << endl;
    cout << "2nd item = " << std::get<2>(t) << endl;

    std::get<1>(t) = 103;
    cout << "1st item = " << std::get<1>(t) << endl;
  }

  cout << "\n=== Variadic template class ===\n";
  {
    {
      VarT<const char *, double, uint64_t, const char *> var("common elem",
                                                             12.2, 42, "big");

      cout << var.GetCommonVal() << endl;
      cout << var.GetVal<0>() << endl;
      cout << var.GetVal<1>() << endl;
      cout << var.GetVal<2>() << endl;

      cout << endl;
      var.printAll();
    }
    cout << endl;
    {
      VarArrT<const char *, int32_t> var_arr({"Element 00", "Element 01"},
                                             {10, 11});

      cout << var_arr.getArr<0>()[0] << ", " << var_arr.getArr<0>()[1] << endl;
      cout << var_arr.getArr<1>()[0] << ", " << var_arr.getArr<1>()[1] << endl;
    }
    cout << endl;
    {
      Var2T<const char *, double, uint64_t, const char *> var("1st elem", 1.1,
                                                              2, "last elem");

      var.printAll();
    }
  }

  cout << "\n=== Template function in header file ===\n";
  {
    Basic b;
    b.PrT<>(1);
    b.PrT<const char *>("test");
  }
  cout << endl;

  cout << "\n=== initalization (meta programming) ===\n";
  {
    IntStruct num;
    cout << num.InitValue << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;
  return 0;
}
