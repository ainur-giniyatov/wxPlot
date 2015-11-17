#pragma once
#include <wx/panel.h>

#include "plot_defs.h"

#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Axis.h"
#include "Renderer.h"
#include "Scale.h"

#include <vector>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Scale;

class ScaleWindow :
	public Scale, public wxPanel
{
public:
	ScaleWindow(wxWindow *parent, wxOrientation orient = wxVERTICAL, double offset = 0, double range = 1000);
	virtual ~ScaleWindow();
	
	virtual void ScaleRedraw() override;

private:
	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnResize(wxSizeEvent &event);
	void OnMouseWheel(wxMouseEvent &event);
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);

	bool m_ispanning;
	wxOrientation m_orient;
	DECLARE_EVENT_TABLE()
};

