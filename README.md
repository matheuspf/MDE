# MDE---Modified-Differential-Evolution
A C++14 implementation of MDE - Modified Differential Evolution

MDE is a modified differential evolution method for solving non-linearly constrained real optimization problems.

Considering no information about the function at hand (no gradients for example), the algorithm produces very good convergence results on difficult optimization problems.

The original paper can be found at: [Efrén Mezura-Montes, Jesús Velázquez-Reyes and Carlos A. Coello Coello
, 2006](ieeexplore.ieee.org/iel5/11108/35623/01688286.pdf). All credits for the authors.

It was one of the competing methods of IEEE CEC2006 Special Session on Constrained Real-Parameter Optimization (http://www.ntu.edu.sg/home/EPNSugan/index_files/CEC-06/CEC06.htm).

This implementation handles any kind of non-linear constraints in a very simple way. No dependencies, just include and use (tested on g++ 6.2.0 and clang 3.9.1). All the 24 functions of CEC2006 are under the namespace 'de::CEC_2006'.

Example of use (function taken from: https://www.mathworks.com/help/optim/ug/fmincon.html):


```C++

#include <iostream>

#include "src/MDE.h"


using namespace std;


// Here, FunctionBase<>::Vector is the individual element of MDE and extends either from 
// 'std::array<double, N>' or 'std::vector<double>', depending if 'N' is known at compile time or not.
// It also has information regarding fitness and violation and is defined at "src/Vector.h""

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
      return { pow(x[0] - 1.0/3, 2) + pow(x[1] - 1.0/3, 2) - pow(1.0/3, 2) };
    }
    
    
    // No equality constraints here.
     
    // vector<double> equalities (const Vector& x)
};




int main()
{
    rng::Rand::generator.seed(270001);   // feed random number generator with deterministic seed
    
    // Any function from CEC_2006 is ready for use, but some parameters 
    // must be tuned to reach the performance of the original paper.
    
    //de::MDE<de::CEC_2006::F1> mde; 
    
    de::MDE<NLP> mde;     // some default parameters

    auto best = mde();    // operator() runs MDE and returns the best individual found


    cout << "Best individual found:    "; for(auto x : best) cout << x << "   "; cout << "\n\n";

    cout << "Fitness:                  " << best.fitness << "\n\n";

    cout << "Constraints Violation:    " << best.violation << "\n";


    return 0;
}
```

Outputs:


```C++

Best individual found:    0.5   0.25   

Fitness:                  0.25

Constraints Violation:    0

```
