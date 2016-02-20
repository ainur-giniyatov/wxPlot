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
		public wxPanel
	{
	public:
		ScaleWindow(wxWindow *parent, AXIS_DIR axis_dir, wxOrientation orient = wxVERTICAL, double offset = 0, double range = 1000);
		virtual ~ScaleWindow();

		Scale *GetScale() { return m_scale; }


	private:
		class MyScale : public Scale
		{
		public:
			MyScale(ScaleWindow *me, AXIS_DIR axis_dir):Scale(axis_dir) { m_me = me; }
			virtual ~MyScale() {};
			virtual void Validate() override;
		private:
			ScaleWindow *m_me;
		};
		void OnPaint(wxPaintEvent &event);
		void OnEraseBackground(wxEraseEvent &event);
		void OnResize(wxSizeEvent &event);
		void OnMouseWheel(wxMouseEvent &event);
		void OnLeftDown(wxMouseEvent &event);
		void OnLeftUp(wxMouseEvent &event);
		void OnMouseMove(wxMouseEvent &event);
		void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);
		void validate();
		bool m_ispanning;
		wxOrientation m_orient;
		wxFont m_font;
		Scale *m_scale;
		DECLARE_EVENT_TABLE()
	};

}