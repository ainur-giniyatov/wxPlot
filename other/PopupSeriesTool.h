#pragma once
#include <wx/popupwin.h>
#include <wx/minifram.h>
#include <wx/event.h>
#include "plot_defs.h"
#include "SeriesTool.h"
#include "Series.h"

class DLLIMPEXP_PLOTLIB wxPopupSeriesTool : public wxPopupWindow //wxPopupTransientWindow
{
public:
	wxPopupSeriesTool(wxWindow *parent);
	virtual ~wxPopupSeriesTool();

	void SetSelectedSeries(plot::Series *series);
protected:
private:
	SeriesTool *m_seriestool;

	//virtual void OnDismiss() override;
	//virtual bool ProcessLeftDown(wxMouseEvent &event) override;
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent &event);
	void OnCloseButton(wxCommandEvent &event);

	bool m_moving;
	wxPoint m_start_moving_pos_mouse;
	wxPoint m_start_moving_pos;

	wxDECLARE_EVENT_TABLE();
};