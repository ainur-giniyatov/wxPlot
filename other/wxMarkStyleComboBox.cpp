#include "wxMarkStyleComboBox.h"
#include "wx/colorbase.h"

wxMarkStyleComboBox::wxMarkStyleComboBox(wxWindow *parent, wxWindowID id):wxOwnerDrawnComboBox(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
    //ctor
    //for(int i = 0; i < MARKERSTYLES_COUNT; i++)
    //{
    //    Append(wxEmptyString, (void *)MARKERSTYLES[i]);
    //}


	plot::wxMarker *marker;
	marker = new plot::wxMarkerCircle();
	m_markers.push_back(marker);
	Append(wxEmptyString, marker);

	marker = new plot::wxMarkerSquare();
	m_markers.push_back(marker);
	Append(wxEmptyString, marker);

	marker = new plot::wxMarkerRomb();
	m_markers.push_back(marker);
	Append(wxEmptyString, marker);
}

wxMarkStyleComboBox::~wxMarkStyleComboBox()
{
    //dtor
	for (auto marker : m_markers)
		delete marker;
}

void wxMarkStyleComboBox::OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const
{
    if(item == wxNOT_FOUND)
        return;

    wxGraphicsContext *gc;
    gc = wxGraphicsContext::Create(*(wxWindowDC*)&dc);
    wxPoint pos;
    pos = rect.GetPosition() + rect.GetSize().Scale(0.5, 0.5);

	plot::wxMarker *marker = m_markers[item];
	marker->InitStyleAndColour(gc);
	if(!IsEnabled())
	{
		wxColor color(dc.GetPen().GetColour().MakeDisabled(100));
		wxPen pen(color);
		gc->SetPen(pen);

		wxBrush brush(color);
		gc->SetBrush(brush);
	}
	marker->Render(gc, Point<int>(pos.x, pos.y));

    delete gc;

	if(flags & wxODCB_PAINTING_CONTROL)
        return;

    if(flags & wxODCB_PAINTING_SELECTED)
    {
        dc.SetPen(*wxBLUE_PEN);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(rect);
    }

}

void wxMarkStyleComboBox::SetMarkStyleSelection(plot::wxMarker *marker)
{
	for (int indx = 0; indx < GetCount(); indx++)
	{
		plot::wxMarker *marker1;
		marker1 = (plot::wxMarker *)GetClientData(indx);
		if (marker1->_getid() == marker->_getid())
		{
			SetSelection(indx);
		}
	}
	CopyMarkerAttribs(marker);
}

void wxMarkStyleComboBox::CopyMarkerAttribs(plot::wxMarker * marker)
{
	for (auto marker_i : m_markers)
	{
		marker_i->SetSize(marker->GetSize());
		marker_i->SetFillColourIndex(marker->GetFillColourIndex());
	}
	Refresh();
}

plot::wxMarker * wxMarkStyleComboBox::GetSelectedMarker()
{
	int indx;
	indx = GetSelection();
	if (indx == wxNOT_FOUND)
		return nullptr;


	
	return m_markers[indx];
}