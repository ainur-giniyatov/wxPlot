#pragma once

#include <vector>
#include <map>

#include "plot_defs.h"

#include "Series.h"
#include "SubPlot.h"
#include "ValueAdaptor.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Subplot;
	class DLLIMPEXP_PLOTLIB AxisValueAdaptor;

	class DLLIMPEXP_PLOTLIB Scale
	{
	public:
		Scale(AXIS_DIR axis_dir);
		virtual ~Scale();

		void ChangeViewDepth(int vcd, bool swtch);

		void SetOffset(double offset);
		void SetRange(double range);

		double GetOffset() { return m_offset; }
		double GetRange() { return m_range; }

		void ZoomAt(double rv, double factor);
		void StartPanAt(double rv);
		void ProceedPanAt(double rv);
		void EndPanAt();

		void SetValueAdaptor(AxisValueAdaptor *valueadaptor);
		AxisValueAdaptor *GetValueAdaptor() { return m_valueadaptor; }

		void SetLimits(double max, double min, bool update = true);
		bool IsInRange(double new_range);

		double inline GetRangeMax() { return m_range_max; };
		double inline GetRangeMin() { return m_range_min; };

		virtual void Validate() {};

		AXIS_DIR _get_axis_dir() { return m_axis_dir; }
		const auto &_get_plots() { return m_subplots; }
		void _addseries(Series *series);
		void _removeseries(Series *series);
		void _refresh_plot_list();
	protected:
		std::vector<Series *> m_serie;
		std::vector<Subplot *> m_subplots;//for keeping track of plots that are affected
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

		AxisValueAdaptor *m_valueadaptor;
	};

}