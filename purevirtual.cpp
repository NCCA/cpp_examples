#include <iostream>


class A {
public:
  A() {;}
  virtual ~A() {;}          /* why does this need to be virtual? */
  virtual void print() = 0; /* What happens when this != 0? */
};

class B : public A {
public:
  B() : A() {;}
  ~B() {;}
  void print() {
    std::cout << "Class B\n";
//    A::print(); /* This won't work - why? */
  }
};

/* Create some structs and dump the size */
int main() {
  A a;	        /* This won't work - why? */
  B b; 		/* This is ok */
  return 0;
}
