#pragma once
#include <wx/panel.h>
#include <vector>

#include "plot_defs.h"

#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Axis.h"
#include "Scale.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB Axis;
	class DLLIMPEXP_PLOTLIB Scale;

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
		wxFont m_font;
		DECLARE_EVENT_TABLE()
	};

}