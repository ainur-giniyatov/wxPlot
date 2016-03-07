#pragma once
#include <wx/graphics.h>

#include "Line.h"

namespace plot
{
	class DLLIMPEXP_PLOTLIB wxLine : public Line
	{
	public:
		wxLine() ;
		virtual ~wxLine() {};

		void InitStyleAndColour(wxGraphicsContext *gc);

	protected:
	private:
	};

	class DLLIMPEXP_PLOTLIB wxSimpleLine : public wxLine
	{
	public:
		wxSimpleLine() {};
		wxSimpleLine(int color_indx, int thickness, bool vsbl = true);
		virtual ~wxSimpleLine() {};

		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &line_coord1, Point<int> &line_coord2) override;
		virtual void Render(void *, const Point<int> &line_coord1, const Point<int> &line_coord2) override;

	protected:
	private:
	};
};
