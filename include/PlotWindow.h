#pragma once
#include <wx/window.h>
#include <wx/panel.h>

#include <wx/graphics.h>
#include "Plot.h"
#include "ScaleWindow.h"

class WXDLLIMPEXP_PLOTLIB PlotWindow :
	  public wxWindow, public Plot //let wxPanel come first!!
{
public:
	PlotWindow(wxWindow *parent);
	virtual ~PlotWindow();

private:
	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnResize(wxSizeEvent &event);
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);
	void OnMouseWheel(wxMouseEvent &event);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);

	void Render(wxGraphicsContext *gc);
	virtual void RedrawPlot();

	virtual void GetSize(int *width, int *height);
	
	wxSizer *m_sizer;
	std::vector<ScaleWindow *> m_scalewindows;

	DECLARE_EVENT_TABLE()
};

