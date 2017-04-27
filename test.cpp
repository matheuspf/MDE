#include <iostream>

#include "src/MDE.h"
#include "src/FunctionBase.h"
#include "src/CEC_2006.h"

using namespace std;



struct NLP : de::FunctionBase<>
{
	using Base = de::FunctionBase<>;

	NLP (int N = 2) : Base(N)
	{
		lower = {0.0, 0.2};
		upper = {0.5, 0.8};
	}


	double operator () (const Vector& x)
	{
		return 100 * pow(x[1] - x[0] * x[0], 2) + pow(1 - x[0], 2);
	}

	double constraints (const Vector& x)
	{
		return x[0] * x[0] + x[1] * x[1] - 1;
	}
};




int main()
{
	int seed = 270001;

	rng::Rand::generator.seed(seed);



	//de::MDE<de::CEC_2006::F1> mde;

	de::Parameters param; param.popSize = 50;
	
	de::MDE<NLP> mde(param);

	auto best = mde();

	cout << "Best individual found:    "; for(auto x : best) cout << x << "   "; cout << "\n\n";

	cout << "Fitness:     " << best.fitness << "\n\n";

    cout << "Constraint Violation:     " << best.violation << "\n";



    return 0;
}