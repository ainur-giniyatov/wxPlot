#pragma once
#include <time.h>
#include "plot_defs.h"
#include "Series.h"
#include "SubPlot.h"
#include "Scale.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Subplot;
	class DLLIMPEXP_PLOTLIB Renderer2D;
	class DLLIMPEXP_PLOTLIB Scale;

	class DLLIMPEXP_PLOTLIB AxisAdaptor
	{
	public:
		AxisAdaptor();
		virtual ~AxisAdaptor() { DPRINTF("AxisAdaptor dtor\n"); };

		virtual void InitState(double offset, double range, double rwidth);
		virtual bool MajorStep();
		virtual bool MinorStep();
		double GetMajorTick() { return m_major_stepper; };
		double GetMinorTick() { return m_minor_stepper + m_major_stepper; };
		virtual bool IsMiddleMinor();
		virtual void SetLimitsForScale(Scale *scale);
	protected:
		double m_offset;
		double m_range;
		double m_major_tick_step;
		double m_minor_tick_step;
		double m_major_stepper;
		double m_minor_stepper;

		const char *m_format_str;
	private:
	};

	class DLLIMPEXP_PLOTLIB AxisValueAdaptor : public AxisAdaptor
	{
	public:
		AxisValueAdaptor();
		virtual ~AxisValueAdaptor();

		virtual size_t ValToStr(char *str, size_t len, double val) = 0;
		virtual size_t ValToStr(char *str, size_t len) = 0;
		virtual bool ValBiggerPart(char *str, size_t len) = 0;
		bool IsBold() { return m_makebold; }

	protected:
		bool m_makebold;
	};


	class DLLIMPEXP_PLOTLIB TimeAxisValueAdaptor :public AxisValueAdaptor
	{
	public:
		TimeAxisValueAdaptor();
		virtual ~TimeAxisValueAdaptor();
		virtual size_t ValToStr(char *str, size_t len) override;
		virtual size_t ValToStr(char *str, size_t len, double val) override;
		virtual bool ValBiggerPart(char *str, size_t len) override;

		virtual void InitState(double offset, double range, double rwidth) override;
		virtual bool MajorStep() override;
		virtual bool MinorStep() override;
		virtual bool IsMiddleMinor() override;
		virtual void SetLimitsForScale(Scale *scale) override;
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

		double _getstep(double r);
	};

	class DLLIMPEXP_PLOTLIB SimpleAxisValueAdaptor :public AxisValueAdaptor
	{
	public:
		SimpleAxisValueAdaptor();
		virtual ~SimpleAxisValueAdaptor();

		virtual size_t ValToStr(char *str, size_t len) override;
		virtual size_t ValToStr(char *str, size_t len, double val) override;
		virtual bool ValBiggerPart(char *str, size_t len) override;

	protected:

	private:
};

}