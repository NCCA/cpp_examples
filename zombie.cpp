#include <iostream>
#include <exception>
#include <string>

/**
 * @brief The Exception class
 */
class Exception: public std::exception {
public:
    /// Construct from a char*
    explicit Exception(const char* msg): std::exception(), m_msg(msg) {;}

    /// Construct from a std::string
    explicit Exception(const std::string& msg) : std::exception(), m_msg(msg) {;}

    /// In case we want subclasses
    virtual ~Exception() throw () {;}

    /// Standard function which returns the message
    virtual const char* what() const throw () {
        return m_msg.c_str();
    }
protected:
    /// The message for this error
    std::string m_msg;
};

/**
 * @brief The Foo class
 */
class Foo {
public:
    /// Constructor which always throws an exception
    Foo() throw (const Exception&) : i(1) {
        throw (Exception("Foo::Foo() - It's BROOOOKEN!"));
    }

    /// Destructor
    ~Foo() {;}

    /// A trivial member to test for zombie-ness
    int i;
};

/**
 * @brief testFoo
 */
void testFoo() {
    Foo foo;
}

/**
 * The main loop
 */
int main() {
//    // 1. This bombs --- if the exception is not handled, the program teminates
//    Foo foo;

//    // 2. This works: handle the exception normally. However, outside of the try section, foo is outside of {}, so no zombie problems.
//    try {
//        Foo foo;
//    } catch (const Exception &e) {
//        std::cerr << "Exception thrown! "<< e.what() << "\n";
//    }

    // 3. This works too, but who would be dumb enough to access *foo after this loop?
    Foo *foo;
    try {
        foo = new Foo();
    } catch (const Exception &e) {
        std::cerr << "Exception thrown! "<< e.what() << "\n";
    }
    // Now see if this class is initialised or zombified
    std::cout << "foo->i="<<foo->i<<"\n";
    return 0;
}
