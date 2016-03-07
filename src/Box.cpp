#include <algorithm>
#include <string.h>

#include "Box.h"
#include "SubPlot.h"

using namespace plot;

const int Box::s_snapdistance = 10;

Box::Box(int flags):m_rect(0, 0, 50, 50)
{
	m_flags = flags;
	m_border_thickness = 5;
	m_owner = nullptr;
	m_stickbox[0] = nullptr;
	m_stickbox[1] = nullptr;
	m_stickbox[2] = nullptr;
	m_stickbox[3] = nullptr;
}

Box::~Box()
{
}

void Box::_ownersize(const Size<int> &ownersize)
{

	if (m_flags & EXPANDHOR)
	{
		m_rect.left = 0;
		m_rect.right = ownersize.w;
	}

	if (m_flags & EXPANDVERT)
	{
		m_rect.top = ownersize.h;
		m_rect.bottom = 0;
	}
}

plot::TitleBox::TitleBox(int flags): Box(flags)
{
	m_title = nullptr;

}

plot::TitleBox::~TitleBox()
{
	if (m_title != nullptr)
		free((void *)m_title);
}

void plot::TitleBox::_setowner(Subplot * subplot)
{
	Box::_setowner(subplot);
	m_title = (char *)malloc(strlen(subplot->GetSubplotName()) + 1);
	strcpy((char *)m_title, subplot->GetSubplotName());
}
