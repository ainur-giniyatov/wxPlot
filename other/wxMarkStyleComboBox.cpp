#include "wxMarkStyleComboBox.h"
#include "wx/colorbase.h"

wxMarkStyleComboBox::wxMarkStyleComboBox(wxWindow *parent, wxWindowID id):wxOwnerDrawnComboBox(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
    //ctor
    for(int i = 0; i < MARKERSTYLES_COUNT; i++)
    {
        Append(wxEmptyString, (void *)MARKERSTYLES[i]);
    }
    m_colour_indx = 0;
    m_mark_size = 3;
}

wxMarkStyleComboBox::~wxMarkStyleComboBox()
{
    //dtor
}

void wxMarkStyleComboBox::OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const
{
    if(item == wxNOT_FOUND)
        return;

    wxGraphicsContext *gc;
    gc = wxGraphicsContext::Create(*(wxWindowDC*)&dc);
//    dc.SetPen(wxColour(COLOR_BASE[m_colour_indx]));
//    dc.SetBrush(wxColour(COLOR_BASE[m_colour_indx]));
	MARKER_STYLES mark_style = (MARKER_STYLES)(int)GetClientData(item);
    PrepareMarkGC(gc, mark_style, m_mark_size, m_colour_indx);
    wxPoint pos;
    pos = rect.GetPosition() + rect.GetSize().Scale(0.5, 0.5);

    PutMark(gc, pos.x, pos.y, mark_style, m_mark_size);
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

void wxMarkStyleComboBox::SetMarkStyleSelection(int indx)
{
	for (int i = 0; i < GetCount(); i++)
	{
		if (indx == (int)GetClientData(i))
		{
			SetSelection(i);
			return;
			break;
		}
	}
	assert(0);
}

void wxMarkStyleComboBox::SetColourIndex(int color_indx)
{
    m_colour_indx = color_indx;
    Refresh();
}

void wxMarkStyleComboBox::SetMarkSize(int mark_size)
{
    m_mark_size = mark_size;
    Refresh();
}
