/** \file CEC_Function.h
  *
  * This is a  simple wrappers to make the interface of the CEC functions
  * compatible with MDE functions. The number of variables, equalities and
  * inequalities are always constant, so the 'Vector' type will always be
  * a 'std::array'.
*/


#ifndef MDE_CEC_FUNCTION_BASE_H
#define MDE_CEC_FUNCTION_BASE_H

#include "../../include/MDE/Function.h"


namespace mde
{

/// Number of variables, equations and inequations are always constant
template<int Variables, int NumEqualities, int NumInequalities>
struct CEC_Function : public Function<Variables>
{
    /// Inheriting from 'mde::Function' and using its 'Vector' type
    using Base   = Function<Variables>;
    using Vector = typename Base::Vector;


    /// The function pointer type of CEC functions
    using CECFunc = void (*)(double*, double*, double*, double*, int);

    /// Number of function evaluations
    int FEs = 0;



    /// Initializes 'func' with the corresponding CEC function
    CEC_Function (CECFunc func) : func(func) {}

    CEC_Function (CECFunc func, double l, double u, double optimal) : func(func), Base(l, u, optimal) {}



    /** The 'operator()' returns the function value given the vector 'x'.
      * The CEC function is called here only once in the 'operator()'.
      * This function returns the function values and the values of all
      * equalities and inequalities. As the 'operator()' function is called
      * first, there is no need to call the CEC function again to calculate
      * the equalities and inequalities. They are stored in 'eqs' and 'ineqs'
      * arrays.
      *
    */
    double operator () (const Vector& x)
    {
        /// Increase number of function calls
        FEs++;

        double f;

        /// CEC functions receive a non const pointer
        func(const_cast<double*>(&x[0]), &f, &ineqs[0], &eqs[0], int(x.size()));

        return f;
    }


    /** Equalities and inequalities values are already calculated and stored 
      * in 'eqs' and 'ineqs'. Notice here the const reference as a return. We
      * only need to iterate through it's values.
    */
    const auto& equalities (const Vector& x)
    {
        return eqs;
    }

    const auto& inequalities (const Vector& x)
    {
        return ineqs;
    }




    CECFunc func;

    std::array<double, NumEqualities> eqs;
    std::array<double, NumInequalities> ineqs;
};

}

// namespace mde

#endif // MDE_CEC_FUNCTION_BASE_H