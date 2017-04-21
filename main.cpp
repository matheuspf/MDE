#include <bits/stdc++.h>

#include "MDE.h"
#include "Constraints.h"
#include "CEC_2006.h"

using namespace std;





int main()
{
	de::MDE<de::PenaltyEps<de::CEC_2006::F1>> mde;

	auto best = mde();

    cout << "\n\n" << best.fitness << "        " << best.violation << "\n";

    for(auto x : best) cout << x << "   "; cout << "\n";


    return 0;
}