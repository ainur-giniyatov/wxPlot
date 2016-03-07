#pragma once
#include <vector>

#include "plot_defs.h"
#include "Scale.h"
#include "SubPlot.h"

namespace plot
{
	
	class DLLIMPEXP_PLOTLIB Scale;
	class DLLIMPEXP_PLOTLIB Renderer;
	class DLLIMPEXP_PLOTLIB Subplot;

	class DLLIMPEXP_PLOTLIB Series
	{
	public:
		Series(size_t size, const char *series_name = NULL);
		virtual ~Series();

		void SetSeriesName(const char *series_name = NULL);
		const char *GetSeriesName() { return m_series_name; }

		void SetUserData(void *data) { m_user_data = data; }
		void *GetUserData() { return m_user_data; }

		bool IsValid();
		void Validate();

		void SetXScale(Scale *scale);
		void SetYScale(Scale *scale);

		void Fit(int axis_mask);

		void SetRenderer(Renderer *renderer);//previous renderer will be deleted
		Renderer *GetRenderer() { return m_renderer; };

		void BringToFront();

		auto GetXData() { return m_xdata; }
		auto GetYData() { return m_ydata; }
		auto GetDataSize() { return data_size; }

		//internal use methods
		void _setowner(Subplot *subplot) { m_owner = subplot; };
		Subplot *_getowner() { return m_owner; }
		Scale *_getxscale() { return m_xscale; }
		Scale *_getyscale() { return m_yscale; }
	protected:
		char *m_series_name;
		Subplot *m_owner;
		Renderer *m_renderer;

		void *m_user_data;
		Scale *m_xscale;
		Scale *m_yscale;
	private:

		double *m_xdata;
		double *m_ydata;
		size_t data_size;
	};

	class SeriesSelection
	{
	public:
		SeriesSelection(Series *series = nullptr, size_t b = 0, size_t e = 0) { m_series_selected = series; m_begin = b; m_end = e; };
		Series *GetSeries() { return m_series_selected; }
		size_t GetStartIndex() { return m_begin; }
		size_t GetEndIndex() { return m_end; }
		virtual ~SeriesSelection() {};
	protected:
	private:
		Series *m_series_selected;
		size_t m_begin;
		size_t m_end;
	};

}