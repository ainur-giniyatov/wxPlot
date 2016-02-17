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

	m_valueadaptor = new TimeAxisValueAdaptor<double>();
}


Scale::~Scale()
{
	for (auto axis : m_axes)
	{
		axis->SetCommonScale(NULL);
	}
	if(m_valueadaptor != NULL)
		delete m_valueadaptor;
}

void Scale::AddAxis(Axis * axis)
{
	assert(m_axis_dir == axis->_get_axis_dir());
	m_axes.push_back(axis);
	axis->SetCommonScale(this);
	axis->SetOffset(m_offset);
	axis->SetRange(m_range);
	axis->AxisUpdated();

	if(axis->GetOwner() != nullptr && axis->GetOwner()->GetOwner() != nullptr)
		axis->GetOwner()->GetOwner()->HandleEvent(PEventScaleSet());
}

void Scale::RemoveAxis(Axis * axis)
{
	assert(m_axis_dir == axis->_get_axis_dir());

	std::vector<Axis *>::iterator tail_i;
	tail_i = std::remove(m_axes.begin(), m_axes.end(), axis);

	if (tail_i != m_axes.end())
	{
		m_axes.erase(tail_i, m_axes.end());
		axis->SetCommonScale(NULL);
		axis->AxisUpdated();
	}
	else
	{
		assert(0);
	}

	//std::vector<Axis *> axes;
	//bool found = false;
	//for (auto axis_i : m_axes)
	//{
	//	if (axis_i == axis)
	//	{
	//		found = true;
	//		continue;
	//	}
	//	axes.push_back(axis_i);
	//}
	//if (found)
	//{
	//	axis->SetCommonScale(NULL);
	//	axis->AxisUpdated();
	//}

	//m_axes = axes;
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
		axis->m_offset = m_offset;

}

void Scale::SetRange(double range)
{
	m_range = range;

	for (auto axis : m_axes)
		axis->m_range = m_range;

}

void Scale::RedrawDependantPlots(bool redraw_immdiately)
{
	//redraw dependant plots uniqly. use stl algorithms
	std::vector<Plot *> vuniqplots;
	for (auto axis : m_axes)
	{
		Plot *plot = axis->GetOwner()->GetOwner();
		if (plot != NULL && std::none_of(vuniqplots.begin(), vuniqplots.end(), [plot](Plot *p) {return p == plot; }))
		{
			plot->_SetViewModifiedFlag();
			if(redraw_immdiately)
				plot->RedrawPlot();
			vuniqplots.push_back(plot);
		}
	}
}

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

//		ScaleRedraw();
		RedrawDependantPlots();
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

//	ScaleRedraw();
	RedrawDependantPlots(false);
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

void Scale::SetRangeLimits(double max, double min, bool update)
{
	m_range_max = max;
	m_range_min = min;

}

bool Scale::IsInRange(double new_range)
{
	return (new_range < m_range_max && new_range > m_range_min);
}
