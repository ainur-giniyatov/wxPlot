//#include "stdafx.h"
#include "Scale.h"
#include <float.h>
#include <algorithm>

Scale::Scale()
{
	m_offset = 0.;
	m_range = 1000.;

	m_range_max = DBL_MAX;
	m_range_min = 3;

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
	m_axes.push_back(axis);
	axis->SetCommonScale(this);
	axis->SetOffset(m_offset);
	axis->SetRange(m_range);
	axis->AxisUpdated();

}

void Scale::RemoveAxis(Axis * axis)
{
	std::vector<Axis *> axes;
	bool found = false;
	for (auto axis_i : m_axes)
	{
		if (axis_i == axis)
		{
			found = true;
			continue;
		}
		axes.push_back(axis_i);
	}
	if (found)
	{
		axis->SetCommonScale(NULL);
		axis->AxisUpdated();
	}

	m_axes = axes;
}

void Scale::SetOffset(double offset)
{
	m_offset = offset;

	for (auto axis : m_axes)
		axis->SetOffset(m_offset);

}

void Scale::SetRange(double range)
{
	m_range = range;

	for (auto axis : m_axes)
		axis->SetRange(m_range);

}

void Scale::RedrawDependantPlots()
{
	//redraw dependant plots uniqly
	std::vector<Plot *> vuniqplots;
	for (auto axis : m_axes)
	{
		Plot *plot = axis->GetOwner()->GetOwner();
		if (plot != NULL && std::count(vuniqplots.begin(), vuniqplots.end(), plot) == 0)
		{
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

		ScaleRedraw();
		RedrawDependantPlots();
	}
}

void Scale::StartPanAt(double rv)
{
	DPRINTF("Scale::StartPanAt\n");
	m_pan_start_at_rv = rv;
	m_pan_start_at_vv = m_offset;
}

void Scale::ProceedPanAt(double rv)
{
	DPRINTF("Scale::ProceedPanAt\n");

	SetOffset(m_pan_start_at_vv - m_range * (rv - m_pan_start_at_rv));

	ScaleRedraw();
	RedrawDependantPlots();
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
