//
// Created by matheus on 3/13/17.
//

#ifndef BRKGA_RANDOM_H
#define BRKGA_RANDOM_H

#include <array>
#include <random>
#include <ctime>
#include <algorithm>
#include <ctime>

namespace rng
{
    struct Rand
    {
        static std::mt19937 generator;
        static std::random_device dvc;
    };

    std::random_device Rand::dvc;
    std::mt19937 Rand::generator(Rand::dvc());


    struct RandInt : Rand
    {
        inline int operator()(int min, int max) const
        {
            return std::uniform_int_distribution<>(min, max - 1)(generator);
        }

        template<class T>
        inline auto operator()(const T &min, T max) const
        {
            std::transform(min.begin(), min.end(), max.begin(), max.begin(),
                           [&](int x, int y) { return operator()(x, y); });

            return max;
        }
    };

    struct RandDouble : Rand
    {
        inline double operator()(double min, double max) const
        {
            return std::uniform_real_distribution<>(min, max)(generator);
        }

        template<class T>
        inline auto operator()(const T &min, T max) const
        {
            std::transform(min.begin(), min.end(), max.begin(), max.begin(),
                           [&](double x, double y) { return operator()(x, y); });

            return max;
        }
    };

}

#endif //BRKGA_RANDOM_H
