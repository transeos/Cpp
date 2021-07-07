// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Updated by Hiranmoy on 17/03/19.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

#define IS_LVALUE(...) std::is_lvalue_reference<decltype((__VA_ARGS__))>::value
#define IS_XVALUE(...) std::is_rvalue_reference<decltype((__VA_ARGS__))>::value
#define IS_PRVALUE(...) !std::is_reference<decltype((__VA_ARGS__))>::value

class Base {
private:
  int32_t _val;
  unique_ptr<Base> _uv;

public:
  Base(int32_t val) : _val(val) {
    printf("Base(%p, val = %d, uval = %d) created\n", this, _val, GetUVal());
  }
  Base(int32_t val, int32_t uval) : _val(val), _uv(new Base(uval)) {
    printf("Base(%p, val = %d, uval = %d) created\n", this, _val, GetUVal());
  }
  Base(int32_t val, unique_ptr<Base> &uv) : _val(val), _uv(std::move(uv)) {
    printf("Base(%p, val = %d, uval = %d) created\n", this, _val, GetUVal());
  }

  // copy constructor
  Base(const Base &rhs) {
    _val = rhs._val;
    if (rhs._uv)
      _uv.reset(new Base(rhs._uv->GetVal()));
    printf("Base(%p, val = %d, uval = %d) copy constructor\n", this, _val,
           GetUVal());
  }

  // move constructor
  Base(Base &&rhs) {
    _val = rhs._val;
    rhs._val = -1;
    _uv.swap(rhs._uv);
    printf("Base(%p, val = %d, uval = %d) move constructor\n", this, _val,
           GetUVal());
  }

  virtual ~Base() { printf("Base(%p, val = %d) destroyed\n", this, _val); }

  virtual int32_t GetVal() const { return _val; }

  int32_t GetUVal() const { return (_uv ? _uv->GetVal() : -1); }

  void update(decltype(_uv) &b) {
    cout << "lvalue_reference call" << endl;
    _uv.swap(b->_uv);
  }
  void update(decltype(_uv) &&b) {
    cout << "rvalue_reference call" << endl;
    _uv.reset(new Base(b->GetUVal()));
  }
};

class Derived : public Base {
private:
  int32_t _dVal;

public:
  Derived(int32_t val) : Base(val - 1), _dVal(val) {
    printf("Derived(%p, val = %d) created\n", this, GetVal());
  }
  virtual ~Derived() { printf("Derived(%p) destroyed\n", this); }

  virtual int32_t GetVal() const override { return _dVal; }
};

template <typename T> void IncrementT(T &t) { t++; }
template <typename T> void IncrementT(T &&t) {
  IncrementT(t);
  cout << "[rvalue] " << t << endl;
}
template <typename T> void IncrementWarp(T &&t) {
  IncrementT(std::forward<T>(t));
}

int32_t main(const int32_t argc, const char **argv) {
  cout << endl << "=== rvalue and lvalue ===" << endl;
  {
    {
      auto byValue = [](int32_t num) {
        cout << "[byValue function] : " << ++num << endl;
      };
      auto bylValueRef = [](int32_t &num) {
        cout << "[bylValue function] : " << ++num << endl;
      };
      auto byrValueRef = [](int32_t &&num) {
        cout << "[byrValue function] : " << ++num << endl;
      };

      int32_t a = 3;
      byValue(a); // copies
      cout << a << endl;
      bylValueRef(a); // reference
      cout << a << endl;
      // byrValueRef(a); // error

      byValue(int32_t{7}); // copies
      // bylValueRef( int32_t{7} ); // error
      byrValueRef(int32_t{7}); // reference ==> temporary object

      byrValueRef(std::move(a)); // reference
      cout << a << endl;
    }
    cout << endl;
    {
      // Base& b = Base(0);  // compile error
      Base &&b = Base(0);
    }
    cout << endl;
    {
      vector<unique_ptr<Base>> v1, v2;
      v1.push_back(unique_ptr<Base>(new Derived(1)));
      cout << "v1 size = " << v1.size() << ", v2 size = " << v2.size() << endl;
      v2 = std::move(v1);
      cout << "v1 size = " << v1.size() << ", v2 size = " << v2.size() << endl;

      cout << endl;
      auto createBase = [](int32_t val) {
        auto b_int32_t = unique_ptr<Base>(new Base(val));
        auto b = unique_ptr<Base>(new Base((val + 1), b_int32_t));
        return b;
      };

      unique_ptr<Base> b = createBase(2);
    }
  }

  cout << endl << "=== copy and move constructor ===" << endl;
  {
    {
      Base b1(3, 4);
      auto b2 = b1;
      auto b3 = std::move(b1);
      cout << endl;
    }
    cout << endl;
    {
      const Base b4(5, 6);
      auto b5 = std::move(b4);
      cout << endl;
    }
  }

  cout << endl << "=== ValueCategories === " << endl;
  {
    int32_t x = 5;
    int32_t &&y = static_cast<int32_t &&>(x);
    cout << x << endl;
    y = 4;
    cout << x << endl;

    if (IS_LVALUE(x))
      cout << "x is lvalue\n";

    if (IS_LVALUE(y))
      cout << "y is lvalue\n";

    if (IS_XVALUE(std::move(x)))
      cout << "std::move(x) is xvalue\n";

    if (IS_PRVALUE(int32_t{7}))
      cout << "int32_t {7} is prvalue\n";

    if (IS_LVALUE("const char*"))
      cout << "const char* is lvalue\n";

    if (IS_PRVALUE(vector<int32_t>(25)))
      cout << "vector<int32_t>(25) is prvalue\n";

    if (IS_LVALUE(vector<int32_t>(25)[0]))
      cout << "vector<int32_t>(25)[0] is lvalue\n";
  }
  cout << endl;

  cout << "=== unique_ptr === " << endl;
  {
    unique_ptr<Base> ub1(new Base(7));
    {
      unique_ptr<Base> ub2(new Base(8, 9));

      cout << endl;
      ub1->update(ub2);
      ub1->update(std::move(ub2));
      cout << endl;
    }
    cout << endl;
    unique_ptr<Base> ub3(new Base(10));
    cout << endl;
  }
  cout << endl;

  cout << "=== std::forward === " << endl;
  {
    int32_t num = 1;
    IncrementWarp(num);
    cout << num << endl;

    IncrementWarp(3);
  }
  cout << endl;

  cout << "=== Finish ===" << endl << endl;
  return 0;
}
