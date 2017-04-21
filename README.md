# MDE---Modified-Differential-Evolution
A C++14 implementation of MDE - Modified Differential Evolution

MDE is a modified differential evolution method for solving nonlinearly constrained real optimization problems.

It handles any kind of non linear constraints in a very simple way. No dependencies, just include and use.

Example of use (function taken from: https://www.mathworks.com/help/optim/ug/fmincon.html):


```C++

#include <iostream>

#include "src/MDE.h"


using namespace std;


// Here, FunctionBase<>::Vector is the individual element of MDE, and extends either from 
// 'std::array<double, N>' or 'std::vector<double>', depending if 'N' is known at compile time or not.
// It also has information regarding fitness and violation, and is defined at "src/Vector.h""

// If the number of variables 'N' is known at compile time, you can use
// de::FunctionBase< N > and get a slightly gain of performance

struct NLP : de::FunctionBase<>
{
    using Base = de::FunctionBase<>;

    NLP (int N = 2) : Base(N)   // number of variables
    {
      lower = {0.0, 0.2};    // lower limits
      upper = {0.5, 0.8};    // upper limits
    }

    double operator () (const Vector& x)  // function
    {
      return 100 * pow(x[1] - x[0] * x[0], 2) + pow(1 - x[0], 2);
    }
    
    // Vector with all inequality constraints values.
    // A const reference can be used for more performance.
    
    vector<double> inequalities (const Vector& x) 
    {
      return { x[0] * x[0] + x[1] * x[1] - 1 };
    }
    
    
    // No equality constraints here.
     
    // vector<double> equalities (const Vector& x)
};




int main()
{
    rng::Rand::generator.seed(270001);   // feed random number generator with deterministic seed
         

    de::MDE<NLP> mde;     // some default parameters

    auto best = mde();    // operator() runs MDE and return best individual found


    cout << "Best individual found:    "; for(auto x : best) cout << x << "   "; cout << "\n\n";

    cout << "Fitness:     " << best.fitness << "\n\n";

    cout << "Constraint Violation:     " << best.violation << "\n";


    return 0;
}
```
