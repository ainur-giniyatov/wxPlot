#include <algorithm>

#include "Box.h"
#include "Plot.h"

using namespace plot;

const int Box::s_snapdistance = 10;

Box::Box():m_rect(0, 0, 50, 50)
{
	m_flags = MOVEABLE | RESIZEABLE ;
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

void Box::_ownersize(int w, int h)
{
	if (m_flags & EXPANDHOR)
	{
		m_rect.left = 0;
		m_rect.right = w - 1;
	}

	if (m_flags & EXPANDVERT)
	{
		m_rect.top = 0;
		m_rect.bottom = h - 1;
	}
}

plot::TitleBox::TitleBox()
{
	m_title = nullptr;
	m_flags = MOVEABLE;
}

plot::TitleBox::~TitleBox()
{
	if (m_title != nullptr)
		free((void *)m_title);
}

void plot::TitleBox::_setowner(Plot * plot)
{
	Box::_setowner(plot);
	m_title = (char *)malloc(strlen(plot->GetPlotName()) + 1);
	strcpy((char *)m_title, plot->GetPlotName());
}
