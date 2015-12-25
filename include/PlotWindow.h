#pragma once
#include <wx/window.h>
#include <wx/panel.h>

#include <wx/graphics.h>
#include <wx/menu.h>

#include <wx/bitmap.h>

#include "Plot.h"
#include "ScaleWindow.h"

class WXDLLIMPEXP_PLOTLIB PlotWindow :
	  public wxWindow, public Plot //let wxPanel come first!!
{
public:
	PlotWindow(wxWindow *parent);
	virtual ~PlotWindow();

	wxMenu &GetMenu() { return m_menu; }
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
	virtual void RedrawPlot();
	virtual void DrawZoomSelection(double rx, double ry) override;
	virtual void GetSize(int *width, int *height);
	
	wxSizer *m_sizer;
	std::vector<ScaleWindow *> m_scalewindows;

	wxMenu m_menu;
	//wxMenu *m_menu_addwidget;
	
	//static const int ID_MENUITEM_ADDLEGENDS;
	//void OnMenuItem_AddLegends(wxCommandEvent &event);

	wxBitmap *m_bitmap_buffer;
	bool m_refresh_bitmap;
	DECLARE_EVENT_TABLE()
};

