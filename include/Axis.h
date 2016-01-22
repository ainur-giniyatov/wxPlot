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
		Axis();
		virtual ~Axis();
		void AxisUpdated();

		void SetOwner(Area *area) { m_owner = area; };
		Area *GetOwner() { return m_owner; }

		void SetOffset(double offset);
		void SetRange(double range);
		double inline GetOffset() { return m_offset; }
		double inline GetRange() { return m_range; }

		void SetCommonScale(Scale *scale) { m_commonscale = scale; };
		Scale *GetCommonScale() { return m_commonscale; }
		//void PropagateToCommonScale();

		//internal use methods
		/*adjust visible range for the axis and redraw dependant plots*/
		void _SetVisibleRange(double offs, double range, bool update = true);
	protected:

		//friend Renderer;
		//friend Renderer2D;
		friend class Scale;
		double m_offset;
		double m_range;

		Area *m_owner;
		Scale *m_commonscale;
	};

}