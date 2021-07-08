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

struct Increment {
  void operator()(int &num) const { num++; }
};

struct MultiplyWith {
  MultiplyWith(int m) : _m(m) {}

  int operator()(int num) const { return (num * 2); }

private:
  int _m;
};

struct Multiply {
  int operator()(int num1, int num2) const { return (num1 * num2); }
};

struct Sum {
  int operator()(int num1, int num2) const { return (num1 + num2); }
};

int main(const int argc, const char **argv) {
  cout << "\n=== parallel ===\n";
  {
    vector<int> vec = {1, 5, 2, 4, 3};

    for_each(std::execution::par_unseq, vec.begin(), vec.end(), Increment());
    std::sort(std::execution::par, vec.begin(), vec.end());

    for (auto elm : vec)
      cout << elm << ", ";
    cout << endl;
  }
  cout << endl;

  cout << "\n=== transform_reduce ===\n";
  {
    vector<int> vec1 = {1, 1, 1, 1, 1};
    vector<int> vec2 = vec1;
    std::sort(std::execution::par_unseq, vec2.begin(), vec2.end());

    std::transform(vec1.begin(), vec1.end(), vec1.begin(), MultiplyWith(2));
    int sum = std::reduce(vec1.begin(), vec1.end(), 1, Sum());
    cout << sum << endl;

    for (auto elm : vec1)
      cout << elm << ", ";
    cout << endl;
    for (auto elm : vec2)
      cout << elm << ", ";
    cout << endl;

    int compute1 =
        std::transform_reduce(std::execution::par_unseq, vec1.begin(),
                              vec1.end(), 0, Sum(), MultiplyWith(2));
    cout << compute1 << endl;

    for (auto elm : vec1)
      cout << elm << ", ";
    cout << endl;

    int compute2 = std::transform_reduce(std::execution::par_unseq,
                                         vec1.begin(), vec1.begin() + 4,
                                         vec2.begin(), 100, Sum(), Multiply());
    cout << compute2 << endl;
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;

  return 0;
}
