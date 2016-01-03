#pragma once
#include <vector>

#include "plot_defs.h"
#include "Data.h"
#include "Area.h"
#include "Renderer.h"

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

		Area *GetOwner() { return m_owner; }

		void SeriesUpdated();

		void SetData(DataNoType *data, AXIS_DIR axis_dir);
		DataNoType *GetData(AXIS_DIR axis_dir);
		//virtual std::vector<DataNoType *> GetDatas() = 0;
		void RemoveData(DataNoType *data);
		void DeleteData(DataNoType *data);

		void Fit(bool update = true);

		void SetRenderer(Renderer *renderer);//previous renderer will be deleted
		Renderer *GetRenderer() { return m_renderer; };

	protected:
		char *m_series_name;
		Area *m_owner;
		Renderer *m_renderer;

		friend class Area;
		void SetOwner(Area *area) { m_owner = area; }

	private:
		int m_dim_num; //number of dimensions
		DataNoType **m_datas;
	};
}