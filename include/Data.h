#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Renderer.h"

class WXDLLIMPEXP_PLOTLIB SeriesND;
class WXDLLIMPEXP_PLOTLIB Renderer;
class WXDLLIMPEXP_PLOTLIB Renderer2D;
template <class T> class WXDLLIMPEXP_PLOTLIB ValueAdaptor;

class WXDLLIMPEXP_PLOTLIB DataNoType
{
public:
	DataNoType(AXIS_DIR axis_dir, size_t size = 0, const char *data_name = NULL);
	virtual ~DataNoType();

	AXIS_DIR GetAxisDir() { return m_axis_dir; }

	void SetSeriesName(const char *name, bool update = true);
	const char *GetDataName() { return m_data_name; }
	void DataUpdated();
	void SetOwner(SeriesND *series) { m_owner_series = series; };
	SeriesND *GetOwner() { return m_owner_series; }

	size_t GetSize() { return m_data_size; };

	void SetMaxMinMode(bool manual, bool update = false);
	virtual double GetDataMax() = 0;
	virtual double GetDataMin() = 0;
	virtual void Fit(bool update = true) = 0;

protected:

	char *m_data_name;
	size_t m_data_size;
	SeriesND *m_owner_series;

	bool m_maxmin_manual;
	AXIS_DIR m_axis_dir;
};


template<class T> class WXDLLIMPEXP_PLOTLIB DataTyped: public DataNoType
{
public:
	DataTyped(AXIS_DIR axis_dir, size_t size = 0, const char *data_name = NULL);
	virtual ~DataTyped();

	void ZeroFill(bool update = true);
	void Allocate(size_t size, bool update = true, bool zerofill = true);
	void Clear(bool update = true);
	void SetValue(T value, size_t indx);

	T *GetDataArray() { return m_data; }

	ValueAdaptor<T> *GetValueAdaptor();
	void SetValueAdaptor(ValueAdaptor<T> *valueadaptor, bool update = false);

	void SetMaxMinValues(T max, T min, bool update = true);
	virtual double GetDataMax();
	virtual double GetDataMin();
	void SetVisibleRange(double offs, double range, bool update = true);
	virtual void Fit(bool update = true);

protected:
	T *m_data;

	T m_manual_max;
	T m_manual_min;

	ValueAdaptor<T> *m_valueadaptor;


};

//#ifdef MAKINGDLL
template WXDLLIMPEXP_PLOTLIB class DataTyped<int>;
template WXDLLIMPEXP_PLOTLIB class DataTyped<time_t>;
template WXDLLIMPEXP_PLOTLIB class DataTyped<double>;
template WXDLLIMPEXP_PLOTLIB class DataTyped<float>;
template WXDLLIMPEXP_PLOTLIB class DataTyped<short int>;
//template WXDLLIMPEXP_PLOTLIB class DataTyped<char>;
//#endif
