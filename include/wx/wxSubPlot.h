#pragma once
#include <wx/event.h>
#include <wx/window.h>
#include <wx/panel.h>

#include <wx/graphics.h>
#include <wx/menu.h>

#include <wx/bitmap.h>

#include "wxScaleWidget.h"
#include "SubPlot.h"

#include "../../other/PopupSeriesTool.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxSubplot;

	class  PlotClickEvent : public wxCommandEvent
	{
	public:
		PlotClickEvent(wxEventType eventType, int winind, wxSubplot *subplot, Series *series = nullptr) : wxCommandEvent(eventType, winind), m_series_selection(nullptr)
		{ 
			//m_box = nullptr;
			m_subplot = subplot;
			//m_box = box;
			m_series_selection = series;
		}
		virtual ~PlotClickEvent() {};

		//void SetBox(wxBox *box) { m_box = box; }
		void SetSeriesSelection(const SeriesSelection &ser_selection) { m_series_selection = ser_selection; }
		wxSubplot *GetSubplot() { return m_subplot; }
		//wxBox *GetBox() { return m_box; }
		SeriesSelection *GetSeriesSelection() { return &m_series_selection; };

		virtual wxEvent *Clone() const { return new PlotClickEvent(*this); }

	protected:
	private:
		SeriesSelection m_series_selection;
		wxSubplot *m_subplot;
		//wxBox *m_box;
	};

};
	wxDECLARE_EXPORTED_EVENT(DLLIMPEXP_PLOTLIB, PLOTCLICKED, plot::PlotClickEvent);
//extern const DLLIMPEXP_PLOTLIB wxEventTypeTag< plot::PlotClickEvent > PLOTCLICKED;
	
	#define PlotClickedEventHandler(func) (&func)
	#define EVT_PLOT_CLICKED(id, func) wx__DECLARE_EVT1(PLOTCLICKED, id, PlotClickedEventHandler(func))

	wxDECLARE_EXPORTED_EVENT(DLLIMPEXP_PLOTLIB, PLOTVIEWCHANGED, wxCommandEvent);

namespace plot
{
		class DLLIMPEXP_PLOTLIB wxSubplot :
		public wxPanel, public Subplot
	{
	public:
		wxSubplot(wxWindow *parent);
		virtual ~wxSubplot();

		wxMenu &GetMenu() { return m_context_menu; }
		virtual void RedrawPlot();

		//void AddLeftScaleWidget(wxScaleWidget *scalewidget);
		//void AddRightScaleWidget(wxScaleWidget *scalewidget);
		//void AddTopScaleWidget(wxScaleWidget *scalewidget);
		//void AddBottomScaleWidget(wxScaleWidget *scalewidget);

		//internal use
		void _popup_seriesmenu(Series *series);
		//void _setphysicaloffsets(int hphoff, int vphoff) { m_hphoff = hphoff; m_vphoff = vphoff; };
		//void _getphysicaloffsets(int *hphoff, int *vphoff) { *hphoff = m_hphoff; *vphoff = m_vphoff; };
		//void _setphysicalranges(int hphrange, int vphrange) { m_hphrange = hphrange; m_vphrange = vphrange; };
		//void _getphysicalranges(int *hphrange, int *vphrange) { *hphrange = m_hphrange; *vphrange = m_vphrange; };
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
//		virtual void DrawZoomSelection() override;
		virtual void GetSize(int *width, int *height);

		//wxSizer *m_sizer;
		std::vector<wxScaleWidget *> m_scalewidgets;

		wxMenu m_context_menu;

		wxMenu m_series_menu;
		Series *m_the_series;//the series which has been right-clicked

		//virtual void _spotseries(SeriesSelection &seriesselection) override;
		
		/*iterate serie and find if mouse_coords points on any serie mark or line and fills seriesselection object*/
		//void _getspottedseries(Point<int>&mouse_coords, SeriesSelection &seriesselection);

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
		virtual const Size<int> _get_backend_size() override;
		int m_diag_texts_pos_y;
		
		int m_hphoff;
		int m_vphoff;
		int m_hphrange;
		int m_vphrange;

		DECLARE_EVENT_TABLE()
	};

}