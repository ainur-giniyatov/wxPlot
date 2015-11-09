//#include "stdafx.h"
#include "ChartWindow.h"


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
	m_scale = new ScaleWindow(this);
//	scsizer->Add(m_scale, 0, wxEXPAND);
	m_orientation = orientation;

	if (m_orientation == wxVERTICAL)
	{
		m_scale->SetMinClientSize(wxSize(wxDefaultCoord, 120));
		m_sizer->Add(m_scale, 0, wxEXPAND | wxALL, 1);
	}
	else
	{
		m_scale->SetMinClientSize(wxSize(50, wxDefaultCoord));
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

}


ChartWindow::~ChartWindow()
{
	//m_mgr.Disconnect(wxEVT_AUI_PANE_MAXIMIZE, (wxObjectEventFunction)&Figure::OnAuiManagerEvent, NULL, this);
	//m_mgr.Disconnect(wxEVT_AUI_PANE_RESTORE, (wxObjectEventFunction)&Figure::OnAuiManagerEvent, NULL, this);
	m_mgr.UnInit();
}

void ChartWindow::addplot(PlotWindow * plot)
{
	wxWindow *wnd;
	wnd = (wxWindow *)plot; //((long)plot + sizeof(Plot));//some hack
	
	if(m_orientation == wxVERTICAL)
		m_mgr.AddPane(wnd, wxAuiPaneInfo().Center().CaptionVisible(false).MaximizeButton(true).MinimizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(false).BottomDockable(false).TopDockable(true).LeftDockable(false).RightDockable(false).MinSize(-1, 0).DestroyOnClose().Position(-1));
	else
	{
		wxASSERT(m_orientation != wxHORIZONTAL);//fix vertical orientation
		m_mgr.AddPane(wnd, wxAuiPaneInfo().Left().CaptionVisible(false).MaximizeButton(true).MinimizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(false).BottomDockable(false).TopDockable(false).LeftDockable(true).RightDockable(false).MinSize(-1, 0).DestroyOnClose().Position(-1));
	}
	
	m_mgr.Update();
}

PlotWindow * ChartWindow::CreatePlotWindow()
{
	PlotWindow *plotwindow = new PlotWindow(m_plotscontainer);
	
	addplot(plotwindow);

	return plotwindow;
}

void ChartWindow::DeletePlot(PlotWindow * plot)
{
	wxASSERT(plot != NULL);
	m_mgr.DetachPane(plot);
	m_mgr.Update();
	plot->Destroy();
}
