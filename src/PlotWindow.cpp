//#include "stdafx.h"
#include "PlotWindow.h"
#include "ChartWindow.h"

#include <wx/dcbuffer.h>

//#include "LegendsWidget.h"

//const int PlotWindow::ID_MENUITEM_ADDLEGENDS = wxNewId();

BEGIN_EVENT_TABLE(PlotWindow, wxWindow)
EVT_PAINT(PlotWindow::OnPaint)
EVT_ERASE_BACKGROUND(PlotWindow::OnEraseBackground)
EVT_SIZE(PlotWindow::OnResize)
EVT_MOUSEWHEEL(PlotWindow::OnMouseWheel)
EVT_LEFT_DOWN(PlotWindow::OnLeftDown)
EVT_LEFT_UP(PlotWindow::OnLeftUp)
EVT_MOTION(PlotWindow::OnMouseMove)
EVT_RIGHT_DOWN(PlotWindow::OnRightDown)
EVT_RIGHT_UP(PlotWindow::OnRightUp)
//EVT_MENU(PlotWindow::ID_MENUITEM_ADDLEGENDS, PlotWindow::OnMenuItem_AddLegends)
END_EVENT_TABLE()


PlotWindow::PlotWindow(wxWindow * parent) :wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER)
{
	DPRINTF("PlotWindow: ctor\n");
	SetName("plot");
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_sizer = new wxBoxSizer(wxHORIZONTAL);


	SetSizer(m_sizer);
	Layout();

	//m_menu = new wxMenu();
	//m_menu_addwidget = new wxMenu();
	//m_menu.AppendSubMenu(m_menu_addwidget, "Add widget");

	//m_menu_addwidget->Append(ID_MENUITEM_ADDLEGENDS, "Legends");
	m_bitmap_buffer = new wxBitmap();
	m_refresh_bitmap = true;
}

PlotWindow::~PlotWindow()
{
	DPRINTF("PlotWindow: dtor\n");
	
	delete m_bitmap_buffer;
	
}

void PlotWindow::OnPaint(wxPaintEvent & event)
{
	wxBufferedPaintDC dc(this);
	//dc.SetPen(*wxTRANSPARENT_PEN);
	//dc.DrawRectangle(GetClientRect());
	//dc.Clear();
	m_refresh_bitmap = true;
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

	dc.DrawBitmap(*m_bitmap_buffer, 0, 0);
}

void PlotWindow::OnEraseBackground(wxEraseEvent & event)
{
	event.GetDC()->Clear();
}

void PlotWindow::OnResize(wxSizeEvent & event)
{
	m_refresh_bitmap = true;
	m_bitmap_buffer->Create(GetClientSize());
	for (auto box : m_boxes)
		box->Sizing();

	Refresh();
	Layout();
}

void PlotWindow::OnLeftDown(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	x = event.GetX();
	y = event.GetY();
	//process interaction with on-plot widgets
	//for (auto widget : m_widgets)
	//{
	//	if(widget->MouseIsInside(x, y))
	//	{ 
	//		widget->OnMouseLeftDown(x, y);
	//		return;
	//	}
	//}

	//process interaction with on-plot boxes
	for (auto box : m_boxes)
	{
		if(box->CheckIsMouseInside(x, y))
		{ 
			box->MouseLeftDown(x, y);
			return;
		}
	}

	//GetParent()->SetFocus();
	int w, h;
	GetClientSize(&w, &h);

	if (m_lbaction == LBA_PAN)
	{
		StartPan((double)x / (double)w, 1 - (double)y / (double)h);
	}

	if (m_lbaction == LBA_ZOOMSELECT)
	{
		StartZoomSelect((double)x / (double)w, 1 - (double)y / (double)h);
	}

	if(!HasCapture())
        CaptureMouse();
}

void PlotWindow::OnLeftUp(wxMouseEvent & event)
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

void PlotWindow::OnRightDown(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	x = event.GetX();
	y = event.GetY();

	//for (auto widget : m_widgets)
	//{
	//	if (widget->MouseIsInside(x, y))
	//	{
	//		widget->OnMouseRightUp(x, y);
	//		return;
	//	}
	//}

	if(m_menu.GetMenuItemCount() != 0)
		PopupMenu(&m_menu);
}

void PlotWindow::OnRightUp(wxMouseEvent & event)
{
	event.Skip();
	int x, y;
	x = event.GetX();
	y = event.GetY();

	//for (auto widget : m_widgets)
	//{
	//	if (widget->MouseIsInside(x, y))
	//	{
	//		widget->OnMouseRightUp(x, y);
	//		return;
	//	}
	//}
}

void PlotWindow::OnMouseMove(wxMouseEvent & event)
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
		ProceedPan((double)x / (double)w, 1 - y / (double)h);
	}

	if (m_lbaction == LBA_ZOOMSELECT && (m_zoomselecting || m_zoomsel_switch))
	{
		ProceedZoomSelect((double)x / (double)w, 1 - (double)y / (double)h);
	}
	//event.Skip();
}

void PlotWindow::OnMouseWheel(wxMouseEvent & event)
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
		ZoomWheel((double)x / (double)w, 1 - (double)y / (double)h, factor, factor);
	else
		if (event.GetModifiers() == wxMOD_SHIFT)
			ZoomWheel((double)x / (double)w, 1 - (double)y / (double)h, 1., factor);
		else
			ZoomWheel((double)x / (double)w, 1 - (double)y / (double)h, factor, 1.);
}

void PlotWindow::Render(wxGraphicsContext * gc)
{
	DPRINTF("PlotWindow::Render\n");
	gc->SetFont(*wxNORMAL_FONT, *wxBLACK);
	int w, h;
	GetClientSize(&w, &h);
	gc->SetAntialiasMode(wxANTIALIAS_NONE);
	gc->DrawText(m_plot_name, w - 30, 2);
	if (m_spaces.empty())
		return;
//render grid
	Grid *grid = NULL;
	grid = m_spaces[0]->GetGrid();
	if(grid != NULL)
		grid->Render(gc);

	
//render data
	for (auto space : m_spaces)
	{
		for (auto series : space->GetSerie())
		{
			//
			Renderer *renderer;
			renderer = series->GetRenderer();
			if(renderer != NULL)
				renderer->Render(gc);
		}
	}

	//render widgets
	//for (auto widget : m_widgets)
	//{
	//	widget->Render(gc);
	//}

	//render boxes
	for (auto box : m_boxes)
	{
		box->Render(gc);
	}
}

void PlotWindow::RedrawPlot()
{
	DPRINTF("Plot updated\n");
	Refresh();
	Update();
}

void PlotWindow::DrawZoomSelection(double rx, double ry)
{
	DPRINTF("PlotWindow::DrawZoomSelection\n");
	int width, height;
	GetSize(&width, &height);

	int x, y, w, h;
	x = m_start_rx_zsel * width;
	y = (1 - m_start_ry_zsel) * height;
	w = (rx - m_start_rx_zsel) * width;
	h = ((1 - ry) - (1 - m_start_ry_zsel)) * height;
	wxClientDC dc(this);
	dc.DrawBitmap(*m_bitmap_buffer, 0, 0);
	dc.SetLogicalFunction(wxXOR);
	dc.DrawRectangle(x, y, w, h);
}

void PlotWindow::GetSize(int * width, int * height)
{
	GetClientSize(width, height);
}

//void PlotWindow::OnMenuItem_AddLegends(wxCommandEvent & event)
//{
//	DPRINTF("PlotWindow::OnMenuItem_AddLegends\n");
//	LegendsWidget *legendswidget;
//	legendswidget = new LegendsWidget(this);
//}


void PlotWindow::OnMouseCaptureLost(wxMouseCaptureLostEvent &event)
{

}
