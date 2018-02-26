
#include "ctimeTree.h"

#include <limits>
#include <cmath>

//#include <iostream>
//double x = -1.1139344547335040e+307;
//double y = 0.00174532925199432957692369076849;
//double z = 0.0017453292519943296;
//
//long long u = x + 0.5;
//
//std::cout << "x = " << x << "\n";
//
//printf("%f\n", x);

constexpr double d1 = 1.0;
constexpr double d3 = d1 / 0.5;
constexpr int n = static_cast<int>(d3);

float x[n];

struct DecimalGrade;

struct GradeMinSec
{
	unsigned int n;
	unsigned int m;
	unsigned int l;

	GradeMinSec()
	{
	}

	GradeMinSec(unsigned int n_, unsigned int m_, unsigned int l_)
		: n(n_)
		, m(m_)
		, l(l_)
	{
	}

	explicit GradeMinSec( DecimalGrade g_ );
};

struct DecimalGrade
{
	double g;

	DecimalGrade()
	{
	}

	explicit DecimalGrade(double g_)
		: g(g_)
	{
	}

	explicit DecimalGrade(GradeMinSec g_)
		: g( g_.n + g_.m / 60.0 + g_.l / 3600.0 )
	{
	}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

GradeMinSec::GradeMinSec(DecimalGrade g_)
{
	double v = g_.g;

	n = static_cast<unsigned int>(v);
	v = (v - n) * 60.0;
	m = static_cast<unsigned int>(v);
	v = (v - m) * 60.0;
	l = static_cast<unsigned int>(v);

}

void ff()
{
	decltype(10) x;

	x = 10;
}


int main(int argc, char** argv)
{
	ctimeTreeRun();

	DecimalGrade g(2.0 / (1 << 12));
	//DecimalGrade g(1.0/3600);
	GradeMinSec gms(g);


	float x = static_cast< float >( ::rand() ) / RAND_MAX;

	double rad = 1.7578125 / 3600.0 * std::atan(1)*4.0 / 180.0;

	float ff = 6.0f / (1 << 8);

	float radFloat = 1.7578125f / 3600.0f * std::atan(1.0f)*4.0f / 180.0f;

	float radFloat2 = 0.0234375f * std::atan(1.0f)*4.0f / 180.0f;

	float inf = std::numeric_limits< float >::infinity();

	float atanInf = std::atan(inf);

    return 0;
}