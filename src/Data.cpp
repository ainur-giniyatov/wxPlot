#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

using namespace plot;

const char *s_data_name_null = "null";

DataNoType::DataNoType(size_t size, const char *data_name)
{
	DPRINTF("DataNoType ctor\n")
	m_data_name = NULL;
	m_owner_series = NULL;
	m_data_size = 0;
	SetDataName(data_name);

	m_maxmin_manual = false;

//	m_axis_dir = AXIS_NONE;
}


DataNoType::~DataNoType()
{
	DPRINTF("DataNoType dtor\n")
	if (m_data_name != NULL && m_data_name != s_data_name_null)
		free(m_data_name);

}

void DataNoType::SetDataName(const char * name)
{
	if (name != NULL)
	{
		m_data_name = (char *)malloc(strlen(name) + 1);
		strcpy(m_data_name, name);
	}
	else
		m_data_name = (char *)s_data_name_null;

}
//
//void DataNoType::DataUpdated()
//{
//	DPRINTF("Data updated\n");
//	if (m_owner_series != NULL)
//		m_owner_series->SeriesUpdated();
//}

void DataNoType::SetMaxMinMode(bool manual)
{
    m_maxmin_manual = manual;
    //if(update)
    //    DataUpdated();
}

void plot::DataNoType::_SetOwner(Series * series)
{
	assert(m_owner_series == nullptr);
	m_owner_series = series;
}

Axis * DataNoType::get_adj_axis()
{
	Axis *axis;
	int axis_dir = -1;
	assert(m_owner_series != NULL && m_owner_series->GetOwner() != NULL);
	for (int indx = 0; m_owner_series->GetData((AXIS_DIR)indx) != nullptr; indx++)
	{
		if (m_owner_series->GetData((AXIS_DIR)indx) == this)
		{
			axis_dir = indx;
			break;
		}
	}

	assert(axis_dir != -1);

	axis = m_owner_series->GetOwner()->GetAxis((AXIS_DIR)axis_dir);
	assert(axis != NULL);
	return axis;
}

template<class T>
DataTyped<T>::DataTyped( size_t size, const char *data_name):DataNoType( size, data_name)
{
	DPRINTF("DataTyped ctor\n")
	m_data = NULL;
	Allocate(size, false);
//	m_valueadaptor = NULL;

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
	//if (m_valueadaptor != NULL)
	//	delete m_valueadaptor;
}

template<class T>
void DataTyped<T>::ZeroFill(bool update)
{
	assert(m_data_size != 0 && m_data != NULL);
	for (size_t indx = 0; indx < m_data_size; indx++)
		m_data[indx] = (T)0;

	//if(update)
	//	DataUpdated();
}

template<class T>
void DataTyped<T>::Allocate(size_t size,bool zerofill)
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
		//if(update)
		//	DataUpdated();
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

//template<class T>
//AxisValueAdaptor<T>* DataTyped<T>::GetValueAdaptor()
//{
//	return m_valueadaptor;
//}
//
//template<class T>
//void DataTyped<T>::SetValueAdaptor(AxisValueAdaptor<T>* valueadaptor, bool update)
//{
//	if (m_valueadaptor != NULL)
//		delete m_valueadaptor;
//
//	m_valueadaptor = valueadaptor;
//	m_valueadaptor->SetData(this);
//	if (update)
//		DataUpdated();
//}

template<class T>
void DataTyped<T>::SetMaxMinValues(T max, T min, bool update)
{
    m_manual_max = max;
    m_manual_min = min;
    //if(update)
    //    DataUpdated();
}

template<class T>
double DataTyped<T>::GetDataMax()
{
	assert(m_data_size != 0);

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
	assert(m_data_size != 0);

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

	assert(maxv >= minv);

	range = maxv - minv;

	get_adj_axis()->_SetVisibleRange(minv, range, update);



}



