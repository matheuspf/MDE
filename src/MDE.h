//
// Created by matheus on 4/17/17.
//

#ifndef DE_DPS_DE_DPS_H
#define DE_DPS_DE_DPS_H

#include <type_traits>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <ctime>
#include <chrono>

#include "Random.h"
#include "FunctionBase.h"

#include <iostream>
#define DB(x) std::cout << x << "\n" << std::flush

namespace de
{
    struct Parameters
    {
        Parameters(int popSize = 30, double Fa = 0.8, double Fb = 0.1, double Cr = 0.9, double Srmax = 0.55,
            double Srmin = 0.025, int childrens = 5, double eps = 1e-4, int maxIter = 3333) :
        popSize(popSize), Fa(Fa), Fb(Fb), Cr(Cr), Srmax(Srmax), Srmin(Srmin), Sr(Srmax),
        childrens(childrens), eps(eps), maxIter(maxIter) { }

        int N;
        int popSize;
        double eps;

        double Fa;
        double Fb;
        double Cr;

        double Srmax;
        double Srmin;
        double Sr;

        int childrens;
        int maxIter;
    };


    template <class FunctionType>
    class MDE : Parameters
    {
    public:

        using Function   = SetValues<FunctionType>;
        using Vector     = typename Function::Vector;
        using Population = std::vector<Vector>;


        using Parameters::Parameters;


        MDE (const Parameters& param) : Parameters(param), permutation(popSize), population(popSize)
        {
            N = function.N;
            
            std::iota( permutation.begin(), permutation.end(), 0 );
        }

        MDE () : permutation(popSize), population(popSize)
        {
            N = function.N;

            std::iota( permutation.begin(), permutation.end(), 0 );
        }


        // MDE(int popSize = 30, double Fa = 0.8, double Fb = 0.1, double Cr = 0.9, double Srmax = 0.55,
        //     double Srmin = 0.025, int childrens = 5, double eps = 1e-4, int maxIter = 3333) :
        //     Parameters{function.N, popSize, eps, Fa, Fb, Cr, Srmax, Srmin, Srmax, childrens, maxIter},
        //     // popSize(popSize), Fa(Fa), Fb(Fb), Cr(Cr), Srmax(Srmax), Srmin(Srmin), Sr(Srmax),
        //     // childrens(childrens), eps(eps), maxIter(maxIter), permutation(popSize), population(popSize)
        //     permutation(popSize), population(popSize)
        // {
        // 	N = function.N;

        //     DB(popSize);

        //     std::iota( permutation.begin(), permutation.end(), 0 );
        // }


        Vector operator () ()
        {
            initialize();

            std::sort( population.begin(), population.end() );

            best = population.front();

            int iter = 0;

            double fitBest = best.fitness;
            int fitCnt = 0;


            while(!converged(best) && iter++ < maxIter)
            {
                for(int i = 0; i < population.size(); ++i)
                {
                    Vector& parent = population[i];

                    Vector bestChild( N );

                    for(int k = 0; k < childrens; ++k)
                    {
                        std::shuffle(permutation.begin(), permutation.end(), rng::Rand::generator);

                        const Vector& x1 = population[permutation[0] != i ? permutation[0] : permutation.back()];
                        const Vector& x2 = population[permutation[1] != i ? permutation[1] : permutation.back()];
                        const Vector& x3 = population[permutation[2] != i ? permutation[2] : permutation.back()];

                        Vector child( N );

                        int jRand = randInt(0, N);

                        for (int j = 0; j < N; ++j)
                        {
                            if (randDouble(0, 1.0) < Cr || j == jRand)
                                child[j] = x3[j] + Fa * (best[j] - x2[j]) + Fb * (parent[j] - x1[j]);
                            else
                                child[j] = parent[j];

                            if(child[j] < function.lower[j] || child[j] > function.upper[j])
                                child[j] = parent[j];
                        }

                        function(child);

                        bestChild = std::min(bestChild, child);
                    }

                    if(converged(bestChild))
                        return (best = bestChild);

                    if(randDouble(0.0, 1.0) < Sr)
                    {
                        if(bestChild.fitness < parent.fitness)
                            parent = bestChild;
                    }

                    else
                        parent = std::min(parent, bestChild);

                    best = std::min(best, bestChild);
                }

                std::sort( population.begin(), population.end() );

                best = std::min(best, population[0]);

                Sr = (iter < (maxIter / 3) ? Sr - (3.0 / maxIter) * (Srmax - Srmin) : Srmin);


                //DB(iter << "      " << best.fitness);
            }

            return best;
        }


        void initialize ()
        {
            for(auto& x : population)
            {
                x = Vector(N);

                for(int i = 0; i < N; ++i)
                    x[i] = randDouble( function.lower[i], function.upper[i] );

                function(x);
            }
        }

        inline bool converged (const Vector& x)
        {
            return x.feasible() && (x.fitness - function.optimal <= eps);
        }



    //private:


        std::vector<int> permutation;


        Population population;

        Vector best;

        Function function;


        rng::RandInt    randInt;
        rng::RandDouble randDouble;
    };



} // namespace de


#endif //DE_DPS_DE_DPS_H
