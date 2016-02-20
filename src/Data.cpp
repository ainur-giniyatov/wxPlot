#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "Series.h"

using namespace plot;

const char *s_data_name_null = "nullptr";

DataNoType::DataNoType(size_t size, const char *data_name)
{
	DPRINTF("DataNoType ctor\n")
	m_data_name = nullptr;
	m_owner_series = nullptr;
	m_data_size = 0;
	SetDataName(data_name);

	m_maxmin_override = false;

}


DataNoType::~DataNoType()
{
	DPRINTF("DataNoType dtor\n")
	if (m_data_name != nullptr && m_data_name != s_data_name_null)
		free(m_data_name);

}

void DataNoType::SetDataName(const char * name)
{
	if (name != nullptr)
	{
		m_data_name = (char *)malloc(strlen(name) + 1);
		strcpy(m_data_name, name);
	}
	else
		m_data_name = (char *)s_data_name_null;

}


void DataNoType::SetMaxMinMode(bool manual)
{
	m_maxmin_override = manual;
    //if(update)
    //    DataUpdated();
}

//Axis * DataNoType::get_adj_axis()
//{
//	Axis *axis;
//	int axis_dir = -1;
//	assert(m_owner_series != nullptr && m_owner_series->GetOwner() != nullptr);
//	for (int indx = 0; m_owner_series->GetData((AXIS_DIR)indx) != nullptr; indx++)
//	{
//		if (m_owner_series->GetData((AXIS_DIR)indx) == this)
//		{
//			axis_dir = indx;
//			break;
//		}
//	}
//
//	assert(axis_dir != -1);
//
//	axis = m_owner_series->GetOwner()->GetAxis((AXIS_DIR)axis_dir);
//	assert(axis != nullptr);
//	return axis;
//}

template<class T>
DataTyped<T>::DataTyped( size_t size, const char *data_name):DataNoType( size, data_name)
{
	DPRINTF("DataTyped ctor\n")
	m_data = nullptr;
	Allocate(size, false);

	m_manual_max = 100.;
	m_manual_min = -100.;
}

template<class T>
DataTyped<T>::~DataTyped()
{
	DPRINTF("DataTyped dtor\n");

//free data arrays
	Clear();

}

template<class T>
void DataTyped<T>::ZeroFill()
{
	assert(m_data_size != 0 && m_data != nullptr);
	for (size_t indx = 0; indx < m_data_size; indx++)
		m_data[indx] = (T)0;

}

template<class T>
void DataTyped<T>::Allocate(size_t size,bool zerofill)
{
	if (size == 0)
		return;

	Clear();
	m_data_size = size;
	if (size > 0)
	{
		m_data = (T*)malloc(sizeof(T) * size);
		if (zerofill)
			ZeroFill();
	}
}

template<class T>
void DataTyped<T>::Clear()
{
	if (m_data != nullptr)
	{
		free(m_data);
		m_data = nullptr;
		m_data_size = 0;
	}
}

template<class T>
void DataTyped<T>::SetValue(T value, size_t indx)
{
#ifdef _DEBUG
	assert(indx < m_data_size);
	assert(m_data != nullptr);
#endif
	m_data[indx] = value;
}

template<class T>
void DataTyped<T>::SetMaxMinValues(T max, T min)
{
    m_manual_max = max;
    m_manual_min = min;
}

template<class T>
double DataTyped<T>::GetDataMax()
{
	assert(m_data_size != 0);

	if (m_maxmin_override)
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

	if (m_maxmin_override)
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
bool plot::DataTyped<T>::IsValid()
{
	return (m_data_size != 0 && m_data != nullptr);
}

template<class T>
void plot::DataTyped<T>::Validate()
{
	if (m_owner_series != nullptr && IsValid())
		m_owner_series->Validate();
}


//template<class T>
//void DataTyped<T>::Fit(bool update)
//{
//	T maxv;
//	T minv;
//	T range;
//	maxv = GetDataMax();
//	minv = GetDataMin();
//
//	assert(maxv >= minv);
//
//	range = maxv - minv;
//
//	get_adj_axis()->_SetVisibleRange(minv, range, update);
//
//
//
//}



