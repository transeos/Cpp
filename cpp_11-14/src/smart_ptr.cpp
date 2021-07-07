// -*- C++ -*-
//
//*****************************************************************
//
// WARRANTY:
// Use all material in this file at your own risk.
//
// Created by Hiranmoy on 10/03/19.
//
//*****************************************************************

#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::weak_ptr;

class Base {
private:
  int32_t _val;

  unique_ptr<Base> ub_;
  shared_ptr<Base> sb_;
  weak_ptr<Base> wb_;

protected:
  bool printVal;

public:
  Base(int32_t val = 1) : _val(val) {
    printf("Base(%p, val = %d) created\n", this, _val);
    printVal = true;
  }
  virtual ~Base() {
    if (printVal)
      printf("Base(%p, val = %d) destroyed\n", this, get());
    else
      printf("Base(%p) destroyed\n", this);
  }

  virtual int32_t get() const { return _val; }

  int32_t GetUVal(int32_t val) {
    if (!ub_)
      ub_.reset(new Base(val));
    return ub_->get();
  }

  void setSB(decltype(sb_) sb) { sb_ = sb; }

  void setWB(decltype(sb_) sb) { wb_ = sb; }

  auto getUB() -> decltype(ub_) & { return ub_; }
  auto getUBPtr() -> decltype(&ub_) { return &ub_; }

  static void sCustomDeleter(Base *b) {
    b->printVal = false;
    cout << "Base::sCustomDeleter called: val = " << b->get() << endl;
    delete b;
  }

  static void sNoDelete(Base *b) {
    // Do nothing so that that the object doesn't get deleted.
  }
};

class Derived : public Base {
private:
  unique_ptr<int32_t> _dVal;

public:
  Derived(int32_t val = 1) : Base(val - 1), _dVal(new int32_t(val)) {
    printf("Derived(%p, val = %d) created\n", this, *_dVal);
  }
  virtual ~Derived() {
    if (printVal)
      printf("Derived(%p, val = %d) destroyed\n", this, get());
    else
      printf("Derived(%p) destroyed\n", this);
  }

  virtual int32_t get() const override { return (_dVal ? *_dVal : -1); }
};

template <typename T, typename U>
void ComparePtrs(T &p1, U &p2, const char *s1, const char *s2) {
  if (p1 == p2)
    printf("%s and %s are same\n", s1, s2);
  else
    printf("%s and %s are different\n", s1, s2);
}

template <typename T> void PrintType(T &p1, const char *s) {
  cout << "Type of " << s << " " << typeid(T).name() << endl;
}

int32_t main(const int32_t argc, const char **argv) {
  cout << endl << "=== unique_ptr ===" << endl;
  {
    unique_ptr<Base> p1;
    PrintType(p1, "p1");
    auto p2 = std::make_unique<Base>();

    cout << p2->get() << endl;
    cout << p2->GetUVal(2) << endl;
    cout << p2->GetUVal(3) << endl << endl;

    auto p3 = p2->getUBPtr();
    PrintType(p3, "p3");
    cout << p3->get() << endl;

    auto &p4 = p2->getUB();
    cout << p4->get() << endl;
    cout << p4.get() << endl;

    unique_ptr<Base, void (*)(Base *)> p5(new Base(3), Base::sCustomDeleter);
    p5.reset(0);
    cout << endl;
    p2.reset(0);

    unique_ptr<Base, void (*)(Base *)> p6(
        new Base(4), [](Base *b) { cout << " lambda delete called\n"; });
    cout << "p5 = " << sizeof(p5) << ", p6 = " << sizeof(p6) << endl;
  }

  cout << endl << "=== shared_ptr ===" << endl;
  {
    {
      shared_ptr<Derived> sp1(new Derived(5), Base::sCustomDeleter);
      shared_ptr<Derived> sp2 = sp1;
      cout << endl
           << "sp1 : " << sp1 << "   "
           << "sp1.get() : " << sp1.get() << endl;
    }
    cout << endl;
    {
      auto dp1 = std::make_shared<Derived>();

      shared_ptr<Base> bp1 = dp1;
      decltype(bp1) bp2(dp1);

      ComparePtrs(bp1, dp1, "bp1", "dp1");
      ComparePtrs(bp1, bp2, "bp1", "bp2");
    }
    cout << endl;
    {
      shared_ptr<Base> sp(new Base(6), Base::sNoDelete);
      cout << "unique : " << sp.unique() << endl;
    }
  }

  cout << endl << "=== weak_ptr ===" << endl;
  {
    {
      weak_ptr<Base> wb;
      cout << "expired : " << wb.expired() << endl;
      auto sb = std::make_shared<Base>(7);
      wb = sb;
      cout << "expired : " << wb.expired() << endl;
      sb.reset();
      cout << "expired : " << wb.expired() << endl;
    }
    cout << endl;
    {
      auto a = std::make_shared<Base>(8);
      a->setSB(a);
    }
    cout << endl;
    {
      auto a = std::make_shared<Base>(9);
      a->setWB(a);
    }
  }

  cout << endl << "=== Things to avoid: pointer to smart pointer ===" << endl;
  {
    auto b1 = new unique_ptr<Base>(new Base(10));
    cout << "(*b1)->get() : " << (*b1)->get() << endl;
  }

  cout << endl << "=== Finish ===" << endl << endl;
  return 0;
}
