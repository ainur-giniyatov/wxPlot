#include <float.h>
#include <algorithm>
#include <assert.h>

#include "Scale.h"

using namespace plot;

Scale::Scale(AXIS_DIR axis_dir)
{
	m_offset = 0.;
	m_range = 1000.;

	m_range_max = DBL_MAX;
	m_range_min = 3;

	m_axis_dir = axis_dir;

	m_valueadaptor = new SimpleAxisValueAdaptor<double>();
}


Scale::~Scale()
{
	for (auto axis : m_axes)
	{
		axis->_setcommonscale(NULL);
	}
	if(m_valueadaptor != NULL)
		delete m_valueadaptor;
}

void Scale::AddAxis(Axis * axis)
{
	assert(m_axis_dir == axis->_get_axis_dir());
	m_axes.push_back(axis);
	axis->_setcommonscale(this);
	axis->_setoffset(m_offset);
	axis->_setrange(m_range);
	
	m_plots.clear();
	for (auto axis : m_axes)
	{
		if (axis->_getowner() != nullptr && axis->_getowner()->_getowner() != nullptr)
		{
			m_plots.push_back(axis->_getowner()->_getowner());
			axis->_getowner()->_getowner()->_refresh_dependant_scales();
		}

		else
			assert(0);
	}
	
	m_plots.erase(std::unique(m_plots.begin(), m_plots.end()), m_plots.end());

}

void Scale::RemoveAxis(Axis * axis)
{
	assert(axis->_getcommonscale() == this);
	assert(m_axis_dir == axis->_get_axis_dir());

	
	m_axes.erase(std::remove(m_axes.begin(), m_axes.end(), axis), m_axes.end());

	m_plots.clear();
	for (auto axis : m_axes)
		m_plots.push_back(axis->_getowner()->_getowner());

	m_plots.erase(std::unique(m_plots.begin(), m_plots.end()), m_plots.end());
}

void plot::Scale::ChangeViewDepth(int vcd, bool swtch)
{
	auto viewstep = m_view_change_steps.find(vcd);
	if (!swtch)
	{
		m_view_change_steps[vcd] = m_previous_view;
	}
	else
	{
		if (viewstep != m_view_change_steps.end())
		{
			VIEWSTEP vstep = m_view_change_steps[vcd];
			SetOffset(vstep.offset);
			SetRange(vstep.range);
			
		}
	}

}

void Scale::SetOffset(double offset)
{
	m_offset = offset;

	for (auto axis : m_axes)
		axis->_setoffset(m_offset);

//	Validate();
}

void Scale::SetRange(double range)
{
	m_range = range;

	for (auto axis : m_axes)
		axis->_setrange(m_range);

//	Validate();
}

//void Scale::RedrawDependantPlots(bool redraw_immdiately)
//{
//	//redraw dependant plots uniqly. use stl algorithms
//	std::vector<Plot *> vuniqplots;
//	for (auto axis : m_axes)
//	{
//		Plot *plot = axis->GetOwner()->GetOwner();
//		if (plot != NULL && std::none_of(vuniqplots.begin(), vuniqplots.end(), [plot](Plot *p) {return p == plot; }))
//		{
//			plot->_SetViewModifiedFlag();
//			if(redraw_immdiately)
//				plot->RedrawPlot();
//			vuniqplots.push_back(plot);
//		}
//	}
//}

void Scale::ZoomAt(double rv, double factor)
{
	DPRINTF("Scale::ZoomAt\n");
	double offs, range, x;
	range = m_range;
	offs = m_offset;
	x = offs + range * rv;

	if (IsInRange(range * factor))
	{
		SetOffset(x - (x - offs) * factor);
		SetRange(range * factor);

	}
}

void Scale::StartPanAt(double rv)
{
	DPRINTF("Scale::StartPanAt\n");
	m_pan_start_at_rv = rv;
	m_pan_start_at_vv = m_offset;
	store_prev_view();
}

void Scale::ProceedPanAt(double rv)
{
	DPRINTF("Scale::ProceedPanAt\n");

	SetOffset(m_pan_start_at_vv - m_range * (rv - m_pan_start_at_rv));

}

void Scale::EndPanAt()
{
	DPRINTF("Scale::EndPanAt\n");


}

void Scale::SetValueAdaptor(AxisValueAdaptor<double>* valueadaptor)
{
	if (m_valueadaptor != NULL)
		delete m_valueadaptor;

	m_valueadaptor = valueadaptor;

}

void Scale::SetLimits(double max, double min, bool update)
{
	m_range_max = max;
	m_range_min = min;

}

bool Scale::IsInRange(double new_range)
{
	return (new_range < m_range_max && new_range > m_range_min);
}
