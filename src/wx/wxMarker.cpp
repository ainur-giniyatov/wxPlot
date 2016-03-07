#include <math.h>
#include <wx/colour.h>
#include "wx/wxMarker.h"
#include "wx/colorbase.h"

using namespace plot;

static int s_color_indx = 0;

static int s_marker_id = 0;

static int get_new_marker_id()
{
	int marker_id = s_marker_id;
	s_marker_id++;
	return marker_id;
}

const int wxMarkerCircle::s_id = get_new_marker_id();
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

wxMarker * plot::wxMarkerCircle::Clone()
{
	return new wxMarkerCircle(*this);
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

void wxMarkerCircle::Render(void *v_gc, const Point<int>& coord)
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

const int wxMarkerSquare::s_id = get_new_marker_id();
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

wxMarker * plot::wxMarkerSquare::Clone()
{
	return new wxMarkerSquare(*this);
}

plot::wxMarkerSquare::~wxMarkerSquare()
{
}

void plot::wxMarkerSquare::Render(void *v_gc, const Point<int>& coord)
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

const int wxMarkerRomb::s_id = get_new_marker_id();
plot::wxMarkerRomb::wxMarkerRomb()
{
}

plot::wxMarkerRomb::wxMarkerRomb(int border_color_indx, int fill_color_indx, int size, bool vsbl)
{
	m_border_colour_indx = border_color_indx;
	m_fill_colour_indx = fill_color_indx;
	m_size = size;
	m_visible = vsbl;
}

wxMarker * plot::wxMarkerRomb::Clone()
{
	return new wxMarkerRomb(*this);
}

plot::wxMarkerRomb::~wxMarkerRomb()
{
}

void plot::wxMarkerRomb::Render(void *v_gc, const Point<int>& coord)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	//gc->DrawRectangle(coord.x - m_size, coord.y - m_size, m_size * 2, m_size * 2);
	m_vertexes[0].m_x = coord.x;
	m_vertexes[0].m_y = coord.y - m_size;

	m_vertexes[1].m_x = coord.x + m_size;
	m_vertexes[1].m_y = coord.y;

	m_vertexes[2].m_x = coord.x;
	m_vertexes[2].m_y = coord.y + m_size;

	m_vertexes[3].m_x = coord.x - m_size;
	m_vertexes[3].m_y = coord.y;

	m_vertexes[4] = m_vertexes[0];

	gc->DrawLines(5, m_vertexes);
}

bool plot::wxMarkerRomb::_isspotted(Point<int>& mouse_coord, Point<int>& marker_coord)
{
	//DPRINTF("wxMarkerSquare::_isspotted\n");
	if (!m_visible)
		return false;

	Point<int> dist = mouse_coord - marker_coord;
	return (abs(dist.x) < m_size && abs(dist.y) < m_size);
}
