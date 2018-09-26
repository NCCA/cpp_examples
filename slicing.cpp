#include <iostream>
#include <stdio.h>


/* In this example I'll do some object slicing. The results may be counter-intuitive. Can you explain what's going on? */

class A {
public:
  A(const float& _f=0.0) : f(_f) {}
  virtual ~A() {} 
  virtual void print() {
    std::cout << "f="<<f<<"\n";
  }
private:
  float f;
};

class B : public A {
public:
  B(const float &_f=0.0, const int & _i=0) : A(_f), i(_i) {}
  ~B() {}
  void print() {
    A::print();
    std::cout << "i="<<i<<"\n";
  }
private:
  int i;
};

/* Create some structs and dump the size */
int main() {
  B b1(1.0, 1);
  B b2(2.0, 2);
  A& a_ref = b2;
  a_ref = b1;
  a_ref.print(); // WTF?
  return 0;
}
