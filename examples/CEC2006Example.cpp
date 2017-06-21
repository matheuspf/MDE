/**	\file CEC2006Example.cpp
  *
  * This file shows how to optimize the CEC 2006 functions using MDE.
  * See more in:
  *
  * http://www.ntu.edu.sg/home/EPNSugan/index_files/CEC-06/CEC06.html
*/

#include <iostream>

#include "MDE/MDE.h"			/// MDE header
#include "CEC2006/CEC2006.h"	/// CEC2006 header --- must compile with CEC2006_C_Functions.cpp and CEC2006.cpp


int main ()
{
	mde::Parameters params;		 /// Define some parameters. Everything else is set to the default values

	params.eqTol = 1e-4;	/// Tolerance for equality constraints

	/** Bounds handling function. In the MDE paper, there is no information 
	  * about how out of bounds solutions are handled. The best way I found
	  * is the "conservate" (which is the default) option. For more, see the 
	  * 'MDE.h' file and the paper:
	  *
	  * https://elektron.elka.pw.edu.pl/~jarabas/ALHE/krakow1.pdf
	*/
	params.bndHandle = "conservate";


	/// Chose the function. They range from F1-F24 in the namespace mde::CEC2006
	using Function = mde::CEC2006::F1;


	/// Instantiate a 'MDE' class with function 'Function' and parameters 'params'
	mde::MDE<Function> de(params);


	auto best = de();	/// Run MDE and retrieve the best element found during the search


	/// Display information about that element
	std::cout << "Best element found:\n\n";

	for(auto x : best)
		std::cout << x << "   ";
	std::cout << "\n\n\n";

	std::cout << "Fitness:                   " << best.fitness << "\n\n";
	std::cout << "Violation:                 " << best.violation << "\n\n";
	std::cout << "Distance from optimal:     " << best.fitness - Function().optimal << "\n\n";


	return 0;
}