// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 17/03/19.
//
//*****************************************************************

#include <bits/stdc++.h>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::thread;

template<typename T = int32_t>
class Base
{
  private:
    T _val;

    std::function<void(const T&)> lambda_;

  public:
    Base(const T& val) : _val(val)
    {
      printf("Base(%p, val = %d) created\n", this, _val);

      lambda_ = [&](const T& a) { cout << GetMultipliedVal(a) << endl; };
    }
    virtual ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

    virtual T GetVal() const { return _val; }
    virtual void SetVal(const T& val) { _val = val; }

    virtual T GetMultipliedVal(const T& mult) const { return (_val * mult); }

    void setLambda(std::function<void(const T&)> lambda) { lambda_ = lambda; }
    void lambdaCall(const T& multiplier) const { lambda_(multiplier); }
};

// typedef version of function pointer
//typedef void (Base<>::*BaseFnPtr)(int32_t);

// alias version of function pointer
template<typename T = int32_t> using BaseFnPtr = void (Base<T>::*)(const T&);

class Derived : public Base<>
{
  private:
    int32_t _dVal;

  public:
    Derived(int32_t val) : Base(val - 1), _dVal(val)
    {
      printf("Derived(%p, val = %d) created\n", this, _dVal);
    }
    virtual ~Derived() { printf("Derived(%p, val = %d) destroyed\n", this, _dVal); }

    virtual int32_t GetVal() const { return _dVal; }
    virtual void SetVal(const int32_t& val) override { _dVal = val; }

    virtual int32_t GetMultipliedVal(const int32_t& mult) const override { return (_dVal * mult); }
};

int32_t gNumber = 5;
auto delBase = [&gNumber](Base<>* b)
{
  cout << "custom lambda deleter (" << gNumber << ")" << endl;
  delete b;
};

void BindFnCallBack(std::function<int32_t(void)> callback)
{
  cout << callback() << endl;
}

auto mult = [](int32_t a, int32_t b) -> int32_t
{
  return (a * b);
};

int32_t main(const int32_t argc, const char** argv)
{
  cout << "\n=== funcion pointers ===\n";
  {
    {
      Derived d(2);
      BindFnCallBack(std::bind(&Base<>::GetMultipliedVal, &d, 5));
    }
    cout << endl;
    {
      Base<> b(3);
      Derived d(5);

      BaseFnPtr<> fn = &Base<>::SetVal;

      (b.*fn)(6);
      (d.*fn)(7);
      cout << endl;
    }
  }

  cout << "\n=== lambda expressions ===\n";
  {
    {
      vector<int32_t> v = {4, 1, 3, 6, 2, 3, 1, 7};
      for (auto& item : v)
        cout << item << " ";
      cout <<endl;

      sort(v.begin(), v.end(), [](const int32_t& a, const int32_t& b) -> bool { return a > b; } );

      for (auto& item : v)
        cout << item << " ";
      cout << endl;

      vector<int32_t>::iterator iter = find_if(v.begin(), v.end(), [](int32_t a) {
        return a < 5;
      } );
      cout << "[" << (iter - v.begin()) << "] " << *iter << endl;

      auto sum = [](const vector<int32_t>& vec) 
      {
        int32_t s = 0;
        for (auto& item : vec)
          s += item;
        return s;
      };
      cout << "sum of all elements = " << sum(v) << endl;
    }
    cout << endl;

    {
      cout << mult(2, 4.1) << endl;
    }

    {
      shared_ptr<Base<>> sb(new Base<>(1), [](Base<>* ptr) { cout << "Deletion skipped" << endl; });
      unique_ptr<Base<>, decltype(delBase)> ub(new Base<>(2), delBase);
      cout << endl;

      sb->lambdaCall(5);

      sb->setLambda([sb](const int32_t& a) { cout << (sb->GetMultipliedVal(a) * 2) << endl; } );
      sb->lambdaCall(5);

      cout << endl;
    }
    cout << endl;
  }

  cout << "\n=== unique pointer size ===\n";
  {
    shared_ptr<Base<>> sb(new Base<>(1), [](Base<>* ptr) { cout << "Deletion skipped" << endl; });
    unique_ptr<Base<>, decltype(delBase)> ub(new Base<>(2), delBase);
    cout << endl;
    unique_ptr<Base<>, void(*)(Base<>*)> ub2(new Base<>(3),
                                             [](Base<>* b)
                                             {
                                               cout << "inline lambda delete called\n";
                                               delete b;
                                             } );
    unique_ptr<Base<>, std::function<void(Base<>*)>> ub3(new Base<>(4),
                                                         [](Base<>* b)
                                                         {
                                                           cout << "decltype lambda delete called\n";
                                                           delete b;
                                                         } );
    cout << "==== ub = " << sizeof(ub) << endl;
    cout << "==== ub2 = " << sizeof(ub2) << endl;
    cout << "==== ub3 = " << sizeof(ub2) << endl;
  }
  cout << endl;

  cout << "\n=== lambda functions with thread ===\n";
  {
    vector<thread> workers;
    for (int32_t idx = 0; idx < 5; idx++) {
      workers.emplace_back(
        ([idx]() 
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (5 - idx)));
            cout << "thread function " << idx << endl;
          } ) );
    }
    cout << "main thread\n";

    std::for_each(workers.begin(), workers.end(), [](thread &t) {
      t.join();
    } );
  }

  cout << endl << "=== Finish ===" << endl << endl;
  return 0;
}
