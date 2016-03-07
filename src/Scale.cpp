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
	m_range_min = DBL_MIN;

	m_axis_dir = axis_dir;

	m_valueadaptor = new SimpleAxisValueAdaptor();
}


Scale::~Scale()
{
	if(m_valueadaptor != NULL)
		delete m_valueadaptor;
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

//	Validate();
}

void Scale::SetRange(double range)
{
	m_range = range;

//	Validate();
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

void Scale::SetValueAdaptor(AxisValueAdaptor *valueadaptor)
{
	if (m_valueadaptor != NULL)
		delete m_valueadaptor;

	m_valueadaptor = valueadaptor;
	if (valueadaptor != nullptr)
		m_valueadaptor->SetLimitsForScale(this);
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

void plot::Scale::_addseries(Series * series)
{
	m_serie.push_back(series);
	_refresh_plot_list();
}

void plot::Scale::_removeseries(Series * series)
{
	m_serie.erase(std::remove(m_serie.begin(), m_serie.end(), series), m_serie.end());
	_refresh_plot_list();
}

void plot::Scale::_refresh_plot_list()
{
	m_subplots.clear();
	for (auto series : m_serie)
		if (series->_getowner() != nullptr)
			m_subplots.push_back(series->_getowner());
	std::sort(m_subplots.begin(), m_subplots.end());
	m_subplots.erase(std::unique(m_subplots.begin(), m_subplots.end()), m_subplots.end());
}
