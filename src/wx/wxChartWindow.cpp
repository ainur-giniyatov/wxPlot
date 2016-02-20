#include <algorithm>

#include "wx/wxChartWindow.h"

using namespace plot;

const int wxChartWindow::ID_PLOTMENUITEM_CLOSE = wxNewId();

BEGIN_EVENT_TABLE(wxChartWindow, wxPanel)
EVT_MENU(ID_PLOTMENUITEM_CLOSE, wxChartWindow::OnPlotMenuItem_close)
EVT_COMMAND(wxID_ANY, PLOTVIEWCHANGED, wxChartWindow::on_plot_view_changed)
END_EVENT_TABLE()

wxChartWindow::wxChartWindow(wxWindow *parent, int orientation) :wxPanel(parent, wxID_ANY)
{
	SetName("chart");
	m_sizer = new wxBoxSizer(orientation);

	m_plotscontainer = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTAB_TRAVERSAL);

	m_sizer->Add(m_plotscontainer, 1, wxEXPAND);

	//wxPanel* scale_container;
	//scale_container = new wxPanel(this);

	//wxBoxSizer *scsizer = new wxBoxSizer(wxVERTICAL);
	//scale_container->SetSizer(scsizer);
	m_scale = new ScaleWindow(this, AXIS_X, wxHORIZONTAL);
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

	m_view_change_index = 0;
	m_lbaction = LBA_PAN;
}


wxChartWindow::~wxChartWindow()
{
	m_mgr.UnInit();
}

void wxChartWindow::OnPlotMenuItem_close(wxCommandEvent & event)
{
	DPRINTF("wxChartWindow::OnPlotMenuItem_close\n");
	wxPlotWindow *plotwindow;
	wxMenu *menu;
	menu = (wxMenu *)event.GetEventObject();
	plotwindow = (wxPlotWindow *)menu->GetInvokingWindow();

	CallAfter(&wxChartWindow::close_plot_delayed, plotwindow);
}

void plot::wxChartWindow::on_plot_view_changed(wxCommandEvent & event)
{
	DPRINTF("plot view changed\n");
	plotviewchanged(m_view_change_index, false);
	m_view_change_index++;

}

void plot::wxChartWindow::plotviewchanged(int vcd, bool swtc)
{
	std::vector<Scale *> scales;
	//scales.push_back(m_scale);
	//auto plots = getplots();

	////collect all scales
	//std::vector<Scales *> p_scales = m_s
	//for_each(plots.begin(), plots.end(), [&scales](Plot *plot) { scales.insert(scales.end(), p_scales.begin(), p_scales.end()); });

	////call each scale's ChangeViewDepth
	//int vd = vcd;
	//int sw = swtc;
	//for_each(scales.begin(), scales.end(), [vd, sw](Scale *scale) {scale->ChangeViewDepth(vd, sw); scale->RedrawDependantPlots(false); });
	//
	//Refresh();

}

void wxChartWindow::addplot(wxPlotWindow * plot)
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

void wxChartWindow::close_plot_delayed(wxPlotWindow * plot)
{
	DeletePlot(plot);
}

std::vector<wxPlotWindow*> plot::wxChartWindow::getplots()
{
	std::vector<wxPlotWindow*> plots;
	wxWindowList wlist;
	wlist = m_plotscontainer->GetChildren();
	for (auto wlist_iter = wlist.begin(); wlist_iter != wlist.end(); ++wlist_iter)
		if (!(*wlist_iter)->GetName().Cmp("plot"))
			plots.push_back(((wxPlotWindow *)(*wlist_iter)));

	return plots;
}

wxPlotWindow * wxChartWindow::CreatewxPlotWindow()
{
	wxPlotWindow *plotwindow = new wxPlotWindow(m_plotscontainer);
	plotwindow->SetLeftButtonAction(m_lbaction);
	addplot(plotwindow);
	//plotwindow->SetCommonScale(m_scale->GetScale());

	return plotwindow;
}

void wxChartWindow::DeletePlot(wxPlotWindow * plot)
{
	wxASSERT(plot != NULL);
	m_mgr.DetachPane(plot);
	m_mgr.Update();
	plot->Destroy();
}

void wxChartWindow::SetLeftButtonAction(LEFTBUTTON_ACTION lba)
{
	m_lbaction = lba;

	for (auto plot : getplots())
		plot->SetLeftButtonAction(m_lbaction);
	
}

void plot::wxChartWindow::UndoView()
{
	if (m_view_change_index > 0)
	{
		m_view_change_index--;
		plotviewchanged(m_view_change_index, true);
	}
}

void plot::wxChartWindow::RedoView()
{
	m_view_change_index++;
	plotviewchanged(m_view_change_index, true);
}

void plot::wxChartWindow::Fit(int axis_mask)
{

	//std::vector<Scale *> scales;
	//
	//if((1 << m_scale->_get_axis_dir()) & axis_mask)
	//	scales.push_back(m_scale);

	//for (auto plot : getplots())
	//	for (auto scale : plot->_get_scales())
	//		if ((1 << scale->_get_axis_dir()) & axis_mask)
	//			scales.push_back(scale);
	//	
	//for (int xd = 0; xd < 3; xd++)
	//	if ((1 << xd) & axis_mask)
	//	{
	//		double vmax = 0, vmin = 0;
	//		bool data_aval = false;

	//		for (auto scale : scales)
	//		{
	//			if (xd != scale->_get_axis_dir())
	//				continue;

	//			for (auto axis : scale->GetAxes())
	//			{
	//				for (auto data : axis->_get_adj_datas())
	//				{
	//					vmax = data->GetDataMax();
	//					vmin = data->GetDataMin();
	//					data_aval = true;
	//					break;
	//				}
	//				if (data_aval)
	//					break;
	//			}

	//			if (data_aval)
	//				break;
	//		}

	//		if (!data_aval)
	//			continue;

	//		for (auto scale : scales)
	//		{
	//			if (xd !=  scale->_get_axis_dir())
	//				continue;

	//			for (auto axis : scale->GetAxes())
	//			{
	//				for (auto data : axis->_get_adj_datas())
	//				{
	//					double tvmin, tvmax;
	//					tvmin = data->GetDataMin();
	//					tvmax = data->GetDataMax();
	//					vmax = vmax > tvmax ? vmax : tvmax;
	//					vmin = vmin < tvmin ? vmin : tvmin;
	//					
	//				}
	//			}
	//			double range = vmax - vmin;
	//			scale->SetOffset(vmin - range / 10.);
	//			scale->SetRange(range + range / 5.);
	//			scale->RedrawDependantPlots(false);
	//		}

	//	}

	//Refresh();
}
