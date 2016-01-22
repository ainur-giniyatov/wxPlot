#include <wx/dcclient.h>
#include <assert.h>
#include "wxColorComboBox.h"
#include "wx/colorbase.h"

wxColorComboBox::wxColorComboBox(wxWindow *parent, wxWindowID id):wxOwnerDrawnComboBox(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
    //ctor
    for(int i = 0; i < COLOR_BASE_COUNT; i++)
    {
        wxColour *colour = new wxColour(COLOR_BASE[i]);
        Append(wxEmptyString, colour);
    }
}

wxColorComboBox::~wxColorComboBox()
{
    //dtor
    for(int i = 0; i < COLOR_BASE_COUNT; i++)
    {
        wxColour *colour = (wxColour *)GetClientData(i);
        delete colour;
    }
}

void wxColorComboBox::OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const
{
    if(item == wxNOT_FOUND)
        return;
    wxColour *colour;
    colour = (wxColour *)GetClientData(item);
    dc.SetPen(*colour);
    dc.SetBrush(*colour);
    dc.DrawRectangle(rect);
}

int wxColorComboBox::GetColourSelection()
{
    int indx;
    indx = GetSelection();
    if(indx == wxNOT_FOUND)
        indx = 0;
    return indx;
}

void wxColorComboBox::SetColorSelection(int indx)
{
    assert(indx < COLOR_BASE_COUNT);
    SetSelection(indx);
}
