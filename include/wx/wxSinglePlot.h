#pragma once
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/aui/aui.h>

#include "plot_defs.h"
#include "Series.h"
#include "wxScaleWidget.h"

#include "../other/Pane_fb.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;

	class DLLIMPEXP_PLOTLIB wxSinglePlot :
		public wxSinglePlot_fb
	{
	public:
		wxSinglePlot(wxWindow *parent, int orientation = wxVERTICAL);
		virtual ~wxSinglePlot();
		
		void SetLeftButtonAction(LEFTBUTTON_ACTION lba) { m_lbaction = lba; };
		LEFTBUTTON_ACTION GetLeftButtonAction() { return m_lbaction; }

		void AddLeftScaleWidget(wxScaleWidget *scalewidget);
		//void AddRightScaleWidget(wxScaleWidget *scalewidget);
		//void AddTopScaleWidget(wxScaleWidget *scalewidget);
		void AddBottomScaleWidget(wxScaleWidget *scalewidget);

		wxSubplot *GetSubplot() { return m_subplot; }
		//void UndoView();
		//void RedoView();

		//void Fit(int axis_mask);
	private:

		//void on_plot_view_changed(wxCommandEvent &event);
		//void plotviewchanged(int vcd, bool swtc);
		//int m_view_change_index;
		int m_orientation;


		LEFTBUTTON_ACTION m_lbaction;


		//DECLARE_EVENT_TABLE()

		//some helpers

	};

}