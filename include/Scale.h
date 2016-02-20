#pragma once

#include <vector>
#include <map>

#include "plot_defs.h"

#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Axis.h"
#include "ValueAdaptor.h"

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
		Scale(AXIS_DIR axis_dir);
		virtual ~Scale();

		void AddAxis(Axis *axis);
		void RemoveAxis(Axis *axis);


		void ChangeViewDepth(int vcd, bool swtch);

		/*sets offset for the scale and propagates to bound axes*/
		void SetOffset(double offset);

		/*sets range for the scale and propagates to bound axes*/
		void SetRange(double range);

		double GetOffset() { return m_offset; }
		double GetRange() { return m_range; }
		/*iterate plots and redraw them uniqly*/
		//void RedrawDependantPlots(bool redraw_immdiately = true);


		/*redraw scale gui component*/
		//virtual void ScaleRedraw() = 0;

		void ZoomAt(double rv, double factor);
		void StartPanAt(double rv);
		void ProceedPanAt(double rv);
		void EndPanAt();

		void SetValueAdaptor(AxisValueAdaptor<double > *valueadaptor);
		AxisValueAdaptor<double> *GetValueAdaptor() { return m_valueadaptor; }
		void SetLimits(double max, double min, bool update = true);
		bool IsInRange(double new_range);
		double inline GetRangeMax() { return m_range_max; };
		double inline GetRangeMin() { return m_range_min; };

		virtual void Validate() {};
		AXIS_DIR _get_axis_dir() { return m_axis_dir; }
		const auto &_get_axes() { return m_axes; };
		const auto &_get_plots() { return m_plots; }
	protected:
		std::vector<Axis *> m_axes;
		std::vector<Plot *> m_plots;//for keeping track of plots that are affected
		AXIS_DIR m_axis_dir;
		
		double m_offset;
		double m_range;
		struct VIEWSTEP
		{
			VIEWSTEP() = default;
			double offset;
			double range;
		};
		VIEWSTEP m_previous_view;
		void store_prev_view() { m_previous_view.offset = m_offset; m_previous_view.range = m_range; };
		std::map<int, VIEWSTEP> m_view_change_steps;

		double m_range_max;
		double m_range_min;

		double m_pan_start_at_rv;
		double m_pan_start_at_vv;

		AxisValueAdaptor<double> *m_valueadaptor;
	};

}