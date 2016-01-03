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
	class DLLIMPEXP_PLOTLIB Axis;
	class DLLIMPEXP_PLOTLIB Scale;
	class DLLIMPEXP_PLOTLIB Box;
	class DLLIMPEXP_PLOTLIB ScaleBox;
	class DLLIMPEXP_PLOTLIB Area;
	class DLLIMPEXP_PLOTLIB PEvent;
	class DLLIMPEXP_PLOTLIB PEventList;
	class DLLIMPEXP_PLOTLIB PEventHandler;

	class DLLIMPEXP_PLOTLIB Plot
	{
	public:
		Plot(const char *plotname = NULL);
		virtual ~Plot();

		void SetPlotName(const char *plotname = NULL);
		const char *GetPlotName() { return m_plot_name; }

		void AddArea(Area *area);
		void RemoveArea(Area *area);
		void DeleteArea(Area *area);

		Area *GetArea(size_t indx) { return m_areas[indx]; }
		void Clear(bool update = true);

		virtual void RedrawPlot() {};
		virtual void GetSize(int *width, int *height) {};

		void FitPlot(bool update = true);

		void SetCommonScale(Scale *scale);
		Scale *GetCommonScale() { return m_commonscale; }

		void RemoveBox(Box *box);
		void DeleteBox(Box *box);
		void AddBox(Box *box);

		void SetLeftButtonAction(LEFTBUTTON_ACTION lba) { m_lbaction = lba; };

		//internal use methods start with _
		void _SetViewModifiedFlag();
		PEventList *_GetEventsList() { return m_eventslist; }

	protected:

		PEventList *m_eventslist;

		void StartPan(const Point<double> &pan_start_rel_coord);
		void ProceedPan(const Point<double> &pan_proceed_rel_coord);
		void EndPan();

		void StartZoomSelect(const Point<double> &zoom_sel_start_rel_coord);
		void ProceedZoomSelect(const Point<double> &zoom_sel_proceed_rel_coord);
		void EndZoomSelect();
		virtual void DrawZoomSelection() {};

		void Zoom(const Point<double> &zoom_wheel_rel_coord, double xfactor, double yfactor);

		//std::vector<SpaceND *> m_spaces;
		std::vector<Area *> m_areas;

		bool m_panning;

		bool m_zoomsel_switch;
		bool m_zoomselecting;

		char *m_plot_name;

		Scale *m_commonscale;

		std::vector<Box *> m_boxes;

		LEFTBUTTON_ACTION m_lbaction;

		bool m_is_data_view_modified;
		//helpers
		void iterate_axes_redraw_uniq_commonscales_uniq_plots();

		friend class Box;
		//friend class ScaleBox;

	};


	//event types
	class DLLIMPEXP_PLOTLIB PEventSeriesAdded : public PEvent
	{
	public:
		PEventSeriesAdded();
		virtual ~PEventSeriesAdded();
		void SetSeries(Series *series) { m_event_data = series; };
		Series *GetSeries() { return (Series *)m_event_data; };
		static int GetEventId() { return s_event_id; }
		void SetFlag(bool f) { m_addedoremoved = f; }//true if added, false is removed
		bool GetFlag() { return m_addedoremoved; }
	protected:
	private:
		static const int s_event_id;
		bool m_addedoremoved;
	};

	class DLLIMPEXP_PLOTLIB PEventAreaAdded : public PEvent
	{
	public:
		PEventAreaAdded();
		virtual ~PEventAreaAdded();
		void SetArea(Area *area) { m_event_data = area; };
		Area *GetArea() { return (Area *)m_event_data; };
		static int GetEventId() { return s_event_id; }
	protected:
	private:
		static const int s_event_id;
	};

}