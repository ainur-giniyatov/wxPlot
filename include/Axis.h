#pragma once
#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Area.h"
#include "Plot.h"
#include "Scale.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB Area;
	class DLLIMPEXP_PLOTLIB Scale;

	class DLLIMPEXP_PLOTLIB Axis
	{
	public:
		Axis(AXIS_DIR axis_dir);
		virtual ~Axis();


		//internal use methods
		AXIS_DIR _get_axis_dir() { return m_axis_dir; }
		const std::vector<DataNoType *> _get_adj_datas();
		void _setowner(Area *area) { m_owner = area; };
		Area *_getowner() { return m_owner; }

		void _setoffset(double offset) { m_offset = offset; };
		void _setrange(double range) { m_range = range; };
		double inline _getoffset() { return m_offset; }
		double inline _getrange() { return m_range; }
		void _setcommonscale(Scale *scale) { m_commonscale = scale; };
		Scale *_getcommonscale() { return m_commonscale; }
	protected:

		double m_offset;
		double m_range;

		AXIS_DIR m_axis_dir;
		Area *m_owner;
		Scale *m_commonscale;
	};

}