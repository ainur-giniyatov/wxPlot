#pragma once

#include "plot_defs.h"
#include "Series.h"
#include "Data.h"
#include "Plot.h"
#include "Area.h"
#include "Axis.h"
#include "ValueAdaptor.h"

namespace plot
{
	template <typename T> class DLLIMPEXP_PLOTLIB DataTyped;
	class DLLIMPEXP_PLOTLIB DataNoType;
	class DLLIMPEXP_PLOTLIB Series;
	class DLLIMPEXP_PLOTLIB Plot;
	class DLLIMPEXP_PLOTLIB Axis;
	template <typename T> class DLLIMPEXP_PLOTLIB AxisValueAdaptor;

	class DLLIMPEXP_PLOTLIB Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		void SetOwner(Series *series);
		Series *GetOwner() { return m_owner_series; }

		virtual void Render(void *) = 0;
		virtual void PutMark(void *, int x, int y) = 0;
		virtual void PutLine(void *, int x, int y, int w, int h) = 0;
		void SetMarkerStyle(MARKER_STYLES marker_style);
		void SetMarkerSize(int marker_size);
		void SetMarkerColourIndex(int marker_colour_index);
		void SetLineStyle(LINE_STYLES line_style);
		void SetLineThickness(int line_thickness);
		void SetLineColourIndex(int line_colour_index);

	protected:
		Series *m_owner_series;

		int m_text_pos;

		MARKER_STYLES m_marker_style;
		int m_marker_size;
		size_t m_marker_color_index;

		LINE_STYLES m_line_style;
		int m_line_thickness;
		size_t m_line_color_index;

	};

}