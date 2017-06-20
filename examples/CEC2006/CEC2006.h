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

struct F1 : public CEC_Function<13, 0, 9> { using Base = CEC_Function<13, 0, 9>;  F1(); };

struct F2 : public CEC_Function<20, 0, 2> { using Base = CEC_Function<20, 0, 2>;  F2(); };

struct F3 : public CEC_Function<10, 1, 0> { using Base = CEC_Function<10, 1, 0>;  F3(); };

struct F4 : public CEC_Function<5, 0, 6>  { using Base = CEC_Function<5, 0, 6>;   F4(); };

struct F5 : public CEC_Function<4, 3, 2>  { using Base = CEC_Function<4, 3, 2>;   F5(); };

}

} // namespace CEC2006


#endif //MDE_CEC_2006_H
