#include <bits/stdc++.h>

#include "MDE.h"
#include "Constraints.h"
#include "CEC_2006.h"

using namespace std;





int main()
{
	int seed = 270001;

	int n = 25, FEs = 0, suc = 0;

	for(int i = 0; i < n; ++i)
	{
		rng::Rand::generator.seed(seed++);

	    de::MDE<de::PenaltyEps<de::CEC_2006::F2>> mde;

	    auto best = mde();

	    //if(mde.fitness.FEs >= 5e5) DB("Do not converged\n");

	    if(mde.fitness.FEs <= 5e5)
	    	FEs += mde.fitness.FEs, suc++;
	}

	DB((FEs / double(suc)) * (n / double(suc)));


	// int seed = 270005;
	// rng::Rand::generator.seed(seed++);

	// de::MDE<de::PenaltyEps<de::CEC_2006::F2>> mde;

	// auto best = mde();


 //    DB("\n\n" << best.fitness << "        " << best.violation << "\n");

 //    for(auto x : best) cout << x << "   "; cout << "\n";


    return 0;
}