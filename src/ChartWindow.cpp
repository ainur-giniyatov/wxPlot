//#include "stdafx.h"
#include "ChartWindow.h"


const int ChartWindow::ID_PLOTMENUITEM_CLOSE = wxNewId();

BEGIN_EVENT_TABLE(ChartWindow, wxPanel)
EVT_MENU(ID_PLOTMENUITEM_CLOSE, ChartWindow::OnPlotMenuItem_close)
//EVT_COMMAND(wxID_ANY, wxCommandEventQueued, ChartWindow::OnPlotMenuItem_close_queued)
END_EVENT_TABLE()

ChartWindow::ChartWindow(wxWindow *parent, int orientation) :wxPanel(parent, wxID_ANY)
{
	SetName("chart");
	m_sizer = new wxBoxSizer(orientation);

	m_plotscontainer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL);

	m_sizer->Add(m_plotscontainer, 1, wxEXPAND);

	//wxPanel* scale_container;
	//scale_container = new wxPanel(this);

	//wxBoxSizer *scsizer = new wxBoxSizer(wxVERTICAL);
	//scale_container->SetSizer(scsizer);
	m_scale = new ScaleWindow(this, wxHORIZONTAL);
//	scsizer->Add(m_scale, 0, wxEXPAND);
	m_orientation = orientation;

	if (m_orientation == wxVERTICAL)
	{
		//m_scale->SetMinClientSize(wxSize(wxDefaultCoord, 120));
		m_sizer->Add(m_scale, 0, wxEXPAND | wxALL, 1);
	}
	else
	{
	//	m_scale->SetMinClientSize(wxSize(50, wxDefaultCoord));
		m_sizer->Insert(0, m_scale, 0, wxEXPAND | wxALL, 1);
	}


	SetSizer(m_sizer);
	Layout();

	m_mgr.SetManagedWindow(m_plotscontainer);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_SASH_SIZE, 2);
	//m_mgr.GetArtProvider()->SetColor(wxAUI_DOCKART_SASH_COLOUR, wxColour(0, 0, 0));
	m_mgr.Update();

	//m_mgr.Connect(wxEVT_AUI_PANE_MAXIMIZE, (wxObjectEventFunction)&Figure::OnAuiManagerEvent, NULL, this);
	//m_mgr.Connect(wxEVT_AUI_PANE_RESTORE, (wxObjectEventFunction)&Figure::OnAuiManagerEvent, NULL, this);

	m_lbaction = LBA_PAN;
}


ChartWindow::~ChartWindow()
{
	//m_mgr.Disconnect(wxEVT_AUI_PANE_MAXIMIZE, (wxObjectEventFunction)&Figure::OnAuiManagerEvent, NULL, this);
	//m_mgr.Disconnect(wxEVT_AUI_PANE_RESTORE, (wxObjectEventFunction)&Figure::OnAuiManagerEvent, NULL, this);
	m_mgr.UnInit();
}

void ChartWindow::OnPlotMenuItem_close(wxCommandEvent & event)
{
	DPRINTF("ChartWindow::OnPlotMenuItem_close\n");
	PlotWindow *plotwindow;
	wxMenu *menu;
	menu = (wxMenu *)event.GetEventObject();
	plotwindow = (PlotWindow *)menu->GetInvokingWindow();

	CallAfter(&ChartWindow::close_plot_delayed, plotwindow);
	//wxCommandEvent *evt = new wxCommandEvent(wxCommandEventQueued);
	//evt->SetEventObject(plotwindow);
	//QueueEvent(evt);
}

//void ChartWindow::OnPlotMenuItem_close_queued(wxCommandEvent & event)
//{
//	DPRINTF("ChartWindow::OnPlotMenuItem_close_queued\n");
//	PlotWindow *plotwindow;
//	plotwindow = (PlotWindow *)event.GetEventObject();
//	DeletePlot(plotwindow);
//}

void ChartWindow::addplot(PlotWindow * plot)
{
	wxWindow *wnd;
	wnd = (wxWindow *)plot; //((long)plot + sizeof(Plot));//some hack
	
	plot->GetMenu().Append(ID_PLOTMENUITEM_CLOSE, "Close");

	if(m_orientation == wxVERTICAL)
		m_mgr.AddPane(wnd, wxAuiPaneInfo().Center().CaptionVisible(false).MaximizeButton(true).MinimizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(false).BottomDockable(false).TopDockable(true).LeftDockable(false).RightDockable(false).MinSize(-1, 0).DestroyOnClose().Position(-1));
	else
	{
		wxASSERT(m_orientation != wxHORIZONTAL);//fix vertical orientation
		m_mgr.AddPane(wnd, wxAuiPaneInfo().Left().CaptionVisible(false).MaximizeButton(true).MinimizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(false).BottomDockable(false).TopDockable(false).LeftDockable(true).RightDockable(false).MinSize(-1, 0).DestroyOnClose().Position(-1));
	}
	
	m_mgr.Update();
}

void ChartWindow::close_plot_delayed(PlotWindow * plot)
{
	DeletePlot(plot);
}

PlotWindow * ChartWindow::CreatePlotWindow()
{
	PlotWindow *plotwindow = new PlotWindow(m_plotscontainer);
	plotwindow->SetLeftButtonAction(m_lbaction);
	addplot(plotwindow);
	plotwindow->SetCommonScale(m_scale);

	return plotwindow;
}

void ChartWindow::DeletePlot(PlotWindow * plot)
{
	wxASSERT(plot != NULL);
	m_mgr.DetachPane(plot);
	m_mgr.Update();
	plot->Destroy();
}

void ChartWindow::SetLeftButtonAction(LEFTBUTTON_ACTION lba)
{
	m_lbaction = lba;
	wxWindowList wlist;
	wlist = m_plotscontainer->GetChildren();
	for (auto wlist_iter = wlist.begin(); wlist_iter != wlist.end(); ++wlist_iter)
	{
		if (!(*wlist_iter)->GetName().Cmp("plot"))
		{
			((PlotWindow *)*wlist_iter)->SetLeftButtonAction(lba);
		}
	}
}
