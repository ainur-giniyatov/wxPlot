//#include "stdafx.h"
#include <wx/dcbuffer.h>

#include "wx/wxPlotWindow.h"
#include "wx/wxChartWindow.h"
#include "wx/wxGrid.h"
#include "wx/wxRenderer.h"

//#include "../../other/PopupToolBar.h"



using namespace plot;

wxDEFINE_EVENT(PLOTCLICKED, plot::PlotClickEvent);

const int wxPlotWindow::IDMENUITEM_SERIESPROPERTIES = wxNewId();
const int wxPlotWindow::IDMENUITEM_DELETESERIES = wxNewId();
//const int wxPlotWindow::IDMENUITEM_SERIESPROPERTIES = wxNewId();
const int wxPlotWindow::IDMENUITEM_SERIESFITVERT = wxNewId();
const int wxPlotWindow::IDMENUITEM_SERIESFITHOR = wxNewId();
const int wxPlotWindow::IDMENUITEM_SERIESFITALL = wxNewId();

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
//EVT_MENU(wxPlotWindow::ID_MENUITEM_ADDLEGENDS, wxPlotWindow::OnMenuItem_AddLegends)
END_EVENT_TABLE()


wxPlotWindow::wxPlotWindow(wxWindow * parent) :wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER)
{
	DPRINTF("wxPlotWindow: ctor\n");
	SetName("plot");
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_sizer = new wxBoxSizer(wxHORIZONTAL);


	SetSizer(m_sizer);
	Layout();

	m_seriesmenu.Append(IDMENUITEM_SERIESFITVERT, "Fit vertical");
	Connect(IDMENUITEM_SERIESFITVERT, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_SeriesFitVert);

	m_seriesmenu.Append(IDMENUITEM_SERIESFITHOR, "Fit horiz");
	Connect(IDMENUITEM_SERIESFITHOR, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_SeriesFitHor);
	
	m_seriesmenu.Append(IDMENUITEM_SERIESFITALL, "Fit both");
	Connect(IDMENUITEM_SERIESFITALL, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_SeriesFitAll);
	
	m_seriesmenu.Append(IDMENUITEM_SERIESPROPERTIES, "Properties");
	Connect(IDMENUITEM_SERIESPROPERTIES, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_SeriesProperties);

	m_seriesmenu.Append(IDMENUITEM_DELETESERIES, "Delete");
	Connect(IDMENUITEM_DELETESERIES, wxEVT_MENU, (wxObjectEventFunction)&wxPlotWindow::OnMenuItem_DeleteSeries);
	
	
	m_bitmap_buffer = new wxBitmap();

	m_diag_texts_pos_y = 5;

	wxTitleBox *titlebox;
	titlebox = new wxTitleBox(this);
	AddBox(titlebox);

	m_popup_tool = new wxPopupSeriesTool(this);
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
	
	for (auto area : m_areas)
		for (auto series : area->GetSerie())
			series->GetRenderer()->_setsize(sz.GetWidth(), sz.GetHeight());
		
	
	m_bitmap_buffer->Create(sz);
	for (auto box : m_boxes)
		box->Sizing();

	Refresh();
	Layout();
}

void plot::wxPlotWindow::_popup_seriesmenu(Series * series)
{
	//m_series_pointed = series;
	m_popup_tool->SetSelectedSeries(series);
	m_popup_tool->Position(wxGetMousePosition(), wxSize(0, 0));
	m_popup_tool->Show();
//	popup_tool->Popup();
//	wxPopupToolBar *poptbar;
//	poptbar = new wxPopupToolBar(this, series);
////	poptbar->Show();
//	poptbar->Popup();
//	//ToolBarMenu *tbm;
//	//tbm = new ToolBarMenu(this);
//	//PopupMenu(&m_seriesmenu);
}

void plot::wxPlotWindow::OnMenuItem_DeleteSeries(wxCommandEvent & event)
{
	//m_series_pointed->GetOwner()->DeleteSeries(m_series_pointed);
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
		if(box->CheckIsMouseInside(x, y))
		{
			box->MouseLeftDown(x, y);
			//plotclick_event.SetBox(box);
			return;
		}
	}

	SeriesSelection ser_sel;
	_getspottedseries(Point<int>(x, y), ser_sel);
	if (ser_sel.GetSeries() != nullptr)
	{
		ser_sel.GetSeries()->BringToFront();
		ser_sel.GetSeries()->SeriesUpdated();
		plotclick_event.SetSeriesSelection(ser_sel);
		if (m_popup_tool->IsShown())
		{
			m_popup_tool->SetSelectedSeries(ser_sel.GetSeries());
		}
	}

	
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

	//for (auto widget : m_widgets)
	//{
	//	if (widget->MouseIsInside(x, y))
	//	{
	//		widget->OnMouseLeftUp(x, y);
	//		//return;
	//	}
	//}

	//process interaction with on-plot boxes
	for (auto box : m_boxes)
	{
		if (box->CheckIsMouseInside(x, y))
		{
			box->MouseLeftUp(x, y);
//			return;
		}
	}

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
	for (auto box : m_boxes)
	{
		if (box->CheckIsMouseInside(x, y))
		{
			box->MouseRightDown(x, y);
						return;
		}
	}

	//series menu
	SeriesSelection ser_sel;
	_getspottedseries(Point<int>(x, y), ser_sel);
	if (ser_sel.GetSeries() != nullptr)
	{
		ser_sel.GetSeries()->BringToFront();
		_popup_seriesmenu(ser_sel.GetSeries());
		return;
	}

	//plot menu
	if(m_menu.GetMenuItemCount() != 0)
		PopupMenu(&m_menu);
}


void wxPlotWindow::OnRightUp(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	x = event.GetX();
	y = event.GetY();

	//process interaction with on-plot boxes
	for (auto box : m_boxes)
	{
		if (box->CheckIsMouseInside(x, y))
		{
			box->MouseRightUp(x, y);
						return;
		}
	}

}

void wxPlotWindow::OnMouseMove(wxMouseEvent & event)
{
	int w, h, x, y;
	GetClientSize(&w, &h);
	x = event.GetPosition().x;
	y = event.GetPosition().y;

	//for (auto widget : m_widgets)
	//{
	//	if (widget->MouseIsInside(x, y))
	//	{
	//		widget->MouseMoving(x, y);
	//	}
	//}

	for (auto box : m_boxes)
	{
		if (box->CheckIsMouseInside(x, y))
		{
			box->MouseMove(x, y);
		}
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
			//gc->SetAntialiasMode(wxANTIALIAS_NONE);
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
	for (auto box_iter = m_boxes.rbegin(); box_iter != m_boxes.rend(); ++box_iter)
	{
		((wxBox*)*box_iter)->Render(gc);
	}

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

	for (auto box : m_boxes)
		box->Render(gc);

	delete gc;
}

void wxPlotWindow::GetSize(int * width, int * height)
{
	GetClientSize(width, height);
}

//void plot::wxPlotWindow::_spotseries(SeriesSelection & seriesselection)
//{
//#ifdef _DEBUG
//	printf("spot: %s %i %i\n", seriesselection.GetSeries()->GetSeriesName(), seriesselection.GetStartIndex(), seriesselection.GetEndIndex());
//#endif
//}

//void wxPlotWindow::OnMenuItem_AddLegends(wxCommandEvent & event)
//{
//	DPRINTF("wxPlotWindow::OnMenuItem_AddLegends\n");
//	LegendsWidget *legendswidget;
//	legendswidget = new LegendsWidget(this);
//}


void wxPlotWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}

void plot::wxPlotWindow::OnMenuItem_SeriesProperties(wxCommandEvent & event)
{

}

void plot::wxPlotWindow::OnMenuItem_SeriesFitVert(wxCommandEvent & event)
{
}

void plot::wxPlotWindow::OnMenuItem_SeriesFitHor(wxCommandEvent & event)
{

}

void plot::wxPlotWindow::OnMenuItem_SeriesFitAll(wxCommandEvent & event)
{
	//m_series_pointed->Fit();

}