//
// Created by matheus on 3/26/17.
//

#ifndef BRKGA_FUNCTIONBASE_H
#define BRKGA_FUNCTIONBASE_H

#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <type_traits>
#include <iostream>
#include <numeric>
#include "Vector.h"


#define USING_FUNCTION(...) using Base = __VA_ARGS__;   \
                               using typename Base::Vector;   using Base::equations;        \
                               using Base::inequations;    using Base::lower;       \
                               using Base::upper;     using Base::numVariables;        \
                               using Base::numEquations;   using Base::numInequations;


namespace de
{
    template<int Variables, int Equations = 0, int Inequations = 0>
    struct FunctionBase
    {
        using Vector = de::vector::Constrained<Variables>;

        using ConstraintType = double (*)(const Vector &);

        enum { numVariables = Variables, numEquations = Equations, numInequations = Inequations };

        FunctionBase () {}

        FunctionBase (double l, double u, double optimal = -1e8) : optimal(optimal)
        {
            std::fill(lower.begin(), lower.end(), l);
            std::fill(upper.begin(), upper.end(), u);
        }


        int N = Variables;

        double optimal;

        Vector lower;
        Vector upper;

        std::array<ConstraintType, numEquations> equations;
        std::array<ConstraintType, numInequations> inequations;
    };


    //-----------------------------------------------------


    template<int Variables, int Equations = 0, int Inequations = 0>
    struct CEC_FunctionBase : public FunctionBase<Variables, Equations, Inequations>
    {
        USING_FUNCTION(FunctionBase<Variables, Equations, Inequations>);

        using FunctionType = void(*)(double*, double*, double*, double*, int);

        int FEs = 0;
        int id;


        CEC_FunctionBase () {}

        CEC_FunctionBase (FunctionType func, double l = 0.0, double u = 0.0, double optimal = -1e8) : func(func), Base(l, u, optimal) {}


        void operator () (Vector& x)
        {
            FEs++;

            func(&x[0], &f, &ineqs[0], &eqs[0], int(x.size()));

            //h = std::accumulate(eqs.begin(), eqs.end(), 0.0, [](double a, double b){ return a + std::abs(b); });
            g = std::accumulate(ineqs.begin(), ineqs.end(), 0.0, [](double a, double b){ return a + std::max(0.0, b); });
        }


        FunctionType func;

        double f;
        double g;
        double h;

        de::vector::Constrained<Equations> eqs;
        de::vector::Constrained<Inequations> ineqs;
    };
}



#endif //BRKGA_FUNCTIONBASE_H
