//#include "stdafx.h"
#include "Scale.h"


Scale::Scale()
{
	m_offset = 0.;
	m_range = 1000.;

	m_range_max = 10000000;
	m_range_min = 3;

	m_valueadaptor = new TimeValueAdaptor<double>();
}


Scale::~Scale()
{
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

void Scale::SetOffset(double offset, bool update)
{
	m_offset = offset;
	if (update)
		ScaleUpdated();
}

void Scale::SetRange(double range, bool update)
{
	m_range = range;
	if (update)
		ScaleUpdated();
}

void Scale::ScaleUpdated()
{
	for (auto axis : m_axes)
	{
		axis->SetRange(m_range);
		axis->SetOffset(m_offset);
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
		m_offset = (x - (x - offs) * factor);
		m_range = (range * factor);

		ScaleUpdated();
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

	m_offset = (m_pan_start_at_vv - m_range * (rv - m_pan_start_at_rv));

	ScaleUpdated();

}

void Scale::EndPanAt()
{
	DPRINTF("Scale::EndPanAt\n");

	
}

void Scale::SetValueAdaptor(ValueAdaptor<double>* valueadaptor)
{
	if (m_valueadaptor != NULL)
		delete m_valueadaptor;

	m_valueadaptor = valueadaptor;

	ScaleUpdated();
}

void Scale::SetRangeLimits(double max, double min, bool update)
{
	m_range_max = max;
	m_range_min = min;

	if (update)
		ScaleUpdated();
}

bool Scale::IsInRange(double new_range)
{
	return (new_range < m_range_max && new_range > m_range_min);
}
