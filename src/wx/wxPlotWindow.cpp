//#include "stdafx.h"
#include <algorithm>
#include <wx/dcbuffer.h>

#include "wx/wxPlotWindow.h"
#include "wx/wxChartWindow.h"
#include "wx/wxGrid.h"
#include "wx/wxRenderer.h"
#include "wx/wxBox.h"
#include "wx/wxScaleBox.h"

using namespace plot;

wxDEFINE_EVENT(PLOTCLICKED, plot::PlotClickEvent);

wxDEFINE_EVENT(PLOTVIEWCHANGED, wxCommandEvent);

const int wxPlotWindow::IDMENUITEM_REMOVESERIES = wxNewId();
const int wxPlotWindow::IDMENUITEM_SERIESFITVERT = wxNewId();
const int wxPlotWindow::IDMENUITEM_SERIESFITHOR = wxNewId();
const int wxPlotWindow::IDMENUITEM_SERIESFITALLDIMS = wxNewId();

BEGIN_EVENT_TABLE(wxPlotWindow, wxWindow)
EVT_PAINT(wxPlotWindow::OnPaint)
EVT_ERASE_BACKGROUND(wxPlotWindow::OnEraseBackground)
EVT_SIZE(wxPlotWindow::OnResize)
EVT_MOUSEWHEEL(wxPlotWindow::OnMouseWheel)
EVT_LEFT_DOWN(wxPlotWindow::OnLeftDown)
EVT_LEFT_UP(wxPlotWindow::OnLeftUp)
EVT_MOTION(wxPlotWindow::OnMouseMove)
EVT_RIGHT_DOWN(wxPlotWindow::OnRightDown)
EVT_RIGHT_UP(wxPlotWindow::OnRightUp)
END_EVENT_TABLE()


wxPlotWindow::wxPlotWindow(wxWindow * parent) :wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER)
{
	DPRINTF("wxPlotWindow: ctor\n");
	SetName("plot");
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_sizer = new wxBoxSizer(wxHORIZONTAL);


	SetSizer(m_sizer);
	Layout();

	m_series_menu.Append(IDMENUITEM_REMOVESERIES, "Remove");
	Connect(IDMENUITEM_REMOVESERIES, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_RemoveSeries);
	
	m_series_menu.Append(IDMENUITEM_SERIESFITVERT, "Fit vertical");
	Connect(IDMENUITEM_SERIESFITVERT, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_SeriesFitVert);

	m_series_menu.Append(IDMENUITEM_SERIESFITHOR, "Fit horiz");
	Connect(IDMENUITEM_SERIESFITHOR, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_SeriesFitHor);
	
	m_series_menu.Append(IDMENUITEM_SERIESFITALLDIMS, "Fit both");
	Connect(IDMENUITEM_SERIESFITALLDIMS, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_SeriesFitAllDims);
	
	m_bitmap_buffer = new wxBitmap();

	m_diag_texts_pos_y = 5;


	Box *box = new wxBox();
	AddBox(box);

	box = new wxTitleBox();
	AddBox(box);


//	wxTitleBox *titlebox;
//	titlebox = new wxTitleBox();
//	AddBox(titlebox);

//	m_popup_tool = new wxPopupSeriesTool(this);
}

wxPlotWindow::~wxPlotWindow()
{
	DPRINTF("wxPlotWindow: dtor\n");

	delete m_bitmap_buffer;

}

void wxPlotWindow::OnPaint(wxPaintEvent & event)
{
	wxBufferedPaintDC dc(this);
	//dc.SetPen(*wxTRANSPARENT_PEN);
	//dc.DrawRectangle(GetClientRect());
	//dc.Clear();
	/*m_refresh_bitmap = true;
	if (m_refresh_bitmap)
	{
		wxMemoryDC memdc;
		memdc.SelectObject(*m_bitmap_buffer);
		memdc.SetBackground(dc.GetBackground());
		memdc.Clear();
		wxGraphicsContext *gc = wxGraphicsContext::Create(memdc);

		Render(gc);
		delete gc;

		memdc.SelectObject(wxNullBitmap);

		m_refresh_bitmap = false;
	}

	dc.DrawBitmap(*m_bitmap_buffer, 0, 0);*/

	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	
	Render(gc);

	delete gc;
}

void wxPlotWindow::OnEraseBackground(wxEraseEvent & event)
{
	event.GetDC()->Clear();
}

void wxPlotWindow::OnResize(wxSizeEvent & event)
{
	m_is_data_view_modified = true;
	
	wxSize sz(GetClientSize());
		
	m_bitmap_buffer->Create(sz);


	plot_resized();


	plot::Plot::Validate();

}

void plot::wxPlotWindow::_popup_seriesmenu(Series * series)
{
	m_the_series = series;
	series->BringToFront();
	series->Validate();
	m_series_menu.FindItem(IDMENUITEM_REMOVESERIES)->SetItemLabel(wxString::Format("Remove %s", series->GetSeriesName()));
	PopupMenu(&m_series_menu);
}

void wxPlotWindow::OnLeftDown(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	x = event.GetX();
	y = event.GetY();

	PlotClickEvent plotclick_event(PLOTCLICKED, GetId(), this);
	plotclick_event.SetEventObject(this);

	//process interaction with on-plot boxes
	for (auto box : m_boxes)
	{
		if (box->_get_rect().IsInside(Point<int>(x, y)) && box->_has_flags(Box::MOVEABLE))
		{
			m_selected_box = box;
			auto &rect = m_selected_box->_get_rect();
			auto border_thickness = m_selected_box->_get_borderthickenss();
			m_selected_box_sides = BOXNONESIDE;
			if (rect.left <= x && rect.left + border_thickness >= x)
				m_selected_box_sides |= BOXLEFT;

			if ((rect.right >= x && rect.right - border_thickness <= x) && !(m_selected_box_sides & BOXLEFT))
				m_selected_box_sides |= BOXRIGHT;

			if (rect.top <= y && rect.top + border_thickness >= y)
				m_selected_box_sides |= BOXTOP;

			if ((rect.bottom >= y && rect.bottom - border_thickness <= y) && !(m_selected_box_sides & BOXTOP))
				m_selected_box_sides |= BOXBOTTOM;

			m_box_click_delta = Point<int>(x - rect.left, y - rect.top);
			m_box_click_delta2 = Point<int>(rect.right - x, rect.bottom - y);

			if (m_selected_box_sides == BOXNONESIDE)
			{
				m_selected_box_state = BOXMOVING;
			}
			else
			{
				if(box->_has_flags(Box::RESIZEABLE))
					m_selected_box_state = BOXRESIZING;
			}

			return;
		}
	}

	SeriesSelection ser_sel;
	_getspottedseries(Point<int>(x, y), ser_sel);
	if (ser_sel.GetSeries() != nullptr)
	{
		ser_sel.GetSeries()->BringToFront();
		ser_sel.GetSeries()->Validate();
		plotclick_event.SetSeriesSelection(ser_sel);
	//	if (m_popup_tool->IsShown())
	//	{
	//		m_popup_tool->SetSelectedSeries(ser_sel.GetSeries());
	//	}
	}
	//else 
	//{
	//	m_popup_tool->SetSelectedSeries(nullptr);
	//}

	
	ProcessWindowEvent(plotclick_event);

	int w, h;
	GetClientSize(&w, &h);

	if (m_lbaction == LBA_PAN)
	{
		StartPan(Point<double>((double)x / (double)w, 1 - (double)y / (double)h));
	}

	if (m_lbaction == LBA_ZOOMSELECT)
	{
		StartZoomSelect(Point<double>((double)x / (double)w, 1 - (double)y / (double)h));
	}

	if(!HasCapture())
        CaptureMouse();
}

void plot::wxPlotWindow::_getspottedseries(Point<int>&mouse_coords, SeriesSelection & seriesselection)
{
	seriesselection = SeriesSelection(nullptr, 0, 0);

	//selection of series
	for (auto area : m_areas)
		for (auto series = area->GetSerie().rbegin(); series != area->GetSerie().rend(); ++ series)
			if ((*series)->GetRenderer()->_isspotted(mouse_coords, seriesselection))
			{
#ifdef _DEBUG
				printf("spot: %s, [%i %i]\n", seriesselection.GetSeries()->GetSeriesName(), seriesselection.GetStartIndex(), seriesselection.GetEndIndex());
#endif
				return;
			}
}

void wxPlotWindow::OnLeftUp(wxMouseEvent & event)
{
	int x, y;
	x = event.GetX();
	y = event.GetY();


	EndPan();
	EndZoomSelect();

	m_selected_box = nullptr;

	//process interaction with on-plot boxes
//	for (auto box : m_boxes)
//	{
//		if (box->CheckIsMouseInside(x, y))
//		{
//			box->MouseLeftUp(x, y);
////			return;
//		}
//	}

	if(HasCapture())
        ReleaseMouse();

}

void wxPlotWindow::OnRightDown(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	x = event.GetX();
	y = event.GetY();

	//process interaction with on-plot boxes
	//for (auto box : m_boxes)
	//{
	//	if (box->CheckIsMouseInside(x, y))
	//	{
	//		box->MouseRightDown(x, y);
	//					return;
	//	}
	//}

	//series menu
	SeriesSelection ser_sel;
	_getspottedseries(Point<int>(x, y), ser_sel);
	if (ser_sel.GetSeries() != nullptr)
	{
		_popup_seriesmenu(ser_sel.GetSeries());
		
		return;
	}

	//plot menu
	if(m_context_menu.GetMenuItemCount() != 0)
		PopupMenu(&m_context_menu);
}


void wxPlotWindow::OnRightUp(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	x = event.GetX();
	y = event.GetY();

	//process interaction with on-plot boxes
	//for (auto box : m_boxes)
	//{
	//	if (box->CheckIsMouseInside(x, y))
	//	{
	//		box->MouseRightUp(x, y);
	//					return;
	//	}
	//}

}

void wxPlotWindow::OnMouseMove(wxMouseEvent & event)
{
	int w, h, x, y;
	GetClientSize(&w, &h);
	x = event.GetPosition().x;
	y = event.GetPosition().y;

	if (event.LeftIsDown() && m_selected_box != nullptr)
	{
		auto &rect = m_selected_box->_get_rect();
		auto snap_distance = m_selected_box->_getsnapdistance();
		if (m_selected_box_state == BOXMOVING)
		{
			if (!m_selected_box->_has_flags(Box::EXPANDVERT))
			{
				auto ny = y - m_box_click_delta.y;
				if (abs(ny) < snap_distance)
					ny = 0;
				if (abs(ny + rect.Height() - h - 1) < snap_distance)
					ny = h - rect.Height() - 1;
				rect.SetTop(ny);
			}

			if (!m_selected_box->_has_flags(Box::EXPANDHOR))
			{
				auto nx = x - m_box_click_delta.x;
				if (abs(nx) < snap_distance)
					nx = 0;
				if (abs(nx + rect.Width() - w - 1) < snap_distance)
					nx = w - rect.Width() - 1;
				rect.SetLeft(nx);
			}
		}
		if (m_selected_box_state == BOXRESIZING)
		{
			int wr, hr, ms, v;
			wr = rect.Width();
			hr = rect.Height();
			ms = m_selected_box->_get_borderthickenss() * 2 + 5;

			if (!m_selected_box->_has_flags(Box::EXPANDVERT))
			{
				if (m_selected_box_sides & BOXTOP)
				{
					v = y - m_box_click_delta.y;
					if (abs(v) < snap_distance)
						v = 0;
					if (rect.bottom - v > ms)
						rect.SetTop(v, false);
					else
						rect.SetTop(rect.bottom - ms, false);
				}

				if (m_selected_box_sides & BOXBOTTOM)
				{
					v = y + m_box_click_delta2.y;
					if (abs(h - v - 1) < snap_distance)
						v = h - 1;
					if (v - rect.top > ms)
						rect.SetBottom(v, false);
					else
						rect.SetBottom(ms + rect.top, false);
				}

			}

			if (!m_selected_box->_has_flags(Box::EXPANDHOR))
			{
				if (m_selected_box_sides & BOXLEFT)
				{
					v = x - m_box_click_delta.x;
					if (abs(v) < snap_distance)
						v = 0;
					if (rect.right - v > ms)
						rect.SetLeft(v, false);
					else
						rect.SetLeft(rect.right - ms, false);
				}

				if (m_selected_box_sides & BOXRIGHT)
				{
					v = x + m_box_click_delta2.x;
					if (abs(w - v - 1) < snap_distance)
						v = w - 1;
					if (v - rect.left > ms)
						rect.SetRight(v, false);
					else
						rect.SetRight(ms + rect.left, false);
				}
			}
		}

		Plot::Validate(false);
	}

	if (m_lbaction == LBA_PAN && m_panning)
	{
		ProceedPan(Point<double>((double)x / (double)w, 1 - y / (double)h));
	}

	if (m_lbaction == LBA_ZOOMSELECT && (m_zoomselecting || m_zoomsel_switch))
	{
		ProceedZoomSelect(Point<double>((double)x / (double)w, 1 - (double)y / (double)h));
	}
	//event.Skip();
}

void wxPlotWindow::OnMouseWheel(wxMouseEvent & event)
{
	int x, y;
	x = event.GetX();
	y = event.GetY();

	double factor;
	if (event.GetWheelRotation() > 0)
		factor = 0.8;
	else
		factor = 1.2;

	//process interaction with on-plot widgets
	//for (auto widget : m_widgets)
	//{
	//	if (widget->MouseIsInside(x, y))
	//	{
	//		widget->MouseWheel(factor, x, y);
	//		return;
	//	}
	//}



#ifdef _DEBUG
	printf("factor=%f\n", factor);
#endif

	int w, h;
	GetClientSize(&w, &h);
	if(event.GetModifiers() == wxMOD_CONTROL)
		Zoom(Point<double>((double)x / (double)w, 1 - (double)y / (double)h), factor, factor);
	else
		if (event.GetModifiers() == wxMOD_SHIFT)
			Zoom(Point<double>((double)x / (double)w, 1 - (double)y / (double)h), 1., factor);
		else
			Zoom(Point<double>((double)x / (double)w, 1 - (double)y / (double)h), factor, 1.);
}

void wxPlotWindow::Render(wxGraphicsContext * gc)
{
	wxDouble diag_texts_pos_y = m_diag_texts_pos_y;
	DPRINTF("wxPlotWindow::Render\n");
#ifdef _DEBUG
	Timer timer;
#endif

	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	int w, h;
	GetClientSize(&w, &h);
	gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

	if (!m_areas.empty())
	{
		////render grid
		//wxGrid *grid = NULL;
		//grid = (wxGrid *)m_areas[0]->GetGrid();
		//if (grid != NULL)
		//	grid->Render(gc);

		if (m_is_data_view_modified)
		{
			wxMemoryDC memdc;
			memdc.SelectObject(*m_bitmap_buffer);
			memdc.SetBackground(GetBackgroundColour());
			memdc.Clear();
			wxGraphicsContext *gc = wxGraphicsContext::Create(memdc);
			gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
			gc->SetAntialiasMode(wxANTIALIAS_NONE);
			//render data
			for (auto area : m_areas)
			{
				for (auto series : area->GetSerie())
				{
					Renderer *renderer;
					renderer = series->GetRenderer();
					if (renderer != NULL)
						renderer->Render(gc);
					else
					{
						wxDouble text_height;
						wxString diag_text = wxString::Format("No renderer set for series ""%s""", series->GetSeriesName());
						gc->DrawText(diag_text, 5, diag_texts_pos_y);
						gc->GetTextExtent(diag_text, NULL, &text_height);
						diag_texts_pos_y += text_height;
					}
				}
			}

			delete gc;

			memdc.SelectObject(wxNullBitmap);

			m_is_data_view_modified = false;
		}

		gc->SetCompositionMode(wxCOMPOSITION_CLEAR);
		gc->DrawBitmap(*m_bitmap_buffer, 0, 0, w, h);

		//render grid
		wxGrid *grid = NULL;
		grid = (wxGrid *)m_areas[0]->GetGrid();
		if (grid != NULL)
			grid->Render(gc);

	}

//render boxes
	for_each(m_boxes.rbegin(), m_boxes.rend(), [gc](Box *box) { box->Render(gc); });
	//for (auto box_iter = m_boxes.rbegin(); box_iter != m_boxes.rend(); ++box_iter)
	//{
	//	((wxBox*)*box_iter)->Render(gc);
	//}

#ifdef _DEBUG
	double t = timer.elapsed() * 1000.;
	printf("render elapsed: %f\n", t);
#endif

}

void wxPlotWindow::RedrawPlot()
{
	DPRINTF("Plot updated\n");
	Refresh();
	Update();
}

void wxPlotWindow::DrawZoomSelection()
{
	DPRINTF("wxPlotWindow::DrawZoomSelection\n");
	int width, height;
	GetSize(&width, &height);

	int x, y, w, h;
	x = m_zoom_sel_start_rel_coord.x * width;
	y = (1 - m_zoom_sel_start_rel_coord.y) * height;
	w = m_zoom_sel_end_rel_coord.x * width - x;
	h = (1 - m_zoom_sel_end_rel_coord.y) * height - y;
	wxClientDC dc(this);
	dc.DrawBitmap(*m_bitmap_buffer, 0, 0);
	dc.SetLogicalFunction(wxXOR);
	dc.DrawRectangle(x, y, w, h);

	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

	wxGrid *grid = NULL;
	grid = (wxGrid *)m_areas[0]->GetGrid();
	if (grid != NULL)
		grid->Render(gc);

	//for (auto box : m_boxes)
	//	box->Render(gc);

	delete gc;
}

void wxPlotWindow::GetSize(int * width, int * height)
{
	GetClientSize(width, height);
}


void wxPlotWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}

void plot::wxPlotWindow::OnMenuItem_RemoveSeries(wxCommandEvent & event)
{
	DPRINTF("wxPlotWindow::OnMenuItem_RemoveSeries\n");
	//Area *area;
	//area = m_the_series->GetOwner();
	//area->DeleteSeries(m_the_series);
	//area->GetOwner()->_SetViewModifiedFlag();
	//area->GetOwner()->RedrawPlot();
}

void plot::wxPlotWindow::OnMenuItem_SeriesFitVert(wxCommandEvent & event)
{
	DPRINTF("wxPlotWindow::OnMenuItem_SeriesFitVert\n");
	//m_the_series->GetData(AXIS_Y)->Fit();
}

void plot::wxPlotWindow::OnMenuItem_SeriesFitHor(wxCommandEvent & event)
{
	DPRINTF("wxPlotWindow::OnMenuItem_SeriesFitHor\n");
	//m_the_series->GetData(AXIS_X)->Fit();
}

void plot::wxPlotWindow::OnMenuItem_SeriesFitAllDims(wxCommandEvent & event)
{
	DPRINTF("wxPlotWindow::OnMenuItem_SeriesFitAllDims\n");
	//m_the_series->Fit();
//	assert(0);
}

void plot::wxPlotWindow::emit_viewchanged()
{
	wxCommandEvent event(PLOTVIEWCHANGED, GetId());
	event.SetEventObject(this);
	ProcessWindowEvent(event);
}