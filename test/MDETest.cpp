#include <cmath>

#include "gtest/gtest.h"
#include "MDE/MDE.h"
#include "CEC2006/CEC2006.h"

using namespace mde;
using namespace mde::CEC2006;


#define TEST_FUNCTION(FUNC)       		  \
							      		  \
TEST_F(MDETest, FUNC)         	  		  \
{							      		  \
	using namespace mde;		  		  \
	using namespace mde::CEC2006; 		  \
						          		  \
	MDE<FUNC> mde(params);  			  \
							      		  \
	SCOPED_TRACE(#FUNC); 	      		  \
							      		  \
	check(mde(), 			      		  \
		  mde.function.lowerBounds,       \
		  mde.function.upperBounds);      \
}



namespace
{

struct MDETest : public ::testing::Test
{
	MDETest () { }

	virtual ~MDETest () { }


	virtual void SetUp ()
	{
		params.popSize = 30;
		params.Fa = 0.8;
		params.Fb = 0.1;
		params.Cr = 0.9;
		params.Srmax = 0.55;
		params.Srmin = 0.025;
        params.children = 5;
        params.maxIter = 3333;
        params.eqTol = 1e-4;
        params.bndHandle = "conservate";
	}


	virtual void TearDown () {}


	template <class Vector>
	void checkNan (const Vector& v)
	{
		for(auto x : v)
			EXPECT_FALSE(std::isnan(x));

		EXPECT_FALSE(std::isnan(v.fitness));
		EXPECT_FALSE(std::isnan(v.violation));
	}


	template <class Vector>
	void checkInf (const Vector& v)
	{
		for(auto x : v)
			EXPECT_FALSE(std::isinf(x));

		EXPECT_FALSE(std::isinf(v.fitness));
		EXPECT_FALSE(std::isinf(v.violation));
	}


	template <class Vector>
	void checkBounds (const Vector& v, const Vector& l, const Vector& u)
	{
		for(int i = 0; i < v.size(); ++i)
		{
			EXPECT_GE(v[i], l[i]);
			EXPECT_LE(v[i], u[i]);
		}
	}


	template <class Vector>
	void check (const Vector& x, const Vector& l, const Vector& u)
	{
		checkNan(x);
		checkInf(x);
		checkBounds(x, l, u);
	}


	Parameters params;

};



struct Ackley : public mde::Function<>
{
    Ackley (int M = 20) : a(20.0), b(0.2), c(8.0*std::atan(1.0)), l(-30.0), r(30.0)
    {
        lowerBounds = Vector(M, l);
        upperBounds = Vector(M, r);
    }


    inline double operator () (const std::vector<double>& v) const
    {
        double y1 = std::accumulate(v.begin(), v.end(), 0.0, [&](double acum, double x){ return acum + x*x; });
        double y2 = std::accumulate(v.begin(), v.end(), 0.0, [&](double acum, double x){ return acum + std::cos(c * x); });

        return -a * std::exp(-b * std::sqrt(y1 / v.size())) - std::exp(y2 / v.size()) + a + std::exp(1.0);
    }

    double a, b, c, l, r;
};



struct Rosenbrock : mde::Function<>
{
    Rosenbrock (int M = 10)
    {
        lowerBounds = Vector(M, -10.0);
        upperBounds = Vector(M, 10.0);
        optimal = 1e-10;
    }


    double operator () (const Vector& x) const
    {
        double r = 0.0;

        for(int i = 0; i < x.size() - 1; ++i)
            r += 100.0 * std::pow(x[i] * x[i] - x[i+1], 2) + std::pow(x[i] - 1.0, 2);

        return r;
    }
};



struct ConstRosenbrock : mde::Function<>
{
	ConstRosenbrock ()
	{
		//lowerBounds = {0.0, 0.2};
		//upperBounds = {0.5, 0.8};
	}


	double operator () (const Vector& x)
	{
		return 100.0 * std::pow(x[1] - x[0] * x[0], 2) + std::pow(1.0 - x[0], 2);
	}

	double inequalities (const Vector& x)
	{
		return std::pow(x[0] - 1.0/3, 2) + std::pow(x[1] - 1.0/3, 2) - std::pow(1.0/3, 2);
	}

	int N = 2;
};



TEST_FUNCTION(F1)
TEST_FUNCTION(F2)
TEST_FUNCTION(F3)
TEST_FUNCTION(F4)
TEST_FUNCTION(F5)
TEST_FUNCTION(F6)
TEST_FUNCTION(F7)
TEST_FUNCTION(F8)
TEST_FUNCTION(F9)
TEST_FUNCTION(F10)
TEST_FUNCTION(F11)
TEST_FUNCTION(F12)
TEST_FUNCTION(F13)
TEST_FUNCTION(F14)
TEST_FUNCTION(F15)
TEST_FUNCTION(F16)
TEST_FUNCTION(F17)
TEST_FUNCTION(F18)
TEST_FUNCTION(F19)
TEST_FUNCTION(F20)
TEST_FUNCTION(F21)
TEST_FUNCTION(F22)
TEST_FUNCTION(F23)
TEST_FUNCTION(F24)




TEST_F(MDETest, Ackley)
{
	params.bndHandle = "clip";

	MDE<Ackley> mde(params);
							      
	SCOPED_TRACE("Ackley"); 	      
							      
	check(mde(), mde.function.lowerBounds, mde.function.upperBounds);
}


TEST_F(MDETest, Rosenbrock)
{
	params.bndHandle = "reinitialize";

	MDE<Rosenbrock> mde(params);
							      
	SCOPED_TRACE("Rosenbrock"); 	      
							      
	check(mde(), mde.function.lowerBounds, mde.function.upperBounds);
}


TEST_F(MDETest, ConstRosenbrock)
{
	params.bndHandle = "reinitialize";

	MDE<ConstRosenbrock> mde(params);
							      
	SCOPED_TRACE("ConstRosenbrock"); 	      
							      
	check(mde(), mde.function.lowerBounds, mde.function.upperBounds);
}




} // namespace

