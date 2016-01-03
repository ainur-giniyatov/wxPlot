#include <algorithm>
#include <assert.h>
#include <string.h>

#include "Series.h"


using namespace plot;

const char *s_series_name_null = "null";

Series::Series(int dim_num, const char *series_name)
{
	DPRINTF("Series ctor\n");
	m_series_name = NULL;
	m_owner = NULL;
	SetSeriesName(series_name, false);
	m_renderer = NULL;

	m_dim_num = dim_num;
	assert(m_dim_num > 0 && m_dim_num < 3);

	m_datas = (DataNoType **)malloc(sizeof(DataNoType *) * m_dim_num);
	for (int indx = 0; indx < m_dim_num; indx++)
		m_datas[indx] = nullptr;
}

Series::~Series()
{
	DPRINTF("Series dtor\n");
	if (m_series_name != NULL && m_series_name != s_series_name_null)
		free(m_series_name);

//delete renderer
	if (m_renderer != NULL)
	{
		m_renderer->SetOwner(NULL);
		delete m_renderer;
	}

//delete data
	for (int indx = 0; indx < m_dim_num; indx++)
	{
		if (m_datas[indx] != nullptr)
			DeleteData(m_datas[indx]);
	}

	free(m_datas);
}

void Series::SetSeriesName(const char * series_name, bool update)
{
	if (m_series_name != NULL && m_series_name != s_series_name_null)
	{
		free(m_series_name);
	}

	if (series_name != NULL)
	{
		m_series_name = (char *)malloc(strlen(series_name) + 1);
		strcpy(m_series_name, series_name);
	}
	else
		m_series_name = (char *)s_series_name_null;

	if (update)
		SeriesUpdated();
}

void Series::SeriesUpdated()
{
}

void Series::SetData(DataNoType * data, AXIS_DIR axis_dir)
{
	assert(axis_dir < m_dim_num);
	assert(data != nullptr);
	if (m_datas[axis_dir] != nullptr)
		DeleteData(m_datas[axis_dir]);

	m_datas[axis_dir] = data;
	data->_SetOwner(this);
}

DataNoType * Series::GetData(AXIS_DIR axis_dir)
{
	//assert(axis_dir < m_dim_num);
	return axis_dir < m_dim_num ? m_datas[axis_dir] : nullptr;
}

void Series::RemoveData(DataNoType * data)
{
	int indx;
	for (indx = 0; indx < m_dim_num; indx++)
	{
		if (m_datas[indx] == data)
		{
			m_datas[indx] = nullptr;
			data->_SetOwner(nullptr);
			break;
		}
	}
	assert(indx != m_dim_num);//not found
}

void Series::DeleteData(DataNoType * data)
{
	int indx;
	for (indx = 0; indx < m_dim_num; indx++)
	{
		if (m_datas[indx] == data)
		{
			m_datas[indx] = nullptr;
			//data->_SetOwner(nullptr);
			delete data;
			break;
		}
	}
	assert(indx != m_dim_num);//not found

}

void Series::Fit(bool update)
{
}

void Series::SetRenderer(Renderer * renderer)
{
	if (m_renderer != nullptr)
		delete m_renderer;
	m_renderer = renderer;
	m_renderer->SetOwner(this);
}

//void Series::SeriesUpdated()
//{
//	DPRINTF("Series updated\n");
//	/*if (m_owner_area != NULL)
//		m_owner_area->AreaUpdated();*/
//	//if (m_owner_space != NULL)
//	//	m_owner_space->SpaceUpdated();
//}
//
//Renderer * Series::GetRenderer()
//{
////	wxASSERT(m_renderer != NULL);
//	return m_renderer;
//}


//
//void Series::Fit(bool update)
//{
//	for (auto data : m_datas)
//	{
//		data->Fit(false);
//	}
//
//	if (update)
//	{
//		std::vector<Plot *> vuniqplot;
//		for (size_t indx = 0; indx < m_owner_space->GetDimsCount(); indx++) //auto axis : m_owner_space->GetAxes())
//		{
//			Scale *scale;
//			scale = m_owner_space->GetAxis((AXIS_DIR)indx)->GetCommonScale();
//			if (scale != NULL)
//			{
//				scale->ScaleRedraw();
//				for (auto axis : scale->GetAxes())
//				{
//					Plot *plot;
//					plot = axis->GetOwner()->GetOwner();
//					if (plot != NULL && std::count(vuniqplot.begin(), vuniqplot.end(), plot) == 0)
//					{
//						plot->RedrawPlot();
//						vuniqplot.push_back(plot);
//					}
//				}
//			}
//		}
//	}
//}

//void Series::SetRenderer(Renderer2D * renderer2d)
//{
//	assert(renderer2d != NULL);
//	if (m_renderer != NULL)
//	{
//		m_renderer->SetOwner(NULL);
//		delete m_renderer;
//	}
//
//	m_renderer = renderer2d;
//	m_renderer->SetOwner(this);
//	SeriesUpdated();
//}
//
//Series2D::Series2D(const char * series_name):Series(series_name)
//{
//	m_xdata = m_ydata = nullptr;
//}
//
//Series2D::~Series2D()
//{
//	if (m_xdata != nullptr)
//		delete m_xdata;
//
//	if (m_ydata != nullptr)
//		delete m_ydata;
//}
//
//void Series2D::SetData(DataNoType * data, AXIS_DIR axis_dir, bool update)
//{
//	if (axis_dir == AXIS_X)
//	{
//		if (m_xdata != nullptr)
//			delete m_xdata;
//
//		m_xdata = data;
//		m_xdata->SetOwner(this);
//	}
//	else
//		if (axis_dir == AXIS_Y)
//		{
//			if (m_ydata != nullptr)
//				delete m_ydata;
//			m_ydata = data;
//			m_ydata->SetOwner(this);
//		}
//		else
//			assert(0);
//}
//
//DataNoType * Series2D::GetData(AXIS_DIR axis_dir)
//{
//	if (axis_dir == AXIS_X)
//		return m_xdata;
//
//	if (axis_dir == AXIS_Y)
//		return m_ydata;
//
//	assert(0);
//	return nullptr;
//}
//
//std::vector<DataNoType*> Series2D::GetDatas()
//{
//	std::vector<DataNoType*> datas;
//	if (m_xdata != nullptr)
//		datas.push_back(m_xdata);
//
//	if (m_ydata != nullptr)
//		datas.push_back(m_ydata);
//
//	return datas;
//}
//
//void Series2D::RemoveData(DataNoType * data)
//{
//	if (data == m_xdata)
//		m_xdata = nullptr;
//
//	if (data == m_ydata)
//		m_ydata = nullptr;
//}
//
//void Series2D::Fit(bool update)
//{
//}
