#include <vector>
#include <iostream>
#include <math.h>
#include <type_traits>

/* Example to demonstrate the use of the "pod-detector" provided in C++11 */

/* This struct is a Plain Old Data (POD) struct */
typedef struct {
  int i;
  float f;
} pod;

/* This class is not POD - virtual functions */
class nonpod {
public:
  nonpod(int _i = 0) : i(_i) {}
  virtual ~nonpod() {;};
  virtual void doSomething() {i=1;}
  int i;
};

/* This class is derived from a nonpod - the std::is_pod can figure out from parent classes whether this is POD!*/
class nonpod_derived : public nonpod {
public:
  nonpod_derived(int _i = 0) : nonpod(_i) {}
  ~nonpod_derived() {;};
  void doSomething() {i = 2;}
};

int main() {
  // The std::is_pod function will tell me if the class is POD
  std::cout << "type pod = "<<std::is_pod<pod>::value << '\n';
  std::cout << "type nonpod = "<<std::is_pod<nonpod>::value << '\n';
  std::cout << "type nonpod_derived = "<<std::is_pod<nonpod_derived>::value << '\n';


  std::vector<pod> podvec;
  std::vector<nonpod> nonpodvec;
  int i;
  for (i=0; i<10; ++i) {
    nonpod_derived d(i);
    nonpodvec.push_back(d);
  }
  // Note that the vtab won't be used to evaluate doSomething().
  for (i=0; i<10; ++i) {
    nonpodvec[i].doSomething();
    std::cout << "vec["<<i<<"] is a " << ((nonpodvec[i].i==2)?"nonpod_derived":"nonpod") << "\n";
  }
}	

