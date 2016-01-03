#include <wx/textdlg.h>
#include <float.h>

#include "myframe.h"

#include "Series.h"
#include "Data.h"
#include "Area.h"
#include "wx/wxBox.h"
#include "wx/wxScaleBox.h"
#include "wx/wxGrid.h"
#include "wx/wxRenderer.h"
#include "wx/colorbase.h"

const int MyFrame::ID_MENUPLOT_ADDLEGEND = wxNewId();
const int MyFrame::ID_MENUPLOT_ADDVERTICALSCALE = wxNewId();

BEGIN_EVENT_TABLE(MyFrame, MainFrame)
EVT_MOUSEWHEEL(MyFrame::OnMouseWheel)
EVT_MENU(MyFrame::ID_MENUPLOT_ADDLEGEND, MyFrame::OnMenu_AddLegend)
EVT_MENU(MyFrame::ID_MENUPLOT_ADDVERTICALSCALE, MyFrame::OnMenu_AddVerticalScale)
END_EVENT_TABLE()

static int s_plc = 1;
MyFrame::MyFrame():MainFrame(NULL)
{

	//1st page
	m_chartwindow = new plot::wxChartWindow(m_panel2, wxVERTICAL);
	bSizer3->Add(m_chartwindow, 1, wxEXPAND);
	m_panel2->Layout();

	m_wxPlotWindow = NULL;
	m_series = NULL;
	m_data = NULL;


//2nd page

	m_2ndpageplotwindow = new plot::wxPlotWindow(m_panel6);
	m_2ndpageplotwindow->SetLeftButtonAction(LBA_PAN);
	bSizer7->Add(m_2ndpageplotwindow, 1, wxEXPAND);
	m_panel_page2->Layout();

	m_2ndlegendsbox = new plot::wxLegendsBox(m_2ndpageplotwindow);

	m_2ndpagearea = new plot::Area(2);

	int datasize = 10000;
	plot::DataTyped<double> *xdata = new plot::DataTyped<double>(datasize);
	plot::DataTyped<double> *ydata = new plot::DataTyped<double>(datasize);

	double sp = 300.;
	double vel = 0., acc = 0.;
	double v = 0.;
	for (int indx = 0; indx < datasize; indx++)
	{
		xdata->SetValue(indx, indx);
		ydata->SetValue(v, indx);
		acc = (sp - v) / 10000.;
		vel += acc / 10.;
		vel -= 0.0001;
		v += vel;
	}

	m_2ndpageydata = ydata;
	m_2ndpagexdata = xdata;

	m_2ndpageseries = new plot::Series(2, "temperature");
	m_2ndpageseries->SetData(xdata, AXIS_X);
	m_2ndpageseries->SetData(ydata, AXIS_Y);

	plot::Renderer *renderer = new plot::wxRendererTyped<double, double>();
	m_2ndpageseries->SetRenderer(renderer);
	renderer->SetMarkerStyle(MARKER_CIRCLE);
	renderer->SetLineColourIndex(2);
	renderer->SetLineThickness(4);

	m_2ndpagearea->AddSeries(m_2ndpageseries);

	//
	datasize = 200;
	xdata = new plot::DataTyped<double>(datasize);
	ydata = new plot::DataTyped<double>(datasize);

	for (int indx = 0; indx < datasize; indx++)
	{
		xdata->SetValue(indx / 200. * 10000, indx);
		ydata->SetValue(sin(indx / 200. * 6.) * 400., indx);
	}

	plot::Series *series = new plot::Series(2, "channel 1");
	series->SetData(xdata, AXIS_X);
	series->SetData(ydata, AXIS_Y);

	renderer = new plot::wxRendererTyped<double, double>();
	series->SetRenderer(renderer);
	renderer->SetMarkerStyle(MARKER_SQUARE);
	renderer->SetMarkerColourIndex(6);
	renderer->SetLineColourIndex(3);
	renderer->SetLineThickness(1);

	m_2ndpageplotwindow->AddArea(m_2ndpagearea);
	m_2ndpagearea->AddSeries(series);

	//

	//m_2ndlegendsbox->AddSeries(m_2ndpageseries);
	//m_2ndlegendsbox->AddSeries(series);

	plot::wxScaleBox *scalebox;
	scalebox = new plot::wxScaleBox(m_2ndpageplotwindow, DIR_VER);
	scalebox->AddAxis(m_2ndpagearea->GetAxis(AXIS_Y));
	scalebox->SetRangeLimits(DBL_MAX, DBL_MIN);
	scalebox->SetValueAdaptor(new plot::SimpleAxisValueAdaptor<double>());

	scalebox = new plot::wxScaleBox(m_2ndpageplotwindow, DIR_HOR);
	scalebox->AddAxis(m_2ndpagearea->GetAxis(AXIS_X));
	scalebox->SetRangeLimits(DBL_MAX, DBL_MIN);
	scalebox->SetValueAdaptor(new plot::SimpleAxisValueAdaptor<double>());

	plot::Grid *grid;
	grid = new plot::wxGrid(m_2ndpagearea);

}


MyFrame::~MyFrame()
{
}

void MyFrame::m_menuItem_ExitOnMenuSelection(wxCommandEvent & event)
{
	Close();
}

void MyFrame::m_button1OnButtonClick(wxCommandEvent & event)
{
	int datasize = 5000;
	if (m_wxPlotWindow == NULL)
	{
		wxBell();
		return;
	}
	plot::DataTyped<int> *xdata = new plot::DataTyped<int>(datasize, "TIME");
	plot::DataTyped<int> *ydata = new plot::DataTyped<int>(datasize, "DATA");

	for (int i = 0; i < datasize; i++)
	{
		xdata->SetValue(i , i);
		ydata->SetValue((int)(sin((double)i / (double)datasize * 10) * 30.) + 50, i);
	}

	plot::Series *series = new plot::Series(2, "SERIES");


	plot::Area *area = m_wxPlotWindow->GetArea(0);



	series->SetData(xdata, AXIS_X);
	series->SetData(ydata, AXIS_Y);



	//Renderer2D *renderer2d;
	//renderer2d = new Renderer2DTyped<int, int>();

	series->SetRenderer(new plot::wxRendererTyped<int, int>());

//	TimeAxisValueAdaptor<int> *tvadap = new TimeAxisValueAdaptor<int>();
//	xdata->SetValueAdaptor(tvadap);
	area->AddSeries(series);




	fill_series_choices();
}

void MyFrame::m_button2OnButtonClick(wxCommandEvent & event)
{
	if (m_wxPlotWindow == NULL)
	{
		wxBell();
		return;
	}

	int datasize = 500;
	plot::DataTyped<double> *xdata = new plot::DataTyped<double>(datasize, "FTIME");
	plot::DataTyped<double> *ydata = new plot::DataTyped<double>(datasize, "FDATA");

	double shft = (rand() % 700);
	double phshft = (rand() % 10);
	double ampshft = (rand() % 100) + 30;
	for (int i = 0; i < datasize; i++)
	{
		xdata->SetValue((double)i / 2., i);
		ydata->SetValue(sin((double)i / (double)datasize * (37. + rand() % 2) + phshft) * ampshft + shft, i);
	}

	plot::Series *series = new plot::Series(2, "FSERIES");

	plot::Area *area = m_wxPlotWindow->GetArea(0);

	area->AddSeries(series);

	series->SetData(xdata, AXIS_X);
	series->SetData(ydata, AXIS_Y);



	//Renderer2D *renderer2d;
	//renderer2d = new Renderer2DTyped<double, double>();
	plot::wxRendererTyped<double, double> *renderer;
	renderer = new plot::wxRendererTyped<double, double>();
	renderer->SetLineColourIndex(rand() % COLOR_BASE_COUNT);
	renderer->SetLineThickness(rand() % 3 + 1);
	renderer->SetMarkerSize(rand() % 4 + 2);
	renderer->SetMarkerColourIndex(rand() % COLOR_BASE_COUNT);
	switch (rand() % 5)
	{
	case 0:
		renderer->SetMarkerStyle(MARKER_CIRCLE);
		break;
	case 1:
		renderer->SetMarkerStyle(MARKER_ROMB);
		break;
	case 2:
		renderer->SetMarkerStyle(MARKER_SQUARE);
		break;
	case 3:
		renderer->SetMarkerStyle(MARKER_CROSS);
		break;
	case 4:
		renderer->SetMarkerStyle(MARKER_PLUS);
		break;
	default:;
		assert(0);
	}
	series->SetRenderer(renderer);

	wxTextEntryDialog dlg(this, "Series name");
	if (dlg.ShowModal() == wxID_OK)
	{
		series->SetSeriesName(static_cast<const char *>(dlg.GetValue()));
	}

	fill_series_choices();
}

void MyFrame::m_button3OnButtonClick(wxCommandEvent & event)
{
	/*int datasize = 500;
	DataTyped<float> *data = new DataTyped<float>(datasize, "FME");


	for (int i = 0; i < datasize; i++)
	{
		data->SetValue(sin((double)i / (double)datasize * (27.)) * 30. + 60 + rand() % 130, i);
	}

	Series1D *series1d = new Series1D("FSIES");

	SpaceND *space = m_wxPlotWindow->GetSpace(0);

	space->AddSeries(series1d, true);

	series1d->SetData(data);


	Renderer1D *renderer1d;
	renderer1d = new Renderer1DTyped<float>();

	series1d->SetRenderer(renderer1d);

    TimeValueAdaptor<float> *tvadaptor = new TimeValueAdaptor<float>();
	data->SetValueAdaptor(tvadaptor);*/
}


void MyFrame::m_button_newplotOnButtonClick(wxCommandEvent & event)
{
	plot::wxPlotWindow *plotwindow;
	plotwindow= m_chartwindow->CreatewxPlotWindow();

	plot::wxLegendsBox *legendsbox = new plot::wxLegendsBox(plotwindow);
	wxTextEntryDialog dlg(this, "Plot name");

	if (dlg.ShowModal() == wxID_OK)
	{
		plotwindow->SetPlotName(static_cast<const char *>(dlg.GetValue()));
	}

	plot::Area *area;
	area = new plot::Area(2);
	plotwindow->AddArea(area);

	m_chartwindow->GetScaleWindow()->AddAxis(area->GetAxis(AXIS_X));
//	wxPlotWindow->GetYScale()->AddAxis(space->GetAxis(AXIS_Y));

	//ScaleWidget *scalewidget;
	//scalewidget = new ScaleWidget(wxPlotWindow, wxVERTICAL);
	plot::wxScaleBox *scalebox = new plot::wxScaleBox(plotwindow, DIR_VER);

	plot::Grid *grid;
	grid = new plot::wxGrid(area);

	scalebox->AddAxis(area->GetAxis(AXIS_Y));
	scalebox->SetValueAdaptor(new plot::SimpleAxisValueAdaptor<double>());

	plotwindow->RedrawPlot();
	//LegendsWidget *legendswidget;

	//legendswidget = new LegendsWidget(wxPlotWindow);
	//legendswidget->SetAnchorPosition(1., 0.5);
	//legendswidget->SetAnchorDelta(15, 0);

	fill_plot_choices();

	wxMenu *plotsubmenu;
	plotsubmenu = new wxMenu();

	plotwindow->GetMenu().AppendSubMenu(plotsubmenu, "More");

	plotsubmenu->Append(ID_MENUPLOT_ADDLEGEND, "Add legends");
	plotsubmenu->Append(ID_MENUPLOT_ADDVERTICALSCALE, "Add vertical scale");
}

void MyFrame::m_choice_plotsOnChoice(wxCommandEvent & event)
{
	m_wxPlotWindow = (plot::wxPlotWindow *)event.GetClientData();
	plot::Area *area= m_wxPlotWindow->GetArea(0);
	m_checkBox_connecttoscale->SetValue(area->GetAxis(AXIS_X)->GetCommonScale() != NULL);

	fill_series_choices();

}

void MyFrame::m_menuItem_timeOnMenuSelection(wxCommandEvent & event)
{
	plot::TimeAxisValueAdaptor<double> *tvadaptor = new plot::TimeAxisValueAdaptor<double>();
	m_chartwindow->GetScaleWindow()->SetValueAdaptor(tvadaptor);
}

void MyFrame::m_menuItem_secsOnMenuSelection(wxCommandEvent & event)
{
	//ValueAdaptor<double> *tvadaptor = new SecsValueAdaptor<double>();
	//m_chartwindow->GetScaleWindow()->SetValueAdaptor(tvadaptor);
}

void MyFrame::m_menuItem_nullOnMenuSelection(wxCommandEvent & event)
{
	m_chartwindow->GetScaleWindow()->SetValueAdaptor(NULL);
}

void MyFrame::m_checkBox_connecttoscaleOnCheckBox(wxCommandEvent & event)
{
	if(m_choice_plots->GetSelection() == wxNOT_FOUND)
		return;

	wxASSERT(m_wxPlotWindow != NULL);

	plot::ScaleWindow *scalewindow = m_chartwindow->GetScaleWindow();
	plot::Axis *axis;
	axis = m_wxPlotWindow->GetArea(0)->GetAxis(AXIS_X);
	wxASSERT(axis != NULL);
	if (event.IsChecked())
	{
		scalewindow->AddAxis(axis);
	}
	else
	{
		scalewindow->RemoveAxis(axis);
	}

}

void MyFrame::m_choice_seriesOnChoice(wxCommandEvent & event)
{
	m_series = (plot::Series *)event.GetClientData();
	fill_datas_choices();
}

void MyFrame::
m_choice_dataOnChoice(wxCommandEvent & event)
{
	m_data = (plot::DataNoType *)event.GetClientData();
}

void MyFrame::m_button_FitOnButtonClick(wxCommandEvent & event)
{
	if (m_data != NULL)
	{
		//m_data->Fit();
		return;
	}
	if (m_series != NULL)
	{
		m_series->Fit();
		return;
	}
	if (m_wxPlotWindow != NULL)
	{
		m_wxPlotWindow->FitPlot();
		return;
	}
}

void MyFrame::m_button_RenameOnButtonClick(wxCommandEvent & event)
{
}

void MyFrame::m_button_DeleteOnButtonClick(wxCommandEvent & event)
{
	if (m_data != NULL)
	{
		delete m_data;
		m_data = NULL;
		m_choice_data->Clear();
		return;
	}

	if (m_series != NULL)
	{
		delete m_series;
		m_series = NULL;
		m_choice_series->Clear();
		return;
	}
	if (m_wxPlotWindow != NULL)
	{
		m_chartwindow->DeletePlot(m_wxPlotWindow);
		m_wxPlotWindow = NULL;
		m_choice_plots->Clear();
		return;
	}
}

void MyFrame::m_button_dataupdatedOnButtonClick(wxCommandEvent & event)
{
	//m_2ndpageydata->DataUpdated();
}

void MyFrame::m_button_seriesupdateOnButtonClick(wxCommandEvent & event)
{
	m_2ndpageseries->SeriesUpdated();
}

void MyFrame::m_button_spaceupdateOnButtonClick(wxCommandEvent & event)
{
	//m_2ndpagearea->SpaceUpdated();
}

void MyFrame::m_menuItem_panOnMenuSelection(wxCommandEvent & event)
{
	m_chartwindow->SetLeftButtonAction(LBA_PAN);
}

void MyFrame::m_menuItem_zoomOnMenuSelection(wxCommandEvent & event)
{
	m_chartwindow->SetLeftButtonAction(LBA_ZOOMSELECT);
}

void MyFrame::m_button_add_boxOnButtonClick(wxCommandEvent & event)
{
	plot::wxBox *box;
	box = new plot::wxBox(m_2ndpageplotwindow);
}

void MyFrame::OnMouseWheel(wxMouseEvent & event)
{
	DPRINTF("MyFrame OnMouseWheel\n");
	wxWindow *wnd;
	wnd = wxFindWindowAtPoint(wxGetMousePosition());
	if (wnd != NULL)
	{
		if (!wnd->GetName().compare("plot") || !wnd->GetName().compare("scalewindow"))
		{
			wxPoint mp(wnd->ScreenToClient(wxGetMousePosition()));
			event.SetPosition(mp);
			wnd->ProcessWindowEvent(event);
		}
	}
}

void MyFrame::OnMenu_AddLegend(wxCommandEvent & event)
{
	DPRINTF("MyFrame::OnMenu_AddLegend\n");
	plot::wxPlotWindow *plotwindow;
	wxMenu *menu;
	menu = (wxMenu *)event.GetEventObject();
	plotwindow = (plot::wxPlotWindow *)menu->GetInvokingWindow();

	//LegendsWidget *legendswidget;
	//legendswidget = new LegendsWidget(wxPlotWindow);
	//legendswidget->SetAnchorPosition(1, 0.5);
	//legendswidget->SetAnchorDelta(15, 0);
}

void MyFrame::OnMenu_AddVerticalScale(wxCommandEvent & event)
{
	DPRINTF("MyFrame::OnMenu_AddVerticalScale\n");
	plot::wxPlotWindow *plotwindow;
	wxMenu *menu;
	menu = (wxMenu *)event.GetEventObject();
	plotwindow = (plot::wxPlotWindow *)menu->GetInvokingWindow();

	//ScaleWidget *scalewidget;
	//scalewidget = new ScaleWidget(wxPlotWindow, wxVERTICAL);
	//scalewidget->SetValueAdaptor(new SimpleAxisValueAdaptor<double>());
	//scalewidget->AddAxis(wxPlotWindow->GetSpace(0)->GetAxis(AXIS_Y));
}

void MyFrame::fill_plot_choices()
{
	m_choice_plots->Clear();
	m_choice_series->Clear();
	m_choice_data->Clear();
	m_wxPlotWindow = NULL;
	m_series = NULL;
	m_data = NULL;

	for (auto plot : m_chartwindow->GetPlotContainer()->GetChildren())
	{
		if (plot->GetName().Cmp("plot"))
			continue;
		m_choice_plots->Append(((plot::wxPlotWindow *)plot)->GetPlotName(), plot);
	}
}

void MyFrame::fill_series_choices()
{

	m_choice_series->Clear();
	m_choice_data->Clear();
	m_data = NULL;
	m_series = NULL;
	if (m_wxPlotWindow == NULL)
		return;

	plot::Area *area = m_wxPlotWindow->GetArea(0);

	for (auto series : area->GetSerie())
	{
		m_choice_series->Append(wxString(series->GetSeriesName()), series);
	}
}

void MyFrame::fill_datas_choices()
{
	m_choice_data->Clear();
	m_data = NULL;
	if (m_series == NULL)
		return;

	for (int indx = 0; m_series->GetData((AXIS_DIR)indx) != nullptr; indx++)
	{
		plot::DataNoType *data;
		data = m_series->GetData((AXIS_DIR)indx);
		if(data != NULL)
			m_choice_data->Append(data->GetDataName(), data);
	}
}

