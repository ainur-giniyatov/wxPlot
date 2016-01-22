#include <wx/dcclient.h>
#include "wxLineStyleComboBox.h"
#include "wx/colorbase.h"

wxLineStyleComboBox::wxLineStyleComboBox(wxWindow *parent, wxWindowID id):wxOwnerDrawnComboBox(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
    //ctor
    m_width = 1;
    m_colour_indx = 0;
    for(int i = 0; i < MYDASHES_COUNT; i++)
    {
        Append(wxEmptyString, (void*)i);
    }
}

wxLineStyleComboBox::~wxLineStyleComboBox()
{
    //dtor
}

int wxLineStyleComboBox::GetPenStyleSelection()
{
    return GetSelection();
}

void wxLineStyleComboBox::SetPenStyleSelection(int indx)
{
    SetSelection(indx);
}

void wxLineStyleComboBox::OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const
{
    if(item == wxNOT_FOUND)
        return;
    int ii;
    ii = (int)GetClientData(item);
    wxPen pen(wxColour(COLOR_BASE[m_colour_indx]), m_width);
    if(ii != 0)
    {
        pen.SetStyle(wxPENSTYLE_USER_DASH);
        pen.SetDashes(6, MYDASHES[ii]);
    }

    dc.SetPen(pen);//wxPen(*wxBLACK, 1, PENSTYLE_BASE[ii]));

    int width, heigth;
    width = rect.GetWidth();
    heigth = rect.GetHeight();
    dc.DrawLine(4, rect.GetY() + heigth / 2, width - 4, rect.GetY() + heigth / 2);
    if(flags & wxODCB_PAINTING_CONTROL)
        return;

    if(flags & wxODCB_PAINTING_SELECTED)
    {
        dc.SetPen(*wxBLUE_PEN);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawRectangle(rect);
    }
}

void wxLineStyleComboBox::SetColourIndex(int colour_indx)
{
    m_colour_indx = colour_indx;
    Refresh();
}

void wxLineStyleComboBox::SetWidth(int width)
{
    m_width = width;
    Refresh();
}
