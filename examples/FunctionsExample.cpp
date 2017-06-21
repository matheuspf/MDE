/**	\file CEC2006Example.cpp
  *
  * This file shows how to define and optimize a function using MDE
*/

#include <iostream>
  
#include "MDE/MDE.h"	/// MDE header


/** The 'mde::Function<>' defines some necessary variables for you, such as the 
 *  number of variables, lower and upper bounds, optimal function value and dummy 
 *  equality and inequality constraints. All of them have default values, but you 
 *  need to specify either the number of variables ('N' at runtime or using 
 * 'mde::Function<NUM>', at compile time) or  lower/uppper bounds.
*/



/** The Ackley function:  https://www.sfu.ca/~ssurjano/ackley.html
 *
 * Here I inherit from 'mde::Function<>'. It is a template, where you can
 * pass the number of variables at compile time to have a 'std::array' as
 * the 'Vector' type instead of a 'std::vector'. However, this way I can
 * decide the number of parameters at runtime.
 *

*/
struct Ackley : public mde::Function<>	 /// Inheriting from 'mde::Function<>'
{
	/// Number of parameters at runtime. All the other stuff is specific to this function
    Ackley (int N = 5) : N(N), a(20.0), b(0.2), c(8.0*std::atan(1.0)), l(-30.0), r(30.0)
    {
    	 /** Here I also define the optimal value, so the MDE stops immediatelly when it finds
    	  * a (feasible solution) with fitness value smaller than 'optimal'. However, it is
    	  * totally optional to use it or not. Of course, you will always want to define a 
    	  * value slightly above the optimum o avoid floating point precision problems. 
    	*/
        optimal = 1e-10;

    	/** Lower and upper bounds. The interface for 'Vector' is similar to 'std::vector'.
    	  * For more, see the 'Vector.h' file. You really dont need to do much here. The 
    	  * bounds are optional, but not specifying them can lead to much longer running times.
    	*/
        lowerBounds = Vector(N, l);		/// 'N' elements with value 'l', just like as 'std::vector'
        upperBounds = Vector(N, r);		/// 'N' elements with value 'r', just like as 'std::vector'
    }


    /** This is where the function value is returned from a given vector 'v'.  In this case, as the 
      * 'Vector' class inherits from 'std::vector', you could really just use:
      *
      *	double operator () (const std::vector<double>& v)
    */
    double operator () (const Vector& v)
    {
        double y1 = std::accumulate(v.begin(), v.end(), 0.0, [&](double acum, double x){ return acum + x*x; });
        double y2 = std::accumulate(v.begin(), v.end(), 0.0, [&](double acum, double x){ return acum + std::cos(c * x); });

        return -a * std::exp(-b * std::sqrt(y1 / N)) - std::exp(y2 / N) + a + std::exp(1.0);
    }


    int N;	 /// Number of variables. Must use this or specify lower/upper bounds (or both)

    double a, b, c, l, r;	 /// Parameters of the Ackley function
};



/** The Rosenbrock function:  https://www.sfu.ca/~ssurjano/rosen.html
  *
  * Same as the Ackley function
*/
struct Rosenbrock : mde::Function<>   /// Inheriting from 'mde::Function<>'
{
	/// Defining the number of variables
    Rosenbrock (int N = 5) : N(N)
    {
        optimal = 1e-10;	/// Slightly above the optimal


        /// Defining lower and upper bounds
        lowerBounds = Vector(N, -10.0);
        upperBounds = Vector(N, 10.0);
    }


    /// Function definition
    double operator () (const Vector& x)
    {
        double r = 0.0;

        for(int i = 0; i < N - 1; ++i)
            r += 100.0 * std::pow(x[i] * x[i] - x[i+1], 2) + std::pow(x[i] - 1.0, 2);

        return r;
    }


    int N;	 /// Number of variables
};



/** Constrained Rosenbrock function in 2D:  https://www.mathworks.com/help/optim/ug/fmincon.html
  *
  * This is an example of a constrained function
*/
struct ConstRosenbrock : mde::Function<2>	/// The number of variables is known at compile time, so use it
{
	/// Nothing to do here
	ConstRosenbrock ()
	{
		optimal = 0.25 + 1e-10;	  /// Slightly above the optimal


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
	  *	g(x) <= 0
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
	// 	return std::array<double, 1>{ std::pow(x[0] - 1.0/3, 2) + std::pow(x[1] - 1.0/3, 2) - std::pow(1.0/3, 2) };
	// }
};



template <class Vector>
void displayResult (const Vector& best)
{
	std::cout << "Best element found:\n\n";

	for(auto x : best)
		std::cout << x << "   ";
	std::cout << "\n\n\n";

	std::cout << "Fitness:                   " << best.fitness << "\n\n";
	std::cout << "Violation:                 " << best.violation << "\n\n\n\n";
}




int main ()
{
	mde::Parameters params;		 /// Define some parameters. Everything else is set to the default values

	params.bndHandle = "clip";	 /// Using another bounds handling function. Thats also optional



	/// Instantiate a MDE with the 'Ackley' function, using parameters 'params'
	mde::MDE<Ackley> mdeAckley(params);

	std::cout << "Ackley:\n\n";

	displayResult(mdeAckley());		/// Execute and display result


	/** Instantiate a MDE with the Rosenbrock function, using parameters params.
	  * You can also pass any argument to the function if you want
	*/
	mde::MDE<Rosenbrock> mdeRosenbrock(params, Rosenbrock(5));

	std::cout << "Rosenbrock:\n\n";

	displayResult(mdeRosenbrock());		/// Execute and display result


	/// Instantiate a MDE with the Constrained Rosenbrock function in 2d
	mde::MDE<ConstRosenbrock> mdeConstRosenbrock(params);

	std::cout << "Constrained Rosenbrock:\n\n";

	displayResult(mdeConstRosenbrock());		/// Execute and display result



	return 0;
}