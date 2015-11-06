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
	    time_t tv = val;
        struct tm tmstruct;
        memset(&tmstruct, 0, sizeof(struct tm));
        memcpy(&tmstruct, gmtime(&tv), sizeof(struct tm));
        rlen = strftime(str, len, "%H:%M:%S", &tmstruct);
	}else
	{
        str[0] = '\0';
        rlen = 0;
	}
        return rlen;
}

template<typename T>
double TimeValueAdaptor<T>::GetStep(double r)
{
	r *= 10.;
	printf("r=%f\n", r);
	if(r > 60)
		return 60 * 10.;
	if (r > 30)
		return 60.;
	if (r > 10)
		return 30.;
	if (r > 1)
		return 10.;

	if (r > 0.1)
		return 1.;

	return 0.1;
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
