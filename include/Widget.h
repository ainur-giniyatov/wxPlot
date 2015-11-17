/*
Widget class is an ancestor for on-plot drawn widgets such as scales, legends, etc
*/
#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Renderer.h"

#include <wx/graphics.h>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Renderer2D;

enum POS_RELATIVE {
	POS_TOPLEFT,
	POS_TOPRIGHT,
	POS_BOTTOMLEFT,
	POS_BOTTOMRIGHT,
	POS_AUTO
};

enum WIDGET_MOUSE_EVENT {
	WME_RDOWN,
	WME_LDOWN,
	WME_MDOWN,
	WME_RUP,
	WME_LUP,
	WME_MUP
};

class WXDLLIMPEXP_PLOTLIB Widget
{
public:
	Widget(Plot *owner, SpaceND *bound_to_space = NULL);
	virtual ~Widget();

	/*true if mouse cursor is in the widget area. all other mouse-related methods must be preceeded by it*/
	bool MouseIsInside(int x, int y);

	/*handle mouse movements*/
	void MouseMoving(int x, int y);

	/*mouse click events*/
	virtual void MouseButton(WIDGET_MOUSE_EVENT wme, int x, int y);

	virtual void MouseWheel(double factor, int x, int y);

	virtual void Render(wxGraphicsContext *gc);
	
	/*for internal use. converts m_*_anchor, m_d* to DC coords according to m_pos_rel*/
	void CalculatetoDCcoords();

	/*calculate size*/
	void virtual Fit();

protected:

	double m_x_anchor;//position of the widget in the space or 0..1 coordinate
	double m_y_anchor;

	int m_dx, m_dy; //delta x, y from the anchor

	int m_widget_x, m_widget_y;//postition of the widget in the dc of the plot
	int m_width;
	int m_height;

	SpaceND *m_bound_to_space;
	Plot *m_owner;

	POS_RELATIVE m_pos_rel;

	bool m_dragging;//set true when the widget is being dragged by mouse
	int m_drag_x;
	int m_drag_y;
	int m_drag_dx;
	int m_drag_dy;

//helper funcs
	void start_dragging(int drag_x, int drag_y);
	virtual void proceed_dragging(int x, int y);
	void end_dragging();
private:
};
