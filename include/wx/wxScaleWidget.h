#pragma once
#include <wx/panel.h>
#include <wx/layout.h>
#include <vector>

#include "plot_defs.h"

#include "Series.h"
#include "SubPlot.h"
#include "Scale.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Subplot;
	class DLLIMPEXP_PLOTLIB Scale;

	class DLLIMPEXP_PLOTLIB wxScaleWidget:
		public wxPanel
	{
	public:
		wxScaleWidget(wxWindow *parent, AXIS_DIR axis_dir, wxOrientation orient = wxVERTICAL, wxEdge scale_pos = wxBottom, double offset = 0, double range = 1000);
		virtual ~wxScaleWidget();

		Scale *GetScale() { return m_scale; }

		int _getscalephysicalrange();
	private:
		class MyScale : public Scale
		{
		public:
			MyScale(wxScaleWidget *me, AXIS_DIR axis_dir):Scale(axis_dir) { m_me = me; }
			virtual ~MyScale() {};
			virtual void Validate() override;
		private:
			wxScaleWidget *m_me;
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
		int m_size_recalculated;
		wxEdge m_scale_position;
		DECLARE_EVENT_TABLE()
	};

}