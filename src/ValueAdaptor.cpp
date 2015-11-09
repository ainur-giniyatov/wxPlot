//#include "stdafx.h"
#include "ValueAdaptor.h"
#include <time.h>
//#include <math.h>

template<class T> ValueAdaptor<T>::ValueAdaptor()
{
	DPRINTF("ValueAdaptor ctor\n");
	m_data = NULL;

}

template<typename T>
void ValueAdaptor<T>::SetData(DataTyped<T>* data)
{
	m_data = data;
}


template<class T> ValueAdaptor<T>::~ValueAdaptor()
{
	DPRINTF("ValueAdaptor dtor\n");
//	m_data->SetValueAdaptor(NULL); causes loop
}

template<typename T>
size_t ValueAdaptor<T>::ConvertToStr(char * str, size_t len, size_t indx)
{
	wxASSERT(indx < ValueAdaptor<T>::m_data->GetSize());

	T *data;
	data = ValueAdaptor<T>::m_data->GetDataArray();
	T val = data[indx];
	return ValToStr(str, len, val);
}

template<typename T>
void ValueAdaptor<T>::InitState(T offset, T range, T wdth)
{
	m_offset = offset;
	m_range = range;
	m_step = GetStep(wdth);
	m_ticker = -fmod(m_offset, m_step);//(int)(m_offset / m_step) * m_step - m_offset;
	if(m_offset < 0)
        m_ticker -= m_step;
}

template<typename T>
bool ValueAdaptor<T>::Step()
{
	if(m_ticker > m_range)
		return false;

	m_ticker += m_step;
	return true;
}

template<typename T>
T ValueAdaptor<T>::GetTicker()
{
	return m_ticker;
}

template<class T>
TimeValueAdaptor<T>::TimeValueAdaptor()
{
	DPRINTF("TimeValueAdaptor ctor\n");

}

template<class T>
TimeValueAdaptor<T>::~TimeValueAdaptor()
{
	DPRINTF("TimeValueAdaptor dtor\n");
}

template<typename T>
size_t TimeValueAdaptor<T>::ValToStr(char * str, size_t len, T val)
{
    int rlen;
    if(val >=0)
	{
	    time_t tv = time_value_integer + ValueAdaptor<T>::m_offset;
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
void TimeValueAdaptor<T>::InitState(T offset, T range, T wdth)
{
	ValueAdaptor<T>::m_offset = offset;
	ValueAdaptor<T>::m_range = range;

	m_timetick_granularity = TIMETICK_20YEARS;
	double r;
	r = wdth * ValueAdaptor<T>::m_range;
	//if (r < 0.1)
	//	m_timetick_granularity = TIMETICK_1S;
	//else
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

	ValueAdaptor<T>::m_step = GetStep(wdth);
	ValueAdaptor<T>::m_ticker = -fmod(ValueAdaptor<T>::m_offset, ValueAdaptor<T>::m_step);//(int)(m_offset / m_step) * m_step - m_offset;
	time_value_integer = ValueAdaptor<T>::m_ticker;
	time_value_fraction = fmod(ValueAdaptor<T>::m_ticker, 1);


	if (ValueAdaptor<T>::m_offset < 0)
		time_value_integer -= ValueAdaptor<T>::m_step - 1;

}

template<typename T>
bool TimeValueAdaptor<T>::Step()
{
	if ((time_value_integer + time_value_fraction)> ValueAdaptor<T>::m_range)
		return false;

	time_value_integer += ValueAdaptor<T>::m_step;
	return true;
}

template<typename T>
double TimeValueAdaptor<T>::GetStep(double r)
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
T TimeValueAdaptor<T>::GetTicker()
{
	return time_value_integer + time_value_fraction;
}


template<typename T>
SecsValueAdaptor<T>::SecsValueAdaptor()
{
	DPRINTF("SecsValueAdaptor ctor\n");
}

template<typename T>
SecsValueAdaptor<T>::~SecsValueAdaptor()
{
	DPRINTF("SecsValueAdaptor dtor\n");
}


template<typename T>
size_t SecsValueAdaptor<T>::ValToStr(char * str, size_t len, T val)
{
	if (val >= 0)
		sprintf(str, "%.0f", val);
	else
		str[0] = '\0'; //strcpy(str, "NEG");
	return 0;
}

template<typename T>
double SecsValueAdaptor<T>::GetStep(double r)
{
	return 1.0;
}
