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
}


Renderer::~Renderer()
{
	DPRINTF("Renderer dtor\n");

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

	gc->DrawText("Renderer2DTyped", 10, m_text_pos);

	gc->SetPen(*wxBLACK_PEN);
	gc->SetBrush(*wxTRANSPARENT_BRUSH);

	SeriesND *series;
	series = (SeriesND *)m_owner_series;

	DataTyped<T1> *xdata = (DataTyped<T1> *)series->GetNData(AXIS_X);
	DataTyped<T2> *ydata = (DataTyped<T2> *)series->GetNData(AXIS_Y);

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

	for (size_t indx = 0; indx < data_size; indx++)
	{
		int x, y;
		x = ((double)xda[indx] - xoffset) / xrange * (double)width;
		y = ((double)yda[indx] - yoffset) / yrange * (double)height;
		gc->DrawEllipse(x, y, 2, 2);
	}

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
