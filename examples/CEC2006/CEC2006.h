/** \file CEC2006.h
  *
  * Definition of the CEC functions using 'CEC_Functions' class to make
  * them compatible with MDE functions. 
*/


#ifndef MDE_CEC_2006_H
#define MDE_CEC_2006_H

#include "CEC_Function.h"
#include "CEC2006_C_Functions.h"

namespace mde
{

namespace CEC2006
{

struct F1 : public CEC_Function<13, 0, 9>   { using Base = CEC_Function<13, 0, 9>;  F1(); };

struct F2 : public CEC_Function<20, 0, 2>   { using Base = CEC_Function<20, 0, 2>;  F2(); };

struct F3 : public CEC_Function<10, 1, 0>   { using Base = CEC_Function<10, 1, 0>;  F3(); };

struct F4 : public CEC_Function<5, 0, 6>    { using Base = CEC_Function<5, 0, 6>;   F4(); };

struct F5 : public CEC_Function<4, 3, 2>    { using Base = CEC_Function<4, 3, 2>;   F5();  };

struct F6 : public CEC_Function<2, 0, 2>    { using Base = CEC_Function<2, 0, 2>;   F6();  };

struct F7 : public CEC_Function<10, 0, 8>   { using Base = CEC_Function<10, 0, 8>;  F7();  };

struct F8 : public CEC_Function<2, 0, 2>    { using Base = CEC_Function<2, 0, 2>;   F8();  };

struct F9 : public CEC_Function<7, 0, 4>    { using Base = CEC_Function<7, 0, 4>;   F9();  };

struct F10 : public CEC_Function<8, 0, 6>   { using Base = CEC_Function<8, 0, 6>;   F10(); };

struct F11 : public CEC_Function<2, 1, 0>   { using Base = CEC_Function<2, 1, 0>;   F11(); };

struct F12 : public CEC_Function<3, 0, 1>   { using Base = CEC_Function<3, 0, 1>;   F12(); };

struct F13 : public CEC_Function<5, 3, 0>   { using Base = CEC_Function<5, 3, 0>;   F13(); };

struct F14 : public CEC_Function<10, 3, 0>  { using Base = CEC_Function<10, 3, 0>;  F14(); };

struct F15 : public CEC_Function<3, 2, 0>   { using Base = CEC_Function<3, 2, 0>;   F15(); };

struct F16 : public CEC_Function<5, 0, 38>  { using Base = CEC_Function<5, 0, 38>;  F16(); };

struct F17 : public CEC_Function<6, 4, 0>   { using Base = CEC_Function<6, 4, 0>;   F17(); };

struct F18 : public CEC_Function<9, 0, 13>  { using Base = CEC_Function<9, 0, 13>;  F18(); };

struct F19 : public CEC_Function<15, 0, 5>  { using Base = CEC_Function<15, 0, 5>;  F19(); };

struct F20 : public CEC_Function<24, 12, 6> { using Base = CEC_Function<24, 12, 6>; F20(); };

struct F21 : public CEC_Function<7, 5, 1>   { using Base = CEC_Function<7, 5, 1>;   F21(); };

struct F22 : public CEC_Function<22, 4, 2>  { using Base = CEC_Function<22, 4, 2>;  F22(); };

struct F23 : public CEC_Function<9, 4, 2>   { using Base = CEC_Function<9, 4, 2>;   F23(); };

struct F24 : public CEC_Function<2, 0, 2>   { using Base = CEC_Function<2, 0, 2>;   F24(); };


} // namespace CEC2006

} // namespace mde


#endif //MDE_CEC_2006_H
