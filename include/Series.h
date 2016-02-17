#pragma once
#include <vector>

#include "plot_defs.h"
#include "Data.h"
#include "Area.h"
#include "Renderer.h"
#include "pevent.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Area;
	class DLLIMPEXP_PLOTLIB Renderer;

	class DLLIMPEXP_PLOTLIB Series
	{
	public:
		Series(int dim_num, const char *series_name = NULL);
		virtual ~Series();

		void SetSeriesName(const char *series_name = NULL, bool update = true);
		const char *GetSeriesName() { return m_series_name; }

		void SetUserData(void *data) { m_user_data = data; }
		void *GetUserData() { return m_user_data; }

		Area *GetOwner() { return m_owner; }

		void SeriesUpdated();

		void SetData(DataNoType *data, AXIS_DIR axis_dir);
		DataNoType *GetData(AXIS_DIR axis_dir);

		void RemoveData(DataNoType *data);
		void DeleteData(DataNoType *data);

		void Fit(int axis_mask);

		void SetRenderer(Renderer *renderer);//previous renderer will be deleted
		Renderer *GetRenderer() { return m_renderer; };

		void BringToFront();


		void _setowner(Area *area);
	protected:
		char *m_series_name;
		Area *m_owner;
		Renderer *m_renderer;

		void *m_user_data;

	private:
		int m_dim_num; //number of dimensions
		DataNoType **m_datas;
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

	class DLLIMPEXP_PLOTLIB PEventSeriesNameChanged : public PEvent
	{
	public:
		PEventSeriesNameChanged();
		virtual ~PEventSeriesNameChanged() {};
		static int GetEventId() { return s_event_id; }
	protected:
	private:
		static const int s_event_id;
	};

}