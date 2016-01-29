#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Area.h"
#include "Axis.h"
#include "ValueAdaptor.h"
#include "Marker.h"
#include "Line.h"

namespace plot
{
	template <typename T> class DLLIMPEXP_PLOTLIB DataTyped;
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB Axis;
	class SeriesSelection;
	template <typename T> class DLLIMPEXP_PLOTLIB AxisValueAdaptor;

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

		virtual bool _isspotted(Point<int> &mouse_coord, SeriesSelection & series_selection) = 0;
		void _setsize(int w, int h) { m_width = w; m_height = h; };
		void _setowner(Series *series);

	protected:
		Series *m_owner_series;

		int m_text_pos;
		bool m_visible;

		Marker *m_marker;
		Line *m_line;

		int m_width, m_height; //size of draw area, updated on plot resizing, adding items

	};

}