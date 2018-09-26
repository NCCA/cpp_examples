// Compile this with: 
// clang++ -cc1 -fdump-record-layouts vtab.cpp 
// This will display the data alignment of the class (note that -cc1 will stop clang from finding headers)

/** Base class
  */
class Base {
public:
  Base() {;}
  virtual ~Base() {;}

  /// Note the difference in size when this function is virtual
  virtual void foo(const int &_i) { 
    m_i = _i;
  }
protected:
  int m_i;

};

/** Derived class
  */
class Derived : Base {
public:
  Derived() : Base() {;}
  virtual ~Derived() {;}

  virtual void foo(const int &_i) {
    Base::foo(_i);
  }
protected:
  int m_i; // Note what happens in the data record with repeated members!
};


/**
 * The main loop
 */
int main() {  
  // Do something silly so the compiler doesn't ignore the classes
  return sizeof(Derived);
}
