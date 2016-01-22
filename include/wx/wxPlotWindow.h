#pragma once
#include <wx/window.h>
#include <wx/panel.h>

#include <wx/graphics.h>
#include <wx/menu.h>

#include <wx/bitmap.h>

#include "../Plot.h"
#include "ScaleWindow.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxPlotWindow :
		public wxWindow, public Plot
	{
	public:
		wxPlotWindow(wxWindow *parent);
		virtual ~wxPlotWindow();

		wxMenu &GetMenu() { return m_menu; }
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

		wxMenu m_menu;

		wxMenu m_seriesmenu;
		Series *m_series_pointed;
		
		static const int IDMENUITEM_DELETESERIES;
		void OnMenuItem_DeleteSeries(wxCommandEvent &event);
		
		static const int IDMENUITEM_SERIESPROPERTIES;
		void OnMenuItem_SeriesProperties(wxCommandEvent &event);

		static const int IDMENUITEM_SERIESFITVERT;
		void OnMenuItem_SeriesFitVert(wxCommandEvent &event);
		
		static const int IDMENUITEM_SERIESFITHOR;
		void OnMenuItem_SeriesFitHor(wxCommandEvent &event);
		
		static const int IDMENUITEM_SERIESFITALL;
		void OnMenuItem_SeriesFitAll(wxCommandEvent &event);
		//wxMenu *m_menu_addwidget;

		//static const int ID_MENUITEM_ADDLEGENDS;
		//void OnMenuItem_AddLegends(wxCommandEvent &event);

		wxBitmap *m_bitmap_buffer;


		int m_diag_texts_pos_y;
		DECLARE_EVENT_TABLE()
	};

}