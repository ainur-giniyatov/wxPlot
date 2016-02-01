#pragma once
#include <wx/event.h>
#include "../Box.h"
#include "wxPlotWindow.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxPlotWindow;

	class DLLIMPEXP_PLOTLIB wxBox : public wxEvtHandler, public Box
	{
	public:
		wxBox(wxPlotWindow *plotwindow);
		virtual ~wxBox();

		virtual void Render(void *) override;

	protected:
		wxMenu m_menu;
	private:
		virtual void MouseRightUp(int mx, int my) override;
		
		static const int IDMENUITEM_CLOSE;
		void OnMenu_Close(wxCommandEvent& event);

		//helpers
		void deletebox();
	};

	class DLLIMPEXP_PLOTLIB wxTitleBox : public wxBox
	{
	public:
		wxTitleBox(wxPlotWindow *plotwindow);
		virtual ~wxTitleBox();

		virtual void Render(void *) override;

	protected:
	private:
		wxString m_title;

		virtual void Sizing() override;
	};

	class DLLIMPEXP_PLOTLIB wxLegendsBox : public LegendsBox
	{
	public:
		wxLegendsBox(wxPlotWindow *plotwindow);
		virtual ~wxLegendsBox();

		virtual void Render(void *) override;

	protected:
	private:
		void MouseRightUp(int mx, int my) override;
		virtual void MouseLeftDown(int mx, int my) override;
		virtual void Sizing() override;

		int margin;
	};
}