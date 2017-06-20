/** \file CEC2006.cpp
  *
  * Implementation of CEC2006.h definitions.
  * Here all 'optimal' values are set to '1e-4' above, to reach
  * the CEC convergence condition
*/


#include "CEC2006.h"


namespace mde
{

namespace CEC2006
{


F1::F1 () : Base(g01)
{
    optimal = -15.0 + 1e-4;

    for(int i = 0; i < 9; ++i)
        lowerBounds[i] = 0.0, upperBounds[i] = 1.0;

    for(int i = 9; i < 12; ++i)
        lowerBounds[i] = 0.0, upperBounds[i] = 1e2;

    lowerBounds[12] = 0.0, upperBounds[12] = 1.0;
}


F2::F2 () : Base(g02, 0.0, 10.0, -0.8036191042 + 1e-4) {}


F3::F3 () : Base(g03, 0.0, 1.0, -1.0005001000 + 1e-4) {}


F4::F4 () : Base(g04)
{
    optimal = -30665.5386717834 + 1e-4;

    lowerBounds[0] = 78.0, lowerBounds[1] = 33.0;
    upperBounds[0] = 102.0, upperBounds[1] = 45.0;

    for(int i = 2; i < 5; ++i)
        lowerBounds[i] = 27.0, upperBounds[i] = 45.0;
}


F5::F5 () : Base(g05)
{
    optimal = 5126.4967140071 + 1e-4;

    lowerBounds[0] = lowerBounds[1] = 0.0;
    upperBounds[0] = upperBounds[1] = 1200.0;
    lowerBounds[2] = lowerBounds[3] = -0.55;
    upperBounds[2] = upperBounds[3] = 0.55;
}


} // namespace CEC2006

} // namespace mde