#pragma once
#include "plot_defs.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Line
	{
	public:
		Line();
		virtual ~Line();

		virtual void Render(void *, Point<int> &line_coord1, Point<int> &line_coord2) = 0;

		void SetColourIndex(int color_indx) { m_colour_indx = color_indx; };
		void SetThickness(int thickness) { m_thickness = thickness; };
		void SetVisible(bool vsbl) { m_visible = vsbl; };

		int GetColourIndex() { return m_colour_indx; };
		int GetThickness() { return m_thickness; };
		bool GetVisible() { return m_visible; };

		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &line_coord1, Point<int> &line_coord2) = 0;
		bool _isvisible() { return m_visible; };

	protected:
		int m_colour_indx;
		int m_thickness;
		bool m_visible;

	private:
	};
};