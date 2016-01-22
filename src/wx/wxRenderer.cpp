#include <wx/graphics.h>

#include "wx/wxRenderer.h"
#include "wx/colorbase.h"

using namespace plot;

//wxRenderer::wxRenderer()
//{
//}
//
//wxRenderer::~wxRenderer()
//{
//}

template<typename T1, typename T2>
wxRendererTyped<T1, T2>::wxRendererTyped()
{
}

template<typename T1, typename T2>
wxRendererTyped<T1, T2>::~wxRendererTyped()
{
}

template<typename T1, typename T2>
void wxRendererTyped<T1, T2>::Render(void* v_gc)
{
	if (!m_visible)
		return;

	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	int width, height;
	
	assert(m_owner_series != NULL);
		
	m_owner_series->GetOwner()->GetOwner()->GetSize(&width, &height);
	
	//gc->DrawText("Renderer2DTyped", 10, m_text_pos);
	
	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxTRANSPARENT_BRUSH);
		
	Series *series;
	series = (Series *)m_owner_series;
	
	DataTyped<T1> *xdata = (DataTyped<T1> *)series->GetData(AXIS_X);
	DataTyped<T2> *ydata = (DataTyped<T2> *)series->GetData(AXIS_Y);
	
	if (xdata == NULL || ydata == NULL)
	{
		gc->DrawText("Renderer2DTyped: incosistent series", 10, m_text_pos);
		return;
	}
	
	wxASSERT(xdata->GetSize() == ydata->GetSize());
	size_t data_size;
	
	data_size = xdata->GetSize();
	
	Axis *xaxis;
	Axis *yaxis;
	
	Area *space = (Area*)m_owner_series->GetOwner();
	
	xaxis = space->GetAxis(AXIS_X);
	yaxis = space->GetAxis(AXIS_Y);
	
	auto xda = xdata->GetDataArray();
	auto yda = ydata->GetDataArray();
	
	double xoffset, yoffset, xrange, yrange;
	
	xoffset = xaxis->GetOffset();
	xrange = xaxis->GetRange();
	yoffset = yaxis->GetOffset();
	yrange = yaxis->GetRange();
	
	size_t indx = 0;
		
	//drawing lines
	if (m_line_visible)
	{
	
		int x1, y1, x2, y2;
	
		x1 = ((double)xda[indx] - xoffset) / xrange * (double)width;
		y1 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;
	
		indx++;
	
		wxPen pen;
		pen.SetWidth(m_line_thickness);
		pen.SetColour(COLOR_BASE[m_line_color_index]);
		gc->SetPen(pen);
	
		for (; indx < data_size - 1; indx++)
		{
	
			if (x1 > width)
				break;
	
//			indx++;
			y2 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;
			x2 = ((double)xda[indx] - xoffset) / xrange * (double)width;
			if (x2 < 0)
				continue;
	
	
	
			while (abs(x2 - x1) < 4 && abs(y2 - y1) < 4)
			{
				indx++;
				if (indx == data_size)
					break;
				x2 = ((double)xda[indx] - xoffset) / xrange * (double)width;
				y2 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;
			}
	
			gc->StrokeLine(x1, y1, x2, y2);
			x1 = x2;
			y1 = y2;
		}
	}
	
	//draw marks
	if (m_markers_visible)
	{
		indx = 0;
		int x1, y1, x2, y2;
	
		x1 = ((double)xda[indx] - xoffset) / xrange * (double)width;
		y1 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;
	
		indx++;
	
		PrepareMarkGC(gc, m_marker_style, m_marker_size, m_marker_color_index);
		for (; indx < data_size ; indx++)
		{
	
			if (x1 > width)
				break;
	
//			indx++;
			y2 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;
			x2 = ((double)xda[indx] - xoffset) / xrange * (double)width;
	
			if (x2 < 0)
				continue;
	
			while (abs(x2 - x1) < 4 && abs(y2 - y1) < 4)
			{
				indx++;
				if (indx == data_size)
					break;
				x2 = ((double)xda[indx] - xoffset) / xrange * (double)width;
				y2 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;
			}
	
			//if (m_marker_style == MARKER_CIRCLE)
			//{
			//	int r;
			//	r = m_marker_size / 2 + 1;
			//	gc->DrawEllipse(x1 - r, y1 - r, r + r, r + r);
			//	//gc->DrawBitmap(marker, x1 - 5, y1 - 5, 10, 10);
			//}
			::PutMark(gc, x1, y1, m_marker_style, m_marker_size);
			x1 = x2;
			y1 = y2;
		}
	}
	
	//max/min lines
	//double maxy, miny;
	//maxy = ydata->GetDataMax();
	//miny = ydata->GetDataMin();
	//int y;
	//y = height - (maxy - yoffset) / yrange * (double)height;
	//gc->StrokeLine(0, y, width, y);
	//y = height - (miny - yoffset) / yrange * (double)height;
	//gc->StrokeLine(0, y, width, y);
}

template<typename T1, typename T2>
void plot::wxRendererTyped<T1, T2>::PutMark(void *v_gc, int x, int y)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	PrepareMarkGC(gc, m_marker_style, m_marker_size, m_marker_color_index);
	::PutMark(gc, x, y, m_marker_style, m_marker_size);
}

template<typename T1, typename T2>
void plot::wxRendererTyped<T1, T2>::PutLine(void *v_gc, int x, int y, int w, int h)
{
	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	wxPen pen;
	pen.SetWidth(m_line_thickness);
	pen.SetColour(COLOR_BASE[m_line_color_index]);
	gc->SetPen(pen);
	gc->StrokeLine(x, y, x + w, y + h);

}
