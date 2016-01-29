#include <wx/graphics.h>

#include "wx/wxRenderer.h"
#include "wx/colorbase.h"
#include "wx/wxMarker.h"
#include "wx/wxLine.h"

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
	m_marker = new wxMarkerSquare();
	m_line = new wxSimpleLine();

	m_left_index = 0;
	m_right_index = 0;
}

template<typename T1, typename T2>
wxRendererTyped<T1, T2>::~wxRendererTyped()
{
	if(m_marker != nullptr)
		delete m_marker;

	if(m_line != nullptr)
		delete m_line;
}

template<typename T1, typename T2>
bool plot::wxRendererTyped<T1, T2>::_isspotted(Point<int>& mouse_coord, SeriesSelection & series_selection)
{
	//int m_width, m_height;

	assert(m_owner_series != NULL);

	if (!m_visible)
		return false;

	//m_owner_series->GetOwner()->GetOwner()->GetSize(&m_width, &m_height);

	Series *series;
	series = (Series *)m_owner_series;

	double x1, y1, x2, y2;
	DataTyped<T1> *xdata = (DataTyped<T1> *)series->GetData(AXIS_X);
	DataTyped<T2> *ydata = (DataTyped<T2> *)series->GetData(AXIS_Y);
	
	assert(xdata != nullptr);
	assert(ydata != nullptr);

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

	if (m_marker != nullptr && m_marker->_isvisible())
	{
		for (size_t indx = m_left_index; indx <= m_right_index; indx++)
		{
			x1 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
			y1 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
			if (m_marker->_isspotted(mouse_coord, Point<int>(x1, y1)))
			{
				series_selection = SeriesSelection(m_owner_series, indx, indx);
				return true;
			}
		}
	}

	if (m_line != nullptr && m_line->_isvisible())
	{
		x1 = ((double)xda[m_left_index] - xoffset) / xrange * (double)m_width;
		y1 = m_height - ((double)yda[m_left_index] - yoffset) / yrange * (double)m_height;
		for (size_t indx = m_left_index + 1; indx <= m_right_index; indx++)
		{
			x2 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
			y2 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
			if (m_line->_isspotted(mouse_coord, Point<int>(x1, y1), Point<int>(x2, y2)))
			{
				series_selection = SeriesSelection(m_owner_series, 0, xdata->GetSize());
				return true;
			}

			x1 = x2;
			y1 = y2;
		}
	}

	return false;
}

template<typename T1, typename T2>
void wxRendererTyped<T1, T2>::Render(void* v_gc)
{
	if (!m_visible)
		return;

	wxGraphicsContext *gc = (wxGraphicsContext *)v_gc;
	
	assert(m_owner_series != NULL);

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
	
	Area *area = (Area*)m_owner_series->GetOwner();
	
	xaxis = area->GetAxis(AXIS_X);
	yaxis = area->GetAxis(AXIS_Y);
	
	auto xda = xdata->GetDataArray();
	auto yda = ydata->GetDataArray();
	
	double xoffset, yoffset, xrange, yrange;
	
	xoffset = xaxis->GetOffset();
	xrange = xaxis->GetRange();
	yoffset = yaxis->GetOffset();
	yrange = yaxis->GetRange();
	

	//x1 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
	double x_width_div_range = (double)m_width / xrange;
	double x_offs_mult_width_div_range = xoffset * x_width_div_range;

	//y1 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
	double y_height_div_range = (double)m_height / yrange;
	double y_offs_mult_width_div_range = yoffset * y_height_div_range;


	size_t indx = 0;

	//determine first and last visible marks. TO DO: binary search
	for (; indx < data_size; indx++)
	{
		int x;
		x = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
		if (x > 0)
			break;
	}

	m_left_index = (indx != 0) ? indx - 1 : 0;
	
	for (; indx < data_size; indx++)
	{
		int x;
		x = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
		if (x > m_width)
			break;
	}

	m_right_index = (indx == data_size) ? indx - 1 : indx;

#ifdef _DEBUG
	int points_count = 0;
#endif

	//drawing lines
	if (m_line != nullptr && m_line->_isvisible())
	{
	
		int x1, y1, x2, y2;
	
		indx = m_left_index;

		x1 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
		//y1 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
		y1 = m_height - (double)yda[indx] * y_height_div_range + y_offs_mult_width_div_range;
		
	
		indx++;
	
		((wxLine *)m_line)->InitStyleAndColour(gc);

		for (; indx <= m_right_index ; indx++)
		{

			//x2 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
			x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
			//y2 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
			y2 = m_height - (double)yda[indx] * y_height_div_range + y_offs_mult_width_div_range;
	
			while (abs(x2 - x1) < 4 && abs(y2 - y1) < 4)
			{
				if (indx == m_right_index)
					break;

				indx++;
				//x2 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
				x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
				//y2 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
				y2 = m_height - (double)yda[indx] * y_height_div_range + y_offs_mult_width_div_range;
			}
	
			points_count++;

			m_line->Render(gc, Point<int>(x1, y1), Point<int>(x2, y2));
			x1 = x2;
			y1 = y2;
		}

	}
	
	//draw marks
	if (m_marker != nullptr &&	m_marker->_isvisible())
	{

		int x1, y1, x2, y2;
		
		indx = m_left_index;

		//x2 = x1 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
		x2 = x1 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
		//y2 = y1 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
		y2 = y1 = m_height - (double)yda[indx] * y_height_div_range + y_offs_mult_width_div_range;
	
		indx++;
	
		((wxMarker *)m_marker)->InitStyleAndColour(gc);

		for (; indx <= m_right_index; indx++)
		{
			//x2 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
			x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
			//y2 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
			y2 = m_height - (double)yda[indx] * y_height_div_range + y_offs_mult_width_div_range;
	
			while (abs(x2 - x1) < 4 && abs(y2 - y1) < 4)
			{
				indx++;

				//x2 = ((double)xda[indx] - xoffset) / xrange * (double)m_width;
				x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
				//y2 = m_height - ((double)yda[indx] - yoffset) / yrange * (double)m_height;
				y2 = m_height - (double)yda[indx] * y_height_div_range + y_offs_mult_width_div_range;

				if (indx == m_right_index)
					break;
			}
	
			m_marker->Render(gc, Point<int>(x1, y1));

			x1 = x2;
			y1 = y2;
		}
		m_marker->Render(gc, Point<int>(x2, y2));
	}
	
#ifdef _DEBUG
	//printf("leftindx = %i, right indx = %i\n", m_left_index, m_right_index);
	printf("series: %s items: %i\n", m_owner_series->GetSeriesName(), points_count);
#endif

}
