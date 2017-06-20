/** \file CEC2006_C_Functions.h
  *
  * These are functions taken from IEEE CEC (Congress on Evolutionary Computation) 
  * 2006 competition on Constrained Real-Parameter Optimization :
  *
  * http://www.ntu.edu.sg/home/EPNSugan/index_files/CEC-06/CEC06.html
  *
  * The original paper:
  *
  * http://web.mysites.ntu.edu.sg/epnsugan/PublicSite/Shared%20Documents/CEC-2006/technical_report.pdf
  *
  * I simply took off the unnecessary parameters. They get a pointer 'x'
  * to the variable to be evaluated, a pointer 'f' for the function value,
  * a pointer 'g' for the inequalities, a pointer 'h' for the equalities and
  * a value 'nx' for the number of variables.
*/

#ifndef MDE_CEC_2006_C_FUNCTIONS_H_H
#define MDE_CEC_2006_C_FUNCTIONS_H_H


#include <math.h>

namespace mde
{

namespace CEC2006
{

void g01 (double*, double*, double*, double*, int);

void g02 (double*, double*, double*, double*, int);

void g03 (double*, double*, double*, double*, int);

void g04 (double*, double*, double*, double*, int);

void g05 (double*, double*, double*, double*, int);

void g06 (double*, double*, double*, double*, int);

void g07 (double*, double*, double*, double*, int);

void g08 (double*, double*, double*, double*, int);

void g09 (double*, double*, double*, double*, int);

void g10 (double*, double*, double*, double*, int);

void g11 (double*, double*, double*, double*, int);

void g12 (double*, double*, double*, double*, int);

void g13 (double*, double*, double*, double*, int);

void g14 (double*, double*, double*, double*, int);

void g15 (double*, double*, double*, double*, int);

void g16 (double*, double*, double*, double*, int);

void g17 (double*, double*, double*, double*, int);

void g18 (double*, double*, double*, double*, int);

void g19 (double*, double*, double*, double*, int);

void g20 (double*, double*, double*, double*, int);

void g21 (double*, double*, double*, double*, int);

void g22 (double*, double*, double*, double*, int);

void g23 (double*, double*, double*, double*, int);

void g24 (double*, double*, double*, double*, int);


} // naspace CEC2006

} // namespace mde

#endif //MDE_CEC_2006_C_FUNCTIONS_H_H
