#pragma once
#include <wx/graphics.h>
#include "../Marker.h"

namespace plot
{

	class DLLIMPEXP_PLOTLIB wxMarker : public Marker
	{
	public:
		wxMarker();
		virtual ~wxMarker();

		void InitStyleAndColour(wxGraphicsContext *gc);

	protected:
	private:

	};

	class DLLIMPEXP_PLOTLIB wxMarkerCircle : public wxMarker
	{
	public:
		wxMarkerCircle();
		wxMarkerCircle(int border_color_indx, int fill_color_indx, int size = 4, bool vsbl = true);
		virtual ~wxMarkerCircle();
		virtual void Render(void *, Point<int> &coord) override;
		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &marker_coord) override;
	protected:
	private:
	};

	class DLLIMPEXP_PLOTLIB wxMarkerSquare : public wxMarker
	{
	public:
		wxMarkerSquare();
		wxMarkerSquare(int border_color_indx, int fill_color_indx, int size = 4, bool vsbl = true);
		virtual ~wxMarkerSquare();
		virtual void Render(void *, Point<int> &coord) override;
		virtual bool _isspotted(Point<int> &mouse_coord, Point<int> &marker_coord) override;
	protected:
	private:
	};
}