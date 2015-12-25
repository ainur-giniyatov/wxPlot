#include "Box.h"

Box::Box(Plot * owner, SpaceND *space)
{
	m_owner = owner;

	m_bound_space = space;

	m_rel_x = 0.5f;
	m_rel_y = 0.5f;
	m_x = 0;
	m_y = 0;
	m_width = 20;
	m_height = 20;

	m_isdragging = false;
	m_flag_dragdir = DRAGDIR_ALL;

	m_relpointalign_ver= RELPA_MIDDLE;
	m_relpointalign_hor= RELPA_MIDDLE;

	m_owner->AddBox(this);
}

Box::~Box()
{
}

void Box::Render(wxGraphicsContext * gc)
{
	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);
	gc->DrawRectangle(m_x, m_y, m_width, m_height);
}

bool Box::CheckIsMouseInside(int mx, int my)
{
	return ( ( mx > m_x && mx < (m_x + m_width) ) && ( my > m_y && my < (m_y + m_height) ) ) || m_isdragging;
}

void Box::MouseMove(int mx, int my)
{
	DPRINTF("Box::MouseMove\n");
	if (m_isdragging)
	{
		int pw, ph;
		m_owner->GetSize(&pw, &ph);
		if (m_flag_dragdir & DRAGDIR_HOR)
		{
			m_x = mx - m_drag_dx;
			switch (m_relpointalign_hor)
			{
			case Box::RELPA_CLOSER:
				m_rel_x = (double)m_x / (double)pw;
				break;
			case Box::RELPA_MIDDLE:
				m_rel_x = ((double)m_x + m_width / 2.) / (double)pw;
				break;
			case Box::RELPA_FURTHER:
				m_rel_x = ((double)m_x + m_width)/ (double)pw;
				break;
			default:
				assert(0);
				break;
			}

		}
		if (m_flag_dragdir & DRAGDIR_VER)
		{
			m_y = my - m_drag_dy;
			switch (m_relpointalign_ver)
			{
			case Box::RELPA_CLOSER:
				m_rel_y = (double)m_y / (double)ph;
				break;
			case Box::RELPA_MIDDLE:
				m_rel_y = ((double)m_y + m_height / 2.) / (double)ph;
				break;
			case Box::RELPA_FURTHER:
				m_rel_y = ((double)m_y + m_height) / (double)ph;
				break;
			default:
				assert(0);
				break;
			}
		}

		m_owner->RedrawPlot();
	}
}

void Box::MouseLeftDown(int mx, int my)
{
	DPRINTF("Box::MouseLeftDown\n");
	m_isdragging = true;
	m_drag_dx = mx - m_x;
	m_drag_dy = my - m_y;
}

void Box::MouseLeftUp(int mx, int my)
{
	DPRINTF("Box::MouseLeftUp\n");
	m_isdragging = false;
}

void Box::Sizing()
{
	int pw, ph;
	m_owner->GetSize(&pw, &ph);

	switch (m_relpointalign_hor) 
	{
	case RELPA_CLOSER:
		m_x = pw * m_rel_x;
		break;
	case RELPA_MIDDLE:
		m_x = pw * m_rel_x - m_width / 2.;
		break;
	case RELPA_FURTHER:
		m_x = pw * m_rel_x - m_width;
		break;
	default:
		assert(0);
	}

	switch (m_relpointalign_ver)
	{
	case RELPA_CLOSER:
		m_y = ph * m_rel_y;
		break;
	case RELPA_MIDDLE:
		m_y = ph * m_rel_y - m_height / 2.;
		break;
	case RELPA_FURTHER:
		m_y = ph * m_rel_y - m_height;
		break;
	default:
		assert(0);
	}

}