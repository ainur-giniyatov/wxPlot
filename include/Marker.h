#pragma once
#include "plot_defs.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB Marker
	{
	public:
		Marker();
		virtual ~Marker();

		virtual void Render(void *, Point<int> &coord) = 0;

		void SetFillColourIndex(int color_indx) { m_fill_colour_indx = color_indx; };
		void SetBorderColourIndex(int color_indx) { m_border_colour_indx = color_indx; };
		void SetSize(int size) { m_size = size; };
		void SetVisible(bool vsbl) { m_visible = vsbl; };

		int GetFillColourIndex() { return m_fill_colour_indx; };
		int GetBorderColourIndex() { return m_border_colour_indx; };
		int GetSize() { return m_size; };
		bool GetVisible() { return m_visible; };

		//internal use functions
		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &marker_coord) = 0;
		bool _isvisible() { return m_visible; };

	protected:
		int m_fill_colour_indx;
		int m_border_colour_indx;
		int m_size;
		bool m_visible;

	private:
	};
}