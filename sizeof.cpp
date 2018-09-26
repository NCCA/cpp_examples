#include <iostream>

/* This simple example will calculate the size of a base and derived class. You'll see that A will be bigger
   than just the 3 floats (on my system this evaluates to 24) - why? */

class A {
public:
  A() {};
  virtual ~A() {};
protected:
  float x,y,z;
};

class B : public A {
public:
  B() : A() {};
  ~B() {};
protected:
  float w,t,u,v;
};

typedef struct {
int a,b;
} test;

int main() {
  A a;
  B b;
  std::cout << "sizeof(a)="<<sizeof(a)<<", sizeof(b)="<<sizeof(b)<<", sizeof(test)="<<sizeof(test)<<"\n";
  return 0;
}
