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

class WXDLLIMPEXP_PLOTLIB AxisAdaptor
{
public:
	AxisAdaptor() { DPRINTF("AxisAdaptor ctor\n"); };
	virtual ~AxisAdaptor() { DPRINTF("AxisAdaptor dtor\n"); };

	virtual void InitState(double offset, double range, double wdth);
	virtual bool Step();
	virtual double GetTicker() = 0;
	virtual double GetStep(double r) = 0;
	//virtual int GetTickLenght() = 0;
	//virtual int GetTickWeight() = 0;

protected:
	double m_offset;
	double m_range;
	double m_ticker;
	double m_step;

private:

};

template<typename T> class WXDLLIMPEXP_PLOTLIB AxisValueAdaptor: public AxisAdaptor
{
public:
	AxisValueAdaptor();
	void SetData(DataTyped<T> * data);
	virtual ~AxisValueAdaptor();
	size_t ConvertToStr(char *str, size_t len, size_t indx);
	virtual size_t ValToStr(char *str, size_t len, T val) = 0;
	virtual size_t ValToStr(char *str, size_t len) = 0;
	
	
protected:
	DataTyped<T> *m_data;

};


template<typename T> class WXDLLIMPEXP_PLOTLIB TimeAxisValueAdaptor:public AxisValueAdaptor<T>
{
public:
	TimeAxisValueAdaptor();
	virtual ~TimeAxisValueAdaptor();
	virtual size_t ValToStr(char *str, size_t len);
	virtual size_t ValToStr(char *str, size_t len, T val);

	virtual void InitState(double offset, double range, double wdth) override;
	virtual bool Step() override;
	virtual double GetStep(double r) override;
	virtual double GetTicker() override;
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
//
//template<typename T> class WXDLLIMPEXP_PLOTLIB SecsAxisValueAdaptor :public AxisValueAdaptor<T>
//{
//public:
//	SecsAxisValueAdaptor();
//	virtual ~SecsAxisValueAdaptor();
//
//	virtual size_t ValToStr(char *str, size_t len) override;
//	virtual size_t ValToStr(char *str, size_t len, T val) override;
//	virtual double GetStep(double r) override;
//protected:
//
//};


template class WXDLLIMPEXP_PLOTLIB AxisValueAdaptor<int>;
template class WXDLLIMPEXP_PLOTLIB AxisValueAdaptor<time_t>;
template class WXDLLIMPEXP_PLOTLIB AxisValueAdaptor<float>;
template class WXDLLIMPEXP_PLOTLIB AxisValueAdaptor<short>;
template class WXDLLIMPEXP_PLOTLIB AxisValueAdaptor<double>;


template class WXDLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<int>;
template class WXDLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<time_t>;
template class WXDLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<float>;
template class WXDLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<short>;
template class WXDLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<double>;

//template class WXDLLIMPEXP_PLOTLIB SecsAxisValueAdaptor<short>;
//template class WXDLLIMPEXP_PLOTLIB SecsAxisValueAdaptor<time_t>;
//template class WXDLLIMPEXP_PLOTLIB SecsAxisValueAdaptor<float>;
//template class WXDLLIMPEXP_PLOTLIB SecsAxisValueAdaptor<int>;
//template class WXDLLIMPEXP_PLOTLIB SecsAxisValueAdaptor<double>;
//
