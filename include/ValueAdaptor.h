#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Renderer.h"
#include "Scale.h"
#include "Axis.h"

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Renderer2D;
class WXDLLIMPEXP_PLOTLIB Scale;
class WXDLLIMPEXP_PLOTLIB Axis;
template <class T> class WXDLLIMPEXP_PLOTLIB DataTyped;


template<typename T> class WXDLLIMPEXP_PLOTLIB ValueAdaptor
{
public:
	ValueAdaptor();
	void SetData(DataTyped<T> * data);
	virtual ~ValueAdaptor();
	size_t ConvertToStr(char *str, size_t len, size_t indx);
	virtual size_t ValToStr(char *str, size_t len, T val) = 0;
	//DataTyped<T> *GetData(){return m_data;}

	virtual void InitState(T offset, T range, T wdth);
	virtual bool Step();
	virtual T GetTicker();
	virtual double GetStep(double r) = 0;
	//virtual int GetTickLenght() = 0;
	//virtual int GetTickWeight() = 0;

protected:
	DataTyped<T> *m_data;

	T m_offset;
	T m_range;
	T m_ticker;
	T m_step;
};


template<typename T> class WXDLLIMPEXP_PLOTLIB TimeValueAdaptor:public ValueAdaptor<T>
{
public:
	TimeValueAdaptor();
	virtual ~TimeValueAdaptor();
	virtual size_t ValToStr(char *str, size_t len, T val);

	virtual void InitState(T offset, T range, T wdth);
	virtual bool Step();
	virtual double GetStep(double r);
	virtual T GetTicker();
protected:

private:

	enum TIME_TICK_GRAN {
		TIMETICK_1S,
		TIMETICK_10S,
		TIMETICK_1MIN,
		TIMETICK_10MIN,
		TIMETICK_1H,
		TIMETICK_6H,
		TIMETICK_12H,
		TIMETICK_1DAY,
		TIMETICK_1WEEK,
		TIMETICK_1MONTH,
		TIMETICK_1YEAR,
		TIMETICK_10YEARS,
		TIMETICK_20YEARS
	};

	TIME_TICK_GRAN m_timetick_granularity;
	time_t time_value_integer;
	float time_value_fraction;
};

template<typename T> class WXDLLIMPEXP_PLOTLIB SecsValueAdaptor :public ValueAdaptor<T>
{
public:
	SecsValueAdaptor();
	virtual ~SecsValueAdaptor();
	virtual size_t ValToStr(char *str, size_t len, T val);
	virtual double GetStep(double r);
protected:

};


template class WXDLLIMPEXP_PLOTLIB ValueAdaptor<int>;
template class WXDLLIMPEXP_PLOTLIB ValueAdaptor<time_t>;
template class WXDLLIMPEXP_PLOTLIB ValueAdaptor<float>;
template class WXDLLIMPEXP_PLOTLIB ValueAdaptor<short>;
template class WXDLLIMPEXP_PLOTLIB ValueAdaptor<double>;


template class WXDLLIMPEXP_PLOTLIB TimeValueAdaptor<int>;
template class WXDLLIMPEXP_PLOTLIB TimeValueAdaptor<time_t>;
template class WXDLLIMPEXP_PLOTLIB TimeValueAdaptor<float>;
template class WXDLLIMPEXP_PLOTLIB TimeValueAdaptor<short>;
template class WXDLLIMPEXP_PLOTLIB TimeValueAdaptor<double>;

template class WXDLLIMPEXP_PLOTLIB SecsValueAdaptor<short>;
template class WXDLLIMPEXP_PLOTLIB SecsValueAdaptor<time_t>;
template class WXDLLIMPEXP_PLOTLIB SecsValueAdaptor<float>;
template class WXDLLIMPEXP_PLOTLIB SecsValueAdaptor<int>;
template class WXDLLIMPEXP_PLOTLIB SecsValueAdaptor<double>;

