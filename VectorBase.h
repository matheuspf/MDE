//
// Created by matheus on 4/17/17.
//

#ifndef DE_DPS_VECTOR_H
#define DE_DPS_VECTOR_H

#include <type_traits>
#include <vector>
#include <array>
#include <algorithm>


namespace de
{
    namespace help
    {

        template <typename T, std::size_t N>
        struct SelectType
        {
            static constexpr std::size_t maxSize = 10000 * sizeof(char);

            using type = std::conditional_t< (N == 0 || N >= maxSize), std::vector<T>, std::array<T, N> >;
        };

        template <typename T, std::size_t N>
        using SelectType_t = typename SelectType<T, N>::type;


        template <typename T, std::size_t N = 0>
        struct VectorBase : public SelectType_t<T, N>
        {
            using Base = SelectType_t<T, N>;
            using Base::Base;   // Inherits all constructors of std::vector, given that std::array has no user defined constructors


            static constexpr bool isArray  = std::is_same<std::array<T, N>, Base>::value;
            static constexpr bool isVector = std::is_same<std::vector<T>, Base>::value;


            VectorBase () : Base() {}


            // Constructor needed for initializing the class as: cnt::VectorBase<T, N> v = {...}, if inheriting from std::array
            template <typename U = Base, typename = std::enable_if_t< std::is_same<std::array<T, N>, U>::value>>
            VectorBase (std::initializer_list<T> in) { std::copy(in.begin(), in.end(), this->begin()); }

            // Dummy constructor for std::array
            template <typename U = Base, typename = std::enable_if_t< std::is_same<std::array<T, N>, U>::value>>
            VectorBase (int) : Base{} {}

        };

    } // namespace help


        template <std::size_t N = 0>
        struct Vector : public help::VectorBase<double, N>
        {
            using Base = help::VectorBase<double, N>;
            using Base::Base;

            double fitness;
            double violation;

            double factor;
            double cross;
        };


} // namespace de



#endif //DE_DPS_VECTOR_H
