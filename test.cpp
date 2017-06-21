#include <iostream>

#include "include/MDE/MDE.h"
#include "examples/CEC2006/CEC2006.h"

using namespace std;





struct NLP : mde::Function<>
{
	NLP (double opt = 0.25)
	{
		lowerBounds = {0.0, 0.2};
		upperBounds = {0.5, 0.8};

		optimal = opt + 1e-10;
	}


	double operator () (const vector<double>& x)
	{
		return 100 * pow(x[1] - x[0] * x[0], 2) + pow(1 - x[0], 2);
	}

	auto equalities (const vector<double>& x)
	{
		return 0.0;
	}

	initializer_list<double> inequalities (const vector<double>& x)
	{
		return {0.0};
	}

	int N = 2;
	int FEs = 0;
};




int main()
{
	int seed = 270011;

	//help::Rand::generator.seed(seed);


	mde::Parameters params;

	//params.maxIter = 500;
	//params.popSize = 200;
	params.eqTol = 1e-4;
	params.bndHandle = "conservate";


	auto best = mde::MDE<NLP>(params)();

	//de::Parameters param; param.popSize = 50;
	
	//de::MDE<NLP> mde;


	cout << "\n\n\n";

	cout << "Best individual found:    "; for(auto x : best) cout << x << "   "; cout << "\n\n";

	cout << "Fitness:     " << best.fitness << "\n\n";

    cout << "Constraint Violation:     " << best.violation << "\n\n";



    return 0;
}