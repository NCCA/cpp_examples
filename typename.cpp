#include <stdlib.h>
#include <iostream>

class Rational {
public:
    typedef int NumType;
    Rational(const NumType &_numer=1, const NumType & _denom=0) : numer(_numer),denom(_denom) {;}
    ~Rational() {;}
    double toFloat() {return float(denom)/float(numer);}
private:
    NumType numer,denom;
};

template <class T> class Base {
public:
    Base<T>() {;}
    virtual ~Base<T>() {;}
};

template <class T>
class Derived : public Base<T> {
public:
    Derived();
    ~Derived() {}
};


template<class T>
Derived<T>::Derived() : Base<T>() {
    // You can happily use the template parameter as a type
    T test;
    std::cout << test.toFloat() << "\n";

    // But problems arise when trying to use a "nested dependent type":
    // the compiler assumes it is a static data member. Avoid this with
    // the keyword "typename"
    //T::NumType *tptr;           // This doesn't work
    //typename T::NumType *tptr;  // This works
}


int main(int argc, char *argv[])
{
    Derived<Rational> d;
    return EXIT_SUCCESS;
}
