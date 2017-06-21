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


F6::F6 () : Base(g06)
{
    optimal = -6961.81387558015+1e-4;

    lowerBounds[0] = 13.0, upperBounds[0] = 100.0;
    lowerBounds[0] = 0.0,  upperBounds[1] = 100.0;
}


F7::F7 () : Base(g07, -10.0, 10.0, 24.30620906818+1e-4) {}

        
F8::F8 () : Base(g08, 0, 10.0, -0.0958250414180359+1e-4) {}


F9::F9 () : Base(g09, -10.0, 10.0, 680.630057374402+1e-4) {}


F10::F10 () : Base(g10)
{
    optimal = 7049.24802052867+1e-4;

    lowerBounds[0] = 100.0, upperBounds[0] = 10000.0;

    for(int i = 1; i < 3; ++i)
        lowerBounds[i] = 1000.0, upperBounds[i] = 10000.0;

    for(int i = 3; i < 8; ++i)
        lowerBounds[i] = 10.0, upperBounds[i] = 1000.0;

}

  
F11::F11 () : Base(g11, -1.0, 1.0,  0.7499+1e-4) {}


F12::F12 () : Base(g12, 0.0, 10.0, -1.0+1e-4) {  }


        
F13::F13 () : Base(g13)
{
    optimal = 0.053941514041898+1e-4;

    lowerBounds = {-2.3, -2.3, -3.2, -3.2, -3.2};
    upperBounds = {2.3, 2.3, 3.2, 3.2, 3.2};
}


F14::F14 () : Base(g14, 0.0, 10.0, -47.7648884594915+1e-4) {}

        
F15::F15 () : Base(g15, 0.0, 10.0, 961.715022289961+1e-4) {}


F16::F16 () : Base(g16)
{
    optimal = -1.90515525853479+1e-4;

    lowerBounds[0] = 704.4148, upperBounds[0] = 906.3855;
    lowerBounds[1] = 68.6,     upperBounds[1] = 288.88;
    lowerBounds[2] = 0,        upperBounds[2] = 134.75;
    lowerBounds[3] = 193.0,    upperBounds[3] = 287.0966;
    lowerBounds[4] = 25.0;     upperBounds[4] = 84.1988;
}


F17::F17 () : Base(g17)
{
    optimal = 8853.53967480648+1e-4;

    lowerBounds[0] = 0.0,      upperBounds[0] = 400.0;
    lowerBounds[1] = 0.0,      upperBounds[1] = 1000.0;
    lowerBounds[2] = 340.0,    upperBounds[2] = 420.0;
    lowerBounds[3] = 340.0,    upperBounds[3] = 420.0;
    lowerBounds[4] = -1000.0;  upperBounds[4] = 1000.0;
    lowerBounds[5] = 0.0;      upperBounds[5] = 0.5236;
}


F18::F18 () : Base(g18)
{
    

    optimal = -0.866025403784439+1e-4;

    for(int i = 0; i < 8; ++i)
        lowerBounds[i] = -10.0, upperBounds[i] = 10.0;

    lowerBounds[8] = 0.0, upperBounds[8] = 20.0;
}



F19::F19 () : Base(g19, 0.0, 10.0, 32.6555929502463+1e-4) {}


F20::F20 () : Base(g20, 0.0, 10.0, 0.2049794002+1e-4) {}


F21::F21 () : Base(g21)
{
    optimal = 193.724510070035+1e-4;

    lowerBounds[0] = 0.0,      upperBounds[0] = 1000.0;
    lowerBounds[1] = 0.0,      upperBounds[1] = 40.0;
    lowerBounds[2] = 0.0,      upperBounds[2] = 40.0;
    lowerBounds[3] = 100.0,    upperBounds[3] = 300.0;
    lowerBounds[4] = 6.3;      upperBounds[4] = 6.7;
    lowerBounds[5] = 5.9;      upperBounds[5] = 6.4;
    lowerBounds[6] = 4.5;      upperBounds[6] = 6.25;
}


F22::F22 () : Base(g22)
{
    optimal = 236.430975504001+1e-4;

    lowerBounds[0] = 0.0, upperBounds[0] = 20000.0;
    for(int i = 1; i < 4; ++i) lowerBounds[i] = 0.0, upperBounds[i] = 1e6;
    for(int i = 4; i < 7; ++i) lowerBounds[i] = 0.0, upperBounds[i] = 4e7;
    lowerBounds[7] = 100.0, upperBounds[7] = 299.99;
    lowerBounds[8] = 100.0, upperBounds[8] = 399.99;
    lowerBounds[9] = 100.01, upperBounds[9] = 300.0;
    lowerBounds[10] = 100.0, upperBounds[10] = 400.0;
    lowerBounds[11] = 100.0, upperBounds[11] = 600.0;
    for(int i = 12; i < 15; ++i) lowerBounds[i] = 0.0, upperBounds[i] = 500.0;
    lowerBounds[15] = 0.01, upperBounds[15] = 300.0;
    lowerBounds[16] = 0.01, upperBounds[16] = 400.0;
    for(int i = 17; i < 22; ++i) lowerBounds[i] = -4.7, upperBounds[i] = 6.25;
}

        
F23::F23 () : Base(g23)
{
    optimal = -400.055099999999584+1e-4;

    lowerBounds[0] = lowerBounds[1] = lowerBounds[5] = 0.0;
    upperBounds[0] = upperBounds[1] = upperBounds[5] = 300.0;

    lowerBounds[2] = lowerBounds[4] = lowerBounds[6] = 0.0;
    upperBounds[2] = upperBounds[4] = upperBounds[7] = 100.0;

    lowerBounds[3] = lowerBounds[7] = 0.0;
    upperBounds[3] = upperBounds[7] = 200.0;

    lowerBounds[8] = 0.01, upperBounds[8] = 0.03;
}

        
F24::F24 () : Base(g24)
{
    optimal = -5.50801327159536+1e-4;

    lowerBounds = Vector{0.0, 0.0};
    upperBounds = Vector{3.0, 4.0};
}


} // namespace CEC2006

} // namespace mde