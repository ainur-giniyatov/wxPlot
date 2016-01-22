#include <wx/sizer.h>
#include "PopupSeriesTool.h"

wxBEGIN_EVENT_TABLE(wxPopupSeriesTool, wxPopupWindow)
EVT_LEFT_DOWN(wxPopupSeriesTool::OnLeftDown)
EVT_LEFT_UP(wxPopupSeriesTool::OnLeftUp)
EVT_MOTION(wxPopupSeriesTool::OnMouseMove)
EVT_MOUSE_CAPTURE_LOST(wxPopupSeriesTool::OnMouseCaptureLost)

wxEND_EVENT_TABLE();

wxPopupSeriesTool::wxPopupSeriesTool(wxWindow * parent, plot::Series * series):wxPopupWindow(parent, wxBORDER_STATIC)
{
	wxSizer *bSizer;
	bSizer = new wxBoxSizer(wxVERTICAL);

	wxButton *button_close = new wxButton(this, wxID_ANY, "x", wxDefaultPosition, wxSize(15, 15));
	bSizer->Add(button_close, 0, wxALIGN_RIGHT, 4);
	
	m_seriestool = new SeriesTool(this, series);
	bSizer->Add(m_seriestool, 1, wxALL | wxEXPAND, 4);

	SetSizer(bSizer);
	Fit();

	m_seriestool->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&wxPopupSeriesTool::OnLeftDown, nullptr, this);
	m_seriestool->Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&wxPopupSeriesTool::OnLeftUp, nullptr, this);
	m_seriestool->Connect(wxEVT_MOTION, (wxObjectEventFunction)&wxPopupSeriesTool::OnMouseMove, nullptr, this);
	Connect(button_close->GetId(), wxEVT_BUTTON, (wxObjectEventFunction)&wxPopupSeriesTool::OnCloseButton);

	Position(wxGetMousePosition(), wxSize(0, 0));

	m_moving = false;
}

wxPopupSeriesTool::~wxPopupSeriesTool()
{
}

//void wxPopupSeriesTool::OnDismiss()
//{
//	Destroy();
//}
//
//bool wxPopupSeriesTool::ProcessLeftDown(wxMouseEvent & event)
//{
//	return false;
//}

void wxPopupSeriesTool::OnLeftDown(wxMouseEvent & event)
{
	DPRINTF("wxPopupSeriesTool::OnLeftDown\n");
	m_moving = true;
	m_start_moving_pos_mouse = wxGetMousePosition();
	m_start_moving_pos = GetPosition();
	if (!HasCapture())
		CaptureMouse();
}

void wxPopupSeriesTool::OnLeftUp(wxMouseEvent & event)
{
	DPRINTF("wxPopupSeriesTool::OnLeftUp\n");
	m_moving = false;
	if (HasCapture())
		ReleaseMouse();
}

void wxPopupSeriesTool::OnMouseMove(wxMouseEvent & event)
{
	if (event.LeftIsDown() && m_moving)
	{
		SetPosition(m_start_moving_pos + (wxGetMousePosition() - m_start_moving_pos_mouse));
	}
}

void wxPopupSeriesTool::OnMouseCaptureLost(wxMouseCaptureLostEvent & event)
{
	
}

void wxPopupSeriesTool::OnCloseButton(wxCommandEvent & event)
{
	DPRINTF("wxPopupSeriesTool::OnCloseButton\n");
	Destroy();
}


