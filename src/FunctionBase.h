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



namespace de
{
    template<int Variables = 0>
    struct FunctionBase
    {
        using Vector = ::de::Vector<Variables>;


        FunctionBase (int N) : N(N), lower(N), upper(N) {}


        FunctionBase (double l, double u, double optimal = -1e18) : FunctionBase(Variables, l, u, optimal) {}

        FunctionBase (int N, double l, double u, double optimal = -1e18) : N(N), lower(N), upper(N), optimal(optimal)
        {
            std::fill(lower.begin(), lower.end(), l);
            std::fill(upper.begin(), upper.end(), u);
        }


        virtual double constraints (const Vector&) { return 0.0; }


        int N = Variables;

        double optimal;

        Vector lower;
        Vector upper;
    };


    //-----------------------------------------------------


    template<int Variables, int Equations, int Inequations>
    struct CEC_FunctionBase : public FunctionBase<Variables>
    {
        using Base   = FunctionBase<Variables>;
        using Vector = typename Base::Vector;

        using FunctionType = void(*)(double*, double*, double*, double*, int);

        int FEs = 0;
        int id;


        CEC_FunctionBase () {}

        CEC_FunctionBase (FunctionType func, double l = 0.0, double u = 0.0, double optimal = -1e8) : func(func), Base(l, u, optimal) {}


        double operator () (Vector& x)
        {
            FEs++;

            func(&x[0], &f, &ineqs[0], &eqs[0], int(x.size()));

            h = std::accumulate(eqs.begin(), eqs.end(), 0.0, [](double a, double b){ return a + std::abs(b); });
            g = std::accumulate(ineqs.begin(), ineqs.end(), 0.0, [](double a, double b){ return a + std::max(0.0, b); });

            return f;
        }

        double constraints (const Vector&)
        {
            return g + h;
        }



        FunctionType func;

        double f;
        double g;
        double h;

        de::Vector<Equations> eqs;
        de::Vector<Inequations> ineqs;
    };



    template<class Function>
    struct SetValues : public Function
    {
        using Vector = typename Function::Vector;

        inline double operator () (Vector& x)
        {
            x.fitness = Function::operator()(x);

            x.violation = std::max(0.0, Function::constraints(x));

            return x.fitness;
        }
    };
}



#endif //BRKGA_FUNCTIONBASE_H
