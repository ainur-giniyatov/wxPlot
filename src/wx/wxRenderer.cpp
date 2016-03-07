#include <wx/graphics.h>

#include "wx/wxRenderer.h"
#include "wx/colorbase.h"
#include "wx/wxMarker.h"
#include "wx/wxLine.h"
#include "wx/wxSubPlot.h"

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
	m_marker = new wxMarkerCircle();
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
Series * plot::wxRendererTyped<T1, T2>::_isspotted(Point<int>& mouse_coord, int *dotindex_first, int *dotindex_last)
{
	////int m_width, m_height;
	*dotindex_first = -1;
	*dotindex_last = -1;
	assert(m_owner_series != NULL);

	if (!m_visible)
		return false;

//	Plot *plot = m_owner_series->_getowner()->GetOwner();
	//Size<int> size;
	////if(plot->_get_orientation() == Plot::ORIENTATION_NORMAL)
	//size = plot->_get_size();
	////m_owner_series->GetOwner()->GetOwner()->GetSize(&m_width, &m_height);

	//Series *series;
	//series = (Series *)m_owner_series;

	//double x1, y1, x2, y2;
	//DataTyped<T1> *xdata = (DataTyped<T1> *)series->GetData(AXIS_X);
	//DataTyped<T2> *ydata = (DataTyped<T2> *)series->GetData(AXIS_Y);
	//
	//assert(xdata != nullptr);
	//assert(ydata != nullptr);

	////Axis *xaxis;
	//Axis *yaxis;

	//Area *space = (Area*)m_owner_series->_getowner();

	//xaxis = space->GetAxis(AXIS_X);
	//yaxis = space->GetAxis(AXIS_Y);

	//auto xda = xdata->GetDataArray();
	//auto yda = ydata->GetDataArray();

	//double xoffset, yoffset, xrange, yrange;

	//xoffset = xaxis->_getoffset();
	//xrange = xaxis->_getrange();
	//yoffset = yaxis->_getoffset();
	//yrange = yaxis->_getrange();

	//if (m_marker != nullptr && m_marker->_isvisible())
	//{
	//	for (size_t indx = m_left_index; indx <= m_right_index; indx++)
	//	{
	//		x1 = ((double)xda[indx] - xoffset) / xrange * (double)size.w;
	//		y1 = ((double)yda[indx] - yoffset) / yrange * (double)size.h;
	//		if (m_marker->_isspotted(mouse_coord, Point<int>(x1, y1)))
	//		{
	//			*dotindex_first = *dotindex_last = indx;
	//			return m_owner_series;
	//		}
	//	}
	//}

	//if (m_line != nullptr && m_line->_isvisible())
	//{
	//	x1 = ((double)xda[m_left_index] - xoffset) / xrange * (double)size.w;
	//	y1 = ((double)yda[m_left_index] - yoffset) / yrange * (double)size.h;
	//	for (size_t indx = m_left_index + 1; indx <= m_right_index; indx++)
	//	{
	//		x2 = ((double)xda[indx] - xoffset) / xrange * (double)size.w;
	//		y2 = ((double)yda[indx] - yoffset) / yrange * (double)size.h;
	//		if (m_line->_isspotted(mouse_coord, Point<int>(x1, y1), Point<int>(x2, y2)))
	//		{
	//			*dotindex_first = 0;
	//			*dotindex_last = xdata->GetSize();
	//			return m_owner_series;
	//		}

	//		x1 = x2;
	//		y1 = y2;
	//	}
	//}

	return nullptr;
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
	wxSubplot *subplot;
	subplot = (wxSubplot *)series->_getowner();

	auto size = subplot->_get_size();

	//int vphoff, hphoff, vphrange, hphrange;;
	//subplot->_getphysicaloffsets(&hphoff, &vphoff);
	//subplot->_getphysicalranges(&hphrange, &vphrange);

	//if (vphrange != 0)
	//	size.h = vphrange;
	//if (hphrange != 0)
	//	size.w = hphrange;

	auto xda = series->GetXData();
	auto yda = series->GetYData();

	size_t data_size = series->GetDataSize();
//
//	xaxis = area->GetAxis(AXIS_X);
//	yaxis = area->GetAxis(AXIS_Y);
//
	double xoffset, yoffset, xrange, yrange;

	if (series->_getxscale() == nullptr)
	{
		xoffset = 0;
		xrange = 1000;
	}
	else
	{
		xoffset = series->_getxscale()->GetOffset();
		xrange = series->_getxscale()->GetRange();
	}

	if (series->_getyscale()== nullptr)
	{
		yoffset = -15;
		yrange = 30;
	}
	else
	{
		yoffset = series->_getyscale()->GetOffset();
		yrange = series->_getyscale()->GetRange();

	}

	//x1 = ((double)xda[indx] - xoffset) / xrange * (double)width;
	double x_width_div_range = (double)(size.w) / xrange;
	double x_offs_mult_width_div_range = xoffset * x_width_div_range;

	//y1 = ((double)yda[indx] - yoffset) / yrange * (double)height;
	double y_height_div_range = (double)size.h / yrange;
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
		if (x > size.w)
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
		y1 = (double)yda[indx] * y_height_div_range - y_offs_mult_width_div_range;


		indx++;

		((wxLine *)m_line)->InitStyleAndColour(gc);

		for (; indx <= m_right_index ; indx++)
		{

			x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
			y2 = (double)yda[indx] * y_height_div_range - y_offs_mult_width_div_range;

			while (abs(x2 - x1) < 4 && abs(y2 - y1) < 4)
			{
				if (indx == m_right_index)
					break;

				indx++;

				x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
				y2 = (double)yda[indx] * y_height_div_range - y_offs_mult_width_div_range;
			}
#if _DEBUG
			points_count++;
#endif
			if(subplot->_get_orientation() == Subplot::ORIENTATION_NORMAL)
				m_line->Render(gc, Point<int>(x1, size.h - y1), Point<int>(x2, size.h - y2) );

			if (subplot->_get_orientation() == Subplot::ORIENTATION_ROTATED)
				m_line->Render(gc, Point<int>(y1 , x1), Point<int>(y2 , x2));


			x1 = x2;
			y1 = y2;
		}

	}

	//draw marks
	if (m_marker != nullptr &&	m_marker->_isvisible())
	{

		int x1, y1, x2, y2;

		indx = m_left_index;

		x2 = x1 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
		y2 = y1 = (double)yda[indx] * y_height_div_range - y_offs_mult_width_div_range;

		indx++;

		((wxMarker *)m_marker)->InitStyleAndColour(gc);

		for (; indx <= m_right_index; indx++)
		{
			x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
			y2 = (double)yda[indx] * y_height_div_range - y_offs_mult_width_div_range;

			while (abs(x2 - x1) < 4 && abs(y2 - y1) < 4)
			{
				indx++;

				x2 = (double)xda[indx] * x_width_div_range - x_offs_mult_width_div_range;
				y2 = (double)yda[indx] * y_height_div_range - y_offs_mult_width_div_range;

				if (indx == m_right_index)
					break;
			}
			if (subplot->_get_orientation() == Subplot::ORIENTATION_NORMAL)
				m_marker->Render(gc, Point<int>(x1, size.h - y1));

			if (subplot->_get_orientation() == Subplot::ORIENTATION_ROTATED)
				m_marker->Render(gc, Point<int>(y1, x1));

			x1 = x2;
			y1 = y2;
		}

		if (subplot->_get_orientation() == Subplot::ORIENTATION_NORMAL)
			m_marker->Render(gc, Point<int>(x2, size.h - y2));

		if (subplot->_get_orientation() == Subplot::ORIENTATION_ROTATED)
			m_marker->Render(gc, Point<int>(y2, x2));

	}

#ifdef _DEBUG
	//printf("leftindx = %i, right indx = %i\n", m_left_index, m_right_index);
	printf("series: %s items: %i\n", m_owner_series->GetSeriesName(), points_count);
#endif

}
