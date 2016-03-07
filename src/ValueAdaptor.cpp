#include <time.h>
#include <algorithm>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#include "ValueAdaptor.h"

using namespace plot;

static const char *s_fmt_f = "  %g"; //"  %.2f";
static const char *s_fmt_e = "  %.2e"; //"  %.2e";

plot::AxisAdaptor::AxisAdaptor()
{
	DPRINTF("AxisAdaptor ctor\n");
	m_offset = 0.;
	m_range = 0.;
	m_major_tick_step  = 0.;
	m_minor_tick_step = 0.;
	m_major_stepper = 0.;
	m_minor_stepper = 0.;
}

void AxisAdaptor::InitState(double offset, double range, double rwidth)
{
	m_offset = offset;
	m_range = range;

	auto rr = rwidth * m_range;

	m_major_tick_step = pow(10, ceil(log10(rr)));//major
	m_minor_tick_step = 0.;//minor

	if (m_major_tick_step / 2. > rr)
	{
		m_major_tick_step /= 2.;
	}

	if (m_major_tick_step / 5. > rr / 4.)
	{
		m_minor_tick_step = m_major_tick_step / 5.;
	}
	else
	{
		if (m_major_tick_step / 4. > rr / 4.)
		{
			m_minor_tick_step = m_major_tick_step / 4.;
		}
	}

	m_major_stepper = -fmod(m_offset, m_major_tick_step) - 2 * m_major_tick_step;
	m_minor_stepper = 0.;

	if (log10(m_range) > 4)
		m_format_str = s_fmt_e;
	else
		m_format_str = s_fmt_f;
}

bool AxisAdaptor::MajorStep()
{
	auto res = (m_major_stepper < m_range);
	m_minor_stepper = 0.;
	m_major_stepper += m_major_tick_step;
	return res;
}

bool plot::AxisAdaptor::MinorStep()
{
	if (m_minor_tick_step == 0.)
		return false;

	m_minor_stepper += m_minor_tick_step;
	return (m_minor_stepper < m_major_tick_step);

}

bool plot::AxisAdaptor::IsMiddleMinor()
{
	return m_major_tick_step / m_minor_stepper == 2.;
}

void plot::AxisAdaptor::SetLimitsForScale(Scale * scale)
{
	scale->SetLimits(DBL_MAX, DBL_MIN);
}

AxisValueAdaptor::AxisValueAdaptor()
{
	DPRINTF("AxisValueAdaptor ctor\n");

}

AxisValueAdaptor::~AxisValueAdaptor()
{
	DPRINTF("AxisValueAdaptor dtor\n");
}

TimeAxisValueAdaptor::TimeAxisValueAdaptor()
{
	DPRINTF("TimeAxisValueAdaptor ctor\n");

}

TimeAxisValueAdaptor::~TimeAxisValueAdaptor()
{
	DPRINTF("TimeAxisValueAdaptor dtor\n");
}

size_t TimeAxisValueAdaptor::ValToStr(char * str, size_t len)
{
    int rlen = 0;

	time_t tv = m_major_stepper + m_offset + fmod(m_major_stepper, 1);

	struct tm tmstruct;
    memset(&tmstruct, 0, sizeof(struct tm));
	auto pstruct = gmtime(&tv);
	if (pstruct != nullptr)
	{
		memcpy(&tmstruct, pstruct, sizeof(struct tm));

		rlen = strftime(str, len, "%H:%M:%S\n%d-%b-%y", &tmstruct);
	}
	else
		strcpy(str, "F");
	return rlen;
}

size_t TimeAxisValueAdaptor::ValToStr(char * str, size_t len, double val)
{
	m_offset = val;
	m_major_stepper = 0;
	m_format_str = s_fmt_f;
	auto res = ValToStr(str, len);
	return res;
}

bool TimeAxisValueAdaptor::ValBiggerPart(char * str, size_t len)
{
	time_t tv1 =  AxisValueAdaptor::m_offset;
	time_t tv2 =  AxisValueAdaptor::m_offset + AxisValueAdaptor::m_range;
	bool crosses_day;

	crosses_day = (tv2 / (60 * 60 * 24)) > (tv1 / (60 * 60 * 24));

	if (!crosses_day)
	{
		struct tm tmstruct;
		memset(&tmstruct, 0, sizeof(struct tm));
		if (gmtime(&tv1) != NULL)
		{
			memcpy(&tmstruct, gmtime(&tv1), sizeof(struct tm));
			strftime(str, len, "%d-%b-%y", &tmstruct);
		}
		else
		{
			sprintf(str, "error");
		}
		return true;
	}
	return false;
}

void TimeAxisValueAdaptor::InitState(double offset, double range, double rwidth)
{
	AxisValueAdaptor::m_offset = offset;
	AxisValueAdaptor::m_range = range;

	m_timetick_granularity = TIMETICK_20YEARS;

	double r;
	r = rwidth * AxisValueAdaptor::m_range;

	if (r < 1)
		m_timetick_granularity = TIMETICK_1S;
	else
		if (r < 10)
			m_timetick_granularity = TIMETICK_10S;
		else
			if (r < 60)
				m_timetick_granularity = TIMETICK_1MIN;
			else
				if (r < 600)
					m_timetick_granularity = TIMETICK_10MIN;
				else
					if (r < 3600)
						m_timetick_granularity = TIMETICK_1H;
					else
						if (r < 60 * 60 * 6)
							m_timetick_granularity = TIMETICK_6H;
						else
							if (r < 60 * 60 * 12)
								m_timetick_granularity = TIMETICK_12H;
							else
								if (r < 60 * 60 * 24)
									m_timetick_granularity = TIMETICK_1DAY;
								else
									if (r < 60 * 60 * 24 * 7)
										m_timetick_granularity = TIMETICK_1WEEK;
									else
										if (r < 60 * 60 * 24 * 30)
											m_timetick_granularity = TIMETICK_1MONTH;
										else
											if (r < 60 * 60 * 24 * 365)
												m_timetick_granularity = TIMETICK_1YEAR;
											else
												if (r < 60 * 60 * 24 * 365 * 10)
													m_timetick_granularity = TIMETICK_10YEARS;
												else
													if (r < 60 * 60 * 24 * 365 * 20)
														m_timetick_granularity = TIMETICK_20YEARS;

	m_major_tick_step = _getstep(rwidth);
	m_major_stepper = -fmod(AxisValueAdaptor::m_offset, AxisValueAdaptor::m_major_tick_step) - m_major_tick_step;
	m_minor_stepper = 0.;

}

bool TimeAxisValueAdaptor::MajorStep()
{
	auto res = AxisAdaptor::MajorStep();

	return res;
}

bool plot::TimeAxisValueAdaptor::MinorStep()
{
	return AxisAdaptor::MinorStep();
}

bool plot::TimeAxisValueAdaptor::IsMiddleMinor()
{
	return false;
}

void plot::TimeAxisValueAdaptor::SetLimitsForScale(Scale * scale)
{
	scale->SetLimits(2e+9, 1);
}

double TimeAxisValueAdaptor::_getstep(double r)
{
	double rval = 0;

	m_minor_tick_step = 0;

	switch (m_timetick_granularity) {
	case TIMETICK_1S:
		rval = 1;
		m_minor_tick_step = 0;
		break;
	case TIMETICK_10S:
		rval = 10;
		m_minor_tick_step = 1;
		break;
	case TIMETICK_1MIN:
		rval = 60;
		m_minor_tick_step = 10;
		break;
	case TIMETICK_10MIN:
		rval = 600;
		m_minor_tick_step = 60;
		break;
	case TIMETICK_1H:
		rval = 3600;
		m_minor_tick_step = 600;
		break;
	case TIMETICK_6H:
		rval = 3600 * 6;
		break;
	case TIMETICK_12H:
		rval = 3600 * 12;
		break;
	case TIMETICK_1DAY:
		rval = 3600 * 24;
		break;
	case TIMETICK_1WEEK:
		rval = 3600 * 24 * 7;
		break;
	case TIMETICK_1MONTH:
		rval = 3600 * 24 * 31;
		break;
	case TIMETICK_1YEAR:
		rval = 3600 * 24 * 365;
		break;
	case TIMETICK_10YEARS:
		rval = 3600 * 24 * 365 * 10;
		break;
	case TIMETICK_20YEARS:
		rval = 3600 * 24 * 365 * 20;
		break;
	default:
		rval = 3600 * 24 * 365 * 20;
	}

	return rval;
}

SimpleAxisValueAdaptor::SimpleAxisValueAdaptor()
{
	DPRINTF("SimpleAxisValueAdaptor ctor");
}

SimpleAxisValueAdaptor::~SimpleAxisValueAdaptor()
{
	DPRINTF("SimpleAxisValueAdaptor dtor");
}

size_t SimpleAxisValueAdaptor::ValToStr(char * str, size_t len)
{
	double val;
	val = AxisValueAdaptor::m_offset + AxisValueAdaptor::m_major_stepper;
	sprintf(str, m_format_str, val);

	if (!strcmp(str, "-0.00") || !strcmp(str, "0.00"))
	{
		strcpy(str, "0");
	}
	return strlen(str);
}

size_t SimpleAxisValueAdaptor::ValToStr(char * str, size_t len, double val)
{
//	assert(0);
	m_offset = val;
	m_major_stepper = 0;
	m_format_str = s_fmt_f;
	return ValToStr(str, len);
}

bool SimpleAxisValueAdaptor::ValBiggerPart(char * str, size_t len)
{
	return false;
}



