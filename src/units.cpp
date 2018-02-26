
#include "units.h"

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

	explicit GradeMinSec(DecimalGrade g_);
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
		: g(g_.n + g_.m / 60.0 + g_.l / 3600.0)
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

void runUnits()
{
	DecimalGrade g(2.0 / (1 << 12));
	GradeMinSec gms(g);
}