# MDE - Modified Differential Evolution

[![Build Status](https://travis-ci.org/matheuspf/MDE.svg?branch=master)](https://travis-ci.org/matheuspf/MDE) [![Coverage Status](https://coveralls.io/repos/github/matheuspf/MDE/badge.svg?branch=master)](https://coveralls.io/github/matheuspf/MDE?branch=master)

<br>

A C++14 implementation of MDE - Modified Differential Evolution

MDE is a modified differential evolution method for solving non-linearly constrained real optimization problems.

Considering no information about the function at hand (no gradients for example), the algorithm produces very good convergence results on difficult optimization problems.

The original paper can be found at: [MDE](http://ieeexplore.ieee.org/document/1688286/). All credits to the authors.

It was one of the competing methods of IEEE CEC2006 Special Session on Constrained Real-Parameter Optimization [CEC 2006](http://www.ntu.edu.sg/home/EPNSugan/index_files/CEC-06/CEC06.htm).

This implementation handles any kind of non-linear constraints in a very simple way. No dependencies, just include and use (tested on g++ 6.2.0 and clang 3.9.1). All the 24 functions of CEC2006 are under the namespace 'mde::CEC2006'.

<br>

### Google Test


There are a number of tests using [Google Test](https://github.com/google/googletest).

If you want to run the tests:

```
cd test
mkdir build
cd build

cmake ..
cmake --build .

./MDETests
```
  
Google Test will be downloaded automatically from the repository.


<br>

### Documentation

If you want to generate the documentation, install [Doxygen](http://www.stack.nl/~dimitri/doxygen/) and run:

```
cd doc
doxygen Doxyfile
```

<br>

### Examples

If you want to build and run some examples:

```
cd examples
mkdir build
cd build

cmake ..
cmake --build .

./CEC2006Example
./FunctionsExample
```

<br>

Example of use function taken from: [fmincon](https://www.mathworks.com/help/optim/ug/fmincon.html)


```c++

#include <iostream>

#include "MDE/MDE.h"



/** Here, FunctionBase<>::Vector is the individual element of MDE and extends either from 
  * 'std::array<double, N>' or 'std::vector<double>', depending if 'N' is known at compile time or not.
  * It also has information regarding fitness and violation and is defined at "src/Vector.h""
*/
struct NLP: mde::Function<2>   /// The number of variables is known at compile time, so use it
{
    NLP ()   /// Nothing to do here
    {
        optimal = 0.25;   /// Slightly above the optimal

        /// Lower and upper bounds
        lowerBounds = {0.0, 0.2};
        upperBounds = {0.5, 0.8};
    }


    /** As we specify the number of variables at compile time, the 'Vector' type
      * now inherits from 'std::array', so you could use:
      *
      * double operator () (const std::array<double, 2>& v)
    */
    double operator () (const Vector& x)
    {
        return 100.0 * std::pow(x[1] - x[0] * x[0], 2) + std::pow(1.0 - x[0], 2);
    }


    /** Defining inequality constraints. They can return either a floating point
      * value or a iterable container (having both 'std::begin' and 'std::end'
      * defined) with the values for each constraint. All inequalities are of the form:
      *
      * g(x) <= 0
      *
      * and all equalities are define as:
      *
      * h(x) - eqTol <= 0
      *
      * where eqTol is a very small value. For more, see the class 'mde::SetValues' in
      * the file 'Function.h'.
    */
    double inequalities (const Vector& x)
    {
        return std::pow(x[0] - 1.0/3, 2) + std::pow(x[1] - 1.0/3, 2) - std::pow(1.0/3, 2);
    }


    /** You could also defined that same constraint in this way, if you had more than
      * one inequality constraint.
    */
    // auto inequalities (const Vector& x)
    // {
    //  return std::array<double, 1>{ std::pow(x[0] - 1.0/3, 2) + std::pow(x[1] - 1.0/3, 2) - std::pow(1.0/3, 2) };
    // }
};



int main()
{
    mde::MDE<NLP> mde;     // some default parameters

    auto best = mde();    // operator() runs MDE and return best individual found


    std::cout << "Best individual found:    ";

    for(auto x : best)
        std::cout << x << "   ";
    std::cout << "\n\n";


    std::cout << "Fitness:                  " << best.fitness << "\n\n";

    std::cout << "Constraints Violation:    " << best.violation << "\n";


    return 0;
}
```

Outputs:


```

Best individual found:    0.5   0.25   

Fitness:                  0.25

Constraints Violation:    0

```

