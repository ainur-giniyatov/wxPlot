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


class WXDLLIMPEXP_PLOTLIB Box
{
public:

	enum DragDir {
		DRAGDIR_HOR = (1 << 0),
		DRAGDIR_VER = (1 << 1),
		DRAGDIR_ALL = (DRAGDIR_HOR | DRAGDIR_VER)
	};

	
	enum RelPointAlignment {
		RELPA_CLOSER,
		RELPA_MIDDLE,
		RELPA_FURTHER
	};

	Box(Plot *owner, SpaceND *space = NULL);
	virtual ~Box();

	virtual void Render(wxGraphicsContext *gc);
	
	bool CheckIsMouseInside(int mx, int my);
	virtual void MouseMove(int mx, int my);
	virtual void MouseLeftDown(int mx, int my);
	virtual void MouseLeftUp(int mx, int my);

	virtual void Sizing();
protected:
	Plot *m_owner;
	SpaceND *m_bound_space;
	int m_width;
	int m_height;
	int m_x;
	int m_y;

	double m_rel_x;
	double m_rel_y;
private:
	bool m_isdragging;
	int m_drag_dx;
	int m_drag_dy;
	DragDir m_flag_dragdir;

	RelPointAlignment m_relpointalign_ver;
	RelPointAlignment m_relpointalign_hor;
};