#include <math.h>
#include <wx/colour.h>
#include "wx/wxMarker.h"
#include "wx/colorbase.h"

using namespace plot;

static int s_color_indx = 0;

wxMarkerCircle::wxMarkerCircle()
{
	
}

plot::wxMarkerCircle::wxMarkerCircle(int border_color_indx, int fill_color_indx, int size, bool vsbl)
{
	m_border_colour_indx = border_color_indx;
	m_fill_colour_indx = fill_color_indx;
	m_size = size;
	m_visible = vsbl;
}

wxMarkerCircle::~wxMarkerCircle()
{
}

bool wxMarkerCircle::_isspotted(Point<int> &mouse_coord, Point<int> &marker_coord)
{
	//DPRINTF("wxMarkerCircle::_isspotted\n");
	if(!m_visible)
		return false;
	Point<int> dist = mouse_coord - marker_coord;

	//outer sqare
	if (!(abs(dist.x) < m_size && abs(dist.y) < m_size))
		return false;

	//more accurate circle
	int r;
	r = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	return (r < m_size);
}

void wxMarkerCircle::Render(void *v_gc, Point<int>& coord)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	gc->DrawEllipse(coord.x - m_size, coord.y - m_size, m_size * 2, m_size * 2);
}


plot::wxMarker::wxMarker()
{
	m_border_colour_indx = COLOR_BASE_COUNT - 1;
	m_fill_colour_indx = s_color_indx;
	s_color_indx++;
	if (s_color_indx == COLOR_BASE_COUNT)
		s_color_indx = 0;
}

plot::wxMarker::~wxMarker()
{
}

void wxMarker::InitStyleAndColour(wxGraphicsContext *gc)
{
	if (m_border_colour_indx != -1)
	{
		wxPen pen;
		pen.SetColour(wxColour(COLOR_BASE[m_border_colour_indx]));
		gc->SetPen(pen);
	}
	else
	{
		gc->SetPen(*wxTRANSPARENT_PEN);
	}

	if (m_fill_colour_indx != -1)
	{
		wxBrush brush;
		brush.SetColour(wxColour(COLOR_BASE[m_fill_colour_indx]));
		gc->SetBrush(brush);
	}
	else
	{
		gc->SetBrush(*wxTRANSPARENT_BRUSH);
	}

}

plot::wxMarkerSquare::wxMarkerSquare()
{
}

plot::wxMarkerSquare::wxMarkerSquare(int border_color_indx, int fill_color_indx, int size, bool vsbl)
{
	m_border_colour_indx = border_color_indx;
	m_fill_colour_indx = fill_color_indx;
	m_size = size;
	m_visible = vsbl;
}

plot::wxMarkerSquare::~wxMarkerSquare()
{
}

void plot::wxMarkerSquare::Render(void *v_gc, Point<int>& coord)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	gc->DrawRectangle(coord.x - m_size, coord.y - m_size, m_size * 2, m_size * 2);
}

bool plot::wxMarkerSquare::_isspotted(Point<int>& mouse_coord, Point<int>& marker_coord)
{
	//DPRINTF("wxMarkerSquare::_isspotted\n");
	if (!m_visible)
		return false;

	Point<int> dist = mouse_coord - marker_coord;


	return (abs(dist.x) < m_size && abs(dist.y) < m_size);
	


}
