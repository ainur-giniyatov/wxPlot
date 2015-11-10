#include "myframe.h"

#include "Series.h"
#include "Data.h"
#include "Space.h"
#include <wx/textdlg.h>

BEGIN_EVENT_TABLE(MyFrame, MainFrame)
EVT_MOUSEWHEEL(MyFrame::OnMouseWheel)
END_EVENT_TABLE()

static int s_plc = 1;
MyFrame::MyFrame():MainFrame(NULL)
{
	m_chartwindow = new ChartWindow(m_panel2, wxVERTICAL);
	bSizer3->Add(m_chartwindow, 1, wxEXPAND);

	//m_plotwindow = m_chartwindow->CreatePlotWindow();
	//m_choice_plots->Append(wxString::Format("plot %i", s_plc++), m_plotwindow);
	//m_choice_plots->SetSelection(m_choice_plots->GetCount() - 1);
	//SpaceND *space;
	//space = new SpaceND(2);
	//m_plotwindow->AddSpace(space);

	//m_chartwindow->GetScaleWindow()->AddAxis(space->GetAxis(AXIS_X));

	m_plotwindow = NULL;
	m_series = NULL;
	m_data = NULL;
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
	int datasize = 500;
	if (m_plotwindow == NULL)
	{
		wxBell();
		return;
	}
	DataTyped<int> *xdata = new DataTyped<int>(AXIS_X, datasize, "TIME");
	DataTyped<int> *ydata = new DataTyped<int>(AXIS_Y, datasize, "DATA");

	for (int i = 0; i < datasize; i++)
	{
		xdata->SetValue(i + 1447034055, i);
		ydata->SetValue((int)(sin((double)i / (double)datasize * 10) * 30.) + 50, i);
	}

	SeriesND *series = new SeriesND((size_t)2, (char *)"SERIES");


	SpaceND *space = m_plotwindow->GetSpace(0);


	space->AddSeries(series);

	series->SetNData(xdata, AXIS_X, false);
	series->SetNData(ydata, AXIS_Y, false);



	Renderer2D *renderer2d;
	renderer2d = new Renderer2DTyped<int, int>();

	series->SetRenderer(renderer2d);

	TimeAxisValueAdaptor<int> *tvadap = new TimeAxisValueAdaptor<int>();
	xdata->SetValueAdaptor(tvadap);

	fill_series_choices();
}

void MyFrame::m_button2OnButtonClick(wxCommandEvent & event)
{
	if (m_plotwindow == NULL)
	{
		wxBell();
		return;
	}

	int datasize = 500;
	DataTyped<float> *xdata = new DataTyped<float>(AXIS_X, datasize, "FTIME");
	DataTyped<float> *ydata = new DataTyped<float>(AXIS_Y, datasize, "FDATA");

	for (int i = 0; i < datasize; i++)
	{
		xdata->SetValue((float)i / 3., i);
		ydata->SetValue(sin((double)i / (double)datasize * (37. + rand() % 2) ) * 30. + 60 + rand() % 130, i);
	}

	SeriesND *series = new SeriesND((size_t)2, (char *)"FSERIES");

	SpaceND *space = m_plotwindow->GetSpace(0);

	space->AddSeries(series, true);

	series->SetNData(xdata, AXIS_X);
	series->SetNData(ydata, AXIS_Y);

	

	Renderer2D *renderer2d;
	renderer2d = new Renderer2DTyped<float, float>();

	series->SetRenderer(renderer2d);

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

	SpaceND *space = m_plotwindow->GetSpace(0);

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
	PlotWindow *plotwindow;
	plotwindow = m_chartwindow->CreatePlotWindow();
	wxTextEntryDialog dlg(this, "Plot name");
	
	if (dlg.ShowModal() == wxID_OK)
	{
		plotwindow->SetPlotName(static_cast<const char *>(dlg.GetValue()));
	}

	SpaceND *space;
	space = new SpaceND(2);
	plotwindow->AddSpace(space);

	m_chartwindow->GetScaleWindow()->AddAxis(space->GetAxis(AXIS_X));

	fill_plot_choices();
	

}

void MyFrame::m_choice_plotsOnChoice(wxCommandEvent & event)
{
	m_plotwindow = (PlotWindow *)event.GetClientData();
	SpaceND *space = m_plotwindow->GetSpace(0);
	m_checkBox_connecttoscale->SetValue(space->GetAxis(AXIS_X)->GetCommonScale() != NULL);

	fill_series_choices();

}

void MyFrame::m_menuItem_timeOnMenuSelection(wxCommandEvent & event)
{
	TimeAxisValueAdaptor<double> *tvadaptor = new TimeAxisValueAdaptor<double>();
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

	wxASSERT(m_plotwindow != NULL);

	ScaleWindow *scalewindow = m_chartwindow->GetScaleWindow();
	Axis *axis;
	axis = ((SpaceND *)m_plotwindow->GetSpace(0))->GetAxis(AXIS_X);
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
	m_series = (SeriesND *)event.GetClientData();
	fill_datas_choices();
}

void MyFrame::
m_choice_dataOnChoice(wxCommandEvent & event)
{
	m_data = (DataNoType *)event.GetClientData();
}

void MyFrame::m_button_FitOnButtonClick(wxCommandEvent & event)
{
	if (m_data != NULL)
	{
		m_data->Fit();
		return;
	}
	if (m_series != NULL)
	{
		m_series->Fit();
		return;
	}
	if (m_plotwindow != NULL)
	{
		m_plotwindow->FitPlot();
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
	if (m_plotwindow != NULL)
	{
		m_chartwindow->DeletePlot(m_plotwindow);
		m_plotwindow = NULL;
		m_choice_plots->Clear();
		return;
	}
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

void MyFrame::fill_plot_choices()
{
	m_choice_plots->Clear();
	m_choice_series->Clear();
	m_choice_data->Clear();
	m_plotwindow = NULL;
	m_series = NULL;
	m_data = NULL;

	for (auto plot : m_chartwindow->GetPlotContainer()->GetChildren())
	{
		if (plot->GetName().Cmp("plot"))
			continue;
		m_choice_plots->Append(((PlotWindow *)plot)->GetPlotName(), plot);
	}
}

void MyFrame::fill_series_choices()
{
	
	m_choice_series->Clear();
	m_choice_data->Clear();
	m_data = NULL;
	m_series = NULL;
	if (m_plotwindow == NULL)
		return;

	SpaceND *space = (SpaceND *)m_plotwindow->GetSpace(0);
	
	for (auto series : space->GetSerie())
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

	for (auto data : m_series->GetDatas())
	{
		if(data != NULL)
			m_choice_data->Append(data->GetDataName(), data);
	}
}

