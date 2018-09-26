#include <iostream>

/** Try out both of these different versions of real. Can you explain the resulting size of the
    data structure? Hint - the result might be different on a 32bit vs 64bit system. **/

typedef double real; // On my system gives "sizeof(a)=40, sizeof(b)=48".
//typedef float real;// On my system gives "sizeof(a)=24, sizeof(b)=24".


// Class with "neat" data packing.
class A {
public:
  A() {;};
  ~A() {;}; // Try make the destructor virtual. How does this affect the size? Why?
protected:
  real x,y,z;
  int r,g,b;
};

// Class with "messy" data packing.
class B {
public:
  B() {;};
  ~B() {;};
protected:
  real x;
  int r;
  real y;
  int g;
  real z;
  int b;
};

/* Create some structs and dump the size */
int main() {
  std::cout << "sizeof(A)="<<sizeof(A)<<", sizeof(B)="<<sizeof(B)<<"\n";

/*Note that the following returns the same value of the size and is also a valid usage of sizeof*/
// A a; B b;
// std::cout << "sizeof(a)="<<sizeof(a)<<", sizeof(b)="<<sizeof(b)<<"\n";
  return 0;
}
