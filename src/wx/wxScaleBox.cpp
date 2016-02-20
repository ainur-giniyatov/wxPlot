#include <wx/graphics.h>

#include "wx\wxScaleBox.h"

using namespace plot;

plot::wxScaleBox::wxScaleBox(AXIS_DIR axis_dir):ScaleBox(axis_dir)
{

}

plot::wxScaleBox::~wxScaleBox()
{
}

static char s_buff[32];

void plot::wxScaleBox::Render(void *vgc)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)vgc;
	gc->SetPen(*wxRED_PEN);
	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);

	int pw, ph;
	m_owner->GetSize(&pw, &ph);
	Rect<int> rect;
	bool text_is_vert = false;
	if (m_owner->_get_orientation() == Plot::ORIENTATION_NORMAL)
	{
		if (m_axis_dir == AXIS_Y)
		{
			rect = m_rect;
			text_is_vert = true;
		}
		if (m_axis_dir == AXIS_X)
		{
			rect.top = m_rect.left;
			rect.bottom = m_rect.right;
			rect.left = ph - m_rect.bottom;
			rect.right = ph - m_rect.top;
			text_is_vert = false;
		}
	}
	if (m_owner->_get_orientation() == Plot::ORIENTATION_ROTATED)
	{
		if (m_axis_dir == AXIS_Y)
		{
			rect.top = m_rect.left;
			rect.left = ph - m_rect.bottom;
			rect.bottom = m_rect.right;
			rect.right = ph - m_rect.top;
			text_is_vert = false;
		}
		if (m_axis_dir == AXIS_X)
		{
			rect = m_rect;
			text_is_vert = true;
		}
	}

	AxisValueAdaptor<double> *m_valueadaptor;
	m_valueadaptor = GetValueAdaptor();
	if (m_valueadaptor == NULL)
		return;


	wxString text;
	wxDouble fh, fw;

	int i;
	bool isbold;

	m_valueadaptor->InitState(m_offset, m_range, 15. / (double)rect.Height());
	gc->SetPen(*wxBLACK_PEN);
	gc->DrawRectangle(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());
	wxGraphicsBrush gbrush = gc->CreateBrush(*wxWHITE_BRUSH);

	while (m_valueadaptor->Step())
	{
		double ticker = m_valueadaptor->GetTicker();
		int tick_len;
		i = (ticker) / m_range * rect.Height();
		if (m_axis_dir == AXIS_Y && m_owner->_get_orientation() == Plot::ORIENTATION_NORMAL)
			i = rect.Height() - i;
		
			if (i < 0)
			continue;
		if (i > rect.Height())
			break;
		
		tick_len = 5.;


		m_valueadaptor->ValToStr(s_buff, 20);
		text = wxString::Format(" %s ", s_buff);

		gc->GetTextExtent(text, &fw, &fh);
		wxDouble align_offset = 0;

		//if (!(m_orient & DIR_HOR) && (m_sticked_to & STICKEDTO_RIGHT))
		//	align_offset = fw - 7;

		//if ((m_orient & DIR_HOR) && (m_sticked_to & STICKEDTO_BOTTOM))
			align_offset = fw ;

//		if (m_orient & DIR_HOR)
//			gc->DrawText(text, x + fh / 2 + 3, m_rect.top + 7 - align_offset, M_PI / 2. * 3., gbrush);
	//	else
			if(text_is_vert)
				gc->DrawText(text, m_rect.right - align_offset, i - fh / 2., gbrush);
			else
				gc->DrawText(text, i - fh / 2., m_rect.bottom - align_offset, M_PI / 2. * 3., gbrush);

	}



}
