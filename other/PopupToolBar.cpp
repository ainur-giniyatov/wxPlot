#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/tooltip.h>
#include "PopupToolBar.h"


BEGIN_EVENT_TABLE(wxPopupToolBar, wxPopupTransientWindow)
EVT_RIGHT_DOWN(wxPopupToolBar::OnMouseRightDown)
END_EVENT_TABLE();

wxPopupToolBar::wxPopupToolBar(wxWindow * parent, plot::Series *series) :wxPopupTransientWindow(parent, wxBORDER_STATIC)
{
	
	m_series = series;
	m_toolbar = new ToolBarMenu(this, -1, wxDefaultPosition, wxDefaultSize, 0);

	wxSizer *bSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText *stext;
	stext = new wxStaticText(this, wxID_ANY, wxString(series->GetSeriesName()));
	bSizer->Add(stext, 0, wxEXPAND | wxALL & ~wxBOTTOM, 3);
	bSizer->Add(m_toolbar, 1, wxEXPAND | wxALL, 3);
	SetSizer(bSizer);
	Fit();

	Connect(wxEVT_TOOL, (wxObjectEventFunction)&wxPopupToolBar::OnTool_ToolClick);

	SetFocus();
	Position(wxGetMousePosition(), wxSize(0, 0));
}

wxPopupToolBar::~wxPopupToolBar()
{
}

void wxPopupToolBar::OnTool_ToolClick(wxCommandEvent & event)
{
	DPRINTF("wxPopupToolBar::OnTool_ToolClick\n");
	if (event.GetId() == m_toolbar->m_tool_fithor->GetId())
	{
		m_series->GetData(AXIS_X)->Fit();
	}

	if (event.GetId() == m_toolbar->m_tool_fitvert->GetId())
	{
		m_series->GetData(AXIS_Y)->Fit();
	}

	if (event.GetId() == m_toolbar->m_tool_fitall->GetId())
	{
		m_series->Fit();
	}

	if (event.GetId() == m_toolbar->m_tool_delete->GetId())
	{
		m_series->GetOwner()->DeleteSeries(m_series);
	}

	Destroy();
}

void wxPopupToolBar::OnMouseRightDown(wxMouseEvent & event)
{
	Destroy();
}

void wxPopupToolBar::OnDismiss()
{
	wxPopupTransientWindow::OnDismiss();
	Destroy();
}


