#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Axis.h"
#include "Scale.h"
#include "Box.h"
#include "Area.h"
#include "pevent.h"


#include <vector>

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class SeriesSelection;
	class DLLIMPEXP_PLOTLIB Axis;
	class DLLIMPEXP_PLOTLIB Scale;
	class DLLIMPEXP_PLOTLIB Box;
	class DLLIMPEXP_PLOTLIB ScaleBox;
	class DLLIMPEXP_PLOTLIB Area;
	class DLLIMPEXP_PLOTLIB PEvent;
	class DLLIMPEXP_PLOTLIB PEventList;
	class DLLIMPEXP_PLOTLIB PEventHandler;

	class DLLIMPEXP_PLOTLIB PEventAreaAdded;
	class DLLIMPEXP_PLOTLIB PEventSeriesAdded;

	class DLLIMPEXP_PLOTLIB Plot: public PEventHandler
	{
	public:
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

		void SetCommonScale(Scale *scale);
		Scale *GetCommonScale() { return m_commonscale; }

		void RemoveBox(Box *box);
		void DeleteBox(Box *box);
		void AddBox(Box *box);

		void SetLeftButtonAction(LEFTBUTTON_ACTION lba) { m_lbaction = lba; };

		void Fit(int axis_mask);

		//internal use methods start with _
		//virtual void _spotseries(SeriesSelection &seriesselection) = 0;
		void _SetViewModifiedFlag();
		PEventList *_GetEventsList() { return m_eventslist; }
		//std::vector<Scale *> _get_scales();
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
		void update_dependant_scales();
		bool m_panning;

		bool m_zoomsel_switch;
		bool m_zoomselecting;
		Point<double> m_zoom_sel_start_rel_coord;
		Point<double> m_zoom_sel_end_rel_coord;
		char *m_plot_name;

		Scale *m_commonscale;

		std::vector<Box *> m_boxes;

		LEFTBUTTON_ACTION m_lbaction;

		bool m_is_data_view_modified;

		//helpers
		
		friend class Box;
		//friend class ScaleBox;


		//handlers
		void handler_area_added(PEvent &event);
		void handler_series_added(PEvent &event);
		void handler_scale_set(PEvent &event);
	};


	//event types
	class DLLIMPEXP_PLOTLIB PEventSeriesAdded : public PEvent
	{
	public:
		PEventSeriesAdded(Series * series, bool f);//true if added, false if removed
		virtual ~PEventSeriesAdded();
		Series *GetSeries() { return (Series *)m_event_data; };
		static int GetEventId() { return s_event_id; }
		bool GetFlag() { return m_addedoremoved; }
	protected:
	private:
		static const int s_event_id;
		bool m_addedoremoved;
	};

	class DLLIMPEXP_PLOTLIB PEventAreaAdded : public PEvent
	{
	public:
		PEventAreaAdded(bool f);//true if added, false if removed
		virtual ~PEventAreaAdded();
		void SetArea(Area *area) { m_event_data = area; };
		Area *GetArea() { return (Area *)m_event_data; };
		static int GetEventId() { return s_event_id; }
		bool GetFlag() { return m_addedoremoved; }
	protected:
	private:
		static const int s_event_id;
		bool m_addedoremoved;
	};


	class DLLIMPEXP_PLOTLIB PEventScaleSet : public PEvent
	{
	public:
		PEventScaleSet();//true if added, false if removed
		virtual ~PEventScaleSet();
		static int GetEventId() { return s_event_id; }
		bool GetFlag() { return m_addedoremoved; }
	protected:
	private:
		static const int s_event_id;
		bool m_addedoremoved;
	};

}