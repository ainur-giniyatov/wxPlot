#include "Axis.h"

#include <assert.h>

using namespace plot;

Axis::Axis()
{
	DPRINTF("Axis ctor\n");
	m_offset = 0.;
	m_range = 100.0;
	m_owner = NULL;
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
	assert(m_owner != NULL);
	DPRINTF("AxisUpdated\n");
	//if (m_commonscale != NULL)
	//{
	//	m_commonscale->SetRange(m_range);
	//	m_commonscale->SetOffset(m_offset);
	//	m_commonscale->ScaleUpdated(this);
	//}/*else
	//	if (m_owner_space != NULL)
	
//	m_owner_space->SpaceUpdated();

}

void Axis::SetOffset(double offset)
{
	if (m_commonscale != nullptr)
		m_commonscale->SetOffset(offset);
	else
		m_offset = offset;
}

void Axis::SetRange(double range)
{
	if (m_commonscale != NULL)
	{
		if (range < m_commonscale->GetRangeMax())
			if (range > m_commonscale->GetRangeMin())
			{
				m_commonscale->SetRange(range);
				//m_range = range;
			}
		return;
	}
	else
		m_range = range;
}

//void Axis::PropagateToCommonScale()
//{
//	if (m_commonscale != NULL)
//	{
//		m_commonscale->SetOffset(m_offset);
//		m_commonscale->SetRange(m_range);
//	}
//}

//void Axis::SetVisibleRange(double offs, double range, bool update)
//{
//	assert(range > 0);
//
//	Axis *axis;
//
//	SetOffset(offs - range / 10.);
//	SetRange(range + range / 5.);
//
//	//PropagateToCommonScale();
//
//	if(update)
//		if (m_commonscale != NULL)
//		{
//			m_commonscale->RedrawDependantPlots();
//			m_commonscale->ScaleRedraw();
//		}
//		else
//			GetOwner()->GetOwner()->RedrawPlot();
//}

