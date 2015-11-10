#pragma once

#include <wx/graphics.h>

#include "plot_defs.h"
#include "Series.h"
#include "Renderer.h"
#include "Axis.h"
#include "Space.h"

class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB Renderer2D;
class WXDLLIMPEXP_PLOTLIB SpaceND;
template <class T> class WXDLLIMPEXP_PLOTLIB ValueAdaptor;

class WXDLLIMPEXP_PLOTLIB Grid
{
public:
	Grid(SpaceND *owner_space);
	virtual ~Grid();

	void Render(wxGraphicsContext *gc);
	void GridUpdated();

protected:
	SpaceND *m_owner_space;
private:
};