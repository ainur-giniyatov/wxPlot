#include "ScaleBox.h"

using namespace plot;

plot::ScaleBox::ScaleBox(AXIS_DIR axis_dir):Scale(axis_dir)
{
	m_flags = MOVEABLE;
	
}

plot::ScaleBox::~ScaleBox()
{
}

void plot::ScaleBox::_ownersize(int w, int h)
{
	Box::_ownersize(w, h);
	if (m_owner->_get_orientation() == Plot::ORIENTATION_NORMAL)
	{
		if (m_axis_dir == AXIS_Y)
			m_flags = MOVEABLE | EXPANDVERT;
		if (m_axis_dir == AXIS_X)
			m_flags = MOVEABLE | EXPANDHOR;
	}

	if (m_owner->_get_orientation() == Plot::ORIENTATION_ROTATED)
	{
		if (m_axis_dir == AXIS_Y)
			m_flags = MOVEABLE | EXPANDHOR;
		if (m_axis_dir == AXIS_X)
			m_flags = MOVEABLE | EXPANDVERT;
	}

}
