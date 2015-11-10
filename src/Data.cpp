//#include "stdafx.h"
#include "Data.h"

const char *s_data_name_null = "null";

DataNoType::DataNoType(AXIS_DIR axis_dir, size_t size, const char *data_name)
{
	DPRINTF("DataNoType ctor\n")
	m_data_name = NULL;
	m_owner_series = NULL;
	m_data_size = 0;
	SetDataName(data_name, false);

	m_maxmin_manual = false;

	m_axis_dir = axis_dir;
}


DataNoType::~DataNoType()
{
	DPRINTF("DataNoType dtor\n")
	if (m_data_name != NULL && m_data_name != s_data_name_null)
		free(m_data_name);

	if (m_owner_series != NULL)
	{
		SeriesND *series = m_owner_series;
		m_owner_series = NULL;
		series->SetNData(NULL, m_axis_dir, true);
	}
}

void DataNoType::SetDataName(const char * name, bool update)
{
	if (name != NULL)
	{
		m_data_name = (char *)malloc(strlen(name) + 1);
		strcpy(m_data_name, name);
	}
	else
		m_data_name = (char *)s_data_name_null;

	if (update)
		DataUpdated();

}

void DataNoType::DataUpdated()
{
	DPRINTF("Data updated\n");
	if (m_owner_series != NULL)
		m_owner_series->SeriesUpdated();
}

void DataNoType::SetMaxMinMode(bool manual, bool update)
{
    m_maxmin_manual = manual;
    if(update)
        DataUpdated();
}

Axis * DataNoType::get_adj_axis()
{
	Axis *axis;
	wxASSERT(m_owner_series != NULL && m_owner_series->GetOwner() != NULL);
	axis = m_owner_series->GetOwner()->GetAxis(m_axis_dir);
	wxASSERT(axis != NULL);
	return axis;
}

template<class T>
DataTyped<T>::DataTyped(AXIS_DIR axis_dir, size_t size, const char *data_name):DataNoType(axis_dir, size, data_name)
{
	DPRINTF("DataTyped ctor\n")
	m_data = NULL;
	Allocate(size, false);
	m_valueadaptor = NULL;

	m_manual_max = 100.;
	m_manual_min = -100.;
}

template<class T>
DataTyped<T>::~DataTyped()
{
	DPRINTF("DataTyped dtor\n");

//free data arrays
	Clear(false);

//delete valueadaptor
	if (m_valueadaptor != NULL)
		delete m_valueadaptor;
}

template<class T>
void DataTyped<T>::ZeroFill(bool update)
{
	assert(m_data_size != 0 && m_data != NULL);
	for (size_t indx = 0; indx < m_data_size; indx++)
		m_data[indx] = (T)0;

	if(update)
		DataUpdated();
}

template<class T>
void DataTyped<T>::Allocate(size_t size, bool update, bool zerofill)
{
	if (size == 0)
		return;

	Clear(false);
	m_data_size = size;
	if (size > 0)
	{
		m_data = (T*)malloc(sizeof(T) * size);
		if (zerofill)
			ZeroFill(false);
		if (update)
			DataUpdated();
	}
}

template<class T>
void DataTyped<T>::Clear(bool update)
{
	if (m_data != NULL)
	{
		free(m_data);
		m_data = NULL;
		m_data_size = 0;
		if(update)
			DataUpdated();
	}
}

template<class T>
void DataTyped<T>::SetValue(T value, size_t indx)
{
#ifdef _DEBUG
	assert(indx < m_data_size);
	assert(m_data != NULL);
#endif
	m_data[indx] = value;
}

template<class T>
AxisValueAdaptor<T>* DataTyped<T>::GetValueAdaptor()
{
	return m_valueadaptor;
}

template<class T>
void DataTyped<T>::SetValueAdaptor(AxisValueAdaptor<T>* valueadaptor, bool update)
{
	if (m_valueadaptor != NULL)
		delete m_valueadaptor;

	m_valueadaptor = valueadaptor;
	m_valueadaptor->SetData(this);
	if (update)
		DataUpdated();
}

template<class T>
void DataTyped<T>::SetMaxMinValues(T max, T min, bool update)
{
    m_manual_max = max;
    m_manual_min = min;
    if(update)
        DataUpdated();
}

template<class T>
double DataTyped<T>::GetDataMax()
{
	wxASSERT(m_data_size != 0);

	if (m_maxmin_manual)
		return m_manual_max;

	T tmp;
	tmp = m_data[0];
	for (size_t indx = 1; indx < m_data_size; indx++)
	{
		if (tmp < m_data[indx])
			tmp = m_data[indx];
	}
	return (double)tmp;
}

template<class T>
double DataTyped<T>::GetDataMin()
{
	wxASSERT(m_data_size != 0);

	if (m_maxmin_manual)
		return m_manual_min;

	T tmp;
	tmp = m_data[0];
	for (size_t indx = 1; indx < m_data_size; indx++)
	{
		if (tmp > m_data[indx])
			tmp = m_data[indx];
	}
	return tmp;
}


template<class T>
void DataTyped<T>::Fit(bool update)
{
	T maxv;
	T minv;
	T range;
	maxv = GetDataMax();
	minv = GetDataMin();

	wxASSERT(maxv > minv);

	range = maxv - minv;

	

	get_adj_axis()->SetVisibleRange(minv, range, update);

	

}

