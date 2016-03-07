#include "wx/wxSinglePlot.h"

plot::wxSinglePlot::wxSinglePlot(wxWindow * parent, int orientation):wxSinglePlot_fb(parent)
{
	m_orientation = orientation;
}

plot::wxSinglePlot::~wxSinglePlot()
{
}

void plot::wxSinglePlot::AddLeftScaleWidget(wxScaleWidget * scalewidget)
{
	bSizer_left->Add(scalewidget, 1, wxEXPAND | wxRIGHT, 5);
	fgSizer3->Layout();
}

void plot::wxSinglePlot::AddBottomScaleWidget(wxScaleWidget * scalewidget)
{
	bSizer_bottom->Add(scalewidget, 1, wxEXPAND | wxTOP, 5);
	fgSizer3->Layout();
}
