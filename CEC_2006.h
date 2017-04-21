//
// Created by matheus on 3/26/17.
//

#ifndef BRKGA_CEC_2006_H
#define BRKGA_CEC_2006_H

#include "FunctionBase.h"
#include "CEC_2006_C_Functions.h"

namespace de
{
    namespace CEC_2006
    {

        struct F1 : public CEC_FunctionBase<13, 0, 9>
        {
            F1 () : CEC_FunctionBase<13, 0, 9>(g01)
            {
                id = 1;

                optimal = -15.0;

                for(int i = 0; i < 9; ++i)
                    lower[i] = 0.0, upper[i] = 1.0;

                for(int i = 9; i < 12; ++i)
                    lower[i] = 0.0, upper[i] = 1e2;

                lower[12] = 0.0, upper[12] = 1.0;
            }
        };


        struct F2 : public CEC_FunctionBase<20, 0, 2>
        {
            F2 () : CEC_FunctionBase<20, 0, 2>(g02, 0.0, 10.0, -0.8036191042) { id = 2; }
        };


        struct F3 : public CEC_FunctionBase<10, 1, 0>
        {
            F3 () : CEC_FunctionBase<10, 1, 0>(g03, 0.0, 1.0, -1.0005001000) { id = 3; }
        };


        struct F4 : public CEC_FunctionBase<5, 0, 6>
        {
            F4 () : CEC_FunctionBase<5, 0, 6>(g04)
            {
                id = 4;

                optimal = -30665.5386717834;

                lower[0] = 78.0, lower[1] = 33.0;
                upper[0] = 102.0, upper[1] = 45.0;

                for(int i = 2; i < 5; ++i)
                    lower[i] = 27.0, upper[i] = 45.0;
            }
        };


        struct F5 : public CEC_FunctionBase<4, 3, 2>
        {
            F5 () : CEC_FunctionBase<4, 3, 2>(g05)
            {
                id = 5;

                optimal = 5126.4967140071;

                lower[0] = lower[1] = 0.0;
                upper[0] = upper[1] = 1200.0;
                lower[2] = lower[3] = -0.55;
                upper[2] = upper[3] = 0.55;
            }
        };
    }
}


#endif //BRKGA_CEC_2006_H
