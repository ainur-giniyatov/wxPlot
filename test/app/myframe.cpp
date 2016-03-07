#include <wx/textdlg.h>
#include <wx/tooltip.h>
#include <float.h>

#include "myframe.h"

#include "Series.h"
#include "wx/wxGrid.h"
#include "wx/wxRenderer.h"
#include "wx/colorbase.h"
#include "wx/wxMarker.h"
#include "wx/wxLine.h"

const int MyFrame::ID_MENUPLOT_ADDLEGEND = wxNewId();
const int MyFrame::ID_MENUPLOT_ADDVERTICALSCALE = wxNewId();

BEGIN_EVENT_TABLE(MyFrame, MainFrame)
EVT_MOUSEWHEEL(MyFrame::OnMouseWheel)
EVT_MENU(MyFrame::ID_MENUPLOT_ADDLEGEND, MyFrame::OnMenu_AddLegend)
EVT_MENU(MyFrame::ID_MENUPLOT_ADDVERTICALSCALE, MyFrame::OnMenu_AddVerticalScale)
EVT_PLOT_CLICKED(wxID_ANY, MyFrame::OnPlotClicked)

END_EVENT_TABLE()

static int s_plc = 1;
MyFrame::MyFrame():MainFrame(NULL)
{
	wxToolTip::Enable(true);
	//1st page
	//bSizer3->Add(m_singleplot, 1, wxEXPAND);
	//m_panel2->Layout();

	m_series = NULL;
	m_multiplot = new plot::wxMultiPlot(m_panel2);
	bSizer3->Add(m_multiplot, 1, wxEXPAND);
	bSizer3->Layout();
//2nd page

	m_singleplot = new plot::wxSinglePlot(m_panel6, wxVERTICAL);
	//m_2ndpagesubplot->SetLeftButtonAction(LBA_PAN);
	bSizer7->Add(m_singleplot, 1, wxEXPAND);
	m_panel_page2->Layout();

	
	int datasize = 10000;
	
	m_2ndpageseries = new plot::Series(datasize, "dwerfw");
	auto xdata = m_2ndpageseries->GetXData();
	auto ydata = m_2ndpageseries->GetYData();
	double sp = 300.;
	double vel = 0., acc = 0.;
	double v = 0.;
	for (int indx = 0; indx < datasize; indx++)
	{
		xdata[indx] = indx;
		ydata[indx] = v;
		acc = (sp - v) / 10000.;
		vel += acc / 10.;
		vel -= 0.0001;
		v += vel;
	}


	plot::Renderer *renderer = new plot::wxRendererTyped<double, double>();
	m_2ndpageseries->SetRenderer(renderer);

	renderer->SetMarker(new plot::wxMarkerCircle());
	renderer->SetLine(new plot::wxSimpleLine(7, 4));
	
	//
	datasize = 5;
	plot::Series *series = new plot::Series(datasize, "channel 1");
	xdata = series->GetXData();
	ydata = series->GetYData();

	for (int indx = 0; indx < datasize; indx++)
	{
		xdata[indx] = indx / 200. * 10000;
		ydata[indx] = sin(indx / 200. * 6.) * 400.;
	}

	renderer = new plot::wxRendererTyped<double, double>();
	series->SetRenderer(renderer);
	renderer->SetMarker(new plot::wxMarkerSquare());
	renderer->SetLine(new plot::wxSimpleLine(5, 2));


	plot::wxScaleWidget *scalewidget = new plot::wxScaleWidget(m_singleplot, AXIS_Y, wxVERTICAL, wxLeft);
	m_singleplot->AddLeftScaleWidget(scalewidget);
	series->SetYScale(scalewidget->GetScale());
	m_2ndpageseries->SetYScale(scalewidget->GetScale());

	//scalewidget = new plot::wxScaleWidget(m_2ndpagesubplot, AXIS_Y, wxVERTICAL);
	//m_2ndpagesubplot->AddRightScaleWidget(scalewidget);
	//series->SetXScale(scalewidget->GetScale());
	//m_2ndpageseries->SetYScale(scalewidget->GetScale());


	scalewidget = new plot::wxScaleWidget(m_singleplot, AXIS_X, wxHORIZONTAL, wxBottom);
	scalewidget->GetScale()->SetValueAdaptor(new plot::TimeAxisValueAdaptor());
	m_singleplot->AddBottomScaleWidget(scalewidget);
	series->SetXScale(scalewidget->GetScale());
	m_2ndpageseries->SetXScale(scalewidget->GetScale());

	m_singleplot->GetSubplot()->AddSeries(series);
	m_singleplot->GetSubplot()->AddSeries(m_2ndpageseries);






	//plot::Grid *grid;
	//grid = new plot::wxGrid();
	//m_2ndpagearea->SetGrid(grid);

	m_popup_tool = new wxPopupSeriesTool(m_notebook1->GetPage(1));
	//m_popup_tool->Position(wxGetMousePosition(), wxSize(0, 0));
	m_popup_tool->Show();

	//m_notebook1->SetSelection(1);
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
//	int datasize = 5000;
//	if (m_plotpane == NULL)
//	{
//		wxBell();
//		return;
//	}
//	plot::DataTyped<int> *xdata = new plot::DataTyped<int>(datasize, "TIME");
//	plot::DataTyped<int> *ydata = new plot::DataTyped<int>(datasize, "DATA");
//
//	for (int i = 0; i < datasize; i++)
//	{
//		xdata->SetValue(i , i);
//		ydata->SetValue((int)(sin((double)i / (double)datasize * 10) * 30.) + 50, i);
//	}
//
//	plot::Series *series = new plot::Series(2, "SERIES");
//	series->SetRenderer(new plot::wxRendererTyped<int, int>());
//
//
//	plot::Area *area = m_plotpane->GetPlotCanvas()->GetArea(0);
//
//
//
//	series->SetData(xdata, AXIS_X);
//	series->SetData(ydata, AXIS_Y);
//
//
//
//	//Renderer2D *renderer2d;
//	//renderer2d = new Renderer2DTyped<int, int>();
//
//
////	TimeAxisValueAdaptor<int> *tvadap = new TimeAxisValueAdaptor<int>();
////	xdata->SetValueAdaptor(tvadap);
//	area->AddSeries(series);
//
//
//	m_plotpane->GetPlotCanvas()->plot::Plot::Validate();
//
	fill_series_choices();
}

void MyFrame::m_button2OnButtonClick(wxCommandEvent & event)
{
	if (m_subplot == NULL)
	{
		wxBell();
		return;
	}

	int datasize = 500;
	plot::Series *series = new plot::Series(datasize, "Fseries");

	auto xdata = series->GetXData();
	auto ydata = series->GetYData();

	double shft = (rand() % 700);
	double phshft = (rand() % 10);
	double ampshft = (rand() % 100) + 30;
	double xshft = (rand() % 1000);
	for (int i = 0; i < datasize; i++)
	{
		xdata[i] = (double)i / 2. + xshft;
		ydata[i] = sin((double)i / (double)datasize * (37. + rand() % 2) + phshft) * ampshft + shft;
	}


	plot::wxRendererTyped<double, double> *renderer;
	renderer = new plot::wxRendererTyped<double, double>();
	renderer->SetMarker(new plot::wxMarkerCircle());
	series->SetRenderer(renderer);

	series->SetXScale(m_multiplot->GetScaleWidget()->GetScale());
	series->SetYScale(m_multiplot->GetLeftWidgetForSubplot(m_subplot)->GetScale());
	m_subplot->AddSeries(series);

	//wxTextEntryDialog dlg(this, "Series name");
	//if (dlg.ShowModal() == wxID_OK)
	//{
	//	series->SetSeriesName(static_cast<const char *>(dlg.GetValue()));
	//}

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

	SpaceND *space = m_plotpane->GetSpace(0);

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
	plot::wxSubplot *subplot;
	subplot = m_multiplot->CreateSubplot(1);
	if (subplot != nullptr)
	{
		plot::wxScaleWidget *scalewidget = new plot::wxScaleWidget(m_multiplot, AXIS_Y, wxVERTICAL, wxLeft);
		m_multiplot->SetLeftWidgetForSubplot(subplot, scalewidget);

	}
//
//	//plot::wxLegendsBox *legendsbox = new plot::wxLegendsBox();
//	//plotpane->AddBox(legendsbox);
//
//	wxTextEntryDialog dlg(this, "Plot name");
//
//	if (dlg.ShowModal() == wxID_OK)
//	{
//		//plotpane->SetPlotName(static_cast<const char *>(dlg.GetValue()));
//	}
//
//	plot::Area *area;
//	area = new plot::Area(2);
//	plotpane->GetPlotCanvas()->AddArea(area);
//
//	m_singleplot->GetScaleWindow()->GetScale()->AddAxis(area->GetAxis(AXIS_X));
////	wxPlotCanvas->GetYScale()->AddAxis(space->GetAxis(AXIS_Y));
//
//	//ScaleWidget *scalewidget;
//	//scalewidget = new ScaleWidget(wxPlotCanvas, wxVERTICAL);
//	plot::wxScaleBox *scalebox = new plot::wxScaleBox(plot::Box::EXPANDVERT | plot::Box::MOVEABLE, AXIS_Y);
//	plotpane->GetPlotCanvas()->AddBox(scalebox);
//
//	plot::Grid *grid;
//	grid = new plot::wxGrid();
//	area->SetGrid(grid);
//
//	scalebox->AddAxis(area->GetAxis(AXIS_Y));
//	//scalebox->GetScale()->SetValueAdaptor(new plot::SimpleAxisValueAdaptor<double>());
//
//	plotpane->GetPlotCanvas()->RedrawPlot();
//	//LegendsWidget *legendswidget;
//
//	//legendswidget = new LegendsWidget(wxPlotCanvas);
//	//legendswidget->SetAnchorPosition(1., 0.5);
//	//legendswidget->SetAnchorDelta(15, 0);

	fill_plot_choices();

	wxMenu *plotsubmenu;
	//plotsubmenu = new wxMenu();

	//plotpane->GetMenu().AppendSubMenu(plotsubmenu, "More");

	//plotsubmenu->Append(ID_MENUPLOT_ADDLEGEND, "Add legends");
	//plotsubmenu->Append(ID_MENUPLOT_ADDVERTICALSCALE, "Add vertical scale");
}

void MyFrame::m_choice_plotsOnChoice(wxCommandEvent & event)
{
	m_subplot = (plot::wxSubplot*)event.GetClientData();

	//m_checkBox_connecttoscale->SetValue(area->GetAxis(AXIS_X)->_getcommonscale() != NULL);

	fill_series_choices();

}

void MyFrame::m_menuItem_timeOnMenuSelection(wxCommandEvent & event)
{
//	plot::TimeAxisValueAdaptor<double> *tvadaptor = new plot::TimeAxisValueAdaptor<double>();
//	m_singleplot->GetScaleWindow()->GetScale()->SetValueAdaptor(tvadaptor);
}

void MyFrame::m_menuItem_secsOnMenuSelection(wxCommandEvent & event)
{
	//ValueAdaptor<double> *tvadaptor = new SecsValueAdaptor<double>();
	//m_singleplot->GetScaleWindow()->SetValueAdaptor(tvadaptor);
}

void MyFrame::m_menuItem_nullOnMenuSelection(wxCommandEvent & event)
{
//	m_singleplot->GetScaleWindow()->GetScale()->SetValueAdaptor(NULL);
}

void MyFrame::m_checkBox_connecttoscaleOnCheckBox(wxCommandEvent & event)
{
	//if(m_choice_plots->GetSelection() == wxNOT_FOUND)
	//	return;

	//wxASSERT(m_plotpane != NULL);

	//plot::ScaleWindow *scalewindow = m_singleplot->GetScaleWindow();
	//plot::Axis *axis;
	//axis = m_plotpane->GetPlotCanvas()->GetArea(0)->GetAxis(AXIS_X);
	//wxASSERT(axis != NULL);
	//if (event.IsChecked())
	//{
	//	scalewindow->GetScale()->AddAxis(axis);
	//}
	//else
	//{
	//	scalewindow->GetScale()->RemoveAxis(axis);
	//}

}

void MyFrame::m_choice_seriesOnChoice(wxCommandEvent & event)
{
	m_series = (plot::Series *)event.GetClientData();

}

void MyFrame::
m_choice_dataOnChoice(wxCommandEvent & event)
{
//	m_data = (plot::DataNoType *)event.GetClientData();
}

void MyFrame::m_button_FitOnButtonClick(wxCommandEvent & event)
{
//	if (m_data != NULL)
//	{
////		m_data->Fit();
//		return;
//	}
//	if (m_series != NULL)
//	{
//		
//		m_series->Fit(AXIS_MASK_Y | AXIS_MASK_X);
//		return;
//	}
//	if (m_plotpane != NULL)
//	{
//		m_plotpane->GetPlotCanvas()->Plot::Fit(AXIS_MASK_Y | AXIS_MASK_X);
//		
//		return;
//	}
}

void MyFrame::m_button_RenameOnButtonClick(wxCommandEvent & event)
{
}

void MyFrame::m_button_DeleteOnButtonClick(wxCommandEvent & event)
{

	if (m_series != nullptr)
	{
		m_subplot->DeleteSeries(m_series);
		m_series = nullptr;
		m_choice_series->Clear();
		return;
	}

	if (m_subplot != nullptr)
	{
		m_multiplot->DeleteSubplot(m_subplot);
		m_subplot = nullptr;
		m_choice_plots->Clear();
		fill_plot_choices();
		return;
	}
}

void MyFrame::m_button_dataupdatedOnButtonClick(wxCommandEvent & event)
{
	//m_2ndpageydata->DataUpdated();
}

void MyFrame::m_button_seriesupdateOnButtonClick(wxCommandEvent & event)
{
	m_2ndpageseries->Validate();
}

void MyFrame::m_button_spaceupdateOnButtonClick(wxCommandEvent & event)
{
	//m_2ndpagearea->SpaceUpdated();
}

void MyFrame::m_menuItem_panOnMenuSelection(wxCommandEvent & event)
{
	m_singleplot->SetLeftButtonAction(LBA_PAN);
	//m_2ndpageplotwindow->SetLeftButtonAction(LBA_PAN);
}

void MyFrame::m_menuItem_zoomOnMenuSelection(wxCommandEvent & event)
{
	m_singleplot->SetLeftButtonAction(LBA_ZOOMSELECT);
	//m_2ndpageplotwindow->SetLeftButtonAction(LBA_ZOOMSELECT);
}

void MyFrame::m_button_add_boxOnButtonClick(wxCommandEvent & event)
{
	//plot::wxBox *box;
	//box = new plot::wxBox();
	//m_2ndpageplotwindow->AddBox(box);
}

void MyFrame::m_button_chartfitxOnButtonClick(wxCommandEvent & event)
{
	//m_singleplot->Fit(AXIS_MASK_X);
}

void MyFrame::m_button_chartfityOnButtonClick(wxCommandEvent & event)
{
	//m_singleplot->Fit(AXIS_MASK_Y);
}

void MyFrame::m_button_chartfitbothOnButtonClick(wxCommandEvent & event)
{
	//m_singleplot->Fit(AXIS_MASK_X | AXIS_MASK_Y);
}

void MyFrame::m_tool_undo_viewOnToolClicked(wxCommandEvent & event)
{
	//m_singleplot->UndoView();
}

void MyFrame::m_tool_redo_viewOnToolClicked(wxCommandEvent & event)
{
	//m_singleplot->RedoView();
}

void MyFrame::m_tool_orientOnToolClicked(wxCommandEvent & event)
{
	//if(event.IsChecked())
	//	m_2ndpageplotwindow->SetOrientation(plot::Plot::ORIENTATION_ROTATED);
	//else
	//	m_2ndpageplotwindow->SetOrientation(plot::Plot::ORIENTATION_NORMAL);
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
	//DPRINTF("MyFrame::OnMenu_AddLegend\n");
	//plot::wxPlotCanvas *plotpane;
	//wxMenu *menu;
	//menu = (wxMenu *)event.GetEventObject();
	//plotpane = (plot::wxPlotCanvas *)menu->GetInvokingWindow();

	//LegendsWidget *legendswidget;
	//legendswidget = new LegendsWidget(wxPlotCanvas);
	//legendswidget->SetAnchorPosition(1, 0.5);
	//legendswidget->SetAnchorDelta(15, 0);
}

void MyFrame::OnMenu_AddVerticalScale(wxCommandEvent & event)
{
	//DPRINTF("MyFrame::OnMenu_AddVerticalScale\n");
	//plot::wxPlotCanvas *plotpane;
	//wxMenu *menu;
	//menu = (wxMenu *)event.GetEventObject();
	//plotpane = (plot::wxPlotCanvas *)menu->GetInvokingWindow();

	//ScaleWidget *scalewidget;
	//scalewidget = new ScaleWidget(wxPlotCanvas, wxVERTICAL);
	//scalewidget->SetValueAdaptor(new SimpleAxisValueAdaptor<double>());
	//scalewidget->AddAxis(wxPlotCanvas->GetSpace(0)->GetAxis(AXIS_Y));
}

void MyFrame::OnPlotClicked(plot::PlotClickEvent & event)
{
	//DPRINTF("MyFrame::OnPlotClicked\n");
	//printf("plot name: %s\n", event.GetPlot()->GetPlotName());
	//if (event.GetSeriesSelection()->GetSeries() != nullptr)
	//{
	//	auto series = event.GetSeriesSelection()->GetSeries();
	//	printf("series name: %s [%i-%i]\n", series->GetSeriesName(), event.GetSeriesSelection()->GetStartIndex(), event.GetSeriesSelection()->GetEndIndex());
	//	m_popup_tool->SetSelectedSeries(series);
	//}
	//else
	//	m_popup_tool->SetSelectedSeries(nullptr);

	//if (event.GetBox() != nullptr)
	//{
	//	printf("box: __\n");
	//}
}

void MyFrame::fill_plot_choices()
{
	m_choice_plots->Clear();
	m_choice_series->Clear();
	m_choice_data->Clear();

	m_series = NULL;


	for (auto subplot : m_multiplot->GetChildren())
	{
		if (subplot->GetName().Cmp("subplot"))
			continue;
		m_choice_plots->Append(((plot::wxSubplot *)subplot)->GetSubplotName(), subplot);
	}
}

void MyFrame::fill_series_choices()
{

	m_choice_series->Clear();

	
	m_series = nullptr;
	if (m_subplot == nullptr)
		return;

	for (auto series : m_subplot->GetSerie())
	{
		m_choice_series->Append(wxString(series->GetSeriesName()), series);
	}
}

