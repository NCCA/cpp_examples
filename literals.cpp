// This example from http://codexpert.ro/blog/2014/10/13/user-defined-literals/

#include <iostream>

class Employee
{
   std::string name;
public:
   Employee(std::string const & name) :name(name){}
   std::string getName() const { return name; }
};
 
class Developer : public Employee
{
public:
   /// constructor delegation
   using Employee::Employee;
};
 
class QualityAssurer : public Employee
{
public:
   /// constructor delegation
   using Employee::Employee;
};

// Cooked literals 
Developer operator "" _dev(char const * text, std::size_t const size)
{
   return Developer(std::string(text, text + size));
}
 
QualityAssurer operator "" _qa(char const * text, std::size_t const size)
{
   return QualityAssurer(std::string(text, text + size));
}
 
int main()
{
   auto d = "marius"_dev;
   auto q = "john"_qa;
   std::cout << d.getName() << std::endl;
   std::cout << q.getName() << std::endl;
 
   return 0;
}
