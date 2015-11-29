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
#include <wx/menu.h>
#include <wx/event.h>

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


#define	WIDGET_SNAP_NONE 0
#define	WIDGET_SNAP_LEFT  (1 << 0)
#define	WIDGET_SNAP_RIGHT (1 << 1)
#define	WIDGET_SNAP_BOTTOM (1 << 2)
#define	WIDGET_SNAP_TOP (1 << 3)
#define	WIDGET_SNAP_ALL (WIDGET_SNAP_LEFT | WIDGET_SNAP_RIGHT | WIDGET_SNAP_BOTTOM | WIDGET_SNAP_TOP)
#define WIDGET_SNAP_DISTANCE 10

class WXDLLIMPEXP_PLOTLIB Widget:public wxEvtHandler
{
public:
	Widget(Plot *owner, SpaceND *bound_to_space = NULL);
	virtual ~Widget();

	void SetAnchorPosition(double ax, double ay) { m_x_anchor = ax; m_y_anchor = ay; }

	/*true if mouse cursor is in the widget area. all other mouse-related methods must be preceeded by it*/
	bool MouseIsInside(int x, int y);

	/*handle mouse movements*/
	void MouseMoving(int x, int y);

	virtual void OnMouseLeftDown(int x, int y);
	virtual void OnMouseLeftUp(int x, int y);
	virtual void OnMouseRightDown(int x, int y);
	virtual void OnMouseRightUp(int x, int y);

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

	int m_snap_to_border;

	bool m_movable;//allowed to drag by mouse

	wxMenu m_menu;
//helper funcs
	void start_dragging(int drag_x, int drag_y);
	virtual void proceed_dragging(int x, int y);
	void end_dragging();

private:

	/*context menu handlers*/
	void OnMenuCloseWidget(wxCommandEvent &event);
	static const int ID_MENU_CLOSE;

	//some helpers
	/*remove from plot's widgets and delete*/
	void delete_widget();
	DECLARE_EVENT_TABLE();
};
