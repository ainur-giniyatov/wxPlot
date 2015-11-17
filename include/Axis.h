#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Renderer.h"
#include "Scale.h"

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Renderer2D;
class WXDLLIMPEXP_PLOTLIB Scale;

class WXDLLIMPEXP_PLOTLIB Axis
{
public:
	Axis();
	virtual ~Axis();
	void AxisUpdated();
	
	void SetOwner(SpaceND *space) { m_owner_space = space; };
	SpaceND *GetOwner() { return m_owner_space; }
	
	void SetOffset(double offset);
	void SetRange(double range);
	double inline GetOffset() { return m_offset; }
	double inline GetRange() { return m_range; }
	
	void SetCommonScale(Scale *scale) { m_commonscale = scale; };
	Scale *GetCommonScale() { return m_commonscale; }
	void PropagateToCommonScale();

	/*adjust visible range for the axis and redraw dependant plots*/
	void SetVisibleRange(double offs, double range, bool update = true);
protected:

	friend Renderer;
	friend Renderer2D;

	double m_offset;
	double m_range;

	SpaceND *m_owner_space;
	Scale *m_commonscale;
};

