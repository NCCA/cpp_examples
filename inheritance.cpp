#include <iostream>
#include <exception>
#include <string>

/// Base class for this example
class Base {
public:
  Base() {std::cout << "Base::Base()\n";}
  virtual ~Base() {std::cout << "Base::~Base()\n";}
};

/// Below the relationship is inheritance "is-a"
class Inherit : public Base {
public:
  Inherit() : Base() {std::cout << "Inherit::Inherit()\n";}
  ~Inherit() {std::cout << "Inherit::~Inherit()\n";}
};

/// Below the relationship is compositional "has-a"
class Compose {
public:
  Compose() : base() {std::cout << "Compose::Compose()\n";}
  ~Compose() {std::cout << "Compose::~Compose()\n";}
private:
  Base base;
};

int main() {
    // Create some objects and observe
    Inherit i;
    Compose c;

    std::cout << "sizeof(i)="<<sizeof(i)<<", sizeof(c)="<<sizeof(c)<<"\n";
    std::cout << "End of main()\n";
    return 0;
}
