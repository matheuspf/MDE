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

#include <iostream>
#define DB(x) std::cout << x << "\n" << std::flush;


namespace de
{
    template <class FitnessType>
    class MDE
    {
    public:

        using Fitness     = FitnessType;
        using Vector      = typename Fitness::Vector;
        using Population  = std::vector<Vector>;


        MDE(int popSize = 30, double Fa = 0.8, double Fb = 0.1, double Cr = 0.9, double Srmax = 0.55,
            double Srmin = 0.025, int childrens = 5, double eps = 1e-4, int maxIter = 3333) :
            popSize(popSize), Fa(Fa), Fb(Fb), Cr(Cr), Srmax(Srmax), Srmin(Srmin), Sr(Srmax),
            childrens(childrens), eps(eps), maxIter(maxIter), permutation(popSize), 
            population(popSize), rngEngine(std::chrono::system_clock::now().time_since_epoch().count())
        {
        	N = fitness.N;

            std::iota( permutation.begin(), permutation.end(), 0 );
        }


        Vector operator () ()
        {
            initialize();

            std::sort( population.begin(), population.end() );

            best = population.front();

            int iter = 0;

            double fitBest = best.fitness;
            int fitCnt = 0;


            while(!terminate(best) && iter++ < maxIter)
            {
                for(int i = 0; i < population.size(); ++i)
                {
                    Vector& parent = population[i];

                    Vector bestChild( N );

                    for(int k = 0; k < childrens; ++k)
                    {
                        std::shuffle(permutation.begin(), permutation.end(), rng::Rand::generator);

                        // const Vector& x1 = population[randInt(0, popSize)];
                        // const Vector& x2 = population[randInt(0, popSize)];
                        // const Vector& x3 = population[randInt(0, popSize)];


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

                            if(child[j] < fitness.lower[j] || child[j] > fitness.upper[j])
                                //child[j] = parent[j];
                                //child[j] = randInt(0, 2) ? parent[j] : randDouble(fitness.lower[j], fitness.upper[j]);;
                                child[j] = randDouble(fitness.lower[j], fitness.upper[j]);;

                            //child[j] = std::min(fitness.upper[j], std::max(fitness.lower[j], child[j]));
                        }

                        fitness(child);

                        bestChild = std::min(bestChild, child);
                    }

                    if(terminate(bestChild))
                        return (best = bestChild);

                    if(randDouble(0.0, 1.0) < Sr)
                    {
                        if(bestChild.fitness < parent.fitness)
                            parent = bestChild;
                    }
                       // parent = std::min(parent, bestChild, [](const auto& x, const auto& y){ return x.fitness < y.fitness; });

                    else
                        parent = std::min(parent, bestChild);

                    best = std::min(best, bestChild);
                }

                std::sort( population.begin(), population.end() );

                best = population[0];

                Sr = (iter < (maxIter / 3) ? Sr - (3.0 / maxIter) * (Srmax - Srmin) : Srmin);


                if(best.feasible() && std::abs(best.fitness - fitBest) <= 1e-4)
                	fitCnt++;

                else
                	fitBest = best.fitness, fitCnt = 0;

                if(fitCnt >= 50)
                {
                	for(int i = 5; i < popSize; ++i)
                	{
                		for(int j = 0; j < N; ++j)
                			population[i][j] = randDouble( fitness.lower[j], fitness.upper[j] );

                		fitness(population[i]);
                	}

                	std::sort( population.begin(), population.end() );

                	best = population.front();

                	fitCnt = 0;
                }


                DB(iter << "      " << best.fitness << "      " << best.violation << "       " << fitness.FEs);
            }

            return best;
        }


        void initialize ()
        {
            for(auto& x : population)
            {
                x = Vector(N);

                for(int i = 0; i < N; ++i)
                    x[i] = randDouble( fitness.lower[i], fitness.upper[i] );

                fitness(x);
            }
        }

        inline bool terminate (const Vector& x)
        {
            return x.feasible() && (x.fitness < eps);
        }



    //private:

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

        std::vector<int> permutation;


        Population population;

        Vector best;

        Fitness fitness;


        rng::RandInt    randInt;
        rng::RandDouble randDouble;

        std::default_random_engine rngEngine;
    };


} // namespace de


#endif //DE_DPS_DE_DPS_H
