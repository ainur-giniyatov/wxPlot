//#include "stdafx.h"
#include <algorithm>
#include <wx/dcbuffer.h>

#include "wx/wxSubPlot.h"
#include "wx/wxGrid.h"
#include "wx/wxRenderer.h"
#include "wx/wxBox.h"

using namespace plot;

wxDEFINE_EVENT(PLOTCLICKED, plot::PlotClickEvent);

wxDEFINE_EVENT(PLOTVIEWCHANGED, wxCommandEvent);

const int wxSubplot::IDMENUITEM_REMOVESERIES = wxNewId();
const int wxSubplot::IDMENUITEM_SERIESFITVERT = wxNewId();
const int wxSubplot::IDMENUITEM_SERIESFITHOR = wxNewId();
const int wxSubplot::IDMENUITEM_SERIESFITALLDIMS = wxNewId();

BEGIN_EVENT_TABLE(wxSubplot, wxPanel)
EVT_PAINT(wxSubplot::OnPaint)
EVT_ERASE_BACKGROUND(wxSubplot::OnEraseBackground)
EVT_SIZE(wxSubplot::OnResize)
EVT_MOUSEWHEEL(wxSubplot::OnMouseWheel)
EVT_LEFT_DOWN(wxSubplot::OnLeftDown)
EVT_LEFT_UP(wxSubplot::OnLeftUp)
EVT_MOTION(wxSubplot::OnMouseMove)
EVT_RIGHT_DOWN(wxSubplot::OnRightDown)
EVT_RIGHT_UP(wxSubplot::OnRightUp)
END_EVENT_TABLE()


wxSubplot::wxSubplot(wxWindow * parent):wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER) // :wxSubplot_fb(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER)
{
	DPRINTF("wxSubplot: ctor\n");
	SetName("subplot");
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	//m_sizer = new wxBoxSizer(wxHORIZONTAL);


	//SetSizer(m_sizer);
	//Layout();

	m_series_menu.Append(IDMENUITEM_REMOVESERIES, "Remove");
	Connect(IDMENUITEM_REMOVESERIES, wxEVT_MENU, (wxObjectEventFunction)&wxSubplot::OnMenuItem_RemoveSeries);
	
	m_series_menu.Append(IDMENUITEM_SERIESFITVERT, "Fit vertical");
	Connect(IDMENUITEM_SERIESFITVERT, wxEVT_MENU, (wxObjectEventFunction)&wxSubplot::OnMenuItem_SeriesFitVert);

	m_series_menu.Append(IDMENUITEM_SERIESFITHOR, "Fit horiz");
	Connect(IDMENUITEM_SERIESFITHOR, wxEVT_MENU, (wxObjectEventFunction)&wxSubplot::OnMenuItem_SeriesFitHor);
	
	m_series_menu.Append(IDMENUITEM_SERIESFITALLDIMS, "Fit both");
	Connect(IDMENUITEM_SERIESFITALLDIMS, wxEVT_MENU, (wxObjectEventFunction)&wxSubplot::OnMenuItem_SeriesFitAllDims);
	
	m_bitmap_buffer = new wxBitmap();

	m_diag_texts_pos_y = 5;
	m_hphoff = 0;
	m_vphoff = 0;
	m_hphrange = 0;
	m_vphrange = 0;
	//Box *box = new wxBox(Box::MOVEABLE | Box::RESIZEABLE);
	//AddBox(box);

	//Box *box;
	//box = new wxTitleBox();
	//AddBox(box);


//	wxTitleBox *titlebox;
//	titlebox = new wxTitleBox();
//	AddBox(titlebox);

//	m_popup_tool = new wxPopupSeriesTool(this);
	SetBackgroundColour(*wxYELLOW);
}

wxSubplot::~wxSubplot()
{
	DPRINTF("wxSubplot: dtor\n");

	delete m_bitmap_buffer;

}

void wxSubplot::OnPaint(wxPaintEvent & event)
{
	wxBufferedPaintDC dc(this);

	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	
	if (m_serie.empty())
		dc.Clear();

	Render(gc);

	//gc->SetPen(*wxBLACK_PEN);
	//gc->SetBrush(*wxTRANSPARENT_BRUSH);
	//gc->DrawRectangle(0, 0, m_size.w, m_size.h);
	delete gc;
}

void wxSubplot::OnEraseBackground(wxEraseEvent & event)
{
	event.GetDC()->Clear();
}

void wxSubplot::OnResize(wxSizeEvent & event)
{
	m_is_data_view_modified = true;
	
	wxSize sz(GetClientSize());
		
	m_bitmap_buffer->Create(sz);


	plot_resized();


	plot::Subplot::Validate();

	event.Skip();

}

void plot::wxSubplot::_popup_seriesmenu(Series * series)
{
	m_the_series = series;
	series->BringToFront();
	series->Validate();
	m_series_menu.FindItem(IDMENUITEM_REMOVESERIES)->SetItemLabel(wxString::Format("Remove %s", series->GetSeriesName()));
	PopupMenu(&m_series_menu);
}

void wxSubplot::OnLeftDown(wxMouseEvent & event)
{
	event.Skip();

	PlotClickEvent plotclick_event(PLOTCLICKED, GetId(), this);
	plotclick_event.SetEventObject(this);

	Point<int> mcoord(event.GetX(), event.GetY());

	Box *box;
	box = hitbox(mcoord);

	m_selected_box = box;
	if (box != nullptr)
	{
		//box interaction done in Plot class
		m_boxes.erase(std::remove(m_boxes.begin(), m_boxes.end(), box), m_boxes.end());
		m_boxes.insert(m_boxes.begin(), box);
		Subplot::Validate(false);
	}
	else
	{
		Series *series;
		int dotindex_first, dotindex_last;
		series = hitseries(&dotindex_first, &dotindex_last, mcoord);
		if (series != nullptr)
		{
			//interaction with series plot
			SeriesSelection ser_sel = SeriesSelection(series, dotindex_first, dotindex_last);
			plotclick_event.SetSeriesSelection(ser_sel);
			ProcessWindowEvent(plotclick_event);
			series->BringToFront();
			Subplot::Validate(true);
			//return;
		}

	}


	leftdown(mcoord);


	ProcessWindowEvent(plotclick_event);

	if(!HasCapture())
        CaptureMouse();
}

void wxSubplot::OnLeftUp(wxMouseEvent & event)
{
	int x, y;
	x = event.GetX();
	y = event.GetY();
	Point<int> mcoord(x, y);

	leftup(mcoord);
	//EndZoomSelect();

	//boxprocess_leftup(mcoord);

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

void wxSubplot::OnRightDown(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	//x = event.GetX();
	//y = event.GetY();

	////process interaction with on-plot boxes
	////for (auto box : m_boxes)
	////{
	////	if (box->CheckIsMouseInside(x, y))
	////	{
	////		box->MouseRightDown(x, y);
	////					return;
	////	}
	////}

	////series menu
	//SeriesSelection ser_sel;
	//_getspottedseries(Point<int>(x, y), ser_sel);
	//if (ser_sel.GetSeries() != nullptr)
	//{
	//	_popup_seriesmenu(ser_sel.GetSeries());
	//	
	//	return;
	//}

	////plot menu
	//if(m_context_menu.GetMenuItemCount() != 0)
	//	PopupMenu(&m_context_menu);
}


void wxSubplot::OnRightUp(wxMouseEvent & event)
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

void wxSubplot::OnMouseMove(wxMouseEvent & event)
{
	int x, y;
	
	x = event.GetPosition().x;
	y = event.GetPosition().y;
	Point<int> mcoord(x, y);
	int mstate = 0;
	if (event.LeftIsDown())
		mstate |= MOUSESTATE_LEFTBUTTON;

	if (event.LeftIsDown())
		mstate |= MOUSESTATE_RIGHTBUTTON;

	if (event.MiddleIsDown())
		mstate |= MOUSESTATE_MIDDLEBUTTON;

	motion(mstate, mcoord);

	//if (event.LeftIsDown() && m_selected_box != nullptr)
	//{
	//	boxprocess_mousemove(mcoord);
	//}

	//if (m_lbaction == LBA_PAN && m_panning)
	//{
	//	ProceedPan(mcoord);
	//}

	//if (m_lbaction == LBA_ZOOMSELECT && (m_zoomselecting || m_zoomsel_switch))
	//{
	//	//ProceedZoomSelect(Point<double>((double)x / (double)w, 1 - (double)y / (double)h));
	//}
	//event.Skip();
}

void wxSubplot::OnMouseWheel(wxMouseEvent & event)
{
	Point<int> mcoord(event.GetX(), event.GetY());
	int mousestate = 0;
	
	if (event.GetWheelRotation() > 0)
		mousestate |= MOUSESTATE_WHEELDOWN;
	else
		mousestate |= MOUSESTATE_WHEELUP;

	int keymod = 0;
	if(event.GetModifiers() == wxMOD_CONTROL)
		keymod |= KEYMOD_CTRL;
	else
		if (event.GetModifiers() == wxMOD_SHIFT)
			keymod |= KEYMOD_SHIFT;
		
	wheel(keymod, mousestate, mcoord);
	
}

void wxSubplot::Render(wxGraphicsContext * gc)
{
	wxDouble diag_texts_pos_y = m_diag_texts_pos_y;
	DPRINTF("wxSubplot::Render\n");
#ifdef _DEBUG
	Timer timer;
#endif

	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	int w, h;
	GetClientSize(&w, &h);
	gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

	if (!m_serie.empty())
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
			for (auto series : m_serie)
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

			delete gc;

			memdc.SelectObject(wxNullBitmap);

			m_is_data_view_modified = false;
		}

		gc->SetCompositionMode(wxCOMPOSITION_CLEAR);
		gc->DrawBitmap(*m_bitmap_buffer, 0, 0, w, h);

		//render grid
		wxGrid *grid = NULL;
//		grid = (wxGrid *)m_areas[0]->GetGrid();
		if (grid != NULL)
			grid->Render(gc);

	}


	//
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

void wxSubplot::RedrawPlot()
{
	DPRINTF("Plot updated\n");
	Refresh();
	Update();
}
//
//void plot::wxSubplot::AddLeftScaleWidget(wxScaleWidget * scalewidget)
//{
//	bSizer_left->Add(scalewidget, 1, wxEXPAND);
//	fgSizer3->Layout();
//}
//
//void plot::wxSubplot::AddRightScaleWidget(wxScaleWidget * scalewidget)
//{
//	bSizer_right->Add(scalewidget, 1, wxEXPAND);
//	fgSizer3->Layout();
//}
//
//void plot::wxSubplot::AddTopScaleWidget(wxScaleWidget * scalewidget)
//{
//	bSizer_top->Add(scalewidget, 1, wxEXPAND);
//	fgSizer3->Layout();
//}
//
//void plot::wxSubplot::AddBottomScaleWidget(wxScaleWidget * scalewidget)
//{
//	bSizer_bottom->Add(scalewidget, 1, wxEXPAND);
//	fgSizer3->Layout();
//}

//void wxSubplot::DrawZoomSelection()
//{
//	DPRINTF("wxSubplot::DrawZoomSelection\n");
//	int width, height;
//	GetSize(&width, &height);
//
//	int x, y, w, h;
//	x = m_zoom_sel_start_rel_coord.x * width;
//	y = (1 - m_zoom_sel_start_rel_coord.y) * height;
//	w = m_zoom_sel_end_rel_coord.x * width - x;
//	h = (1 - m_zoom_sel_end_rel_coord.y) * height - y;
//	wxClientDC dc(this);
//	dc.DrawBitmap(*m_bitmap_buffer, 0, 0);
//	dc.SetLogicalFunction(wxXOR);
//	dc.DrawRectangle(x, y, w, h);
//
//	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
//
//	wxGrid *grid = NULL;
//	grid = (wxGrid *)m_areas[0]->GetGrid();
//	if (grid != NULL)
//		grid->Render(gc);
//
//	//for (auto box : m_boxes)
//	//	box->Render(gc);
//
//	delete gc;
//}

void wxSubplot::GetSize(int * width, int * height)
{
	GetClientSize(width, height);
}


void wxSubplot::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}

void plot::wxSubplot::OnMenuItem_RemoveSeries(wxCommandEvent & event)
{
	DPRINTF("wxSubplot::OnMenuItem_RemoveSeries\n");
	//Area *area;
	//area = m_the_series->GetOwner();
	//area->DeleteSeries(m_the_series);
	//area->GetOwner()->_SetViewModifiedFlag();
	//area->GetOwner()->RedrawPlot();
}

void plot::wxSubplot::OnMenuItem_SeriesFitVert(wxCommandEvent & event)
{
	DPRINTF("wxSubplot::OnMenuItem_SeriesFitVert\n");
	//m_the_series->GetData(AXIS_Y)->Fit();
}

void plot::wxSubplot::OnMenuItem_SeriesFitHor(wxCommandEvent & event)
{
	DPRINTF("wxSubplot::OnMenuItem_SeriesFitHor\n");
	//m_the_series->GetData(AXIS_X)->Fit();
}

void plot::wxSubplot::OnMenuItem_SeriesFitAllDims(wxCommandEvent & event)
{
	DPRINTF("wxSubplot::OnMenuItem_SeriesFitAllDims\n");
	//m_the_series->Fit();
//	assert(0);
}

void plot::wxSubplot::emit_viewchanged()
{
	wxCommandEvent event(PLOTVIEWCHANGED, GetId());
	event.SetEventObject(this);
	ProcessWindowEvent(event);
}

const Size<int> plot::wxSubplot::_get_backend_size()
{
	int w, h;
	GetClientSize(&w, &h);
	return Size<int>(w - 1, h - 1);
}
