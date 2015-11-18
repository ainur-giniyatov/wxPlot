#include "Widget.h"

Widget::Widget(Plot *owner, SpaceND *bound_to_space)
{
	DPRINTF("Widget ctor\n");

	m_x_anchor = 0.5;
	m_y_anchor = 0.5;

	m_dx = m_dy = 0;
	m_owner = owner;
	m_owner->AddWidget(this);

	m_pos_rel = POS_BOTTOMRIGHT;

	m_bound_to_space = bound_to_space;

	m_dragging = false;
	m_movable = false;
	m_snap_to_border = WIDGET_SNAP_ALL;
	Fit();
}

Widget::~Widget()
{
	DPRINTF("Widget dtor\n");
}

bool Widget::MouseIsInside(int x, int y)
{

	return (x >= m_widget_x && x <= (m_widget_x + m_width)) && (y >= m_widget_y && y <= (m_widget_y + m_height)) || m_dragging;
}

void Widget::MouseMoving(int x, int y)
{
	DPRINTF("Widget:MouseMoving\n");
	if (m_dragging)
		proceed_dragging(x, y);
}

void Widget::MouseButton(WIDGET_MOUSE_EVENT wme, int x, int y)
{
	switch (wme)
	{
	case WME_RDOWN:
		break;
	case WME_LDOWN:
		start_dragging(x, y);
		break;
	case WME_MDOWN:
		break;
	case WME_RUP:
		break;
	case WME_LUP:
		end_dragging();
		break;
	case WME_MUP:
		break;
	default:
		break;
	}
}

void Widget::MouseWheel(double factor, int x, int y)
{
	DPRINTF("Widget::MouseWheel\n");
}

void Widget::Render(wxGraphicsContext * gc)
{
	DPRINTF("Widget::Render\n");

	CalculatetoDCcoords();

	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);
	gc->DrawRectangle(m_widget_x, m_widget_y, m_width, m_height);
}

void Widget::CalculatetoDCcoords()
{
	int w_plot, h_plot;// width , height of the owner plot
	m_owner->GetSize(&w_plot, &h_plot);

	int xa, ya; //anchor coords in dc coords

	xa = 0;
	ya = 0;

	if (m_bound_to_space == NULL)
	{
		xa = w_plot * m_x_anchor;
		ya = h_plot * m_y_anchor;
	}
	else
	{
		xa = w_plot * (m_x_anchor - m_bound_to_space->GetAxis(AXIS_X)->GetOffset()) / m_bound_to_space->GetAxis(AXIS_X)->GetRange();
		ya = h_plot - h_plot * (m_y_anchor - m_bound_to_space->GetAxis(AXIS_Y)->GetOffset()) / m_bound_to_space->GetAxis(AXIS_Y)->GetRange();
	}

	int rx, ry; //widgets top left corner coords
	rx = 0;
	ry = 0;

	switch (m_pos_rel)
	{
	case POS_TOPLEFT:
		rx = xa + m_dx;
		ry = ya + m_dy;
		break;
	case POS_TOPRIGHT:
		rx = xa - m_width - m_dx - 1;
		ry = ya + m_dy;
		break;
	case POS_BOTTOMLEFT:
		rx = xa + m_dx;
		ry = ya - m_height - m_dy - 1;
		break;
	case POS_BOTTOMRIGHT:
		rx = xa - m_width - m_dx - 1;
		ry = ya - m_height - m_dy - 1;
		break;
	case POS_AUTO:
		wxASSERT(0);//to do
		break;
	default:;
	}

	m_widget_x = rx;
	m_widget_y = ry;
}

void Widget::Fit()
{
	//default size for Widget
	m_width = 20;
	m_height = 20;
}

void Widget::start_dragging(int drag_x, int drag_y)
{
	if (!m_movable)
		return;
	DPRINTF("Widget::start_dragging\n");
	m_dragging = true;
	m_drag_x = drag_x;
	m_drag_y = drag_y;
	m_drag_dx = m_drag_x - m_widget_x;
	m_drag_dy = m_drag_y - m_widget_y;
}

void Widget::proceed_dragging(int x, int y)
{
	DPRINTF("Widget::proceed_dragging\n");
	int w_plot, h_plot;
	m_owner->GetSize(&w_plot, &h_plot);

	int new_wx, new_wy; //new coords for the widget top left corner
	new_wx = x - m_drag_dx;
	new_wy = y - m_drag_dy;


	if (m_snap_to_border & WIDGET_SNAP_LEFT)
		if (abs(new_wx) < WIDGET_SNAP_DISTANCE)
		{
			new_wx = 0;

			if (m_pos_rel == POS_BOTTOMRIGHT)
				m_pos_rel = POS_BOTTOMLEFT;

			if (m_pos_rel == POS_TOPRIGHT)
				m_pos_rel = POS_TOPLEFT;
		}

	if (m_snap_to_border & WIDGET_SNAP_RIGHT)
		if (abs(w_plot - (new_wx + m_width)) < WIDGET_SNAP_DISTANCE)
		{
			new_wx = w_plot - m_width - 1;

			if (m_pos_rel == POS_BOTTOMLEFT)
				m_pos_rel = POS_BOTTOMRIGHT;

			if (m_pos_rel == POS_TOPLEFT)
				m_pos_rel = POS_TOPRIGHT;

		}

	if (m_snap_to_border & WIDGET_SNAP_TOP)
		if (abs(new_wy) < WIDGET_SNAP_DISTANCE)
		{
			new_wy = 0;

			if (m_pos_rel == POS_BOTTOMRIGHT)
				m_pos_rel = POS_TOPRIGHT;

			if (m_pos_rel == POS_BOTTOMLEFT)
				m_pos_rel = POS_TOPLEFT;

		}

	if (m_snap_to_border & WIDGET_SNAP_BOTTOM)
		if (abs(h_plot - (new_wy + m_height)) < WIDGET_SNAP_DISTANCE)
		{
			new_wy = h_plot - m_height - 1;

			if (m_pos_rel == POS_TOPRIGHT)
				m_pos_rel = POS_BOTTOMRIGHT;

			if (m_pos_rel == POS_TOPLEFT)
				m_pos_rel = POS_BOTTOMLEFT;

		}

	int new_ax = 0, new_ay = 0;//new dc coords for the anchor point

	switch (m_pos_rel) {
	case POS_TOPLEFT:
		new_ax = new_wx - m_dx;
		new_ay = new_wy - m_dy;
		break;
	case POS_TOPRIGHT:
		new_ax = new_wx + m_width + m_dx + 1;
		new_ay = new_wy - m_dy;
		break;
	case POS_BOTTOMLEFT:
		new_ax = new_wx - m_dx;
		new_ay = new_wy + m_height + m_dy + 1;
		break;
	case POS_BOTTOMRIGHT:
		new_ax = new_wx + m_width + m_dx + 1;
		new_ay = new_wy + m_height + m_dy + 1;
		break;
	case POS_AUTO:
		wxASSERT(0);//to do
		break;
	default:;
	}

	//convert dc coords to .. ehm. vobshem ponyal
	if (m_bound_to_space == NULL)
	{
		m_x_anchor = (double)(new_ax)/ (double)w_plot;
		m_y_anchor = (double)(new_ay)/ (double)h_plot;
	}
	else
	{
		m_x_anchor = (double)new_ax / (double)w_plot * m_bound_to_space->GetAxis(AXIS_X)->GetRange() + m_bound_to_space->GetAxis(AXIS_X)->GetOffset();
		m_y_anchor = (double)(h_plot - new_ay) / (double)h_plot * m_bound_to_space->GetAxis(AXIS_Y)->GetRange() + m_bound_to_space->GetAxis(AXIS_Y)->GetOffset();
	}

	m_owner->RedrawPlot();
}

void Widget::end_dragging()
{
	DPRINTF("Widget::end_dragging\n");
	m_dragging = false;
}

