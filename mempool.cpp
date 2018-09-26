#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

/**
 * @brief The Foo class. It just has a simple default constructor an int member
 */
class Foo {
public:    
    Foo(const int &_i=0) : m_i(_i) {;}
    ~Foo() {;}
    void setI(const int &_i) {m_i = _i;}
private:
    int m_i;
};

/// Allocate memory using new, and then call a member to set the member
Foo *new_alloc(const int &N) {
    Foo *foo_ptr = new Foo[N];
    for (int i=0; i<N; ++i) foo_ptr[i].setI(i);
    return foo_ptr;
}

/// Delete using standard delete
void new_dealloc(Foo *foo_ptr, const int &N) {
    delete [] foo_ptr;
}

/// Allocate memory with malloc and use placement new to construct with value
Foo *place_alloc(const int &N) {
    Foo *foo_ptr = (Foo*) malloc(sizeof(Foo)*N);
    for (int i=0; i<N; ++i) new (foo_ptr+i) Foo(i);
    return foo_ptr;
}

/// Delete the malloc memory by explicitely calling destructor (important!)
void place_dealloc(Foo *foo_ptr, const int &N) {
    for (int i=0; i<N; ++i) foo_ptr[i].~Foo();
    free(foo_ptr);
}

/// Calculate current time in seconds
double time_now_in_secs() {
    struct timeval tim;
    gettimeofday(&tim, NULL);
    return tim.tv_sec+(tim.tv_usec * 1.0e-6);
}

int main() {
    // Some values to use for timing
    double before,after;

    // The size of our memory chunk - feel free to test this (and plot results)
    int N = 1000000;

    // Evaluate the performance of new / delete
    before = time_now_in_secs();
    Foo *foo_ptr1 = new_alloc(N);
    new_dealloc(foo_ptr1,N);
    after = time_now_in_secs();
    std::cout << "It took " << after-before <<"s with new/delete.\n";

    // Evaluate the performance of placement new / delete
    before = time_now_in_secs();
    Foo *foo_ptr2 = place_alloc(N);
    place_dealloc(foo_ptr2,N);
    after = time_now_in_secs();
    std::cout << "It took " << after-before <<"s with placement new/delete.\n";

    return 0;
}
