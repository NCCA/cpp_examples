#include <iostream>

class Base {
public:
    Base() {std::cerr<<"\nBase::Base()";}
    virtual ~Base() {std::cerr<<"\nBase::~Base()";}
    // 1) What happens when you remove the virtual keyword and provide an implementation?
    // 2) What happens when you try to create a Base object?
    virtual void foo() = 0;
private:
    int x;
};

class Derived : public Base {
public:
    Derived() : Base() {std::cerr<<"\nDerived::Derived()";}
    ~Derived() {std::cerr<<"\nDerived::~Derived()";}
    // 1) What happens if Derived::foo() has no implementation?
    // 2) What happens if you cast a Derived to a Base and call foo()?
    void foo() {std::cerr<<"\nDerived::foo()";}
private:
    int x,y;
};


class Dummy {};

int main() {
    Derived *d = new Derived();
    std::cerr << "\nSize of Derived: "<<sizeof(Derived);
    // 1) Could you use a C style static case on d to b? Is this dangerous?
    // 2) Could you cast a Derived to a Dummy?
    Base *b = dynamic_cast<Base*>(d);
    std::cerr << "\nSize of Base: "<<sizeof(Base);
    // 1) Which foo() will get called? What happens if Base::foo() was not virtual?
    b->foo();

    // Note the destructors which get called and in what order!
    delete b;
    std::cerr << "\nmain() - end";
    return 0;
}
