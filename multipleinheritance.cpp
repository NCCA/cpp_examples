#include <iostream>

/** This example demonstrates one of the perils of multiple inheritance. Both B and C inherit from A, but D inherits from B and C. Confusion arises when we try to call print() - which print? */

class A {
public:
  A() {;}
  virtual ~A() {;}          /* why does this need to be virtual? */
  virtual void print() { std::cout << "Class A\n"; } 
};

class B : public A {
public:
  B() : A() {;}
  virtual ~B() {;}
  virtual void print() { std::cout << "Class B\n"; }
};

class C : public A {
public:
  C() : A() {;}
  virtual ~C() {;}
  virtual void print() { std::cout << "Class C\n"; }
};

/* Note that D inherits from both B and C - which print will it use? */
class D : public B, public C {
public:
  D() : B(), C() {;}
  ~D() {;}
  // void print() { std::cout << "Class D\n"; }
};

/* Create some structs and dump the size */
int main() {
  D d;
  d.print();
  return 0;
}
