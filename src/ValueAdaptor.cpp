//#include "stdafx.h"
#include "ValueAdaptor.h"
#include <time.h>
#include <algorithm>

//#include <math.h>

void AxisAdaptor::InitState(double offset, double range, double wdth)
{
	m_offset = offset;
	m_range = range;
	m_step = GetStep(wdth);
	m_ticker = -(float)fmod((float)m_offset, (float)m_step);  //-fmod(m_offset, m_step);//(int)(m_offset / m_step) * m_step - m_offset;
	if (m_offset < 0)
		m_ticker -= m_step;

}

bool AxisAdaptor::Step()
{
	if (m_ticker > m_range)
		return false;

	m_ticker += m_step;
	return true;
}

double AxisAdaptor::GetStep(double r)
{
	double rval = 1.0;

	float pow_ind = floor(log10(m_range * r)) + 1;
	float dts = pow(10, pow_ind);

	//wxString text_format = wxString::Format(wxString("%%.%if"), (pow_ind > 0) ? ((int)0) : ((int)-pow_ind));
	
	//printf("df=%f\n", round(df));


	return dts;

}

template<class T> AxisValueAdaptor<T>::AxisValueAdaptor()
{
	DPRINTF("AxisValueAdaptor ctor\n");
	m_data = NULL;

}

template<typename T>
void AxisValueAdaptor<T>::SetData(DataTyped<T>* data)
{
	m_data = data;
}


template<class T> AxisValueAdaptor<T>::~AxisValueAdaptor()
{
	DPRINTF("AxisValueAdaptor dtor\n");
//	m_data->SetValueAdaptor(NULL); causes loop
}

template<typename T>
size_t AxisValueAdaptor<T>::ConvertToStr(char * str, size_t len, size_t indx)
{
	wxASSERT(indx < AxisValueAdaptor<T>::m_data->GetSize());

	T *data;
	data = AxisValueAdaptor<T>::m_data->GetDataArray();
	T val = data[indx];
	return ValToStr(str, len, val);
}






template<class T>
TimeAxisValueAdaptor<T>::TimeAxisValueAdaptor()
{
	DPRINTF("TimeAxisValueAdaptor ctor\n");

}

template<class T>
TimeAxisValueAdaptor<T>::~TimeAxisValueAdaptor()
{
	DPRINTF("TimeAxisValueAdaptor dtor\n");
}

template<typename T>
size_t TimeAxisValueAdaptor<T>::ValToStr(char * str, size_t len)
{
    int rlen;
	time_t tv = time_value_integer + AxisValueAdaptor<T>::m_offset;
    if((T)time_value_integer + AxisValueAdaptor<T>::m_offset >= 0)
	{
        struct tm tmstruct;
        memset(&tmstruct, 0, sizeof(struct tm));
        memcpy(&tmstruct, gmtime(&tv), sizeof(struct tm));
        rlen = strftime(str, len, "%H:%M:%S %d-%b-%y", &tmstruct);
	}else
	{
        str[0] = '\0';
        rlen = 0;
	}
        return rlen;
}

template<typename T>
size_t TimeAxisValueAdaptor<T>::ValToStr(char * str, size_t len, T val)
{
	wxASSERT(0);
	return size_t();
}

template<typename T>
void TimeAxisValueAdaptor<T>::InitState(double offset, double range, double wdth)
{
	AxisValueAdaptor<T>::m_offset = offset;
	AxisValueAdaptor<T>::m_range = range;

	m_timetick_granularity = TIMETICK_20YEARS;
	double r;
	r = wdth * AxisValueAdaptor<T>::m_range;

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

	AxisValueAdaptor<T>::m_step = GetStep(wdth);
	AxisValueAdaptor<T>::m_ticker = -fmod(AxisValueAdaptor<T>::m_offset, AxisValueAdaptor<T>::m_step);
	
	if (AxisValueAdaptor<T>::m_offset <= 0)
		AxisValueAdaptor<T>::m_ticker -= AxisValueAdaptor<T>::m_step ;

	time_value_integer = AxisValueAdaptor<T>::m_ticker;
	time_value_fraction = fmod(AxisValueAdaptor<T>::m_ticker, 1);

	//printf("step = %f int = %i frac = %f\n", AxisValueAdaptor<T>::m_step, (int)time_value_integer, time_value_fraction);
}

template<typename T>
bool TimeAxisValueAdaptor<T>::Step()
{
	if ((time_value_integer + time_value_fraction)> AxisValueAdaptor<T>::m_range)
		return false;

	time_value_integer += AxisValueAdaptor<T>::m_step;
	return true;
}

template<typename T>
double TimeAxisValueAdaptor<T>::GetStep(double r)
{
	T rval;
	switch (m_timetick_granularity) {
	case TIMETICK_1S:
		rval = 1;
		break;
	case TIMETICK_10S:
		rval = 10;
		break;
	case TIMETICK_1MIN:
		rval = 60;
		break;
	case TIMETICK_10MIN:
		rval = 600;
		break;
	case TIMETICK_1H:
		rval = 3600;
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

template<typename T>
double TimeAxisValueAdaptor<T>::GetTicker()
{
	return (T)time_value_integer + (T)time_value_fraction;
}


template<typename T>
SimpleAxisValueAdaptor<T>::SimpleAxisValueAdaptor()
{
	DPRINTF("SimpleAxisValueAdaptor ctor");
}

template<typename T>
SimpleAxisValueAdaptor<T>::~SimpleAxisValueAdaptor()
{
	DPRINTF("SimpleAxisValueAdaptor dtor");
}

template<typename T>
size_t SimpleAxisValueAdaptor<T>::ValToStr(char * str, size_t len)
{
	double val;
	val = AxisValueAdaptor<T>::m_offset + AxisValueAdaptor<T>::m_ticker;
	sprintf(str, "%.2f", val);
	if (!strcmp(str, "-0.00") || !strcmp(str, "0.00"))
	{
		strcpy(str, "0");
	}
	return strlen(str);
}

template<typename T>
size_t SimpleAxisValueAdaptor<T>::ValToStr(char * str, size_t len, T val)
{
	wxASSERT(0);
	return 0;
}

//
//template<typename T>
//SecsAxisValueAdaptor<T>::SecsAxisValueAdaptor()
//{
//	DPRINTF("SecsAxisValueAdaptor ctor\n");
//}
//
//template<typename T>
//SecsAxisValueAdaptor<T>::~SecsAxisValueAdaptor()
//{
//	DPRINTF("SecsAxisValueAdaptor dtor\n");
//}
//
//template<typename T>
//size_t SecsAxisValueAdaptor<T>::ValToStr(char * str, size_t len, T val)
//{
//	wxASSERT(0);
//	return size_t();
//}
//
//
//template<typename T>
//size_t SecsAxisValueAdaptor<T>::ValToStr(char * str, size_t len)
//{
//	float val;
//	val = m_offset + m_ticker;
//	if (val >= 0)
//		sprintf(str, "%.0f", val);
//	else
//		str[0] = '\0';
//	return 0;
//}
//
//template<typename T>
//double SecsAxisValueAdaptor<T>::GetStep(double r)
//{
//	return 1.0;
//}



