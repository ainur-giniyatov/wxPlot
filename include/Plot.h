#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "Scale.h"
#include "Area.h"
#include "Box.h"

#include <vector>

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Axis;
	class DLLIMPEXP_PLOTLIB Scale;
	class DLLIMPEXP_PLOTLIB Area;
	class SeriesSelection;


	class DLLIMPEXP_PLOTLIB Plot
	{
	public:
		enum ORIENTATION
		{
			ORIENTATION_NORMAL,
			ORIENTATION_ROTATED
		};

		Plot(const char *plotname = NULL);
		virtual ~Plot();

		void SetPlotName(const char *plotname = NULL);
		const char *GetPlotName() { return m_plot_name; }

		void AddArea(Area *area);
		void RemoveArea(Area *area);
		void DeleteArea(Area *area);

		Area *GetArea(size_t indx) { return indx < m_areas.size() ? m_areas[indx] : nullptr; }
		const std::vector<Area *> &GetAreas() { return m_areas; }
		void Clear(bool update = true);

		virtual void RedrawPlot() = 0;
		virtual void GetSize(int *width, int *height) = 0;

		void Validate(bool refresh_buffer = true);

		void SetCommonScale(Scale *scale);
//		Scale *GetCommonScale() { return m_commonscale; }

		//void RemoveBox(Box *box);
		//void DeleteBox(Box *box);
		void AddBox(Box *box);
		//void ArrangeBoxes();

		void SetLeftButtonAction(LEFTBUTTON_ACTION lba) { m_lbaction = lba; };

		void Fit(int axis_mask);

		//internal use methods start with _

		void _SetViewModifiedFlag();

		void _refresh_dependant_scales();
		ORIENTATION _get_orientation() { return m_orientation; }
	protected:
		virtual void emit_viewchanged() = 0;
//		PEventList *m_eventslist;

		void StartPan(const Point<double> &pan_start_rel_coord);
		void ProceedPan(const Point<double> &pan_proceed_rel_coord);
		void EndPan();

		void StartZoomSelect(const Point<double> &zoom_sel_start_rel_coord);
		void ProceedZoomSelect(const Point<double> &zoom_sel_proceed_rel_coord);
		void EndZoomSelect();
		virtual void DrawZoomSelection() = 0;

		void Zoom(const Point<double> &zoom_wheel_rel_coord, double xfactor, double yfactor);

		std::vector<Area *> m_areas;

		/*holds pointers to Scale objects that depend on the plot*/
		std::vector<Scale *> m_dependant_scales;
		//void update_dependant_scales();
		bool m_panning;

		bool m_zoomsel_switch;
		bool m_zoomselecting;
		Point<double> m_zoom_sel_start_rel_coord;
		Point<double> m_zoom_sel_end_rel_coord;
		char *m_plot_name;

		//Scale *m_commonscale;

		Box *m_selected_box;
		BOXSTATE m_selected_box_state;
		int m_selected_box_sides;
		Point<int> m_box_click_delta;//distance between top left and mouse
		Point<int> m_box_click_delta2;//distance between bottom right and mouse
		std::vector<Box *> m_boxes;
		void plot_resized();

		std::vector<Scale *> m_scales;

		LEFTBUTTON_ACTION m_lbaction;

		bool m_is_data_view_modified;
		ORIENTATION m_orientation;
		//helpers
		

	};

}