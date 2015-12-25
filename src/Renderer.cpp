//#include "stdafx.h"
#include "Renderer.h"

static int s_text_pos = 5;
static int s_text_height = 13;

Renderer::Renderer()
{
	DPRINTF("Renderer ctor\n");
	m_owner_series = NULL;

	m_text_pos = s_text_pos;
	s_text_pos += s_text_height;

	m_marker_style = MARKER_CIRCLE;
	m_marker_size = 2;
	m_marker_color_index = 0;

	m_line_style = LINE_SOLID;
	m_line_thickness = 1;
	m_line_color_index = 0;
}


Renderer::~Renderer()
{
	DPRINTF("Renderer dtor\n");
	if (m_owner_series != NULL)
		m_owner_series->SetRenderer(NULL);
}

void Renderer::SetOwner(SeriesND * series)
{
	m_owner_series = series;

}

Renderer2D::Renderer2D()
{
	DPRINTF("Renderer2D ctor\n");
}

Renderer2D::~Renderer2D()
{
	DPRINTF("Renderer2D dtor\n");
}

template<typename T1, typename T2>
Renderer2DTyped<T1, T2>::Renderer2DTyped()
{
	DPRINTF("Renderer2DTyped ctor\n");
}

template<typename T1, typename T2>
Renderer2DTyped<T1, T2>::~Renderer2DTyped()
{
	DPRINTF("Renderer2DTyped dtor\n");
}


template<typename T1, typename T2>
void Renderer2DTyped<T1, T2>::Render(wxGraphicsContext * gc)
{
	int width, height;

	assert(m_owner_series != NULL);
	
	m_owner_series->GetOwner()->GetOwner()->GetSize(&width, &height);

	//gc->DrawText("Renderer2DTyped", 10, m_text_pos);

	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxTRANSPARENT_BRUSH);
	
	SeriesND *series;
	series = (SeriesND *)m_owner_series;

	DataTyped<T1> *xdata = (DataTyped<T1> *)series->GetNData(AXIS_X);
	DataTyped<T2> *ydata = (DataTyped<T2> *)series->GetNData(AXIS_Y);

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

	SpaceND *space = (SpaceND *)m_owner_series->GetOwner();

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
	if (m_line_style != LINE_NONE)
	{

		int x1, y1, x2, y2;

		x1 = ((double)xda[indx] - xoffset) / xrange * (double)width;
		y1 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;

		indx++;

		wxPen pen(*wxBLACK_PEN);
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
	if (m_marker_style != MARKER_NONE)
	{
		//wxBitmap marker(10, 10);
		//wxMemoryDC mdc;
		//mdc.SelectObject(marker);
		//mdc.SetBackground(*wxRED);
		//
		//mdc.Clear();
		//mdc.DrawCircle(4, 4, 3);
		//mdc.SelectObject(wxNullBitmap);
		//marker.SetMask(new wxMask(wxBitmap(marker), *wxRED));
		indx = 0;
		int x1, y1, x2, y2;

		x1 = ((double)xda[indx] - xoffset) / xrange * (double)width;
		y1 = height - ((double)yda[indx] - yoffset) / yrange * (double)height;

		indx++;

		wxPen pen(*wxBLACK_PEN);
		wxBrush brush(*wxWHITE_BRUSH);

		gc->SetPen(pen);
		gc->SetBrush(brush);

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

			if (m_marker_style == MARKER_CIRCLE)
			{
				int r;
				r = m_marker_size / 2 + 1;
				gc->DrawEllipse(x1 - r, y1 - r, r + r, r + r);
				//gc->DrawBitmap(marker, x1 - 5, y1 - 5, 10, 10);
			}
			x1 = x2;
			y1 = y2;
		}
	}

	//max/min lines
	double maxy, miny;
	maxy = ydata->GetDataMax();
	miny = ydata->GetDataMin();
	int y;
	y = height - (maxy - yoffset) / yrange * (double)height;
	gc->StrokeLine(0, y, width, y);
	y = height - (miny - yoffset) / yrange * (double)height;
	gc->StrokeLine(0, y, width, y);

}
//
//Renderer1D::Renderer1D()
//{
//	DPRINTF("Renderer1D ctor\n");
//}
//
//Renderer1D::~Renderer1D()
//{
//	DPRINTF("Renderer1D dtor\n");
//}
//
//template<class T>
//Renderer1DTyped<T>::Renderer1DTyped()
//{
//	DPRINTF("Renderer1DTyped ctor\n");
//}
//
//template<class T>
//Renderer1DTyped<T>::~Renderer1DTyped()
//{
//	DPRINTF("Renderer1DTyped dtor\n");
//}

char s_buff[20];

//template<class T>
//void Renderer1DTyped<T>::Render(wxGraphicsContext * gc)
//{
//	assert(m_owner_series != NULL);
//	gc->DrawText("Renderer1DTyped", 10, m_text_pos);
//
//	gc->SetPen(*wxBLACK_PEN);
//	gc->SetBrush(*wxTRANSPARENT_BRUSH);
//
//	Series1D *series1d;
//	series1d = (Series1D *)m_owner_series;
//
//	DataTyped<T> *data = (DataTyped<T> *)series1d->GetData();
//    ValueAdaptor<T> *vadaptor = data->GetValueAdaptor();
//
//	auto da = data->GetDataArray();
//
//	size_t data_size;
//	data_size = data->GetSize();
//
//	for (size_t indx = 0; indx < data_size; indx++)
//	{
//		int x, y;
//		x = indx;
//		y = da[indx];
//		gc->DrawEllipse(x, y, 2, 2);
//	}
//    vadaptor->ConvertToStr(s_buff, 20, 0);
//    gc->DrawText(wxString(s_buff), 20, 20);
//}
