#include <wx/graphics.h>
#include <wx/dcclient.h>

#include "wx/wxBox.h"
#include "wx/wxSubPlot.h"

using namespace plot;

wxBox::wxBox(int flags):Box(flags)
{
}

wxBox::~wxBox()
{
}

void wxBox::Render(void *vgc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)vgc;
	
	Rect<int> rect;
	auto size = m_owner->_get_size();
	if (_has_flags(BACKENDORIENTED))
		size = m_owner->_get_backend_size();

	if (!_has_flags(BACKENDORIENTED))
		rect = m_owner->_plot_to_backend(m_rect);
	else
	{
		rect.left = m_rect.left;
		rect.right = m_rect.right;
		rect.top = size.h - m_rect.bottom;
		rect.bottom = size.h - m_rect.top;
	}

	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);

	gc->DrawRectangle(rect.left, rect.bottom, rect.Width(), rect.Height());
}

plot::wxTitleBox::wxTitleBox()
{
}

plot::wxTitleBox::~wxTitleBox()
{
}

void plot::wxTitleBox::Render(void *vgc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)vgc;
	auto bsize = m_owner->_get_backend_size();
	Rect<int> rect;
	bool rot = false;
	if(!_has_flags(BACKENDORIENTED))
		rect = m_owner->_plot_to_backend(m_rect);
	else
	{
		rect.left = m_rect.left;
		rect.right = m_rect.right;
		rect.bottom = bsize.h - m_rect.top;
		rect.top = bsize.h - m_rect.bottom;
	}
	
	rot = m_owner->_get_orientation() == Subplot::ORIENTATION_ROTATED;

	wxDouble fw, fh, fdesc;
	wxString text(m_title);
	gc->GetTextExtent(text, &fw, &fh, &fdesc);
	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);
	gc->DrawRectangle(rect.left, rect.bottom, rect.Width(), rect.Height());
	
	gc->DrawText(wxString(m_title), rot ? rect.right : rect.left + (rect.Width() - fw) / 2., rect.bottom + (rect.Height() - fh) / 2., rot ? M_PI / 2. * 3. : 0.0f);
}

void plot::wxTitleBox::_ownersize(const Size<int> &ownersize)
{
	wxSubplot *subplot;
	subplot = dynamic_cast<wxSubplot *>(m_owner);
	wxClientDC dc(subplot);
	wxCoord tw, th;
	dc.GetTextExtent(wxString(m_title), &tw, &th);

	m_rect.SetHeight(th + m_border_thickness * 2);
	m_rect.SetWidth(tw + m_border_thickness * 2);
}
