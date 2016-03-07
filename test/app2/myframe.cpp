#include <wx/textdlg.h>
#include <wx/tooltip.h>
#include <float.h>

#include "myframe.h"

#include "Series.h"

#include "wx/PlotPane.h"
#include "wx/wxScaleWidget.h"
#include "wx/wxRenderer.h"
#include "wx/wxPlot.h"

BEGIN_EVENT_TABLE(MyFrame, MainFrame)

END_EVENT_TABLE()


MyFrame::MyFrame():MainFrame(NULL)
{
	plot::wxPlot *plotwnd;
	plotwnd = new plot::wxPlot(m_panel);
	bSizer_panel->Add(plotwnd, 1, wxEXPAND);

	auto p1 = plotwnd->CreateSubplot();
	auto p2 = plotwnd->CreateSubplot();
	auto p3 = plotwnd->CreateSubplot();

	auto leftscale = new plot::wxScaleWidget(p1, AXIS_Y, wxVERTICAL);
	//auto rightscale = new plot::wxScaleWidget(p1, AXIS_Y, wxVERTICAL);
	p1->bSizer_left->Add(leftscale, 0, wxEXPAND);
	// p1->bSizer_left->Layout();
	//p1->AddLeftPane(leftscale);
	int datasize = 1000;
	plot::Series *ser1, *ser2;
	ser1 = new plot::Series(datasize, "series1");
	ser1->SetRenderer(new plot::wxRendererTyped<double, double>());
	ser1->SetXScale(plotwnd->GetScaleWidget()->GetScale());
	ser1->SetYScale(leftscale->GetScale());
	fillseries(ser1);
	
	ser2 = new plot::Series(datasize, "series2");
	ser2->SetRenderer(new plot::wxRendererTyped<double, double>());
	ser2->SetXScale(plotwnd->GetScaleWidget()->GetScale());
//	ser2->SetYScale(rightscale->GetScale());
	fillseries(ser2);

	p1->AddSeries(ser1);
	p1->AddSeries(ser2);
}


MyFrame::~MyFrame()
{
}

void MyFrame::fillseries(plot::Series * series)
{
	size_t size = series->GetDataSize();
	auto xdata = series->GetXData();
	auto ydata = series->GetYData();

	for (size_t indx = 0; indx < size; indx++)
	{
		xdata[indx] = indx;
		ydata[indx] = sin((double)indx / (double)size * M_PI * 4) * 10.;

	}
}

