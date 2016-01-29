#include "wx/wxLine.h"
#include "wx/colorbase.h"

void plot::wxLine::InitStyleAndColour(wxGraphicsContext * gc)
{
	if (m_colour_indx != -1)
	{
		wxPen pen;
		pen.SetColour(wxColour(COLOR_BASE[m_colour_indx]));
		pen.SetWidth(m_thickness);
		gc->SetPen(pen);
	}
	else
	{
		gc->SetPen(*wxTRANSPARENT_PEN);
	}
}

plot::wxSimpleLine::wxSimpleLine(int color_indx, int thickness, bool vsbl)
{
	m_colour_indx = color_indx;
	m_thickness = thickness;
	m_visible = vsbl;
}

bool plot::wxSimpleLine::_isspotted(Point<int>& mouse_coord, Point<int>& line_coord1, Point<int>& line_coord2)
{
	//DPRINTF("wxSimpleLine::_isspotted\n");
	if (!m_visible)
		return false;

	Rect<int> r(line_coord1, line_coord2);
	r.Inflate(m_thickness); //to avoid cases when the line is horizontal or vertical
	if (!r.IsInside(mouse_coord))
		return false;

	Point<int> m1 = mouse_coord - line_coord1;
	Point<int> l = line_coord2 - line_coord1;
	double a, b, norm_mult, dist;
	if (l.y == 0)
	{
		dist = m1.y;
	}
	else
	{
		if (l.x == 0)
		{
			dist = m1.x;
		}
		else
		{
			a = 1. / (double)l.x;
			b = -1. / (double)l.y;
			norm_mult = -1. / sqrt(pow(a, 2) + pow(b, 2));
			dist = abs((a * m1.x + b * m1.y) * norm_mult);
		}
	}

	return (dist < (double)m_thickness / 2.);
}

void plot::wxSimpleLine::Render(void *v_gc, Point<int>& line_coord1, Point<int>& line_coord2)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	gc->StrokeLine(line_coord1.x, line_coord1.y, line_coord2.x, line_coord2.y);
}
