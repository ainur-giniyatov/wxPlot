#include <algorithm>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>

#include "wx/wxMultiPlot.h"

using namespace plot;

const int wxMultiPlot::ID_PLOTMENUITEM_CLOSE = wxNewId();

BEGIN_EVENT_TABLE(wxMultiPlot, wxPanel)
EVT_MENU(ID_PLOTMENUITEM_CLOSE, wxMultiPlot::OnPlotMenuItem_close)
EVT_COMMAND(wxID_ANY, PLOTVIEWCHANGED, wxMultiPlot::on_plot_view_changed)
EVT_SIZE(wxMultiPlot::OnResize)
EVT_MOTION(wxMultiPlot::OnMotion)
EVT_LEFT_UP(wxMultiPlot::OnLeftUp)
EVT_LEFT_DOWN(wxMultiPlot::OnLeftDown)
EVT_MOUSE_CAPTURE_LOST(wxMultiPlot::OnMouseCaptureLost)
EVT_LEAVE_WINDOW(wxMultiPlot::OnMouseLeave)
EVT_ENTER_WINDOW(wxMultiPlot::OnMouseEnter)
END_EVENT_TABLE()

wxMultiPlot::wxMultiPlot(wxWindow *parent, int orientation) :wxPanel(parent, wxID_ANY)
{
	SetName("chart");

	m_panelsizer = new wxFlexGridSizer(0, 2, 0, 0);
	m_panelsizer->AddGrowableCol(1, 1);
	m_panelsizer->SetFlexibleDirection(wxBOTH);
	m_panelsizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_scalewidget = new wxScaleWidget(this, AXIS_X, wxHORIZONTAL, wxBottom);

	m_orientation = orientation;


	if (m_orientation == wxVERTICAL)
	{
		m_panelsizer->AddSpacer(0);
		m_panelsizer->AddSpacer(0);
		m_panelsizer->AddGrowableRow(0, 1);

		m_panelsizer->AddSpacer(0);
		m_panelsizer->Add(m_scalewidget, 0, wxEXPAND | wxTOP | wxALIGN_BOTTOM , 5);
	}
	else
	{
		assert(0);
		m_panelsizer->Insert(0, m_scalewidget, 0, wxEXPAND);
	//	m_scale->SetMinClientSize(wxSize(50, wxDefaultCoord));
	}
		
	
	SetSizer(m_panelsizer);
	Layout();

	m_view_change_index = 0;
	m_lbaction = LBA_PAN;

	m_backstore = new wxBitmap();
	m_dragging_resize_resize_border = false;
}


wxMultiPlot::~wxMultiPlot()
{
	//m_mgr.UnInit();
	delete m_backstore;
}

void wxMultiPlot::OnPlotMenuItem_close(wxCommandEvent & event)
{
	DPRINTF("wxMultiPlot::OnPlotMenuItem_close\n");
	assert(0);
	//PlotCanvas *plotwindow;
	//wxMenu *menu;
	//menu = (wxMenu *)event.GetEventObject();
	//plotwindow = (PlotCanvas *)menu->GetInvokingWindow();

	//CallAfter(&wxMultiPlot::close_plot_delayed, plotwindow);
}

void plot::wxMultiPlot::on_plot_view_changed(wxCommandEvent & event)
{
	DPRINTF("plot view changed\n");
	plotviewchanged(m_view_change_index, false);
	m_view_change_index++;

}

void plot::wxMultiPlot::plotviewchanged(int vcd, bool swtc)
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

void wxMultiPlot::addsubplot(wxSubplot *subplot, int indx)
{
	int avg_h = 0;

	if (m_panelsizer->GetEffectiveRowsCount() == 2 && m_panelsizer->GetItem(1)->IsSpacer())
	{
		m_panelsizer->Detach(0);
		m_panelsizer->Detach(0);
	}

	for (int indx = 0; indx < m_panelsizer->GetEffectiveRowsCount() - 1; indx++)
	{
		wxSizerItem *sizer_item = m_panelsizer->GetItem(indx * 2 + 1);
		avg_h += sizer_item->GetRect().height;
	}
	if(avg_h != 0)
		avg_h /= (m_panelsizer->GetEffectiveRowsCount() - 1);
	
	if (indx > (m_panelsizer->GetEffectiveRowsCount()) / 2)
		indx = (m_panelsizer->GetEffectiveRowsCount()) / 2;
	
	m_panelsizer->Insert(indx * 2, subplot, 1, wxEXPAND | wxTOP, 5);
	m_panelsizer->InsertSpacer(indx * 2, 0);

	for (int indx = 0; indx < m_panelsizer->GetEffectiveRowsCount(); indx++)
	{
		if (m_panelsizer->IsRowGrowable(indx))
			m_panelsizer->RemoveGrowableRow(indx);
	}
	
	
	for (int indx = 0; indx < m_panelsizer->GetEffectiveRowsCount() - 1; indx++)
	{
		wxSizerItem *sizer_item = m_panelsizer->GetItem(indx * 2 + 1);
		wxWindow *wnd = sizer_item->GetWindow();
		if (wnd != nullptr)
		{
			int h = wnd->GetRect().height;
			if (wnd == subplot)
				h = avg_h;
			m_panelsizer->AddGrowableRow(indx, h);
		}
	}
	//recalc_row_proportions();
	Layout();
//	m_plotscontainer->Layout();
	//if (m_orientation == wxVERTICAL)
	//	m_mgr.AddPane(wnd, wxAuiPaneInfo().Center().CaptionVisible(false).MaximizeButton(true).MinimizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(false).BottomDockable(false).TopDockable(true).LeftDockable(false).RightDockable(false).MinSize(-1, 0).DestroyOnClose().Position(-1));
	//else
	//{
	//	wxASSERT(m_orientation != wxHORIZONTAL);//fix vertical orientation
	//	m_mgr.AddPane(wnd, wxAuiPaneInfo().Left().CaptionVisible(false).MaximizeButton(true).MinimizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize).DockFixed(false).BottomDockable(false).TopDockable(false).LeftDockable(true).RightDockable(false).MinSize(-1, 0).DestroyOnClose().Position(-1));
	//}

	//m_mgr.Update();
}

void wxMultiPlot::close_plot_delayed(wxSubplot * subplot)
{
	DeleteSubplot(subplot);
}

const std::vector<wxSubplot *> plot::wxMultiPlot::getsubplots()
{
	std::vector<wxSubplot *> plots;
	wxWindowList wlist;
	wlist = GetChildren();
	for (auto wlist_iter = wlist.begin(); wlist_iter != wlist.end(); ++wlist_iter)
		if (!(*wlist_iter)->GetName().Cmp("subplot"))
			plots.push_back(((wxSubplot *)(*wlist_iter)));

	return plots;
}

void plot::wxMultiPlot::OnMotion(wxMouseEvent & event)
{
	if (event.Dragging() && event.LeftIsDown() && m_dragging_resize_resize_border)
	{
		DPRINTF("Dragging\n");
		if (!HasCapture())
			CaptureMouse();
		wxPoint mp(event.GetPosition());

		if (m_drag_boundary.GetTop() > mp.y)
			mp.y = m_drag_boundary.GetTop();

		if (m_drag_boundary.GetBottom() < mp.y)
			mp.y = m_drag_boundary.GetBottom();

		wxWindowDC dc(this);
		auto sz = dc.GetSize();
		wxPen pen(dc.GetPen());
		pen.SetWidth(3);
		pen.SetStyle(wxPENSTYLE_FIRST_HATCH);
		dc.SetPen(pen);
		dc.DrawBitmap(*m_backstore, wxPoint(0, 0));
		dc.DrawLine(0, mp.y, sz.x, mp.y);
	}
}

void plot::wxMultiPlot::OnLeftUp(wxMouseEvent & event)
{
	if (HasCapture())
		ReleaseMouse();

	if (m_dragging_resize_resize_border)
	{
		m_dragging_resize_resize_border = false;
		wxWindowDC dc(this);
		dc.DrawBitmap(*m_backstore, wxPoint(0, 0));
		wxRect above_rect = m_above->GetRect();
		wxRect below_rect = m_below->GetRect();
		above_rect.SetBottom(event.GetPosition().y - 2);
		auto bb = below_rect.GetBottom();
		below_rect.SetTop(event.GetPosition().y + 3);
		below_rect.SetBottom(bb);
		m_above->SetSize(above_rect.x, above_rect.y, above_rect.width, above_rect.height);
		m_below->SetSize(below_rect.x, below_rect.y, below_rect.width, below_rect.height);
		recalc_row_proportions();
	}
}

void plot::wxMultiPlot::OnLeftDown(wxMouseEvent & event)
{
	wxWindowDC dc(this);
	auto size = dc.GetSize();
	wxMemoryDC mdc;
	mdc.SelectObject(*m_backstore);
	mdc.Blit(wxPoint(0, 0), m_backstore->GetSize(), &dc, wxPoint(0, 0));
	mdc.SelectObject(wxNullBitmap);

	m_drag_boundary.SetTopLeft(wxPoint(0, 0));
	m_drag_boundary.SetBottomRight(wxPoint(size.x, size.y));

	wxWindow *above = nullptr, *under = nullptr;

	for (auto subplot : getsubplots())
	{
		auto rect = subplot->GetRect();
		rect.SetLeft(0);
		rect.SetRight(size.x);
		wxPoint mp(event.GetPosition());
		mp.y -= 5;
		if (rect.Contains(mp))
		{
			above = subplot;
		}
		mp.y += 10;
		if (rect.Contains(mp))
		{
			under = subplot;
		}
		
	}
	m_above = m_below = nullptr;
	if(under != nullptr && above != nullptr && above != under)
	{
		m_drag_boundary.SetTop(above->GetRect().GetTop());
		m_drag_boundary.SetBottom(under->GetRect().GetBottom());
		m_above = above;
		m_below = under;
		m_dragging_resize_resize_border = true;
	}


}

void plot::wxMultiPlot::OnMouseCaptureLost(wxMouseCaptureLostEvent & event)
{
}

void plot::wxMultiPlot::recalc_row_proportions()
{
	for (int indx = 0; indx < m_panelsizer->GetEffectiveRowsCount() ; indx++)
	{

		if (m_panelsizer->IsRowGrowable(indx))
			m_panelsizer->RemoveGrowableRow(indx);
	}

	for (int indx = 0; indx < m_panelsizer->GetEffectiveRowsCount() - 1; indx++)
	{
		wxWindow *wnd;
		auto sizeritem = m_panelsizer->GetItem(indx * 2 + 1);
		wnd = sizeritem->GetWindow();
		if (wnd != nullptr && wnd != m_scalewidget)
		{
			int h = wnd->GetSize().GetHeight();
		
			//if (m_panelsizer->IsRowGrowable(indx))
			//	m_panelsizer->RemoveGrowableRow(indx);

			m_panelsizer->AddGrowableRow(indx, h);
		}
	}

	Layout();
}

void plot::wxMultiPlot::OnMouseEnter(wxMouseEvent & event)
{
	wxRect rect(GetRect());
	rect.SetTop(m_panelsizer->GetItem((size_t)0)->GetRect().GetTop() );
	rect.SetBottom(m_panelsizer->GetItem((size_t)((m_panelsizer->GetEffectiveRowsCount() - 1) * 2 ))->GetRect().GetBottom());
	if (rect.Contains(event.GetPosition()))
	{
		auto oldcurs = GetCursor();
		SetCursor(wxCURSOR_SIZENS);
		for (auto child : GetWindowChildren())
			child->SetCursor(oldcurs);
	}
}

void plot::wxMultiPlot::OnMouseLeave(wxMouseEvent & event)
{
	SetCursor(wxNullCursor);
}

wxSubplot *wxMultiPlot::CreateSubplot(int indx)
{
	wxSubplot *subplot = nullptr;
	subplot = new wxSubplot(this);
	subplot->SetMinSize(wxSize(wxDefaultCoord, 10));
	addsubplot(subplot, indx);
	return subplot;
}

void plot::wxMultiPlot::SetLeftWidgetForSubplot(wxSubplot * subplot, wxScaleWidget * scalewidget)
{
	int indx = 0;
	bool found = false;
	for (auto sizeitem : m_panelsizer->GetChildren())
	{
		if (sizeitem->GetWindow() == subplot)
		{
			found = true;
			break;
		}

		indx++;
	}

	assert(found == true);

	auto sizeitem = m_panelsizer->GetItem(indx - 1);
	sizeitem->SetProportion(0);
	sizeitem->SetFlag(wxEXPAND | wxRIGHT | wxTOP);
	sizeitem->SetBorder(5);
	sizeitem->AssignWindow(scalewidget);

	Layout();
}

wxScaleWidget * plot::wxMultiPlot::GetLeftWidgetForSubplot(wxSubplot * subplot)
{
	wxScaleWidget *scalewidget = nullptr;

	int indx = 0;
	bool found = false;
	for (auto sizeitem : m_panelsizer->GetChildren())
	{
		if (sizeitem->GetWindow() == subplot)
		{
			found = true;
			break;
		}

		indx++;
	}

	
	scalewidget = (wxScaleWidget *)m_panelsizer->GetItem(indx - 1)->GetWindow();

	return scalewidget;
}

void wxMultiPlot::DeleteSubplot(wxSubplot *subplot)
{
	wxASSERT(subplot != NULL);
	wxWindow *leftwidget = nullptr;
	for (int indx = 0; indx < m_panelsizer->GetEffectiveRowsCount() - 1; indx++)
	{
		if (m_panelsizer->GetItem(indx * 2 + 1)->GetWindow() == subplot)
		{
			leftwidget = m_panelsizer->GetItem(indx * 2)->GetWindow();
			m_panelsizer->Detach(subplot);
			m_panelsizer->Detach(leftwidget);
			subplot->Destroy();
			leftwidget->Destroy();
			break;
		}
	}

	if (m_panelsizer->GetEffectiveRowsCount() == 1)
	{
		m_panelsizer->PrependSpacer(0);
		m_panelsizer->PrependSpacer(0);
		m_panelsizer->RemoveGrowableRow(0);
		m_panelsizer->AddGrowableRow(0, 1);
	}

	m_panelsizer->Layout();
	recalc_row_proportions();

}

void wxMultiPlot::SetLeftButtonAction(LEFTBUTTON_ACTION lba)
{
	m_lbaction = lba;

	//for (auto plot : getplots())
	//	plot->SetLeftButtonAction(m_lbaction);
	
}

void plot::wxMultiPlot::UndoView()
{
	if (m_view_change_index > 0)
	{
		m_view_change_index--;
		plotviewchanged(m_view_change_index, true);
	}
}

void plot::wxMultiPlot::RedoView()
{
	m_view_change_index++;
	plotviewchanged(m_view_change_index, true);
}

void plot::wxMultiPlot::Fit(int axis_mask)
{

	//std::vector<Scale *> scales;
	//
	//if((1 << m_scale->GetScale()->_get_axis_dir()) & axis_mask)
	//	scales.push_back(m_scale->GetScale());

	//for (auto plot : getplots())
	//	for (auto scale : plot->_get_dependant_scales())
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

	//			for (auto axis : scale->_get_axes())
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

	//			for (auto axis : scale->_get_axes())
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
	//			scale->Validate();
	//		}

	//	}

	//for (auto plot : getplots())
	//	plot->Plot::Validate(true);
}

void plot::wxMultiPlot::OnResize(wxSizeEvent & event)
{
	wxSize size = GetSize();

	m_backstore->Create(size);
	event.Skip();
}