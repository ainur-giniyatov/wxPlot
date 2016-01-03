#pragma once

#include "plot_defs.h"

#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Axis.h"
#include "ValueAdaptor.h"

#include <vector>

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB Axis;

	template<typename T> class DLLIMPEXP_PLOTLIB AxisValueAdaptor;

	class DLLIMPEXP_PLOTLIB Scale
	{
	public:
		Scale();
		virtual ~Scale();

		void AddAxis(Axis *axis);

		void RemoveAxis(Axis *axis);

		std::vector<Axis *> &GetAxes() { return m_axes; };

		/*sets offset for the scale and propagates to bound axes*/
		void SetOffset(double offset);

		/*sets range for the scale and propagates to bound axes*/
		void SetRange(double range);

		/*iterate plots and redraw them uniqly*/
		void RedrawDependantPlots();


		/*redraw scale gui component*/
		virtual void ScaleRedraw() = 0;

		void ZoomAt(double rv, double factor);
		void StartPanAt(double rv);
		void ProceedPanAt(double rv);
		void EndPanAt();

		void SetValueAdaptor(AxisValueAdaptor<double > *valueadaptor);
		AxisValueAdaptor<double> *GetValueAdaptor() { return m_valueadaptor; }
		void SetRangeLimits(double max, double min, bool update = true);
		bool IsInRange(double new_range);
		double inline GetRangeMax() { return m_range_max; };
		double inline GetRangeMin() { return m_range_min; };
	protected:
		std::vector<Axis *> m_axes;


		double m_offset;
		double m_range;

		double m_range_max;
		double m_range_min;

		double m_pan_start_at_rv;
		double m_pan_start_at_vv;

		AxisValueAdaptor<double> *m_valueadaptor;
	};

}