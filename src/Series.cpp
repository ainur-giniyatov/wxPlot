//#include "stdafx.h"
#include "Series.h"

const char *s_series_name_null = "null";

SeriesND::SeriesND(size_t dims_count, const char *series_name)
{
	DPRINTF("SeriesND ctor\n");
	m_series_name = NULL;
	//m_owner_area = NULL;
	m_owner_space = NULL;
	SetSeriesName(series_name, false);
	m_renderer = NULL;

	wxASSERT(dims_count > 0);
	wxASSERT(dims_count == 2);//only 2d for now

	m_dims_count = dims_count;
	for (size_t indx = 0; indx < m_dims_count; indx++)
	{
		m_datas.push_back(NULL);
	}
}


SeriesND::~SeriesND()
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

//delete datas
	for (auto data : m_datas)
	{
		if (data == NULL)
			continue;
		data->SetOwner(NULL);
		delete data;
	}

	if(m_owner_space != NULL)
		m_owner_space->RemoveSeries(this);
}

void SeriesND::SetSeriesName(const char * series_name, bool update)
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

void SeriesND::SeriesUpdated()
{
	DPRINTF("Series updated\n");
	/*if (m_owner_area != NULL)
		m_owner_area->AreaUpdated();*/
	if (m_owner_space != NULL)
		m_owner_space->SpaceUpdated();
}

Renderer * SeriesND::GetRenderer()
{
	wxASSERT(m_renderer != NULL);
	return m_renderer;
}


void SeriesND::SetNData(DataNoType * data, AXIS_DIR axis_dir, bool update)
{
	wxASSERT(axis_dir < m_dims_count);

	data->SetAxisDir(axis_dir);

	
	if (m_datas[axis_dir] != NULL && m_datas[axis_dir]->GetOwner() != NULL)
	{
		delete m_datas[axis_dir];
	}

	m_datas[axis_dir] = data;
	if(data != NULL)
		data->SetOwner(this);

	if (update)
		SeriesUpdated();
}

DataNoType * SeriesND::GetNData(AXIS_DIR axis_dir)
{
	wxASSERT(axis_dir < m_dims_count);
	return m_datas[axis_dir];
}


void SeriesND::Fit(bool update)
{
	for (auto data : m_datas)
	{
		data->Fit(false);
	}

	if (update)
	{
		for (size_t indx = 0; indx < m_owner_space->GetDimsCount(); indx++) //auto axis : m_owner_space->GetAxes())
		{
			m_owner_space->GetAxis((AXIS_DIR)indx)->AxisUpdated();
		}
	}
}

void SeriesND::SetRenderer(Renderer2D * renderer2d)
{
	assert(renderer2d != NULL);
	if (m_renderer != NULL)
	{
		m_renderer->SetOwner(NULL);
		delete m_renderer;
	}

	m_renderer = renderer2d;
	m_renderer->SetOwner(this);
	SeriesUpdated();
}
