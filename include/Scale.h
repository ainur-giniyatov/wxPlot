#pragma once

#include "plot_defs.h"

#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Axis.h"
#include "Renderer.h"
#include "ValueAdaptor.h"
//#include "Widget.h"

#include <vector>

class WXDLLIMPEXP_PLOTLIB DataNoType;
class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Plot;
class WXDLLIMPEXP_PLOTLIB Axis;
class WXDLLIMPEXP_PLOTLIB SpaceND;
class WXDLLIMPEXP_PLOTLIB Renderer;
//class WXDLLIMPEXP_PLOTLIB Widget;

template<typename T> class WXDLLIMPEXP_PLOTLIB AxisValueAdaptor;

class WXDLLIMPEXP_PLOTLIB Scale
{
public:
	Scale();
	virtual ~Scale();

	void AddAxis(Axis *axis);
	
	void RemoveAxis(Axis *axis);

	std::vector<Axis *> &GetAxes() { return m_axes; };

	/*sets offset for the scale and propagates to bound axes*/
	void SetOffset(double offset); 
	
	/*sets range for the scale and propagates to bound axes*/
	void SetRange(double range);

	/*iterate plots and redraw them uniqly*/
	void RedrawDependantPlots();

	
	/*redraw scale gui component*/
	virtual void ScaleRedraw() = 0;

	void ZoomAt(double rv, double factor);
	void StartPanAt(double rv);
	void ProceedPanAt(double rv);
	void EndPanAt();

	void SetValueAdaptor(AxisValueAdaptor<double > *valueadaptor);
	AxisValueAdaptor<double> *GetValueAdaptor() { return m_valueadaptor; }
	void SetRangeLimits(double max, double min, bool update = true);
	bool IsInRange(double new_range);
	double inline GetRangeMax() { return m_range_max; };
	double inline GetRangeMin() { return m_range_min; };
protected:
	std::vector<Axis *> m_axes;

	double m_offset;
	double m_range;

	double m_range_max;
	double m_range_min;

	double m_pan_start_at_rv;
	double m_pan_start_at_vv;

	AxisValueAdaptor<double> *m_valueadaptor;
};

