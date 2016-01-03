#pragma once
#include <time.h>
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Scale.h"
#include "Axis.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB Renderer2D;
	class DLLIMPEXP_PLOTLIB Scale;
	class DLLIMPEXP_PLOTLIB Axis;
	template <class T> class DLLIMPEXP_PLOTLIB DataTyped;

	class DLLIMPEXP_PLOTLIB AxisAdaptor
	{
	public:
		AxisAdaptor() { DPRINTF("AxisAdaptor ctor\n"); };
		virtual ~AxisAdaptor() { DPRINTF("AxisAdaptor dtor\n"); };

		virtual void InitState(double offset, double range, double wdth);
		virtual bool Step();
		virtual double GetTicker() { return m_ticker; };
		//virtual int GetTickLenght() = 0;
		//virtual int GetTickWeight() = 0;
		//void SetOffset(double offset);
		//void SetRange(double range);
	protected:
		double m_offset;
		double m_range;
		double m_ticker;
		double m_step;

		virtual double GetStep(double r);


	private:

	};

	template<typename T> class DLLIMPEXP_PLOTLIB AxisValueAdaptor : public AxisAdaptor
	{
	public:
		AxisValueAdaptor();
		void SetData(DataTyped<T> * data);
		virtual ~AxisValueAdaptor();
		size_t ConvertToStr(char *str, size_t len, size_t indx);
		virtual size_t ValToStr(char *str, size_t len, T val) = 0;
		virtual size_t ValToStr(char *str, size_t len) = 0;
		virtual bool ValBiggerPart(char *str, size_t len) = 0;
		bool IsBold() { return m_makebold; }

	protected:
		DataTyped<T> *m_data;
		bool m_makebold;
	};


	template<typename T> class DLLIMPEXP_PLOTLIB TimeAxisValueAdaptor :public AxisValueAdaptor<T>
	{
	public:
		TimeAxisValueAdaptor();
		virtual ~TimeAxisValueAdaptor();
		virtual size_t ValToStr(char *str, size_t len) override;
		virtual size_t ValToStr(char *str, size_t len, T val) override;
		virtual bool ValBiggerPart(char *str, size_t len) override;

		virtual void InitState(double offset, double range, double wdth) override;
		virtual bool Step() override;
		virtual double GetTicker() override;
	protected:

		virtual double GetStep(double r) override;

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

	template<typename T> class DLLIMPEXP_PLOTLIB SimpleAxisValueAdaptor :public AxisValueAdaptor<T>
	{
	public:
		SimpleAxisValueAdaptor();
		virtual ~SimpleAxisValueAdaptor();

		virtual size_t ValToStr(char *str, size_t len) override;
		virtual size_t ValToStr(char *str, size_t len, T val) override;
		virtual bool ValBiggerPart(char *str, size_t len) override;

		//virtual void InitState(double offset, double range, double wdth) override;
		//virtual bool Step() override;
		//virtual double GetTicker() override;
	protected:

		//virtual double GetStep(double r) override;
	private:
	};




	template class DLLIMPEXP_PLOTLIB AxisValueAdaptor<int>;
	template class DLLIMPEXP_PLOTLIB AxisValueAdaptor<time_t>;
	template class DLLIMPEXP_PLOTLIB AxisValueAdaptor<double>;


	template class DLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<int>;
	template class DLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<time_t>;
	template class DLLIMPEXP_PLOTLIB TimeAxisValueAdaptor<double>;

	template class DLLIMPEXP_PLOTLIB SimpleAxisValueAdaptor<double>;


}