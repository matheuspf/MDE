#include <cmath>

#include "gtest/gtest.h"
#include "MDE/MDE.h"
#include "CEC2006/CEC2006.h"

using namespace mde;
using namespace mde::CEC2006;


#define TEST_FUNCTION(FUNC)       \
							      \
TEST_F(MDETest, FUNC)         \
{							      \
	using namespace mde;		  \
	using namespace mde::CEC2006; \
								  \
 	FUNC func;				      \
						          \
	MDE<FUNC> mde(params, func);  \
							      \
	SCOPED_TRACE(#FUNC); 	      \
							      \
	check(mde(), 			      \
		  func.lowerBounds,       \
		  func.upperBounds);      \
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
    Ackley (int N = 20) : N(N), a(20.0), b(0.2), c(8.0*std::atan(1.0)), l(-30.0), r(30.0)
    {
        lowerBounds = Vector(N, l);
        upperBounds = Vector(N, r);
    }


    inline double operator () (const std::vector<double>& v) const
    {
        double y1 = std::accumulate(v.begin(), v.end(), 0.0, [&](double acum, double x){ return acum + x*x; });
        double y2 = std::accumulate(v.begin(), v.end(), 0.0, [&](double acum, double x){ return acum + std::cos(c * x); });

        return -a * std::exp(-b * std::sqrt(y1 / N)) - std::exp(y2 / N) + a + std::exp(1.0);
    }

    int N;
    double a, b, c, l, r;
};



struct Rosenbrock : mde::Function<>
{
    Rosenbrock (int N = 10) : N(N)
    {
        optimal = 1e-10;

        lowerBounds = Vector(N, -10.0);
        upperBounds = Vector(N, 10.0);
    }


    double operator () (const Vector& x) const
    {
        double r = 0.0;

        for(int i = 0; i < N - 1; ++i)
            r += 100.0 * std::pow(x[i] * x[i] - x[i+1], 2) + std::pow(x[i] - 1.0, 2);

        return r;
    }

    int N;
};



struct ConstRosenbrock : mde::Function<2>
{
	ConstRosenbrock ()
	{
		lowerBounds = {0.0, 0.2};
		upperBounds = {0.5, 0.8};
	}


	double operator () (const Vector& x)
	{
		return 100.0 * std::pow(x[1] - x[0] * x[0], 2) + std::pow(1.0 - x[0], 2);
	}

	double inequalities (const Vector& x)
	{
		return std::pow(x[0] - 1.0/3, 2) + std::pow(x[1] - 1.0/3, 2) - std::pow(1.0/3, 2);
	}
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

TEST_FUNCTION(Ackley)
TEST_FUNCTION(Rosenbrock)
TEST_FUNCTION(ConstRosenbrock)



} // namespace

