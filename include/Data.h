#pragma once
#include "plot_defs.h"
#include "Series.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Series2D;

	class DLLIMPEXP_PLOTLIB DataNoType
	{
	public:
		DataNoType(size_t size = 0, const char *data_name = NULL);
		virtual ~DataNoType();

		void SetAxisDir(AXIS_DIR axis_dir) { m_axis_dir = axis_dir; }
		AXIS_DIR GetAxisDir() { return m_axis_dir; }

		void SetDataName(const char *name);
		const char *GetDataName() { return m_data_name; }

		//void DataUpdated();

		Series *GetOwner() { return m_owner_series; }

		size_t GetSize() { return m_data_size; };

		void SetMaxMinMode(bool manual);
		virtual double GetDataMax() = 0;
		virtual double GetDataMin() = 0;

		//virtual void Fit() = 0;
		//internal use methods start with _
		void _SetOwner(Series *series);
	protected:

		char *m_data_name;
		size_t m_data_size;
		Series *m_owner_series;

		bool m_maxmin_manual;
		AXIS_DIR m_axis_dir;



		//helper funcs
		//Axis *get_adj_axis();
	};


	template<class T> class DLLIMPEXP_PLOTLIB DataTyped : public DataNoType
	{
	public:
		DataTyped(size_t size = 0, const char *data_name = NULL);
		virtual ~DataTyped();

		void ZeroFill(bool update = true);
		void Allocate(size_t size, bool zerofill = true);
		void Clear(bool update = true);
		void SetValue(T value, size_t indx);

		T *GetDataArray() { return m_data; }

		//AxisValueAdaptor<T> *GetValueAdaptor();
		//void SetValueAdaptor(AxisValueAdaptor<T> *valueadaptor, bool update = false);

		void SetMaxMinValues(T max, T min, bool update = true);
		virtual double GetDataMax();
		virtual double GetDataMin();

		virtual void Fit(bool update = true);

	protected:
		T *m_data;

		T m_manual_max;
		T m_manual_min;

		//AxisValueAdaptor<T> *m_valueadaptor;


	};

#include <time.h>
	//#ifdef MAKINGDLL
	template DLLIMPEXP_PLOTLIB class DataTyped<int>;
	template DLLIMPEXP_PLOTLIB class DataTyped<time_t>;
	template DLLIMPEXP_PLOTLIB class DataTyped<double>;
	//#endif
}