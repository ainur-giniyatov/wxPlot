#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "SubPlot.h"
#include "ValueAdaptor.h"
#include "Marker.h"
#include "Line.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Subplot;
	class SeriesSelection;
	class DLLIMPEXP_PLOTLIB AxisValueAdaptor;

	class DLLIMPEXP_PLOTLIB Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		Series *GetOwner() { return m_owner_series; }

		virtual void Render(void *) = 0;

		void SetVisible(bool visible) { m_visible = visible; }
		bool GetVisible() { return m_visible; }

		void SetMarker(Marker *marker);
		Marker *GetMarker() { return m_marker; }
		void SetLine(Line *line);
		Line *GetLine() { return m_line; }

		virtual Series * _isspotted(Point<int> &mouse_coord, int *dotindex_first, int *dotindex_last) = 0;
	
		void _setowner(Series *series);

	protected:
		Series *m_owner_series;

		int m_text_pos;
		bool m_visible;

		Marker *m_marker;
		Line *m_line;


	};

}