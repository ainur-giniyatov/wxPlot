#pragma once
#include <wx/event.h>
#include <wx/window.h>
#include <wx/panel.h>

#include <wx/graphics.h>
#include <wx/menu.h>

#include <wx/bitmap.h>

#include "../Plot.h"
#include "ScaleWindow.h"
#include "../../other/PopupSeriesTool.h"
#include "wxBox.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxPlotWindow;
	class DLLIMPEXP_PLOTLIB wxBox;

	class  PlotClickEvent : public wxCommandEvent
	{
	public:
		PlotClickEvent(wxEventType eventType, int winind, wxPlotWindow *plot, Series *series = nullptr, wxBox *box = nullptr) : wxCommandEvent(eventType, winind), m_series_selection(nullptr)
		{ 
			m_plotwindow = nullptr;
			m_box = nullptr;
			m_plotwindow = plot;
			m_box = box;
			m_series_selection = series;
		}
		virtual ~PlotClickEvent() {};

		void SetBox(wxBox *box) { m_box = box; }
		void SetSeriesSelection(const SeriesSelection &ser_selection) { m_series_selection = ser_selection; }
		wxPlotWindow *GetPlot() { return m_plotwindow; }
		wxBox *GetBox() { return m_box; }
		SeriesSelection *GetSeriesSelection() { return &m_series_selection; };

		virtual wxEvent *Clone() const { return new PlotClickEvent(*this); }

	protected:
	private:
		SeriesSelection m_series_selection;
		wxPlotWindow *m_plotwindow;
		wxBox *m_box;
	};

};
	wxDECLARE_EXPORTED_EVENT(DLLIMPEXP_PLOTLIB, PLOTCLICKED, plot::PlotClickEvent);
//extern const DLLIMPEXP_PLOTLIB wxEventTypeTag< plot::PlotClickEvent > PLOTCLICKED;
	
	#define PlotClickedEventHandler(func) (&func)
	#define EVT_PLOT_CLICKED(id, func) wx__DECLARE_EVT1(PLOTCLICKED, id, PlotClickedEventHandler(func))

	wxDECLARE_EXPORTED_EVENT(DLLIMPEXP_PLOTLIB, PLOTVIEWCHANGED, wxCommandEvent);

namespace plot
{
		class DLLIMPEXP_PLOTLIB wxPlotWindow :
		public wxWindow, public Plot
	{
	public:
		wxPlotWindow(wxWindow *parent);
		virtual ~wxPlotWindow();

		wxMenu &GetMenu() { return m_context_menu; }
		virtual void RedrawPlot();

		//internal use
		void _popup_seriesmenu(Series *series);
		
	private:
		void OnPaint(wxPaintEvent &event);
		void OnEraseBackground(wxEraseEvent &event);
		void OnResize(wxSizeEvent &event);
		void OnLeftDown(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
		void OnRightDown(wxMouseEvent &event);
		void OnRightUp(wxMouseEvent &event);
		void OnMouseMove(wxMouseEvent &event);
		void OnMouseWheel(wxMouseEvent &event);
		void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);


		void Render(wxGraphicsContext *gc);
		virtual void DrawZoomSelection() override;
		virtual void GetSize(int *width, int *height);

		wxSizer *m_sizer;
		std::vector<ScaleWindow *> m_scalewindows;

		wxMenu m_context_menu;

		wxMenu m_series_menu;
		Series *m_the_series;//the series which has been right-clicked

		//virtual void _spotseries(SeriesSelection &seriesselection) override;
		
		/*iterate serie and find if mouse_coords points on any serie mark or line and fills seriesselection object*/
		void _getspottedseries(Point<int>&mouse_coords, SeriesSelection &seriesselection);

		static const int IDMENUITEM_REMOVESERIES;
		void OnMenuItem_RemoveSeries(wxCommandEvent &event);
		
		static const int IDMENUITEM_SERIESFITHOR;
		void OnMenuItem_SeriesFitHor(wxCommandEvent &event);

		static const int IDMENUITEM_SERIESFITVERT;
		void OnMenuItem_SeriesFitVert(wxCommandEvent &event);
		
		static const int IDMENUITEM_SERIESFITALLDIMS;
		void OnMenuItem_SeriesFitAllDims(wxCommandEvent &event);



		wxBitmap *m_bitmap_buffer;


		virtual void emit_viewchanged() override;
		int m_diag_texts_pos_y;
		DECLARE_EVENT_TABLE()
	};

}