//#include "stdafx.h"
#include "Axis.h"
//#include "Scale.h"

Axis::Axis()
{
	DPRINTF("Axis ctor\n");
	m_offset = 0.;
	m_range = 500.0;
	m_owner_space = NULL;
	m_commonscale = NULL;

}


Axis::~Axis()
{
	DPRINTF("Axis dtor\n");
	if (m_commonscale != NULL)
		m_commonscale->RemoveAxis(this);
}

void Axis::AxisUpdated()
{
	wxASSERT(m_owner_space != NULL);
	DPRINTF("AxisUpdated\n");
	//if (m_commonscale != NULL)
	//{
	//	m_commonscale->SetRange(m_range);
	//	m_commonscale->SetOffset(m_offset);
	//	m_commonscale->ScaleUpdated(this);
	//}/*else
	//	if (m_owner_space != NULL)
	
	m_owner_space->SpaceUpdated();

}

void Axis::SetOffset(double offset)
{
	m_offset = offset;
}

void Axis::SetRange(double range)
{
	if (m_commonscale != NULL)
	{
		if (range < m_commonscale->GetRangeMax())
			if (range > m_commonscale->GetRangeMin())
				m_range = range;
		return;
	}
	else
		m_range = range;
}

void Axis::PropagateToCommonScale()
{
	if (m_commonscale != NULL)
	{
		m_commonscale->SetOffset(m_offset);
		m_commonscale->SetRange(m_range);

	}
}

void Axis::SetVisibleRange(double offs, double range, bool update)
{
	wxASSERT(range > 0);

	Axis *axis;

	SetOffset(offs - range / 10.);
	SetRange(range + range / 5.);

	PropagateToCommonScale();

	if(update)
		if (m_commonscale != NULL)
		{
			m_commonscale->RedrawDependantPlots();
			m_commonscale->ScaleRedraw();
		}
		else
			GetOwner()->GetOwner()->RedrawPlot();
}

