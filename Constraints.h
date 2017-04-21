//
// Created by matheus on 3/13/17.
//

#ifndef BRKGA_CONSTRAINTS_H
#define BRKGA_CONSTRAINTS_H


#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <type_traits>
#include <iostream>
#include <numeric>



namespace de
{
    template<class Function>
    struct PenaltyEps : public Function
    {
        using Vector = typename Function::Vector;

        inline double operator () (Vector& x)
        {
            Function::operator()(x);

            double eqVal = std::accumulate(Function::eqs.begin(), Function::eqs.end(), 0.0,
                                           [](double a, double b){ return a + (std::abs(b) < 1e-4 ? 0.0 : std::abs(b)); });

            x.fitness   = Function::f - Function::optimal;
            x.violation = Function::g + eqVal;

            //DB(Function::f << "      " << Function::g << "     " << eqVal);

            return x.fitness;
        }
    };

} // namespace brkga

#endif //BRKGA_CONSTRAINTS_H
