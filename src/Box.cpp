#include <assert.h>
#include <stdlib.h>
#include <algorithm>

#include "Box.h"

using namespace plot;

Box::Box(Plot * owner):PEventHandler()
{
	DPRINTF("Box ctor\n");
	m_owner = owner;
	
	
	m_ismoving = false;
	m_ismovable = true;
	m_isresizable = true;
	m_isresizing = false;
	m_snaptoborder = true;
	m_snaptocenter = true;
	m_snaptoeachother = true;
	m_ontop = false;
	m_flag_resonside = 0;

	m_flag_move_dir = DIR_ALL;

	m_flag_expand_dir = DIR_NONE;

	m_border_thickness = 1;
	m_snap_distance = 8;
	m_snap_offset = 5;
	m_sticky = true;
	m_sticked_to = STICKEDTO_NONE;

	m_rect = Rect<int>(0, 0, 30, 30);
	
	m_owner->AddBox(this);

	m_eventslist = m_owner->_GetEventsList();
}

Box::~Box()
{
	DPRINTF("Box dtor\n");
	
	
}



bool Box::CheckIsMouseInside(int mx, int my)
{
	return m_rect.IsInside(Point<int>(mx, my)) || m_ismoving || m_isresizing;
}

void Box::MouseMove(int mx, int my)
{
	DPRINTF("Box::MouseMove\n");

	Point<int> mp(mx, my);

	int pw, ph;
	m_owner->GetSize(&pw, &ph);


	if (m_ismovable && m_ismoving)
	{
		proceed_moving(mp);
		m_owner->RedrawPlot();
	}

	if (m_isresizable && m_isresizing)
	{
		proceed_resizing(mp);
		m_owner->RedrawPlot();
	}
}


void Box::MouseLeftDown(int mx, int my)
{
	DPRINTF("Box::MouseLeftDown\n");
	BringToFront();
	Point<int> mp(mx, my);//mouse pointer

	if (m_isresizable && !m_isresizing)
		start_resizing(mp);

	if (m_ismovable && !m_ismoving && !m_isresizing)
		start_moving(mp);

}

void Box::MouseLeftUp(int mx, int my)
{
	DPRINTF("Box::MouseLeftUp\n");

	if (m_ismovable && m_ismoving)
		end_moving();

	if (m_isresizable && m_isresizing)
		end_resizing();
}

void plot::Box::MouseRightDown(int mx, int my)
{
	DPRINTF("Box::MouseRightDown\n");
	//BringToFront();
}

void plot::Box::MouseRightUp(int mx, int my)
{
	DPRINTF("Box::MouseRightUp\n");
}

void Box::Sizing()
{
	int pw, ph;
	m_owner->GetSize(&pw, &ph);

	if (m_flag_expand_dir & DIR_VER)
	{
		m_rect.top = 0;
		m_rect.bottom = ph - 1;
	}

	if (m_flag_expand_dir & DIR_HOR)
	{
		m_rect.left = 0;
		m_rect.right = pw - 1;
	}

	if (m_sticky)
	{
		if (m_sticked_to & STICKEDTO_RIGHT)
			m_rect.SetRight(pw - 1 - m_snap_offset);

		if (m_sticked_to & STICKEDTO_HOR_CENTER)
			m_rect.SetCenterHor(pw / 2);

		if (m_sticked_to & STICKEDTO_BOTTOM)
			m_rect.SetBottom(ph - 1 - m_snap_offset);

		if (m_sticked_to & STICKEDTO_VER_CENTER)
			m_rect.SetCenterVer(ph / 2);


	}



}

bool Box::ismouseatpoint(const Point<int>& mouse_p, const Point<int>& p, int ar)
{
	return abs(mouse_p.x - p.x) < ar && abs(mouse_p.y - p.y) < ar;
}

void Box::BringToFront()
{
	auto iter_for_self = std::find(m_owner->m_boxes.begin(), m_owner->m_boxes.end(), this);
	assert(iter_for_self != m_owner->m_boxes.end());
	m_owner->m_boxes.erase(iter_for_self);
	m_owner->m_boxes.insert(m_owner->m_boxes.begin(), this);

}

void Box::start_moving(const Point<int>& mcoords)
{
	m_ismoving = true;
	m_start_move_mouse_coords = mcoords;
	m_start_move_initial_p1 = Point<int>(m_rect.left, m_rect.top);
}

void Box::proceed_moving(const Point<int> &mcoords)
{
	int pw, ph;
	m_owner->GetSize(&pw, &ph);
    Point<int> mcoords_l(mcoords);
	Point<int> new_pos(mcoords_l - m_start_move_mouse_coords + m_start_move_initial_p1);

	if (m_snaptoborder)
	{
		if (abs(new_pos.x - m_snap_offset) < m_snap_distance)
		{
			new_pos.x = m_snap_offset;
			m_sticked_to |= STICKEDTO_LEFT;
		}
		else
			m_sticked_to &= ~STICKEDTO_LEFT;

		if (abs(pw - new_pos.x - m_rect.Width() - m_snap_offset) < m_snap_distance)
		{
			new_pos.x = pw - m_rect.Width() - 1 - m_snap_offset;
			m_sticked_to |= STICKEDTO_RIGHT;
		}
		else
			m_sticked_to &= ~STICKEDTO_RIGHT;

		if (abs(new_pos.y - m_snap_offset) < m_snap_distance)
		{
			new_pos.y = m_snap_offset;
			m_sticked_to |= STICKEDTO_TOP;
		}
		else
			m_sticked_to &= ~STICKEDTO_TOP;

		if (abs(ph - new_pos.y - m_rect.Height() - m_snap_offset) < m_snap_distance)
		{
			new_pos.y = ph - m_rect.Height() - 1 - m_snap_offset;
			m_sticked_to |= STICKEDTO_BOTTOM;
		}
		else
			m_sticked_to &= ~STICKEDTO_BOTTOM;

	}

	if (m_snaptocenter)
	{
		if (abs(new_pos.x + (m_rect.Width() - pw) / 2) < m_snap_distance)
		{
			new_pos.x = (pw - m_rect.Width()) / 2;
			m_sticked_to |= STICKEDTO_HOR_CENTER;
		}
		else
			m_sticked_to &= ~STICKEDTO_HOR_CENTER;

		if (abs(new_pos.y + (m_rect.Height() - ph) / 2) < m_snap_distance)
		{
			new_pos.y = (ph - m_rect.Height()) / 2;
			m_sticked_to |= STICKEDTO_VER_CENTER;
		}
		else
			m_sticked_to &= ~STICKEDTO_VER_CENTER;

	}

	if ( (m_flag_expand_dir & DIR_VER) && (m_flag_move_dir & DIR_VER) )
		new_pos.y = m_start_move_initial_p1.y;

	if ((m_flag_expand_dir & DIR_HOR) && (m_flag_move_dir & DIR_HOR))
		new_pos.x = m_start_move_initial_p1.x;

	m_rect.MoveTo(new_pos);
}

void Box::end_moving()
{
	m_ismoving = false;
}

void Box::start_resizing(const Point<int>& mcoords)
{
	int offs = 3;

	m_flag_resonside = 0;

	if (abs(mcoords.x - m_rect.left) < offs && (mcoords.y > m_rect.top - offs ) && (mcoords.y < m_rect.bottom + offs) )
		m_flag_resonside |= RESONSIDE_LEFT;

	if (abs(mcoords.x - m_rect.right) < offs && (mcoords.y > m_rect.top - offs) && (mcoords.y < m_rect.bottom + offs))
		m_flag_resonside |= RESONSIDE_RIGHT;

	if (abs(mcoords.y - m_rect.top) < offs && (mcoords.x > m_rect.left - offs) && (mcoords.x < m_rect.right + offs))
		m_flag_resonside |= RESONSIDE_TOP;

	if (abs(mcoords.y - m_rect.bottom) < offs && (mcoords.x > m_rect.left - offs) && (mcoords.x < m_rect.right + offs))
		m_flag_resonside |= RESONSIDE_BOTTOM;


	if (m_flag_resonside != 0)
		m_isresizing = true;
}

void Box::proceed_resizing(const Point<int>& mcoords)
{
	if (m_flag_resonside & RESONSIDE_LEFT)
		m_rect.SetLeft(mcoords.x, false);

	if (m_flag_resonside & RESONSIDE_RIGHT)
		m_rect.SetRight(mcoords.x, false);

	if (m_flag_resonside & RESONSIDE_TOP)
		m_rect.SetTop(mcoords.y, false);

	if (m_flag_resonside & RESONSIDE_BOTTOM)
		m_rect.SetBottom(mcoords.y, false);
}

void Box::end_resizing()
{
	m_isresizing = false;
}

TitleBox::TitleBox(Plot * owner):Box(owner)
{
	m_isresizable = false;
	m_ismovable = false;

	m_flag_expand_dir = DIR_NONE;

	m_sticked_to = STICKEDTO_HOR_CENTER | STICKEDTO_TOP;

	m_ontop = true;

	
}

TitleBox::~TitleBox()
{
}

//void TitleBox::Render(wxGraphicsContext * gc)
//{
//	//Box::Render(gc);
//	gc->DrawText(wxString(m_owner->GetPlotName()), m_rect.left + 3, m_rect.top + 3);
//}

void TitleBox::Sizing()
{
	Box::Sizing();
}

plot::LegendsBox::LegendsBox(Plot * owner):Box(owner)
{

	Connect(PEventSeriesAdded::GetEventId(), (HandlerMethod)&LegendsBox::OnSeriesAdded);
	m_sticked_to = STICKEDTO_RIGHT | STICKEDTO_VER_CENTER;
	Sizing();
}

plot::LegendsBox::~LegendsBox()
{
	for (auto item : m_items)
		delete item;

	Disconnect(PEventSeriesAdded::GetEventId(), (HandlerMethod)&LegendsBox::OnSeriesAdded);
}

void plot::LegendsBox::AddSeries(Series * series)
{
	LegendItem *item = new LegendItem();
	item->m_series = series;
	m_items.push_back(item);
	Sizing();
}

void plot::LegendsBox::RemoveSeries(Series * series)
{
	for (auto item_iter = m_items.begin(); item_iter != m_items.end(); ++item_iter)
	{
		if ((*item_iter)->m_series == series)
		{
			delete *item_iter;
			m_items.erase(item_iter);
			break;
		}
	}
	Sizing();
}

void plot::LegendsBox::Sizing()
{
	Box::Sizing();
}


void plot::LegendsBox::OnSeriesAdded(PEvent & event)
{
	PEventSeriesAdded &evt = *((PEventSeriesAdded *)&event);
	if (evt.GetFlag())
		AddSeries(evt.GetSeries());
	else
		RemoveSeries(evt.GetSeries());
}

