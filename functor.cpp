#include <memory>
#include <array>
#include <iostream>
#include <functional>
#include <boost/numeric/odeint.hpp>


/**
  * Here's an (almost) useful example of using functors: on dynamic systems.
  * The important bit is that functors essentially allow us to create functions with "state", i.e.
  * we could, for example, implement hybrid dynamic systems.
  * To compile you'll need you --std=c++11 flag (on whatever system you're on)
  */

/// Our state variables are [x,dx/dy]
typedef std::array<double,2> State;

/// A typedef for our RK4 integrator
typedef boost::numeric::odeint::runge_kutta4<State> RK4Integrator;


/** From
 * http://www.mathworks.com/examples/matlab/1125-differential-equations
 */
void VanDerPol(const State& x, State &dxdt, const double &dt, double mu = 1.0) {
    dxdt[0] = x[1];
    dxdt[1] = mu*(1-x[0]*x[0])*x[1]-x[0];
}

/**
 * @brief The Functor class which will store the current state of the object
 */
class VanDerPol_Functor {
public:
    VanDerPol_Functor() : mu(1.0) {;}
    ~VanDerPol_Functor() {;}

    /// Create an operator() to make sure it's a functor
    void operator() (const State& x, State &dxdt, const double &dt) {
        VanDerPol(x,dxdt,dt,mu);
    }

    /// Another function, which can be used by binding it
    void func (const State& x, State &dxdt, const double &dt) {
        VanDerPol(x,dxdt,dt,mu);
    }

    /// Get and set functions to let us mangle the state of the functor
    double setMu(const double &_mu) {mu = _mu;}
    double getMu() const {return mu;}
private:
    /// Our member which we're going to mangle when running this thing
    double mu;
};

/**
 * @brief main Example of how to use functors using boost integrators
 * @return 0 we hope
 */
int main() {
    // The current, end and step time
    double t = 0.0;
    double t_end = 20.0;
    double t_step = 0.1;

    // Initial state for the oscillator
    State x = {2.0, 0.0};

    // Create a functor class to use instead
    VanDerPol_Functor foo;

    // Our RK4 integrator
    RK4Integrator rk4;

    // Create a function for our integrator (thank goodness for auto)
    auto myfun = std::bind(&VanDerPol_Functor::func, // This is our member function to use
                           &foo,                     // First parameter is a pointer to the object
                           std::placeholders::_1,    // 2nd parameter will be the 1st parameter passed to it
                           std::placeholders::_2,    // 3rd parameter will be the 2nd parameter passed to it
                           std::placeholders::_3);   // 4th parameter will be the 3rd parameter passed to it

    // To demangle c++ compiled files, use "c++filt -t"
    //std::cerr << "typeid(myfun)="<<typeid(VanDerPol).name()<<"\n";

    for (; t < t_end; t += t_step) {
        // Simplest method is using a stateless function - note that mu cannot be modified
        // rk4.do_step(VanDerPol, x, 0.0, t_step);

        // this method is using the operator() function, thereby using the functor class
        //rk4.do_step(foo, x, 0.0, t_step);

        // this method is using the member function as a bound object
        rk4.do_step(myfun, x, 0.0, t_step);

        // Here I'm modifying mu - something you can't do without an associated object (or perhaps a global!)
        foo.setMu(foo.getMu() * 1.01);
        std::cout <<t << " "<<x[0]<<" "<<x[1]<<" "<< foo.getMu()<<"\n";
    }

    return EXIT_SUCCESS;
}
