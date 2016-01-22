#pragma once
#include <wx/popupwin.h>
#include <wx/minifram.h>
#include <wx/event.h>
#include "plot_defs.h"
#include "toolbarmenu.h"
#include "Series.h"
class DLLIMPEXP_PLOTLIB wxPopupToolBar : public wxPopupTransientWindow
{
public:
	wxPopupToolBar(wxWindow *parent, plot::Series *series);
	virtual ~wxPopupToolBar();

protected:
private:
	ToolBarMenu *m_toolbar;
	plot::Series *m_series;
	void OnTool_ToolClick(wxCommandEvent &event);
	void OnMouseRightDown(wxMouseEvent& event);
	virtual void OnDismiss() override;
	wxDECLARE_EVENT_TABLE();
};