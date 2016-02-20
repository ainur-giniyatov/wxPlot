#pragma once
#include "plot_defs.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;

	class DLLIMPEXP_PLOTLIB DataNoType
	{
	public:
		DataNoType(size_t size = 0, const char *data_name = nullptr);
		virtual ~DataNoType();

		void SetDataName(const char *name);
		const char *GetDataName() { return m_data_name; }


		size_t GetSize() { return m_data_size; };

		void SetMaxMinMode(bool manual);
		virtual double GetDataMax() = 0;
		virtual double GetDataMin() = 0;

		virtual bool IsValid() = 0;
		

		//internal use methods start with _
		void _setowner(Series *series) { m_owner_series = series; }
		Series *_getowner() { return m_owner_series; }

	protected:
		char *m_data_name;
		size_t m_data_size;
		Series *m_owner_series;

		bool m_maxmin_override;

		//helper funcs

	};


	template<class T> class DLLIMPEXP_PLOTLIB DataTyped : public DataNoType
	{
	public:
		DataTyped(size_t size = 0, const char *data_name = nullptr);
		virtual ~DataTyped();

		void ZeroFill();
		void Allocate(size_t size, bool zerofill = true);
		void Clear();
		void SetValue(T value, size_t indx);

		T *GetDataArray() { return m_data; }

		void SetMaxMinValues(T max, T min);
		virtual double GetDataMax();
		virtual double GetDataMin();

		virtual bool IsValid() override;
		void Validate();
	protected:
		T *m_data;

		T m_manual_max;
		T m_manual_min;

	};

	

#include <time.h>
	//#ifdef MAKINGDLL
	template DLLIMPEXP_PLOTLIB class DataTyped<int>;
	template DLLIMPEXP_PLOTLIB class DataTyped<time_t>;
	template DLLIMPEXP_PLOTLIB class DataTyped<double>;
	//#endif
}